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
		cout << "\n--------[메인 메뉴]--------" << endl;
		cout << "1. 사용자 모드" << endl;
		cout << "2. 관리자 모드" << endl;
		cout << "3. 회원 가입요청" << endl;
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
		cout << "-----[유저 모드 로그인]-----" << endl;
		try {
			Util::GetInputString("ID : ", id, -1);
			Util::GetInputString("Password : ", password, 0); // 비밀번호는 *표로 출력
			Util::GetInputString("권한 레벨 : ", level, -1);
			// 계정 체크
			iter = serverinfo_->usermap_->find(id);
			if (iter == serverinfo_->usermap_->end()) // 존재하지 않는 ID
				throw Exception::get_exceptiontype_(Exception::kNotExistsInUserMap);
			else if (iter->second.dormant)					// 휴면계정인 경우 사용자 모드 진입 X
				throw Exception::get_exceptiontype_(Exception::kDormant);
			else if (iter->second.pass != password)		// 비밀번호를 틀린 경우
				throw Exception::get_exceptiontype_(Exception::kWrongPassword);
			else if (iter->second.level != level)			// 권한 레벨이 틀린 경우
				throw Exception::get_exceptiontype_(Exception::kWrongLevel);
			else {
				iter->second.login_fail_count = 0;		// 실패 정보 초기화
				UserMode usermode(iter->second);	// 사용자 모드에 들어갈 사용자 정보를 담은 사용자모드 객체 생성
				cout << "로그인 성공!" << endl;	// 로그인 성공 문구 출력
				Util::Delay(1000);
				usermode.SelectMenu(*this);		// 사용자 모드 진입
				break;	// 사용자 모드 종료
			}
		}
		catch (string e) {
			if (e == "ESC") return -1;
			else if (e== "비밀번호가 틀렸습니다." || e == "권한 레벨이 틀렸습니다.")
				iter->second.login_fail_count++;			// 카운트 증가
			cout << e << endl;
			Util::Delay(1500);
		}
		try {
			if (iter != serverinfo_->usermap_->end() && iter->second.login_fail_count >= 5)		// 5회 이상 실패시
				throw Exception::get_exceptiontype_(Exception::kFailedFiveTimes);
		}
		catch (string e) {
			iter->second.dormant = true;	// 휴면계정 처리
			iter->second.login_fail_count = 0;	// 실패 정보 초기화
			cout << id << e << endl;
			Util::Delay(2000);
			return 1; // 사용자 모드 진입 X	 (휴면계정 리턴 1)
		}
	}
	return 0;
}

int Server::AdminModeCode()
{
	Util::Clrscr();
	cout << "--------[관리자 모드 코드 입력]--------" << endl;
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
	return 0;	// 관리자 모드 종료
}

int Server::SignUp()
{
	Util::Clrscr();
	cout << "---------[회원가입]---------" << endl;	
	string id;
	while (1) {
		try {
			Util::GetInputString("ID : ", id, -1);
			if (serverinfo_->usermap_->find(id) != serverinfo_->usermap_->end())	// 이미 존재하는 회원 ID인 경우
				throw Exception::get_exceptiontype_(Exception::kExistsInUsermap);
			else if (serverinfo_->waiting_usermap_->find(id) != serverinfo_->waiting_usermap_->end())	// 회원가입 대기열에 존재하는 ID인 경우
				throw Exception::get_exceptiontype_(Exception::kExistInWaitingUsermap);
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ESC 키를 누르면 이전 메뉴로 리턴
			cout << e << endl;
			continue;
		}
		break;
	}

	// 주민번호 입력
	string rrn;
	while (1) {
		rrn.clear();
		try {
			Util::GetInputString("주민번호(하이픈 '-' 포함하여 입력) : ", rrn, 7);	// 주민번호 뒷자리는 *표로 출력
			// 주민번호 유효성 검사
			if (!IsValidRRN(rrn))		// 유효하지 않은 주민번호인 경우
				throw Exception::get_exceptiontype_(Exception::kInvalidRRN);
			else break;	// 유효한 주민번호인 경우
		}
		catch (string e) {
			if (e == "ESC") return -1; // ESC 키를 누르면 이전 메뉴로 리턴
			cout << e << endl;
		}		
	}

	// 권한레벨 입력
	string level;
	while (1) {
		try {
			Util::GetInputString("권한레벨(읽기=R, 쓰기=W, 읽기/쓰기=RW) : ", level, -1);
			// 권한레벨 유효성 검사
			if (level != "R" && level != "W" && level != "RW") // 유효하지 않은 권한레벨인 경우
				throw Exception::get_exceptiontype_(Exception::kInvalidLevel);
			else break;
		}
		catch (string e) {
			if (e == "ESC") return -1;	// ESC 키를 누르면 이전 메뉴로 리턴
			cout << e << endl;
		}
	}

	// 비번 입력
	string password;
	while (1) {
		try {
			Util::GetInputString("Password : ", password, 0);	// 비밀번호는 *표로 출력
			// 비밀번호 유효성 검사
			CheckPassword(password,rrn);	// 정상적인 경우 0 리턴
			break;
		}
		catch (string e) {
			cout << e << endl;
			continue;
		}
	}
	Util::Clrscr();
	// 회원가입 대기열에 추가
	UserInfo waitinguser(id, password, rrn, level);
	serverinfo_->waiting_usermap_->insert({ id, waitinguser });
	cout << "---------------------------" << endl;
	cout << "ID : " << waitinguser.id << endl;
	cout << "PW : " << waitinguser.pass << endl;
	cout << "RRN : " << waitinguser.rrn << endl;
	cout << "Level : " << waitinguser.level << endl;
	cout << "가입 요청이 접수되었습니다." << endl;
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
	if (password.length() < 8)	// 비번의 길이가 8보다 작은 경우
		throw Exception::get_exceptiontype_(Exception::kShortPassword);
	else if (IsNotAlphabetOrNumber(password))	// 비밀번호가 알파벳 대소문자나 숫자로 구성되지 않은 경우
		throw Exception::get_exceptiontype_(Exception::kIsNotAlphabetOrNumber);
	else if (IsRRNInPassword(password, rrn))		// 비밀번호에 사용자의 주민번호가 포함된 경우
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
		for (size_t j = 2; j <= 14; j++) {		// 글자 수
			if (i + j > 14) break;
			str = rrn.substr(i, j);	// 주민번호 i번째 자리부터 j개의 숫자가 포함된 경우
			pos = password.find(str);
			if (pos > 0 && pos < password.length()) 	return true;	// 주민번호 일부가 존재
		}
	}
	return false;
}

bool IsValidRRN(string rrn) {
	// 주민번호 포맷 검사
	regex reg("^(?:[0-9]{2}(?:0[1-9]|1[0-2])(?:0[1-9]|[1,2][0-9]|3[0,1]))-[1-4][0-9]{6}$");	// 주민번호 정규식
	if (!regex_match(rrn, reg)) return false; // 주민번호 포맷에 맞지 않는 경우

	// 값 유효성 검사
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
