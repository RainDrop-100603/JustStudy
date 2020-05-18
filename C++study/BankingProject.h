#ifndef __BANKINGPROJECT_H__
#define __BANKINGPROJECT_H__

/*
 * Banking System Ver 0.6
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 6단계
 */

#include <iostream>
#include <cstring>

using namespace std;

enum Constant {
	MAXACCOUNT = 10,
	NAMELENGTH = 100,
};

enum CreditRating {
	RANK_A = 7,
	RANK_B = 4,
	RANK_C = 2
};


class BankAccount {
private:
	int bankID;
	char* name;
	int balance;
public:
	BankAccount(int bankID, char* name, int balance);
	BankAccount(const BankAccount &ref);
	int GetBankID() const;
	int GetBalance() const;
	//void BalanceChange(int change);
	virtual void Deposit(int money);
	void WithDraw(int money);
	virtual void ShowCustomerInfo() const;
	virtual ~BankAccount();
};

class NormalAccount: public BankAccount{
	int interest;
public:
	NormalAccount(int bankID, char* name, int balance, int interest);
	virtual void Deposit(int money);
	virtual void ShowCustomerInfo() const;
	virtual ~NormalAccount();
};

class HighCreditAccount: public NormalAccount{
	int creditRating;
public:
	HighCreditAccount(int bankID, char* name, int balance, int interest, int creditRating);
	virtual void Deposit(int money);
	virtual void ShowCustomerInfo() const;
	virtual ~HighCreditAccount();
};


class AccountHandler{
	BankAccount* accountArr[MAXACCOUNT];
	int accountNum;
public:
	AccountHandler();
	int BankingMenu() const;
	int ChkAccount(int accountID) const;
	void OpenAccount();
	void Deposit();
	void Withdraw();
	void PrintAllAccount() const;
	virtual ~AccountHandler();
};

void BankProgram(void);

#endif // !__PROJECT1__
