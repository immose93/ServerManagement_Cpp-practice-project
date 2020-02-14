#pragma once
#include <string>
class UserInfo
{
public:
	std::string id;		// ID
	std::string pass;	// Password
	std::string rrn;		// �ֹι�ȣ
	std::string level;	// ���ѷ���
	bool dormant = false;	// �޸���� ����
	int login_fail_count = 0;	// �α��� ���� Ƚ��
	UserInfo(){}
	UserInfo(std::string i, std::string p, std::string r, std::string l):id(i),pass(p),rrn(r),level(l){}	// ������
	UserInfo(const UserInfo& u):id(u.id),pass(u.pass),rrn(u.rrn),level(u.level){}
};
