package com.server;

import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.channel.ChannelStateEvent;
import org.jboss.netty.channel.MessageEvent;
import org.jboss.netty.channel.SimpleChannelHandler;

import com.httpclient.HttpClient;

import lobby.*;
import com.httpclient.*;

public class GameServerHandler extends SimpleChannelHandler{
	private HttpClient httpClient;
	public GameServerHandler(HttpClient _httpClient) {
		httpClient = _httpClient;
	}
	
    @Override
    public void channelConnected(ChannelHandlerContext ctx, ChannelStateEvent e) {
        System.out.println("gameserver connect.");
    }
    
    @Override
    public void messageReceived(ChannelHandlerContext ctx, MessageEvent e) throws Exception {
    	System.out.println("message received");
    	ChannelBuffer messageBuf = (ChannelBuffer)e.getMessage();
    	byte[] bytes = messageBuf.array();
    	byte[] protoBytes = new byte[bytes.length - 12];
    	messageBuf.getBytes(12, protoBytes);				// 去除包头部分，获取包体部分的bytes
    	
    	LobbyProtocol.RequestRegGameServer gameServerReq = LobbyProtocol.RequestRegGameServer.parseFrom(protoBytes);
    	System.out.println("gameserver id=" + gameServerReq.getGsId());
    	
    	httpClient.query("/verify?ptname=test&token=487128819");
    	
    	return;
    }
}
