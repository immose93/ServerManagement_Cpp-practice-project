#include <iostream>
#include <string>
#include "Server.h"
#include "UserInfo.h"
using namespace std;
int main() {
	UserMap initusermap;	// 초기 회원 목록
	initusermap["user1"] = { "user1", "useruser", "901010-1010101", "R" };
	initusermap["user2"] = { "user2", "useruser", "990909-2010101", "W" };
	initusermap["user3"] = { "user3", "useruser", "000101-1234567", "RW" };
	UserMap initwaitingusermap;	// 초기 가입 요청 대기열
	initwaitingusermap["waiting1"] = { "waiting1", "useruser", "880808-1231231", "RW" };
	initwaitingusermap["waiting2"] = { "waiting2", "useruser", "880808-2231231", "RW" };
	Server server(1000, initusermap, initwaitingusermap);		// 하드 용량 1000 짜리 서버 생성
	server.SelectMode();	// 서버 실행
	return 0;
}
