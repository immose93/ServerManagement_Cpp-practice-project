#include "Server.h"
#include "Util.h"
#include "UserMode.h"
#include "AdminMode.h"
#include "UserInfo.h"
#include <regex>

Server::Server(int capacity, UserMap um, UserMap wum)
{
	serverinfo_ = new ServerInfo(capacity, um, wum);
}

Server::~Server()
{
	serverinfo_->~ServerInfo();
}

int Server::SelectMode()
{
	int ch;
	while (1) {
		Util::Clrscr();
		cout << "\n--------[���� �޴�]--------" << endl;
		cout << "1. ����� ���" << endl;
		cout << "2. ������ ���" << endl;
		cout << "3. ȸ�� ���Կ�û" << endl;
		cout << "---------------------------" << endl;
		try {
			ch = _getch();
			if (ch == '1') UserModeLogin();
			else if (ch == '2') AdminModeCode();
			else if (ch == '3') SignUp();
			else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc);
			else throw Exception::get_exceptiontype_(Exception::kInvalidMenuInput);
		}
		catch (string e) {
			if (e == "ESC") return -1;
			cout << e << endl;
			Util::Delay(1000);
		}
	}
	return 0;
}

int Server::UserModeLogin()
{
	string id, password, level;
	UserMap::iterator iter;
	while (1) {
		Util::Clrscr();
		cout << "-----[���� ��� �α���]-----" << endl;
		try {
			Util::GetInputString("ID : ", id, -1);
			Util::GetInputString("Password : ", password, 0); // ��й�ȣ�� *ǥ�� ���
			Util::GetInputString("���� ���� : ", level, -1);
			// ���� üũ
			iter = serverinfo_->usermap_->find(id);
			if (iter == serverinfo_->usermap_->end()) // �������� �ʴ� ID
				throw Exception::get_exceptiontype_(Exception::kNotExistsInUserMap);
			else if (iter->second.dormant)					// �޸������ ��� ����� ��� ���� X
				throw Exception::get_exceptiontype_(Exception::kDormant);
			else if (iter->second.pass != password)		// ��й�ȣ�� Ʋ�� ���
				throw Exception::get_exceptiontype_(Exception::kWrongPassword);
			else if (iter->second.level != level)			// ���� ������ Ʋ�� ���
				throw Exception::get_exceptiontype_(Exception::kWrongLevel);
			else {
				iter->second.login_fail_count = 0;		// ���� ���� �ʱ�ȭ
				UserMode usermode(iter->second);	// ����� ��忡 �� ����� ������ ���� ����ڸ�� ��ü ����
				cout << "�α��� ����!" << endl;	// �α��� ���� ���� ���
				Util::Delay(1000);
				usermode.SelectMenu(*this);		// ����� ��� ����
				break;	// ����� ��� ����
			}
		}
		catch (string e) {
			if (e == "ESC") return -1;
			else if (e== "��й�ȣ�� Ʋ�Ƚ��ϴ�." || e == "���� ������ Ʋ�Ƚ��ϴ�.")
				iter->second.login_fail_count++;			// ī��Ʈ ����
			cout << e << endl;
			Util::Delay(1500);
		}
		try {
			if (iter != serverinfo_->usermap_->end() && iter->second.login_fail_count >= 5)		// 5ȸ �̻� ���н�
				throw Exception::get_exceptiontype_(Exception::kFailedFiveTimes);
		}
		catch (string e) {
			iter->second.dormant = true;	// �޸���� ó��
			iter->second.login_fail_count = 0;	// ���� ���� �ʱ�ȭ
			cout << id << e << endl;
			Util::Delay(2000);
			return 1; // ����� ��� ���� X	 (�޸���� ���� 1)
		}
	}
	return 0;
}

int Server::AdminModeCode()
{
	Util::Clrscr();
	cout << "--------[������ ��� �ڵ� �Է�]--------" << endl;
	string code;
	try {
		Util::GetInputString("Code : ", code, 0);
		if (serverinfo_->admininfo_->code != code) throw Exception::get_exceptiontype_(Exception::kInvalidAdminCode);
		AdminMode adminmode(*serverinfo_->admininfo_);
		adminmode.SelectMenu(*this);
	}
	catch (string e) {
		if (e == "ESC") return -1;
		Util::Clrscr();
		cout << e << endl;
		Util::Delay(2000);
	}
	return 0;	// ������ ��� ����
}

int Server::SignUp()
{
	Util::Clrscr();
	cout << "---------[ȸ������]---------" << endl;	
	string id;
	while (1) {
		try {
			Util::GetInputString("ID : ", id, -1);
			if (serverinfo_->usermap_->find(id) != serverinfo_->usermap_->end())	// �̹� �����ϴ� ȸ�� ID�� ���
				throw Exception::get_exceptiontype_(Exception::kExistsInUsermap);
			else if (serverinfo_->waiting_usermap_->find(id) != serverinfo_->waiting_usermap_->end())	// ȸ������ ��⿭�� �����ϴ� ID�� ���
				throw Exception::get_exceptiontype_(Exception::kExistInWaitingUsermap);
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ESC Ű�� ������ ���� �޴��� ����
			cout << e << endl;
			continue;
		}
		break;
	}

	// �ֹι�ȣ �Է�
	string rrn;
	while (1) {
		rrn.clear();
		try {
			Util::GetInputString("�ֹι�ȣ(������ '-' �����Ͽ� �Է�) : ", rrn, 7);	// �ֹι�ȣ ���ڸ��� *ǥ�� ���
			// �ֹι�ȣ ��ȿ�� �˻�
			if (!IsValidRRN(rrn))		// ��ȿ���� ���� �ֹι�ȣ�� ���
				throw Exception::get_exceptiontype_(Exception::kInvalidRRN);
			else break;	// ��ȿ�� �ֹι�ȣ�� ���
		}
		catch (string e) {
			if (e == "ESC") return -1; // ESC Ű�� ������ ���� �޴��� ����
			cout << e << endl;
		}		
	}

	// ���ѷ��� �Է�
	string level;
	while (1) {
		try {
			Util::GetInputString("���ѷ���(�б�=R, ����=W, �б�/����=RW) : ", level, -1);
			// ���ѷ��� ��ȿ�� �˻�
			if (level != "R" && level != "W" && level != "RW") // ��ȿ���� ���� ���ѷ����� ���
				throw Exception::get_exceptiontype_(Exception::kInvalidLevel);
			else break;
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ESC Ű�� ������ ���� �޴��� ����
			cout << e << endl;
		}
	}

	// ��� �Է�
	string password;
	while (1) {
		try {
			Util::GetInputString("Password : ", password, 0);	// ��й�ȣ�� *ǥ�� ���
			// ��й�ȣ ��ȿ�� �˻�
			CheckPassword(password,rrn);	// �������� ��� 0 ����
			break;
		}
		catch (string e) {
			cout << e << endl;
			continue;
		}
	}
	Util::Clrscr();
	// ȸ������ ��⿭�� �߰�
	UserInfo waitinguser(id, password, rrn, level);
	serverinfo_->waiting_usermap_->insert({ id, waitinguser });
	cout << "---------------------------" << endl;
	cout << "ID : " << waitinguser.id << endl;
	cout << "PW : " << waitinguser.pass << endl;
	cout << "RRN : " << waitinguser.rrn << endl;
	cout << "Level : " << waitinguser.level << endl;
	cout << "���� ��û�� �����Ǿ����ϴ�." << endl;
	cout << "---------------------------" << endl;
	system("pause");
	return 0;
}

void Server::addCapacity(int size)
{
	serverinfo_->totalcapacity_ += size;
	serverinfo_->remaincapacity_ += size;
}

int CheckPassword(string& password, string& rrn)
{
	if (password.length() < 8)	// ����� ���̰� 8���� ���� ���
		throw Exception::get_exceptiontype_(Exception::kShortPassword);
	else if (IsNotAlphabetOrNumber(password))	// ��й�ȣ�� ���ĺ� ��ҹ��ڳ� ���ڷ� �������� ���� ���
		throw Exception::get_exceptiontype_(Exception::kIsNotAlphabetOrNumber);
	else if (IsRRNInPassword(password, rrn))		// ��й�ȣ�� ������� �ֹι�ȣ�� ���Ե� ���
		throw Exception::get_exceptiontype_(Exception::kRRNInPassword);
	return 0;
}

bool IsNotAlphabetOrNumber(string password) {
	for (size_t i = 0; i < password.length(); i++) {
		if (password[i] >= '0' && password[i] <= '9') continue;
		else if (password[i] >= 'A' && password[i] <= 'Z') continue;
		else if (password[i] >= 'a' && password[i] <= 'z') continue;
		else return true;
	}
	return false;
}

bool IsRRNInPassword(string password, string rrn) {
	string str;
	size_t pos;
	for (size_t i = 0; i < 13; i++) {	// index
		for (size_t j = 2; j <= 14; j++) {		// ���� ��
			if (i + j > 14) break;
			str = rrn.substr(i, j);	// �ֹι�ȣ i��° �ڸ����� j���� ���ڰ� ���Ե� ���
			pos = password.find(str);
			if (pos > 0 && pos < password.length()) 	return true;	// �ֹι�ȣ �Ϻΰ� ����
		}
	}
	return false;
}

bool IsValidRRN(string rrn) {
	// �ֹι�ȣ ���� �˻�
	regex reg("^(?:[0-9]{2}(?:0[1-9]|1[0-2])(?:0[1-9]|[1,2][0-9]|3[0,1]))-[1-4][0-9]{6}$");	// �ֹι�ȣ ���Խ�
	if (!regex_match(rrn, reg)) return false; // �ֹι�ȣ ���˿� ���� �ʴ� ���

	// �� ��ȿ�� �˻�
	int arr1[13];
	int arr2[12] = { 2,3,4,5,6,7,8,9,2,3,4,5 };
	for (size_t i = 0; i < 14; i++) {
		if (i < 6) arr1[i] = rrn[i] - '0';
		else if (i > 6) arr1[i - 1] = rrn[i] - '0';
	}
	int sum = 0;
	for (size_t i = 0; i < 12; i++) {
		sum += arr1[i] * arr2[i];
	}
	if (arr1[12] == 11 - (sum % 11)) return true;
	else return false;
}
