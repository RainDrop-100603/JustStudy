#ifndef __BANKACCOUNT_H__
#define __BANKACCOUNT_H__
/*
 * Banking System Ver 0.8
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//BankAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"

class BankAccount {
private:
	int bankID;
	char* name;
	int balance;
public:
	BankAccount(int bankID, char* name, int balance);
	BankAccount(const BankAccount &ref);
	BankAccount& operator=(const BankAccount& ref);
	int GetBankID() const;
	int GetBalance() const;
	virtual void Deposit(int money);
	void WithDraw(int money);
	virtual void ShowCustomerInfo() const;
	~BankAccount();
};

#endif