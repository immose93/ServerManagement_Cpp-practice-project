#pragma once
#include <string>
class UserInfo
{
public:
	std::string id;		// ID
	std::string pass;	// Password
	std::string rrn;		// 주민번호
	std::string level;	// 권한레벨
	bool dormant = false;	// 휴면계정 여부
	int login_fail_count = 0;	// 로그인 실패 횟수
	UserInfo(){}
	UserInfo(std::string i, std::string p, std::string r, std::string l):id(i),pass(p),rrn(r),level(l){}	// 생성자
	UserInfo(const UserInfo& u):id(u.id),pass(u.pass),rrn(u.rrn),level(u.level){}
};
