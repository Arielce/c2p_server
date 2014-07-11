package com.sql;

import java.sql.SQLException;

public class TestSqls {
	public static void main(String[] args) {
		MysqlConnection connection = new MysqlConnection();
		if (!connection.init("127.0.0.1", 3306, "game", "root", "root")) {
			return;
		}
		
		TableOperator tableOperator = new TableOperator(connection.getConnection());
		if (!tableOperator.Init()) {
			return;
		}
		
		try {
			tableOperator.IsPtExist("test");
			tableOperator.RegisterPt("test", "pass", null);
			String passwdString = tableOperator.QueryPasswd("test");
			System.out.print(passwdString);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
	}
}
