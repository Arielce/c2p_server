package com.login;

/**
 * @author Administrator
 * ע����Ҫʹ�õĽӿ�
 */
public interface IRegister {
	/**
	 * �ж��û��Ƿ��Ѿ��洢
	 * @param strName
	 * @return
	 */
	public boolean IsUserExist(String strName);
	public boolean Register(String strPtName, String strPasswd);
}
