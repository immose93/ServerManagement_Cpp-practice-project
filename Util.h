#pragma once
#include <iostream>
#include <conio.h>
#include <Windows.h>
#include "Exception.h"
using std::string;
using std::cout;

class Util
{
public:
	static void Clrscr() { system("cls"); }	// ȭ�� ����� �Լ�
	static bool GetInputString(string msg, string& str, int idx);	// ���ڿ� �Է¹޴� �Լ� (�߰��� ESC �Է� �����Ͽ� �����ϴµ� ���)
	static void Delay(int ms) { Sleep(ms); }	// ���� �ð� sleep
private:
	Util() {}
	~Util(){}
};
