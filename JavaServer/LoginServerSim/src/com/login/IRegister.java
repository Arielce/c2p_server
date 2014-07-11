package com.login;

/**
 * @author Administrator
 * 注册需要使用的接口
 */
public interface IRegister {
	/**
	 * 判断用户是否已经存储
	 * @param strName
	 * @return
	 */
	public boolean IsUserExist(String strName);
	public boolean Register(String strPtName, String strPasswd);
}
