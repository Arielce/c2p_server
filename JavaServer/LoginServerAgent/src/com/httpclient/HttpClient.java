package com.httpclient;

import java.io.PrintStream;
import java.net.InetSocketAddress;
import java.net.URI;
import java.net.URISyntaxException;
import java.nio.charset.Charset;
import java.util.concurrent.Executors;

import net.sf.json.JSONObject;

import org.jboss.netty.bootstrap.ClientBootstrap;
import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.channel.ChannelFuture;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.channel.ChannelPipeline;
import org.jboss.netty.channel.ChannelPipelineFactory;
import org.jboss.netty.channel.ChannelStateEvent;
import org.jboss.netty.channel.Channels;
import org.jboss.netty.channel.Channel;
import org.jboss.netty.channel.MessageEvent;
import org.jboss.netty.channel.SimpleChannelHandler;
import org.jboss.netty.channel.socket.nio.NioClientSocketChannelFactory;
import org.jboss.netty.handler.codec.http.DefaultHttpRequest;
import org.jboss.netty.handler.codec.http.HttpHeaders;
import org.jboss.netty.handler.codec.http.HttpMethod;
import org.jboss.netty.handler.codec.http.HttpRequest;
import org.jboss.netty.handler.codec.http.HttpRequestEncoder;
import org.jboss.netty.handler.codec.http.HttpResponse;
import org.jboss.netty.handler.codec.http.HttpResponseDecoder;
import org.jboss.netty.handler.codec.http.HttpResponseEncoder;
import org.jboss.netty.handler.codec.http.HttpVersion;

public class HttpClient {
	private ClientBootstrap bootstrap;
	private String strHost;
	private int nPort;
	private Channel channel;				// 连接到http服务器的channel
	
	public HttpClient(String _host, int _port) {
		strHost = _host;
		nPort = _port;
	}
	
	public void init() {
		 // Client服务启动器
        bootstrap = new ClientBootstrap(new NioClientSocketChannelFactory(Executors.newCachedThreadPool(), Executors.newCachedThreadPool()));
        
        // 设置一个处理服务端消息和各种消息事件的类(Handler)
        bootstrap.setPipelineFactory(new ClientPipelineFactory());
        bootstrap.connect(new InetSocketAddress(strHost, nPort));
	}
	
	public void query(String strQuery) {
		URI uri = null;
		try {
			uri = new URI("http://" + strHost + ":" + nPort);
		} catch (URISyntaxException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
        String host = uri.getHost() == null? "localhost" : uri.getHost();
        
        HttpRequest request = null;
        request = new DefaultHttpRequest(HttpVersion.HTTP_1_1, HttpMethod.GET, strQuery);				// 设置查询的命令和参数
        request.setHeader(HttpHeaders.Names.HOST, host);
        request.setHeader(HttpHeaders.Names.CONNECTION, HttpHeaders.Values.KEEP_ALIVE);
        
        channel.write(request);
	}
 
	private class ClientPipelineFactory implements ChannelPipelineFactory {
		public ChannelPipeline getPipeline() throws Exception {
			// Create a default pipeline implementation.
			ChannelPipeline pipeline = Channels.pipeline();
						
			//消息处理handler
			pipeline.addLast("encoder", new HttpRequestEncoder());
			pipeline.addLast("decode", new HttpResponseDecoder());
			pipeline.addLast("handler", new HttpResponseHandler());
			return pipeline;
		}
	}
	
    private class HttpResponseHandler extends SimpleChannelHandler {
        @Override
        public void channelConnected(ChannelHandlerContext ctx, ChannelStateEvent e) {
            System.out.println("connect to the host success.");
            channel = (Channel)ctx.getChannel();
        }
        
        public void messageReceived(ChannelHandlerContext ctx, MessageEvent e) throws Exception {
        	HttpResponse response = (HttpResponse)e.getMessage();
        	ChannelBuffer channelBuffer = response.getContent();
        	byte[] queryBuf = new byte[channelBuffer.readableBytes()];
        	channelBuffer.readBytes(queryBuf);
        	String strRet = new String(queryBuf, "UTF-8");
        	
        	JSONObject jsonObject = JSONObject.fromObject(strRet);
        	String strVerifyRet = jsonObject.getString("verify");
        	System.out.println(strVerifyRet);
        }
    }
}
