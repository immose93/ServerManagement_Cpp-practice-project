#pragma once
#include <iostream>
#include <conio.h>
#include <map>
#include "ServerInfo.h"
#include  "Exception.h"
using namespace std;

class Server
{
private:
	ServerInfo *serverinfo_;			// 서버 정보
public:
	Server():serverinfo_(0){};	// default 생성자
	Server(int capacity) { serverinfo_ = new ServerInfo(capacity); }	// 생성자(하드용량 초기화)
	Server(int capacity, UserMap um, UserMap wum);	// 생성자(하드용량, 회원목록, 대기열 초기화)
	~Server();					// 소멸자
	int SelectMode();			// 서버 메인 화면(모드 선택)
	int UserModeLogin();	// 로그인 (사용자 모드)
	int AdminModeCode();	// 코드 입력 (관리자 모드)
	int SignUp();					// 회원가입
	void addCapacity(int size);

	// 멤버변수의 getter와 setter
	ServerInfo *get_serverinfo_() { return serverinfo_; }
	void set_server_(ServerInfo server) { *this->serverinfo_ = server; }
};

int CheckPassword(string& password, string& rrn);
bool IsNotAlphabetOrNumber(string password);			// 비밀번호가 알파벳 대소문자와 숫자로 되어있는지 검사
bool IsRRNInPassword(string password, string rrn);	// 주민번호가 포함된 비밀번호인지 검사
bool IsValidRRN(string rrn);		// 주민번호 유효성 검사