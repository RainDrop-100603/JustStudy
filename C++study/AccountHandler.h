#ifndef __ACCOUNTHANDLER_H__
#define __ACCOUNTHANDLER_H__
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
// #include "AccountArray.h"
#include "BoundCheckArray.h"

class AccountHandler{
	// BankAccount* accountArr[MAXACCOUNT];
	BoundCheckArray<BankAccount*> accountArr;	//
	int accountNum;
public:
	AccountHandler();
	int BankingMenu() const;
	int ChkAccount(int accountID) const;
	void OpenAccount();
  void OPNormalAccount();
  void OPHighCreditAccount();
	void Deposit();
	void Withdraw();
	void PrintAllAccount() const;
	virtual ~AccountHandler();
};


#endif