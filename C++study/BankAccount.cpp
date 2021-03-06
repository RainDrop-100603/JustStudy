/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 6단계
 */

//BankAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"

BankAccount::BankAccount(int bankID, String name, int balance)
	 :bankID(bankID), name(name), balance(balance){}
// BankAccount::~BankAccount() {
// 	delete this->name;
// }
// BankAccount::BankAccount(const BankAccount &ref)
// 		: bankID(ref.bankID), balance(ref.balance),name(ref.name){}
// BankAccount& BankAccount::operator=(const BankAccount& ref){
// 	bankID=ref.bankID;
// 	balance=ref.balance;
// 	name=ref.name;
// 	return *this;
// }
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