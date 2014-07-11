package com.login;

/**
 * µÇÂ½¹¦ÄÜ
 * @author Administrator
 *
 */
public interface ILoginChecker {
	public int Login(String strPtName, String strPasswd);
	public boolean ChangePwd(String strPtName, String strPasswd, String strNewPasswd);
	public boolean VerifyToken(String strPtName, String strToken);
}
