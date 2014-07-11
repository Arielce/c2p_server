package com.login;

import java.sql.SQLException;

import com.sql.*;

public class RegisterImpl implements IRegister {
	private TableOperator tableOperator;
	
	public RegisterImpl(TableOperator _tableOperator) {
		tableOperator = _tableOperator;
	}
	
	@Override
	public boolean IsUserExist(String strName) {
		boolean bRet = true;
		try {
			bRet = tableOperator.IsPtExist(strName);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return bRet;
	}

	@Override
	public boolean Register(String strPtName, String strPasswd) {
		boolean bRet = true;
		try {
			bRet = tableOperator.RegisterPt(strPtName, strPasswd, null);
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		return bRet;
	}

}
