package com.login;

import java.sql.SQLException;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import com.sql.TableOperator;

public class LoginCheckerImpl implements ILoginChecker {
	private TableOperator tableOperator;
	private Map<String, Integer> userTokenMap;
	
	public LoginCheckerImpl(TableOperator _tableOperator) {
		tableOperator = _tableOperator;
		userTokenMap = new HashMap<String, Integer>();
	}
	@Override
	public int Login(String strPtName, String strPasswd) {
		try {
			String strDBPasswd = tableOperator.QueryPasswd(strPtName);
			if (strDBPasswd.equals(strPasswd)) {			// 判断密码是否一致
				int nToken = genToken();
				userTokenMap.put(strPtName, nToken);
				return nToken;
			}
		} catch (SQLException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		return -1;
	}

	@Override
	public boolean ChangePwd(String strPtName, String strPasswd,
			String strNewPasswd) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean VerifyToken(String strPtName, String strToken) {
		Integer token = userTokenMap.get(strPtName);
		String strVerifyToken = Integer.toString(token);
		if (strToken.equals(strVerifyToken)) {
			return true;
		}
		return false;
	}
	
	// 生成token
	private int genToken() {
		Random random = new Random();
		int rand = random.nextInt();
		return rand;
	}
}
