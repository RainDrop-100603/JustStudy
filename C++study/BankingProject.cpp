//#define _CRT_SECURE_NO_WARNINGS

/*
 * Banking System Ver 0.5
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 5단계
 */

#include "BankingProject.h"

enum Constant {
	MAXACCOUNT = 10,
	NAMELENGTH = 100,
};


//class 정의
BankAccount::BankAccount(int iBankID, char* name, int iBalance = 0) :bankID(iBankID), balance(iBalance) {
	int len = strlen(name) + 1;
	this->name = new char[len];
//	strcpy_s(this->name, len, name);
	strcpy(this->name, name); 
}
BankAccount::BankAccount(){}
BankAccount::~BankAccount() {
	delete this->name;
}
BankAccount::BankAccount(const BankAccount &ref)
		: bankID(ref.bankID), balance(ref.balance){
	name = new char[strlen(ref.name) + 1];
	strcpy(name, ref.name);
}
void BankAccount::OpenAccount(int bankID, char* name, int balance = 0) {
	this->bankID = bankID;
	this->balance = balance;
	int len = strlen(name) + 1;
	this->name = new char[len];
//	strcpy_s(this->name, len, name);
	strcpy(this->name, name);
}
int BankAccount::GetBankID() const {
	return bankID;
}
void BankAccount::Deposit() {
	int money;
	cout << "잔 액: " << balance << endl;
	cout << "금액을 입력하십시오: ";
	cin >> money;
	balance += money;
}
void BankAccount::Withdraw() {
	int money;
	cout << "잔 액: " << balance << endl;
	cout << "금액을 입력하십시오: ";
	cin >> money;
	if (balance - money < 0) {
		cout << "잔액이 부족합니다" << endl;
		return;
	}
	balance -= money;
}
void BankAccount::ShowCustomerInfo() const {
	cout << "계좌ID: " << bankID << endl;
	cout << "이 름: " << name << endl;
	cout << "잔 액: " << balance << endl;
}

//함수 정의
void BankProgram(void) {
	BankAccount* accountArray[MAXACCOUNT];
	int accountNum = 0;
	while (1) {
		//---------------------continue가 오는 위치  
		int work = AccountMenu();
		switch (work) {
		case 1:
			accountNum = Menu1_OpenAccount(accountArray, accountNum);
			continue;	//continue는 while문의 시작으로 돌아간다. 
			//break;	//break는 switch문을 탈출한다. 
		case 2:
			Menu2_Deposit(accountArray, accountNum);
			continue;
		case 3:
			Menu3_Withdraw(accountArray, accountNum);
			continue;
		case 4: 
			Menu4_PrintAllAccount(accountArray, accountNum);
			continue;
		case 5:
			goto FINISH;
			//return;	//FINISH구문을 여기다 넣고 return 박아도 된다. 
		default:
			cout << "메뉴를 잘못 입력하셨습니다. 다시 입력해 주십시오" << endl << endl;
			continue;
		}
		//------------------------break가 오는 위치  
	}
FINISH:
	Menu5_Finish(accountArray, accountNum);
	cout << "프로그램을 종료합니다" << endl;
}
int AccountMenu(void) {
	int num;
	cout << endl;
	cout << "-----Menu-----" << endl;
	cout << "1. 계좌개설" << endl;
	cout << "2. 입 금" << endl;
	cout << "3. 출 금" << endl;
	cout << "4. 계좌번호 전체 출력" << endl;
	cout << "5. 프로그램 종료" << endl;
	cout << "선택: ";
	cin >> num;
	cout << "---------------" << endl;
	cout << endl << endl;
	return num;
}
int ChkAccount(BankAccount* accArr[], int accNum) {
	int accountID;
	cout << "계좌 ID를 입력하십시오: ";
	cin >> accountID;
	for (int i = 0; i < accNum; i++) {
		if (accountID == accArr[i]->GetBankID()) {
			return i;
		}
	}
	cout << "입력하신 계좌 ID는 존재하지 않습니다" << endl;
	return -1;
}
int Menu1_OpenAccount(BankAccount* AccArr[], int accNum) {
	if (accNum == MAXACCOUNT) {
		cout << "계좌를 더이상 생성할 수 없습니다" << endl;
		return accNum;
	}
	int bankID;
	char name[NAMELENGTH];
	cout << "[ 계 좌 개 설 ]" << endl;
	cout << "계좌 ID: ";
	cin >> bankID;
	cout << "이 름: ";
	cin >> name;
	cin.ignore();	//한국어 들어갈때 이거 없으면 에러났던거같음. 이유는?
	AccArr[accNum] = new BankAccount(bankID, name);
	cout << endl << "계좌 생성 완료" << endl;
	return (accNum + 1);
}
void Menu2_Deposit(BankAccount* accArr[], int accNum) {
	int realAccNum;
	cout << "[ 입 금 ]" << endl;
	realAccNum = ChkAccount(accArr, accNum);
	if (realAccNum == -1) {
		return;
	}
	accArr[realAccNum]->Deposit();

}
void Menu3_Withdraw(BankAccount* accArr[], int accNum) {
	int realAccNum;
	cout << "[ 출 금 ]" << endl;
	realAccNum = ChkAccount(accArr, accNum);
	if (realAccNum == -1) {
		return;
	}
	accArr[realAccNum]->Withdraw();
}
void Menu4_PrintAllAccount(BankAccount* accArr[], int accNum) {
	for (int i = 0; i < accNum; i++) {
		accArr[i]->ShowCustomerInfo();
		cout << endl;
	}
}
void Menu5_Finish(BankAccount* accArr[], int accNum) {
	for (int i = 0; i < accNum; i++) {
		delete accArr[i];
	}
}