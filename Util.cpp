#include "Util.h"

bool Util::GetInputString(string msg, string& str, int idx)
{
	cout << msg;
	int ch = 0;
	str.clear();
	int i = 0;
	while (1) {
		ch = _getch();
		if (ch == 13) break;					// Enter �Է½� ���ڿ� �Է� ����
		else if (ch == 27) throw Exception::get_exceptiontype_(Exception::kPressEsc); // ESC �Է½� false ���� (��� ���� �÷��׷� Ȱ��)
		else if (ch == 8) {						// �齺���̽� ����
			if (str.length() == 0) continue;
			str.pop_back();
			i--;
			cout << "\b \b";
			continue;
		}
		else str += (char)ch;
		if (idx < 0) cout << (char)ch;	// idx�� ������ �Է��Ѵ�� ���
		else if (i < idx) cout << (char)ch;	// idx ������ �Է��Ѵ�� ���
		else if (i >= idx) cout << "*";	// idx ���ĺ��ʹ� *ǥ�� ���
		i++;
	}
	cout << '\n';
	return true;	// ���������� �Է��� �Ϸ�Ǹ� true ����
}
