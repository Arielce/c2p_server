package com.sql;
import java.sql.*;

public class TableOperator {
	private Connection conn;
	public TableOperator(Connection _conn) {
		conn = _conn;
	}
	
	public boolean Init() {
		if (!CreateTables()) {
			return false;
		}
		return true;
	}
	
	// ’À∫≈ «∑Ò¥Ê‘⁄
	public boolean IsPtExist(String strPtName) throws SQLException {
		String strQuerySqlString = "select *from ptinfo where ptname='" + strPtName + "'";
		PreparedStatement statement = null;
		
		try {
			statement = conn.prepareStatement(strQuerySqlString);
			ResultSet rSet = statement.executeQuery();
			System.out.println(strQuerySqlString);
			
			// ”–º«¬º
			if (rSet.next()) {
				return true;
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
		finally {
			if (statement != null)
				statement.close();
		}
		
		return false;
	}
	
	// ◊¢≤·’À∫≈
	public boolean RegisterPt(String strPtName, String strPasswd, String strEmail) throws SQLException {
		if (IsPtExist(strPtName)) {
			System.out.println("ptname=" + strPtName + " is already exist");
			return false;
		}
		String strRegSqlString = "insert into ptinfo(ptname, passwd, email) values('" + strPtName + "', '" + strPasswd + "', '" + strEmail + "')";
		PreparedStatement statement = null;
		
		try {
			statement = conn.prepareStatement(strRegSqlString);
			boolean bRet = statement.execute();
			System.out.println(strRegSqlString);
			
			if (bRet) {				// bRet should be false where execute insert sql
				System.out.println("Unknown error");
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
		finally {
			if (statement != null)
				statement.close();
		}
		
		return true;
	}
	
	// ªÒ»°’À∫≈√‹¬Î
	public String QueryPasswd(String strPtName) throws SQLException {
		String strQuery = "select passwd from ptinfo where ptname='" + strPtName + "'";
		Statement statement = null;
		
		try {
			statement = conn.createStatement();
			ResultSet rSet = statement.executeQuery(strQuery);
			System.out.println(strQuery);
			
			if (rSet.next()) {
				return rSet.getString(1);
			}
			
		} catch (SQLException e) {
			e.printStackTrace();
		}
		finally {
			if (statement != null)
				statement.close();
		}
		
		return "";
	}
	
	private boolean CreateTables() {
		try {
			if (!CreatePtInfo()) {
				return false;
			}
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return true;
	}
	
	private boolean CreatePtInfo() throws SQLException {
		StringBuilder sb = new StringBuilder();
		sb.append("CREATE TABLE IF NOT EXISTS ptinfo(");
		sb.append(" id			int(16)		NOT NULL primary key auto_increment,");
		sb.append("ptname		varchar(24) NOT NULL default '', ");
		sb.append("passwd		varchar(23) NOT NULL default '', ");
		sb.append("email		varchar(48) NOT NULL default '', ");
		sb.append("INDEX ptname_index (ptname)");
		sb.append(")");
				
		Statement statement = null;
		boolean bRet = true;
		try {
			statement = conn.createStatement();
			statement.execute(sb.toString());
			System.out.println(sb.toString());
			
		} catch (SQLException e) {
			e.printStackTrace();
			bRet = false;
		}
		finally {
			if (statement != null)
				statement.close();
		}
		return bRet;
	}
}
