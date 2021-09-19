/*
 * Banking System Ver 0.7
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트
 */

//AccountHandler 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"
#include "AccountHandler.h"

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
	cout << "선택: "; cin >> num;
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
	if (accountNum == Constant::MAXACCOUNT) {
		cout << "계좌를 더이상 생성할 수 없습니다" << endl;
		return;
	}

	int choice;
	cout << "[계좌종류선택]" << endl;
	cout<<"1. 보통예금계좌 2. 신용신뢰계좌"<<endl;
	cout<<"선택: "; cin>>choice;

	if(choice==1){
		cout<<"[보통예금계좌 개설]"<<endl;
    OPNormalAccount();
	}else if(choice ==2){
		cout<<"[신용신뢰계좌 개설]"<<endl;
    OPHighCreditAccount();
	}else{
		cout<<"잘못된 입력입니다"<<endl;
		return;
	}
}

void AccountHandler::OPNormalAccount(){
  int bankID, balance, interest;
  String name;
	cout << "계좌 ID: ";	cin >> bankID;
	if(ChkAccount(bankID)!=-1){
		cout<<"이미 존재하는 계좌 ID 입니다"<<endl;
		return;
	}
	cout<<"이 름: ";	cin >> name;
	cout<<"입금액: ";	cin>>balance;
	cout<<"이자율: ";	cin>>interest;
	accountArr[accountNum] = new NormalAccount(bankID,name,balance,interest);  
	cout << endl << "계좌 생성 완료" << endl;
	accountNum++;
}

void AccountHandler::OPHighCreditAccount(){
  int bankID, balance, interest, creditRating;
  String name;
	cout << "계좌 ID: ";  cin >> bankID;
	if(ChkAccount(bankID)!=-1){
		cout<<"이미 존재하는 계좌 ID 입니다"<<endl;
		return;
	}
	cout<<"이 름: ";	cin >> name;
	cout<<"입금액: ";	cin>>balance;
	cout<<"이자율: ";	cin>>interest;
	cout<<"신용등급(1toA,2toB,3toC): ";	cin>>creditRating;
	accountArr[accountNum] = new HighCreditAccount(bankID,name,balance,interest,creditRating);
	cout << endl << "계좌 생성 완료" << endl;
	accountNum++;
}

void AccountHandler::Deposit(){
	cout << "[ 입 금 ]" << endl;
	int bankID,accessNum,money;
	cout <<"계좌 ID: "; cin>>bankID;
	accessNum=ChkAccount(bankID);
	if (accessNum ==-1){
		cout<<"존재하지 않는 계좌입니다"<<endl;
		return;
	}
	cout << "잔 액: " << accountArr[accessNum]->GetBalance() << endl;
	cout << "금액을 입력하십시오: ";  cin>>money;
	accountArr[accessNum]->Deposit(money);
	cout<<"입금이 완료되었습니다. 잔액은 "<<accountArr[accessNum]->GetBalance()<<"입니다"<<endl;
}	

void AccountHandler::Withdraw(){
	cout << "[ 출 금 ]" << endl;
	int bankID,accessNum,money;
	cout <<"계좌 ID: "; cin>>bankID;
	accessNum=ChkAccount(bankID);
	if (accessNum ==-1){
		cout<<"존재하지 않는 계좌입니다"<<endl;
		return;
	}
	cout << "잔 액: " << accountArr[accessNum]->GetBalance() << endl;
	cout << "금액을 입력하십시오: ";  cin>>money;
	if (money>accountArr[accessNum]->GetBalance()){
		cout<<"잔액이 부족합니다."<<endl;
		return;
	}
	accountArr[accessNum]->WithDraw(money);
	cout<<"출금이 완료되었습니다. 잔액은 "<<accountArr[accessNum]->GetBalance()<<"입니다"<<endl;
}

void AccountHandler::PrintAllAccount() const{
	for(int i=0;i<accountNum;i++){
		accountArr[i]->ShowCustomerInfo();
		cout<<endl;
	}
}