#include "UserMode.h"
#include "Util.h"

int UserMode::SelectMenu(Server& server)
{
	int ch;
	while (1) {
		Util::Clrscr();
		cout << "--------[����� ���]--------" << endl;
		cout << "���� ��ü�뷮 : " << server.get_serverinfo_()->totalcapacity_ << endl;
		cout << "���� ���뷮 : " << server.get_serverinfo_()->usedcapacity_ << endl;
		cout << "��밡�� �뷮 : " << server.get_serverinfo_()->remaincapacity_ << endl;
		cout << endl;
		cout << "1. ���� ���ε�" << endl;
		cout << "2. ���� ����" << endl;
		cout << "3. ���� �ٿ�ε�" << endl;

		try {
			ch = _getch();
			if (ch == '1') {
				if (user_.level == "R") throw Exception::get_exceptiontype_(Exception::kReadOnly);
				else FileUpload();	// ���� ���ε�
			}
			else if (ch == '2') {
				if (user_.level == "R") throw Exception::get_exceptiontype_(Exception::kReadOnly);
				else FileDelete();		// ���� ����
			}
			else if (ch == '3') {
				if (user_.level == "W") throw Exception::get_exceptiontype_(Exception::kWriteOnly);
				else FileDownload();	// ���� �ٿ�ε�
			}
			else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc);
			else throw Exception::get_exceptiontype_(Exception::kInvalidMenuInput);
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ����� ��� ����
			cout << e << endl;
			Util::Delay(1000);
		}
	}
	return 0;
}

void UserMode::FileUpload()
{
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� ���ε带 �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}

void UserMode::FileDelete()
{
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� ������ �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}

void UserMode::FileDownload()
{
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "���� �ٿ�ε带 �����Ͽ����ϴ�." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
