#ifndef GAMESERVER_KEYGEN_H
#define GAMESERVER_KEYGEN_H

#include "header.h"

#define ROLEDATA "#roledata"
class KeyGen
{
public:
	static string GenRoleDataKey(const string& strPtName)
	{
		return strPtName + ROLEDATA;
	}
};

#endif