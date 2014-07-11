package com.sql;

import java.sql.*;
public class MysqlConnection {
	private Connection conn;
	private String strMysqlIp;
	private int nMysqlPort;
	private String strDatabase;
	private String strUser;
	private String strPasswd;
	
	public boolean init(String mysqlIp, int mysqlPort, String database, String user, String passwd) {
		strMysqlIp = mysqlIp;
		nMysqlPort = mysqlPort;
		strDatabase = database;
		strUser = user;
		strPasswd = passwd;
		
		try{
			//����Class.forName()����������������
			Class.forName("com.mysql.jdbc.Driver");
	        System.out.println("�ɹ�����MySQL������");
	    }catch(ClassNotFoundException e1){
	    	System.out.println("�Ҳ���MySQL����!");
	    	e1.printStackTrace();
	        return false;
	    }
		
		String strUrl = "jdbc:mysql://" + strMysqlIp + ":" + nMysqlPort + "/" + strDatabase;
		try {
			conn = DriverManager.getConnection(strUrl, strUser, strPasswd);
            System.out.print("�ɹ����ӵ����ݿ⣡");
        } catch (SQLException e){
            e.printStackTrace();
            return false;
        }
		
		return true;
	}
	
	public Statement createStatement() throws SQLException {
		return conn.createStatement();
	}
	
	public Connection getConnection() {
		return conn;
	}
}