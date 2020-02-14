#pragma once
#include <iostream>
#include "UserInfo.h"
#include "Server.h"
using namespace std;
class UserMode
{
private:
	UserInfo & user_;	// ����� ��带 ������� ����� ����
public:
	UserMode(UserInfo &user) :user_(user) {};	// ������(����� ��带 ����� ����� ���� �ʱ�ȭ)
	int SelectMenu(Server &server);															// ����� ��� �޴�
	void FileUpload();		// ���� ���ε�
	void FileDelete();		// ���� ����
	void FileDownload();	// ���� �ٿ�ε�
};

