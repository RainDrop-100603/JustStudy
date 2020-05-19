#ifndef __BANKINGSYSTEMMAIN_H__
#define	__BANKINGSYSTEMMAIN_H__

/*
 * Banking System Ver 0.7
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트
 */

//Banking System main 함수

#include "BankingCommonDec1.h"
#include "BankAccount.h"
#include "NormalAccount.h"
#include "HighCreditAccount.h"
#include "AccountHandler.h"

void BankProgram(void) {
	AccountHandler handler;
	int work;
	while (true) {
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

#endif