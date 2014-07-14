package com.server;

import java.net.InetSocketAddress;
import java.util.concurrent.Executors;

import org.jboss.netty.bootstrap.ServerBootstrap;
import org.jboss.netty.buffer.ChannelBuffer;
import org.jboss.netty.channel.Channel;
import org.jboss.netty.channel.ChannelHandlerContext;
import org.jboss.netty.channel.ChannelPipeline;
import org.jboss.netty.channel.ChannelPipelineFactory;
import org.jboss.netty.channel.Channels;
import org.jboss.netty.channel.socket.nio.NioServerSocketChannelFactory;
import org.jboss.netty.handler.codec.frame.FrameDecoder;

import com.message.*;
import com.httpclient.*;

public class LoginServerAgent {
	private ServerBootstrap bootstrap;
	private GameServerHandler gameServerHandler;
	private HttpClient httpClient;
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
		LoginServerAgent loginServerAgent = new LoginServerAgent();
		if (!loginServerAgent.start()) {
			System.out.println("server start failed!!");
			return;
		}
	}

	public boolean start() {
		httpClient = new HttpClient("127.0.0.1", 8080);
		httpClient.init();
		
		gameServerHandler = new GameServerHandler(httpClient);
	
		listen("127.0.0.1", 9100);
		return true;
	}
	
	private void listen(String strIp, int nPort) {
		bootstrap = new ServerBootstrap(new NioServerSocketChannelFactory(Executors.newCachedThreadPool(), Executors.newCachedThreadPool()));
		// 设置 pipeline factory.
		bootstrap.setPipelineFactory(new ServerPipelineFactory());
		// 绑定端口
		bootstrap.bind(new InetSocketAddress(nPort));
		System.out.println("admin start on "+ strIp + ":" + nPort);
		return;
	}
	
	private class ServerPipelineFactory implements ChannelPipelineFactory {
		public ChannelPipeline getPipeline() throws Exception {
			// Create a default pipeline implementation.
			ChannelPipeline pipeline = Channels.pipeline();
						
			//消息处理handler
			pipeline.addLast("decode", new GsMssageDecode());
			pipeline.addLast("handler", gameServerHandler);
			return pipeline;
		}
	}
	
	private class GsMssageDecode extends FrameDecoder {
		final private int nMessageHeader = 12;
		@Override
		protected Object decode(ChannelHandlerContext ctx, Channel channel,
				ChannelBuffer buffer) throws Exception {
			if (buffer.readableBytes() < nMessageHeader) {
				return null;
			}
			
			byte[] sizeBytes = new byte[4];
			buffer.getBytes(0, sizeBytes, 0, 4);
			int nMessageSize = MessageUtil.bytes2int(sizeBytes);
			if (buffer.readableBytes() < nMessageSize) {
				return null;
			}
			
			return buffer.readBytes(nMessageSize);
		}
		
	}
}
