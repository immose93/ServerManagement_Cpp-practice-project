#pragma once
#include "AdminInfo.h"
#include "UserInfo.h"
#include "Server.h"
class AdminMode
{
private:
	AdminInfo &admininfo_; // ������ ��带 ����� ������ ����
public:
	AdminMode(AdminInfo &a) :admininfo_(a){}	// ������(������ ��带 ����� ������ ���� �ʱ�ȭ)
	int SelectMenu(Server &server);					// ������ ��� �޴�
	int UpdateAdminCode(Server &server);			// ������ �ڵ� ����
	void RegisteredUserInfo(Server &server);		// ������ ���� ����
	int AddCapacity(Server &server);					// �ϵ� �뷮 �߰�
	int WaitingUserInfo(Server &server);			// ������� ���� ����
	void FileUpload();		// ���� ���ε�
	void FileDelete();		// ���� ����
	void FileDownload();	// ���� �ٿ�ε�
};
