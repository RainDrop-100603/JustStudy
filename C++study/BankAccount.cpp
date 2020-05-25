/*
 * Banking System Ver 0.8
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 6단계
 */

//BankAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"

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
BankAccount& BankAccount::operator=(const BankAccount& ref){
	bankID=ref.bankID;
	balance=ref.balance;
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