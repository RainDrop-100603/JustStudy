#ifndef __PROJECTVER4_H__
#define __PROJECTVER4_H__

#include <iostream>
#include <cstring>

//OOP 단계별 프로젝트

//2단계

class BankAccount {
private:
	int bankID;
	char* name;
	int balance;
public:
	BankAccount(int iBankID, char* name, int iBalance);
	BankAccount();
	BankAccount(const BankAccount &ref);
	void OpenAccount(int BankID, char* name, int Balance);
	int GetBankID() const;
	void Deposit();
	void Withdraw();
	void ShowCustomerInfo() const;
	~BankAccount();
};

void BankProgram(void);
int AccountMenu(void);
int ChkAccount(BankAccount* accountArray[], int accNum);
int Menu1_OpenAccount(BankAccount* AccArr[], int accNum);
void Menu2_Deposit(BankAccount* accArr[], int accNum);
void Menu3_Withdraw(BankAccount* accArr[], int accNum);
void Menu4_PrintAllAccount(BankAccount* accArr[], int accNum);
void Menu5_Finish(BankAccount* accArr[], int accNum);


#endif // !__PROJECT1__
