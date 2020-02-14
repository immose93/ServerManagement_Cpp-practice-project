#include "AdminMode.h"
#include "Util.h"

int AdminMode::SelectMenu(Server &server)
{
	while (1) {
		Util::Clrscr();
		cout << "\n-------[관리자 모드]-------" << endl;
		cout << "1. 관리자 코드 변경" << endl;
		cout << "2. 가입한 유저 정보" << endl;
		cout << "3. 하드용량 추가" << endl;
		cout << "4. 대기중인 유저 정보" << endl;
		cout << "5. 파일 업로드" << endl;
		cout << "6. 파일 삭제" << endl;
		cout << "7. 파일 다운로드" << endl;
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
			if (e == "ESC") return -1;	// 사용자 모드 종료 (ESC)
			cout << e << endl;
			Util::Delay(1000);
		}
	}
	return 0;
}

int AdminMode::UpdateAdminCode(Server &server)
{
	Util::Clrscr();
	cout << "--------[관리자 코드 변경]--------" << endl;
	string newcode;
	try {
		Util::GetInputString("새로운 code 입력 :  ", newcode, -1);
		cout << "변경 전 code : " << server.get_serverinfo_()->admininfo_->code << endl;
		cout << "변경 될 code : " << newcode << endl;
		server.get_serverinfo_()->admininfo_->code = newcode;
		cout << "관리자 코드 변경 완료." << endl;
		Util::Delay(2000);
	}
	catch (string e) {
		if (e == "ESC") return -1;	// ESC 입력시 관리자 모드 화면으로 돌아감
	}
	return 0;
}

void AdminMode::RegisteredUserInfo(Server &server)
{
	Util::Clrscr();
	cout << "-----------------------[가입한 유저 정보]-----------------------" << endl;
	UserMap::iterator iter = server.get_serverinfo_()->usermap_->begin();
	UserMap::iterator end = server.get_serverinfo_()->usermap_->end();
	for (; iter != end; iter++) {			// 회원 목록의 처음부터 끝까지 iterator를 사용하여 조회
		cout << "ID : " << iter->second.id
			<< ", 비번 : " << "******"			// 추가적으로 암호화 필요
			<< ", 주민번호 : " << "******"		// 추가적으로 암호화 필요
			<< ", 권한레벨 : " << iter->second.level
			<< endl;
		cout << "----------------------------------------------------------------" << endl;
	}
	system("pause");
	return;
}

int AdminMode::AddCapacity(Server &server)
{
	Util::Clrscr();
	cout << "-----------[하드 용량 추가]-----------" << endl;
	try {
		if (admininfo_.addcapacitycount >= 3) // 이미 하드용량을 3회 추가했다면 더이상 추가 불가능
			throw Exception::get_exceptiontype_(Exception::kAddCapacityMaxCount);
		cout << "추가 횟수 : " << admininfo_.addcapacitycount << "회" << endl;	// 현재까지 추가한 횟수 출력
		int add = 0;
		string addstr = "";
		while (1) {
			try {
				cout << "하드 용량을 얼마나 추가하시겠습니까?" << endl;
				Util::GetInputString("추가용량입력 : ", addstr, -1);
				add = atoi(addstr.c_str());
				if (add == 0) throw Exception::get_exceptiontype_(Exception::kInvalidInput);
				else break;
			}
			catch (string e) {
				if (e == "ESC") return -1;	// ESC 입력시 관리자 모드 화면으로 돌아감
				cout << e << endl;
			}
		}
		server.addCapacity(add);	// 서버 하드용량 추가
		cout << endl;
		cout << "서버 하드 용량이 " << add << " 추가되었습니다." << endl;
		cout << "--------------------------------------" << endl;
		cout << "서버 전체용량 : " << server.get_serverinfo_()->totalcapacity_ << endl;
		cout << "현재 사용용량 : " << server.get_serverinfo_()->usedcapacity_ << endl;
		cout << "사용가능 용량 : " << server.get_serverinfo_()->remaincapacity_ << endl;
		cout << "--------------------------------------" << endl;
		admininfo_.addcapacitycount++;		// 하드 용량 추가 카운트 증가	
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
	cout << "----------------------[대기중인 유저 정보]----------------------" << endl;
	UserMap::iterator iter = server.get_serverinfo_()->waiting_usermap_->begin();
	UserMap::iterator end = server.get_serverinfo_()->waiting_usermap_->end();
	int ch;
	string id;
	if (iter == end) {	// 대기열이 없는 경우
		cout << "가입 요청 대기열이 없습니다." << endl;
	}
	else {
		while (iter != end) {
			id = iter->second.id;
			cout << "----------------------------------------------------------------" << endl;
			cout << "ID : " << iter->second.id
				<< ", 비번 : " << "******"			// 추가적으로 암호화 필요
				<< ", 주민번호 : " << "******"	// 추가적으로 암호화 필요
				<< ", 권한레벨 : " << iter->second.level
				<< endl;
			cout << "----------------------------------------------------------------" << endl;
			try {
				cout << "가입을 승인하시겠습니까?(y/n)" << endl;
				ch = _getch();
				if (ch == 'y') {	// 가입 요청 승인
					UserInfo applieduser(iter->second);
					server.get_serverinfo_()->usermap_->insert({ id,applieduser });	// 회원 목록에 추가
					throw Exception::get_exceptiontype_(Exception::kAcceptSignUpRequest);
				}
				else if (ch == 'n')	// 가입 요청 거절
					throw Exception::get_exceptiontype_(Exception::kRejectSignUpRequest);
				else if (ch == 27)	// ESC 입력시 대기열 관리 종료
					throw Exception::get_exceptiontype_(Exception::kPressEsc);
			}
			catch (string e) {
				if (e == "ESC") {	
					cout << "가입 요청 대기열 조회 종료" << endl;
					return -1;
				}
				cout << id << e << endl;
			}
			UserMap::iterator nextiter = next(iter);
			server.get_serverinfo_()->waiting_usermap_->erase(id);		// 대기열에서 제거
			iter = nextiter;
		}
	}
	system("pause");
	return 0;
}

void AdminMode::FileUpload() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "파일 업로드를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
void AdminMode::FileDelete() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "파일 삭제를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}
void AdminMode::FileDownload() {
	Util::Clrscr();
	cout << "=============================" << endl;
	cout << "파일 다운로드를 수행하였습니다." << endl;
	cout << "=============================" << endl;
	Util::Delay(2000);
}