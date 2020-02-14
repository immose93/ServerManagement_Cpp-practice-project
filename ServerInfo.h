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
	UserMap *usermap_;					// 회원 목록
	UserMap *waiting_usermap_;		// 가입 신청 대기열
	AdminInfo *admininfo_;				// 관리자 정보
	int totalcapacity_;		// 서버 전체용량
	int usedcapacity_;		// 현재 사용용량
	int remaincapacity_;	// 사용가능 용량
	ServerInfo(int t);
	ServerInfo(int t, UserMap usermap, UserMap waitingusermap);
	~ServerInfo();
};
