#ifndef __NORMALACCOUNT_H__
#define __NORMALACCOUNT_H__
/*
 * Banking System Ver 0.7
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//NormalAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"

class NormalAccount: public BankAccount{
	int interest;
public:
	NormalAccount(int bankID, char* name, int balance, int interest)
	  :BankAccount(bankID, name, balance), interest(interest){}

	virtual void Deposit(int money){
	  BankAccount::Deposit(money+money*interest/100);
  }

	virtual void ShowCustomerInfo() const{
	  BankAccount::ShowCustomerInfo();
  	cout << "이자율: " << interest << endl;
  }

};


#endif