package com.server;

import java.net.InetSocketAddress;
import java.sql.Connection;
import java.util.concurrent.Executors;

import org.jboss.netty.bootstrap.ServerBootstrap;
import org.jboss.netty.channel.ChannelPipeline;
import org.jboss.netty.channel.ChannelPipelineFactory;
import org.jboss.netty.channel.Channels;
import org.jboss.netty.channel.socket.nio.NioServerSocketChannelFactory;
import org.jboss.netty.handler.codec.http.HttpRequestDecoder;
import org.jboss.netty.handler.codec.http.HttpResponseEncoder;

import com.login.*;
import com.sql.MysqlConnection;
import com.sql.TableOperator;

/**
 * LoginServerSim主要是用来模拟登陆服务器的功能，在实际项目上线之后
 * @author Administrator
 *
 */
public class LoginServerSim {
	private ServerBootstrap bootstrap;
	private MysqlConnection connection;
	private LoginClientHandler clientHandler;
	private ILoginChecker loginChecker;
	
	public LoginServerSim() {
		connection = new MysqlConnection();
		clientHandler = new LoginClientHandler();
		
	}
	
	public static void main(String[] args) {
		LoginServerSim loginServer = new LoginServerSim();
		if (!loginServer.start()) {
			System.out.println("server start failed.");
			return;
		}
	}
	
	/**
	 * 开始监听服务
	 */
	private void listen(String strIp, int nPort) {
		bootstrap = new ServerBootstrap(new NioServerSocketChannelFactory(Executors.newCachedThreadPool(), Executors.newCachedThreadPool()));
		// 设置 pipeline factory.
		bootstrap.setPipelineFactory(new ServerPipelineFactory());
		// 绑定端口
		bootstrap.bind(new InetSocketAddress(nPort));
		System.out.println("admin start on "+ strIp + ":" + nPort);
		return;
	}
	
	public boolean start() {
		if (!connection.init("127.0.0.1", 3306, "game", "root", "root")) {
			return false;
		}
		loginChecker = new LoginCheckerImpl(new TableOperator(connection.getConnection()));
		
		System.out.println(connection);
		listen("127.0.0.1", 8080);
		return true;
	}
	
	private class ServerPipelineFactory implements ChannelPipelineFactory {
		public ChannelPipeline getPipeline() throws Exception {
			// Create a default pipeline implementation.
			ChannelPipeline pipeline = Channels.pipeline();
			pipeline.addLast("decoder", new HttpRequestDecoder());
			pipeline.addLast("encoder", new HttpResponseEncoder());
			
			//http处理handler
			System.out.println(connection);
			IRegister register = new RegisterImpl(new TableOperator(connection.getConnection()));
		
			clientHandler.SetRegister(register);
			clientHandler.SetLoginCheck(loginChecker);
			
			pipeline.addLast("handler", clientHandler);
			return pipeline;
		}
	}
}
