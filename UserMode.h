#pragma once
#include <iostream>
#include "UserInfo.h"
#include "Server.h"
using namespace std;
class UserMode
{
private:
	UserInfo & user_;	// 사용자 모드를 사용중인 사용자 정보
public:
	UserMode(UserInfo &user) :user_(user) {};	// 생성자(사용자 모드를 사용할 사용자 정보 초기화)
	int SelectMenu(Server &server);															// 사용자 모드 메뉴
	void FileUpload();		// 파일 업로드
	void FileDelete();		// 파일 삭제
	void FileDownload();	// 파일 다운로드
};

