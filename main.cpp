#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
//#include <graphics.h>
// #include <mmsystem.h>
// #pragma comment(lib, "winmm.lib") //加载非标准库

#include "hacker.h"

#define CON_LEN 128
#define WIN_COLS 80
#define WIN_LINES 15
#define MSG_MAXSIZE 4096
#define ID_MAXSIZE 64
#define PWD_LEN 16

using namespace std;

void winInit(void);
string input_pwd(void);
void login(const string acc, const string pwd);
void showMenu1(void);
//void showMenu2(void);
int menuChoice(void);
void cleanBuff(void);
void printMiddle(string str, int winWidth);

void website404Attack(void);
void websiteTamper(void);
void websiteRestore(void);
void checkRecord(void);
void handleError(void);

int main(void) {
	const string account = "edward"; //正确的账号
	const string password = "123456"; //正确的密码
	int getChoice = 0;

	winInit();
	login(account, password);

	while (true) {
		showMenu1();
		getChoice = menuChoice();

		switch (getChoice) {
		case 1:
			website404Attack();
			break;
		case 2:
			websiteTamper();
			break;
		case 3:
			websiteRestore();
			break;
		case 4:
			checkRecord();
			break;
		case 5:
			return 0;
		default:
			handleError();
			break;
		}
	}

	system("pause");
	return 0;
}

void winInit(void) {
	char str[CON_LEN];
	sprintf_s(str,"mode con cols=%d lines=%d", WIN_COLS, WIN_LINES);
	system(str);
}

string input_pwd(void) {
	string password;
	char pwd[PWD_LEN] = {};
	char temp;
	int i = 0;

	while (true) {
		temp = _getch();
		if (temp == '\r' || i>= PWD_LEN) {
			pwd[i] = 0;
			break;
		}
		pwd[i++] = temp;
		cout << '*';
	}
	cout << endl;

	password = pwd;
	return  password;
}

void login(const string acc, const string pwd) {
	string getAccount;
	string getPassword;

	while (true) {
		system("cls");
		cout << "请输入账号：";
		cin >> getAccount;
		cout << "请输入密码：";
		getPassword = input_pwd();

		if (getAccount == acc && getPassword == pwd) {
			break;
		}
		else {
			cout << "账号或者密码错误！" << endl;
			system("pause");
		}
	}
}

void printMiddle(string str, int winWidth) {
	int leftDash = 0;
	int rightDash = 0;
	leftDash = (winWidth - str.length()) / 2;
	rightDash = leftDash;

	for (int i = 0; i < leftDash; i++) {
		cout << '-';
	}
	cout << str;
	for (int i = 0; i < rightDash; i++) {
		cout << '-';
	}
	cout << endl;
}

void showMenu1(void) {

	string menu[] = {
		"1. 网站404攻击",
		"2. 网站内容篡改",
		"3. 网站攻击恢复",
		"4. 攻击记录查询",
		"5. 退出软件"
	};
	string title = "黑客工具";

	int maxLen = 0;
	int menuCount = sizeof(menu) / sizeof(menu[0]);
	int leftSpace = 0;

	for (int i = 0; i < menuCount; i++) {
		if (menu[i].length() > maxLen) {
			maxLen = menu[i].length();
		}
	}

	leftSpace = (WIN_COLS - maxLen) / 2;

	system("cls");

	printMiddle(title, WIN_COLS);

	for (int i = 0; i < menuCount; i++) {
		for (int j = 0; j < leftSpace; j++) {
			cout << ' ';
		}
		cout << menu[i] << endl;
	}
	cout << endl;

	for (int j = 0; j < leftSpace; j++) {
		cout << ' ';
	}
	cout << "请输入1到"<< menuCount <<"：";
}

int menuChoice(void) {
	int n = 0;
	cin >> n;
	if (cin.fail()) {
		cleanBuff();
		cin.clear();
		cout << "输入错误！请输入数字！" << endl;
		system("pause");
		return 0;
	}
	else {
		return n;
	}
}

void website404Attack(void) {
	char id[ID_MAXSIZE] = {};
	char msg[MSG_MAXSIZE] = {};
	string response;

	system("cls");
	printMiddle("网站404攻击", WIN_COLS);
	cout << "请输入目标网站ID：";
	scanf_s("%s", id, (unsigned int)sizeof(id));

	hk_404(id, msg);
	cout << "正在对目标网站进行404攻击......" << endl;

	response = UTF8ToGBK(msg);
	cout << response << endl;
	system("pause");
}
void websiteTamper(void) {
	char id[ID_MAXSIZE] = {};
	char msg[MSG_MAXSIZE] = {};
	string response;
	string editComment;

	system("cls");
	printMiddle("网站内容篡改", WIN_COLS);
	cout << "请输入目标网站ID：";
	scanf_s("%s", id, (unsigned int)sizeof(id));

	cout << "请输入你想打印的信息：";
	cin >> editComment;
	GBKToUTF8(editComment);

	hk_tamper(id, (char *)(editComment.c_str()), msg);
	cout << "正在对目标网站进行内容篡改......" << endl;

	response = UTF8ToGBK(msg);
	cout << response << endl;
	system("pause");
}
void websiteRestore(void) {
	char id[ID_MAXSIZE] = {};
	char msg[MSG_MAXSIZE] = {};
	string response;

	system("cls");
	printMiddle("网站攻击恢复", WIN_COLS);
	cout << "请输入目标网站ID：";
	scanf_s("%s", id, (unsigned int)sizeof(id));

	hk_restore(id, msg);
	cout << "正在对目标网站进行恢复" << endl;

	response = UTF8ToGBK(msg);
	cout << response << endl;
	system("pause");
}
void checkRecord(void) {
	char id[ID_MAXSIZE] = {};
	char msg[MSG_MAXSIZE] = {};
	string response;

	system("cls");
	printMiddle("攻击记录查询", WIN_COLS);
	cout << "请输入目标网站ID：";
	scanf_s("%s", id, (unsigned int)sizeof(id));

	hk_record(id, msg);
	cout << "正在查询目标网站的攻击记录" << endl;

	response = UTF8ToGBK(msg);
	cout << response << endl;
	system("pause");
}

void handleError(void) {
	system("cls");
	cout << "没有所选功能，请重新确认！" << endl;
	system("pause");
}

void cleanBuff(void) {
	//清除输入缓存区
	char temp;
	while ((temp = getchar()) != '\n');
}


//void showMenu2(void) {
//	initgraph(600, 400);
//	loadimage(0, _T("bg.jpg"));
//
//	settextcolor(RGB(255, 255, 0));
//	settextstyle(25, 0, _T("微软雅黑"));
//
//	rectangle(300, 20, 500, 60);
//	outtextxy(310, 25, _T("1. 网站404攻击"));
//
//	rectangle(300, 80, 500, 120);
//	outtextxy(310, 85, _T("2. 网站篡改攻击"));
//
//	rectangle(300, 140, 500, 180);
//	outtextxy(310, 145, _T("3. 网站攻击恢复"));
//
//	rectangle(300, 200, 500, 240);
//	outtextxy(310, 205, _T("4. 网站攻击记录查询"));
//
//	rectangle(300, 260, 500, 300);
//	outtextxy(310, 265, _T("5. 退出软件"));
//}