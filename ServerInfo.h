#pragma once
#include "AdminInfo.h"
#include "UserInfo.h"
#include <map>
using std::map;
using std::string;
typedef map<string, UserInfo> UserMap;

class ServerInfo
{
public:
	UserMap *usermap_;					// ȸ�� ���
	UserMap *waiting_usermap_;		// ���� ��û ��⿭
	AdminInfo *admininfo_;				// ������ ����
	int totalcapacity_;		// ���� ��ü�뷮
	int usedcapacity_;		// ���� ���뷮
	int remaincapacity_;	// ��밡�� �뷮
	ServerInfo(int t);
	ServerInfo(int t, UserMap usermap, UserMap waitingusermap);
	~ServerInfo();
};
