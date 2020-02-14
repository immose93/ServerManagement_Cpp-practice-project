#include "Util.h"

bool Util::GetInputString(string msg, string& str, int idx)
{
	cout << msg;
	int ch = 0;
	str.clear();
	int i = 0;
	while (1) {
		ch = _getch();
		if (ch == 13) break;					// Enter 입력시 문자열 입력 종료
		else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc); // ESC 입력시 false 리턴 (기능 종료 플래그로 활용)
		else if (ch == 8) {						// 백스페이스 구현
			if (str.length() == 0) continue;
			str.pop_back();
			i--;
			cout << "\b \b";
			continue;
		}
		else str += (char)ch;
		if (idx < 0) cout << (char)ch;	// idx가 음수면 입력한대로 출력
		else if (i < idx) cout << (char)ch;	// idx 이전은 입력한대로 출력
		else if (i >= idx) cout << "*";	// idx 이후부터는 *표로 출력
		i++;
	}
	cout << '\n';
	return true;	// 정상적으로 입력이 완료되면 true 리턴
}
