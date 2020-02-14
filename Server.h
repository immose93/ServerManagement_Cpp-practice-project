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
	ServerInfo *serverinfo_;			// ���� ����
public:
	Server():serverinfo_(0){};	// default ������
	Server(int capacity) { serverinfo_ = new ServerInfo(capacity); }	// ������(�ϵ�뷮 �ʱ�ȭ)
	Server(int capacity, UserMap um, UserMap wum);	// ������(�ϵ�뷮, ȸ�����, ��⿭ �ʱ�ȭ)
	~Server();					// �Ҹ���
	int SelectMode();			// ���� ���� ȭ��(��� ����)
	int UserModeLogin();	// �α��� (����� ���)
	int AdminModeCode();	// �ڵ� �Է� (������ ���)
	int SignUp();					// ȸ������
	void addCapacity(int size);

	// ��������� getter�� setter
	ServerInfo *get_serverinfo_() { return serverinfo_; }
	void set_server_(ServerInfo server) { *this->serverinfo_ = server; }
};

int CheckPassword(string& password, string& rrn);
bool IsNotAlphabetOrNumber(string password);			// ��й�ȣ�� ���ĺ� ��ҹ��ڿ� ���ڷ� �Ǿ��ִ��� �˻�
bool IsRRNInPassword(string password, string rrn);	// �ֹι�ȣ�� ���Ե� ��й�ȣ���� �˻�
bool IsValidRRN(string rrn);		// �ֹι�ȣ ��ȿ�� �˻�