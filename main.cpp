#include <iostream>
#include <string>
#include "Server.h"
#include "UserInfo.h"
using namespace std;
int main() {
	UserMap initusermap;	// �ʱ� ȸ�� ���
	initusermap["user1"] = { "user1", "useruser", "901010-1010101", "R" };
	initusermap["user2"] = { "user2", "useruser", "990909-2010101", "W" };
	initusermap["user3"] = { "user3", "useruser", "000101-1234567", "RW" };
	UserMap initwaitingusermap;	// �ʱ� ���� ��û ��⿭
	initwaitingusermap["waiting1"] = { "waiting1", "useruser", "880808-1231231", "RW" };
	initwaitingusermap["waiting2"] = { "waiting2", "useruser", "880808-2231231", "RW" };
	Server server(1000, initusermap, initwaitingusermap);		// �ϵ� �뷮 1000 ¥�� ���� ����
	server.SelectMode();	// ���� ����
	return 0;
}
