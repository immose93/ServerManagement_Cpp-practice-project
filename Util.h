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
	static void Clrscr() { system("cls"); }	// 화면 지우는 함수
	static bool GetInputString(string msg, string& str, int idx);	// 문자열 입력받는 함수 (중간에 ESC 입력 감지하여 종료하는데 사용)
	static void Delay(int ms) { Sleep(ms); }	// 일정 시간 sleep
private:
	Util() {}
	~Util(){}
};
