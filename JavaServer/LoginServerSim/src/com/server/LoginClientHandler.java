package com.server;

import static org.jboss.netty.handler.codec.http.HttpResponseStatus.BAD_REQUEST;
import static org.jboss.netty.handler.codec.http.HttpResponseStatus.INTERNAL_SERVER_ERROR;
import static org.jboss.netty.handler.codec.http.HttpResponseStatus.OK;
import static org.jboss.netty.handler.codec.http.HttpVersion.HTTP_1_1;

import java.io.ByteArrayInputStream;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.LinkedHashMap;
import java.util.Map;

import net.sf.json.JSONObject;

import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.buffer.DynamicChannelBuffer;
import org.jboss.netty.channel.Channel;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.channel.ExceptionEvent;
import org.jboss.netty.channel.MessageEvent;
import org.jboss.netty.channel.SimpleChannelUpstreamHandler;
import org.jboss.netty.handler.codec.frame.TooLongFrameException;
import org.jboss.netty.handler.codec.http.DefaultHttpResponse;
import org.jboss.netty.handler.codec.http.HttpRequest;
import org.jboss.netty.handler.codec.http.HttpResponse;
import org.omg.CORBA.portable.InputStream;
import org.eclipse.jetty.util.MultiMap;
import org.eclipse.jetty.util.UrlEncoded;

import net.sf.json.*;
import net.sf.json.util.*;
import net.sf.json.filters.*;
import net.sf.json.xml.*;

import com.login.*;
import com.sql.TableOperator;

public class LoginClientHandler extends SimpleChannelUpstreamHandler{
	private IRegister register;
	private ILoginChecker loginChecker;
	
	void SetRegister(IRegister _register) {
		register = _register;
	}
	void SetLoginCheck(ILoginChecker _loginChecker) {
		loginChecker = _loginChecker;
	}
	
	@Override
	public void messageReceived(ChannelHandlerContext ctx, MessageEvent e)
			throws Exception {
		HttpRequest request = (HttpRequest)e.getMessage();
		String uri = request.getUri();
        System.out.println("uri:" + uri);
        
        int nIndex1 = uri.indexOf('/');
        int nIndex2 = uri.indexOf('?');
        if (nIndex1 == -1 || nIndex2 == -1) {
			System.out.println("uri pattern error!!");
			return;
		}
        String strCmd = uri.substring(nIndex1 + 1, nIndex2);
        System.out.println(strCmd);
        System.out.println(uri.substring(nIndex2 + 1));
        
        MultiMap<String> values = new MultiMap<String>();
        ByteArrayInputStream stream = new ByteArrayInputStream(uri.substring(nIndex2 + 1).getBytes()); 
        
        UrlEncoded.decodeTo(stream, values, "UTF-8", 1000);
        System.out.println(values);
        System.out.println(values.size());
        
        String strRet = null;
        if (strCmd.equals("querypt")) {
        	strRet = procQueryPt(values);
		}
        else if (strCmd.equals("register")) {
        	strRet = procRegister(values);
		}
        else if (strCmd.equals("login")) {
        	strRet = procLogin(values);
		}
        else if (strCmd.equals("verify")) {
        	strRet = procVerify(values);
		}
        
		HttpResponse response = new DefaultHttpResponse(HTTP_1_1, OK);
        ChannelBuffer buffer = new DynamicChannelBuffer(2048);
		
        // 设置返回结果
        buffer.writeBytes(strRet.getBytes("UTF-8"));
		
		response.setContent(buffer);
		response.setHeader("Content-Type", "text/html; charset=UTF-8");
		response.setHeader("Content-Length", response.getContent().writerIndex());
		Channel ch = e.getChannel();
		// Write the initial line and the header.
		ch.write(response);
		//ch.disconnect();
		//ch.close();
	}

	@Override
	public void exceptionCaught(ChannelHandlerContext ctx, ExceptionEvent e)
			throws Exception {
		Channel ch = e.getChannel();
		Throwable cause = e.getCause();
		if (cause instanceof TooLongFrameException) {
			//sendError(ctx, BAD_REQUEST);
			return;
		}

		cause.printStackTrace();
		if (ch.isConnected()) {
			//sendError(ctx, INTERNAL_SERVER_ERROR);
		}
	}
	
	private String procQueryPt(MultiMap<String> paramsMap) {
		String strPtName = paramsMap.getString("ptname");
		System.out.println(strPtName);
		boolean bRet = register.IsUserExist(strPtName);
		
		String strRetString = "";	
		Map<String, String> map = new LinkedHashMap<String, String>();  
		
		if (bRet) {			// 用户已经存在
			map.put("isexist", "1");
		}
		else {
			map.put("isexist", "0");
		}
		JSONObject jsonObject = JSONObject.fromObject(map);
		
		strRetString = jsonObject.toString();
		return strRetString;
	}
	
	private String procRegister(MultiMap<String> paramsMap) {
		String strPtName = paramsMap.getString("ptname");
		String strPasswd = paramsMap.getString("password");
		boolean bRet = register.Register(strPtName, strPasswd);
		
		String strRetString = "";	
		Map<String, String> map = new LinkedHashMap<String, String>();  
		
		if (bRet) {			// 用户已经存在
			map.put("register", "success");
		}
		else {
			map.put("register", "failed");
		}
		JSONObject jsonObject = JSONObject.fromObject(map);
	
		strRetString = jsonObject.toString();
		return strRetString;
	}
	
	private String procLogin(MultiMap<String> paramsMap) {
		String strPtName = paramsMap.getString("ptname");
		String strPasswd = paramsMap.getString("password");
		int nToken = loginChecker.Login(strPtName, strPasswd);
		
		String strRetString = "";
		String strToken = Integer.toString(nToken);
		Map<String, String> map = new LinkedHashMap<String, String>();  
		
		if (nToken == -1) {			// 用户已经存在
			//jsonObject.put("token", "-1");
			map.put("token", "-1");
		}
		else {
			//jsonObject.put("token", strToken);
			map.put("token", strToken);
		}
		JSONObject jsonObject = JSONObject.fromObject(map);
		
		strRetString = jsonObject.toString();
		return strRetString;
	}
	
	private String procVerify(MultiMap<String> paramsMap) {
		String strPtName = paramsMap.getString("ptname");
		String strToken = paramsMap.getString("token");
		boolean bRet = loginChecker.VerifyToken(strPtName, strToken);
		
		String strRetString = "";	
		Map<String, String> map = new LinkedHashMap<String, String>();  
		map.put("user", strPtName);
		
		if (bRet) {			// 用户已经存在
			map.put("verify", "success");
		}
		else {
			map.put("verify", "failed");
		}
		JSONObject jsonObject = JSONObject.fromObject(map);
		
		strRetString = jsonObject.toString();
		return strRetString;
	}
}
