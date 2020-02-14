#include "UserMode.h"
#include "Util.h"

int UserMode::SelectMenu(Server& server)
{
	int ch;
	while (1) {
		Util::Clrscr();
		cout << "--------[사용자 모드]--------" << endl;
		cout << "서버 전체용량 : " << server.get_serverinfo_()->totalcapacity_ << endl;
		cout << "현재 사용용량 : " << server.get_serverinfo_()->usedcapacity_ << endl;
		cout << "사용가능 용량 : " << server.get_serverinfo_()->remaincapacity_ << endl;
		cout << endl;
		cout << "1. 파일 업로드" << endl;
		cout << "2. 파일 삭제" << endl;
		cout << "3. 파일 다운로드" << endl;

		try {
			ch = _getch();
			if (ch == '1') {
				if (user_.level == "R") throw Exception::get_exceptiontype_(Exception::kReadOnly);
				else FileUpload();	// 파일 업로드
			}
			else if (ch == '2') {
				if (user_.level == "R") throw Exception::get_exceptiontype_(Exception::kReadOnly);
				else FileDelete();		// 파일 삭제
			}
			else if (ch == '3') {
				if (user_.level == "W") throw Exception::get_exceptiontype_(Exception::kWriteOnly);
				else FileDownload();	// 파일 다운로드
			}
			else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc);
			else throw Exception::get_exceptiontype_(Exception::kInvalidMenuInput);
		}
		catch (string e) {
			if (e == "ESC") return -1;	// 사용자 모드 종료
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
	cout << "파일 업로드를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}

void UserMode::FileDelete()
{
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "파일 삭제를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}

void UserMode::FileDownload()
{
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "파일 다운로드를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
