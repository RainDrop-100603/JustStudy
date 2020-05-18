//#define _CRT_SECURE_NO_WARNINGS

/*
 * Banking System Ver 0.6
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 6단계
 */

#include "BankingProject.h"

//class 정의
BankAccount::BankAccount(int bankID=-1, char* name=NULL, int balance = 0)
	 :bankID(bankID), balance(balance) {
	this->name = new char[strlen(name)+1];
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
int BankAccount::GetBankID() const {
	return bankID;
}
int BankAccount::GetBalance() const {
	return balance;
}
void BankAccount::Deposit(int money){
	balance+=money;
}
void BankAccount::WithDraw(int money){
	balance-=money;
}
void BankAccount::ShowCustomerInfo() const {
	cout << "계좌ID: " << bankID << endl;
	cout << "이 름: " << name << endl;
	cout << "잔 액: " << balance << endl;
}
NormalAccount::NormalAccount(int bankID, char* name, int balance, int interest)
	:BankAccount(bankID, name, balance), interest(interest){}
void NormalAccount::Deposit(int money){
	BankAccount::Deposit(money+money*interest/100);
}
NormalAccount::~NormalAccount(){}
HighCreditAccount::HighCreditAccount(int bankID, char* name, int balance, int interest, int creditRating)
	:NormalAccount(bankID, name, balance, interest){
		if(creditRating==1){
			this->creditRating=7;
		}else if(creditRating==2){
			this->creditRating=4;
		}else{
			this->creditRating=2;
		}
	}
void HighCreditAccount::Deposit(int money){
	NormalAccount::Deposit(money+money*creditRating/100);
}
HighCreditAccount::~HighCreditAccount(){}

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
			return i;
		}
	}
	return -1;
}
void AccountHandler::OpenAccount() {
	if (accountNum == MAXACCOUNT) {
		cout << "계좌를 더이상 생성할 수 없습니다" << endl;
		return;
	}

	int choice, bankID, balance, interest, creditRating;
	char name[NAMELENGTH];
	cout << "[계좌종류선택]" << endl;
	cout<<"1. 보통예금계좌 2. 신용신뢰계좌"<<endl;
	cout<<"선택";
	cin>>choice;

	if(choice==1){
		cout<<"[보통예금계좌 개설]"<<endl;
		cout << "계좌 ID: ";
		cin >> bankID;
		if(ChkAccount(bankID)!=-1){
			cout<<"이미 존재하는 계좌 ID 입니다"<<endl;
			return;
		}
		cout << "이 름: ";
		cin >> name;
		cin.ignore();
		cout<<"입금액: ";
		cin>>balance;
		cout<<"이자율: ";
		cin>>interest;
		accountArr[accountNum] = new NormalAccount(bankID,name,balance,interest);
	}
	else if(choice ==2){
		cout<<"[신용신뢰계좌 개설]"<<endl;
		cout << "계좌 ID: ";
		cin >> bankID;
		if(ChkAccount(bankID)!=-1){
			cout<<"이미 존재하는 계좌 ID 입니다"<<endl;
			return;
		}
		cout << "이 름: ";
		cin >> name;
		cin.ignore();
		cout<<"입금액: ";
		cin>>balance;
		cout<<"이자율: ";
		cin>>interest;
		cout<<"신용등급(1toA,2toB,3toC)";
		cin>>creditRating;
		accountArr[accountNum] = new HighCreditAccount(bankID,name,balance,interest,creditRating);
	}else{
		cout<<"잘못된 입력입니다"<<endl;
		return;
	}

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
	cout << "잔 액: " << accountArr[accessNum]->GetBalance() << endl;
	cout << "금액을 입력하십시오: ";
	cin>>money;
	accountArr[accessNum]->Deposit(money);
	cout<<money<<"원 입금이 완료되었습니다. 잔액은 "<<accountArr[accessNum]->GetBalance()<<"입니다"<<endl;
}	
void AccountHandler::Withdraw(){
	cout << "[ 출 금 ]" << endl;
	int bankID,accessNum,money;
	cout <<"계좌 ID: ";
	cin>>bankID;
	accessNum=ChkAccount(bankID);
	if (accessNum ==-1){
		cout<<"존재하지 않는 계좌입니다"<<endl;
		return;
	}
	cout << "잔 액: " << accountArr[accessNum]->GetBalance() << endl;
	cout << "금액을 입력하십시오: ";
	cin>>money;
	if (money>accountArr[accessNum]->GetBalance()){
		cout<<"잔액이 부족합니다."<<endl;
		return;
	}
	accountArr[accessNum]->WithDraw(money);
	cout<<money<<"원 출금이 완료되었습니다. 잔액은 "<<accountArr[accessNum]->GetBalance()<<"입니다"<<endl;
}
void AccountHandler::PrintAllAccount() const{
	for(int i=0;i<accountNum;i++){
		accountArr[i]->ShowCustomerInfo();
		cout<<endl;
	}
}

//함수 정의
void BankProgram(void) {
	AccountHandler handler;
	int work;
	while (1) {
		//---------------------continue가 오는 위치  
		work = handler.BankingMenu();
		switch (work) {
		case 1:
			handler.OpenAccount();
			continue;	//continue는 while문의 시작으로 돌아간다. 
			//break;	//break는 switch문을 탈출한다. 
		case 2:
			handler.Deposit();
			continue;
		case 3:
			handler.Withdraw();
			continue;
		case 4: 
			handler.PrintAllAccount();
			continue;
		case 5:
			cout << "프로그램을 종료합니다" << endl;
			return;
		default:
			cout << "메뉴를 잘못 입력하셨습니다. 다시 입력해 주십시오" << endl << endl;
			continue;
		}
		//------------------------break가 오는 위치  
	}
}




// void Menu3_Withdraw(BankAccount* accArr[], int accNum) {
// 	int realAccNum;
// 	cout << "[ 출 금 ]" << endl;
// 	realAccNum = ChkAccount(accArr, accNum);
// 	if (realAccNum == -1) {
// 		return;
// 	}
// 	accArr[realAccNum]->Withdraw();
// }
// void Menu4_PrintAllAccount(BankAccount* accArr[], int accNum) {
// 	for (int i = 0; i < accNum; i++) {
// 		accArr[i]->ShowCustomerInfo();
// 		cout << endl;
// 	}
// }
// void Menu5_Finish(BankAccount* accArr[], int accNum) {
// 	for (int i = 0; i < accNum; i++) {
// 		delete accArr[i];
// 	}
// }