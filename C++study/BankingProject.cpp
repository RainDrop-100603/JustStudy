//#define _CRT_SECURE_NO_WARNINGS

/*
 * Banking System Ver 0.5
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 5단계
 */

#include "BankingProject.h"

//class 정의
BankAccount::BankAccount(int bankID=-1, char* name=NULL, int balance = 0)
	 :bankID(bankID), balance(balance) {
	this->name = new char[strlen(name)+1];
//	strcpy_s(this->name, len, name);
	strcpy(this->name, name); 
}

BankAccount::~BankAccount() {
	delete this->name;
}
BankAccount::BankAccount(const BankAccount &ref)
		: bankID(ref.bankID), balance(ref.balance){
	name = new char[strlen(ref.name) + 1];
	strcpy(name, ref.name);
}
//void BankAccount::OpenAccount(int bankID, char* name, int balance = 0) {
//	this->bankID = bankID;
//	this->balance = balance;
//	int len = strlen(name) + 1;
//	this->name = new char[len];
//	strcpy_s(this->name, len, name);
//	strcpy(this->name, name);
//}
int BankAccount::GetBankID() const {
	return bankID;
}
int BankAccount::GetBalance() const {
	return balance;
}
//void BankAccount::Deposit() {
//	int money;
//	cout << "잔 액: " << balance << endl;
//	cout << "금액을 입력하십시오: ";
//	cin >> money;
//	balance += money;
//}
//void BankAccount::Withdraw() {
//	int money;
//	cout << "잔 액: " << balance << endl;
//	cout << "금액을 입력하십시오: ";
//	cin >> money;
//	if (balance - money < 0) {
//		cout << "잔액이 부족합니다" << endl;
//		return;
//	}
//	balance -= money;
//}
void BankAccount::BalanceChange(int change){
	balance+=change;
}
void BankAccount::ShowCustomerInfo() const {
	cout << "계좌ID: " << bankID << endl;
	cout << "이 름: " << name << endl;
	cout << "잔 액: " << balance << endl;
}
AccountHandler::AccountHandler()
	:accountNum(0){}
AccountHandler::~AccountHandler(){
	for(int i=0;i<accountNum;i++){
		delete accountArr[i];
	}
}
int AccountHandler::BankingMenu() const{
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
int AccountHandler::ChkAccount(int accountID) const{
	for (int i = 0; i < accountNum; i++) {
		if (accountID == accountArr[i]->GetBankID()) {
			return accountID;
		}
	}
	return -1;
}
void AccountHandler::OpenAccount() {
	if (accountNum == MAXACCOUNT) {
		cout << "계좌를 더이상 생성할 수 없습니다" << endl;
		return;
	}

	int bankID;
	char name[NAMELENGTH];
	cout << "[ 계 좌 개 설 ]" << endl;
	cout << "계좌 ID: ";
	cin >> bankID;
	if(ChkAccount(bankID)!=-1){
		cout<<"이미 존재하는 계좌 ID 입니다"<<endl;
		return;
	}
	cout << "이 름: ";
	cin >> name;
	cin.ignore();	//한국어 들어갈때 이거 없으면 에러났던거같음. 이유는?
	accountArr[accountNum] = new BankAccount(bankID,name);
	cout << endl << "계좌 생성 완료" << endl;
	accountNum++;
}
void AccountHandler::Deposit(){
	cout << "[ 입 금 ]" << endl;
	int bankID,accessNum,money;
	cout <<"계좌 ID: ";
	cin>>bankID;
	accessNum=ChkAccount(bankID);
	if (accessNum ==-1){
		cout<<"존재하지 않는 계좌입니다"<<endl;
		return;
	}
	cout << "잔 액: " << accountArr[accessNum]->GetBalance << endl;
	cout << "금액을 입력하십시오: ";
	cin>>money;
	accountArr[accessNum]->BalanceChange(money);
	cout<<money<<"원 입금이 완료되었습니다. 잔액은 "<<accountArr[accessNum]->GetBalance<<"입니다"<<endl;
}	
void Menu2_Deposit(BankAccount* accArr[], int accNum) {
	int realAccNum;
	
	realAccNum = ChkAccount(accArr, accNum);
	if (realAccNum == -1) {
		return;
	}
	accArr[realAccNum]->Deposit();

}
	void Deposit();
	void Withdraw();
	void PrintAllAccount();


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