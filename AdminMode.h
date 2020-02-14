#pragma once
#include "AdminInfo.h"
#include "UserInfo.h"
#include "Server.h"
class AdminMode
{
private:
	AdminInfo &admininfo_; // 관리자 모드를 사용할 관리자 정보
public:
	AdminMode(AdminInfo &a) :admininfo_(a){}	// 생성자(관리자 모드를 사용할 관리자 정보 초기화)
	int SelectMenu(Server &server);					// 관리자 모드 메뉴
	int UpdateAdminCode(Server &server);			// 관리자 코드 변경
	void RegisteredUserInfo(Server &server);		// 가입한 유저 정보
	int AddCapacity(Server &server);					// 하드 용량 추가
	int WaitingUserInfo(Server &server);			// 대기중인 유저 정보
	void FileUpload();		// 파일 업로드
	void FileDelete();		// 파일 삭제
	void FileDownload();	// 파일 다운로드
};
