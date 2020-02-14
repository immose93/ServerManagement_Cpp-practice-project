#include "AdminMode.h"
#include "Util.h"

int AdminMode::SelectMenu(Server &server)
{
	while (1) {
		Util::Clrscr();
		cout << "\n-------[������ ���]-------" << endl;
		cout << "1. ������ �ڵ� ����" << endl;
		cout << "2. ������ ���� ����" << endl;
		cout << "3. �ϵ�뷮 �߰�" << endl;
		cout << "4. ������� ���� ����" << endl;
		cout << "5. ���� ���ε�" << endl;
		cout << "6. ���� ����" << endl;
		cout << "7. ���� �ٿ�ε�" << endl;
		cout << "---------------------------" << endl;
		int ch;
		try {
			ch = _getch();
			if (ch == '1') UpdateAdminCode(server);
			else if (ch == '2') RegisteredUserInfo(server);
			else if (ch == '3') AddCapacity(server);
			else if (ch == '4') WaitingUserInfo(server);
			else if (ch == '5') FileUpload();
			else if (ch == '6') FileDelete();
			else if (ch == '7') FileDownload();
			else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc);	
			else throw Exception::get_exceptiontype_(Exception::kInvalidMenuInput);
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ����� ��� ���� (ESC)
			cout << e << endl;
			Util::Delay(1000);
		}
	}
	return 0;
}

int AdminMode::UpdateAdminCode(Server &server)
{
	Util::Clrscr();
	cout << "--------[������ �ڵ� ����]--------" << endl;
	string newcode;
	try {
		Util::GetInputString("���ο� code �Է� :  ", newcode, -1);
		cout << "���� �� code : " << server.get_serverinfo_()->admininfo_->code << endl;
		cout << "���� �� code : " << newcode << endl;
		server.get_serverinfo_()->admininfo_->code = newcode;
		cout << "������ �ڵ� ���� �Ϸ�." << endl;
		Util::Delay(2000);
	}
	catch (string e) {
		if (e == "ESC") return -1;	// ESC �Է½� ������ ��� ȭ������ ���ư�
	}
	return 0;
}

void AdminMode::RegisteredUserInfo(Server &server)
{
	Util::Clrscr();
	cout << "-----------------------[������ ���� ����]-----------------------" << endl;
	UserMap::iterator iter = server.get_serverinfo_()->usermap_->begin();
	UserMap::iterator end = server.get_serverinfo_()->usermap_->end();
	for (; iter != end; iter++) {			// ȸ�� ����� ó������ ������ iterator�� ����Ͽ� ��ȸ
		cout << "ID : " << iter->second.id
			<< ", ��� : " << "******"			// �߰������� ��ȣȭ �ʿ�
			<< ", �ֹι�ȣ : " << "******"		// �߰������� ��ȣȭ �ʿ�
			<< ", ���ѷ��� : " << iter->second.level
			<< endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	system("pause");
	return;
}

int AdminMode::AddCapacity(Server &server)
{
	Util::Clrscr();
	cout << "-----------[�ϵ� �뷮 �߰�]-----------" << endl;
	try {
		if (admininfo_.addcapacitycount >= 3) // �̹� �ϵ�뷮�� 3ȸ �߰��ߴٸ� ���̻� �߰� �Ұ���
			throw Exception::get_exceptiontype_(Exception::kAddCapacityMaxCount);
		cout << "�߰� Ƚ�� : " << admininfo_.addcapacitycount << "ȸ" << endl;	// ������� �߰��� Ƚ�� ���
		int add = 0;
		string addstr = "";
		while (1) {
			try {
				cout << "�ϵ� �뷮�� �󸶳� �߰��Ͻðڽ��ϱ�?" << endl;
				Util::GetInputString("�߰��뷮�Է� : ", addstr, -1);
				add = atoi(addstr.c_str());
				if (add == 0) throw Exception::get_exceptiontype_(Exception::kInvalidInput);
				else break;
			}
			catch (string e) {
				if (e == "ESC") return -1;	// ESC �Է½� ������ ��� ȭ������ ���ư�
				cout << e << endl;
			}
		}
		server.addCapacity(add);	// ���� �ϵ�뷮 �߰�
		cout << endl;
		cout << "���� �ϵ� �뷮�� " << add << " �߰��Ǿ����ϴ�." << endl;
		cout << "--------------------------------------" << endl;
		cout << "���� ��ü�뷮 : " << server.get_serverinfo_()->totalcapacity_ << endl;
		cout << "���� ���뷮 : " << server.get_serverinfo_()->usedcapacity_ << endl;
		cout << "��밡�� �뷮 : " << server.get_serverinfo_()->remaincapacity_ << endl;
		cout << "--------------------------------------" << endl;
		admininfo_.addcapacitycount++;		// �ϵ� �뷮 �߰� ī��Ʈ ����	
	}
	catch (string e) {
		cout << e << endl;
		system("pause");
		return 1;
	}
	system("pause");
	return 0;
}

int AdminMode::WaitingUserInfo(Server &server)
{
	Util::Clrscr();
	cout << "----------------------[������� ���� ����]----------------------" << endl;
	UserMap::iterator iter = server.get_serverinfo_()->waiting_usermap_->begin();
	UserMap::iterator end = server.get_serverinfo_()->waiting_usermap_->end();
	int ch;
	string id;
	if (iter == end) {	// ��⿭�� ���� ���
		cout << "���� ��û ��⿭�� �����ϴ�." << endl;
	}
	else {
		while (iter != end) {
			id = iter->second.id;
			cout << "----------------------------------------------------------------" << endl;
			cout << "ID : " << iter->second.id
				<< ", ��� : " << "******"			// �߰������� ��ȣȭ �ʿ�
				<< ", �ֹι�ȣ : " << "******"	// �߰������� ��ȣȭ �ʿ�
				<< ", ���ѷ��� : " << iter->second.level
				<< endl;
			cout << "----------------------------------------------------------------" << endl;
			try {
				cout << "������ �����Ͻðڽ��ϱ�?(y/n)" << endl;
				ch = _getch();
				if (ch == 'y') {	// ���� ��û ����
					UserInfo applieduser(iter->second);
					server.get_serverinfo_()->usermap_->insert({ id,applieduser });	// ȸ�� ��Ͽ� �߰�
					throw Exception::get_exceptiontype_(Exception::kAcceptSignUpRequest);
				}
				else if (ch == 'n')	// ���� ��û ����
					throw Exception::get_exceptiontype_(Exception::kRejectSignUpRequest);
				else if (ch == 27)	// ESC �Է½� ��⿭ ���� ����
					throw Exception::get_exceptiontype_(Exception::kPressEsc);
			}
			catch (string e) {
				if (e == "ESC") {	
					cout << "���� ��û ��⿭ ��ȸ ����" << endl;
					return -1;
				}
				cout << id << e << endl;
			}
			UserMap::iterator nextiter = next(iter);
			server.get_serverinfo_()->waiting_usermap_->erase(id);		// ��⿭���� ����
			iter = nextiter;
		}
	}
	system("pause");
	return 0;
}

void AdminMode::FileUpload() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� ���ε带 �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
void AdminMode::FileDelete() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� ������ �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
void AdminMode::FileDownload() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� �ٿ�ε带 �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}