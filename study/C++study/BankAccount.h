#ifndef __BANKACCOUNT_H__
#define __BANKACCOUNT_H__
/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//BankAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "String.h"

class BankAccount {
private:
	int bankID;
	// char* name;
	String name;	//동적할당, 해제는 String class 에서 모두 담당하기 때문에, 전혀 신경 쓸 필요가 없다.
	int balance;
public:
	BankAccount(int bankID, String name, int balance);
	// BankAccount(const BankAccount &ref);	//깊은복사 얕은복사를 신경쓸 필요가 없기 때문에 디폴트 사용 
	// BankAccount& operator=(const BankAccount& ref);
	int GetBankID() const;
	int GetBalance() const;
	virtual void Deposit(int money);
	void WithDraw(int money);
	virtual void ShowCustomerInfo() const;
	// ~BankAccount();
};

#endif