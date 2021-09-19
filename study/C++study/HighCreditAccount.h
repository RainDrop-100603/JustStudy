#ifndef __HIGHCREDITACCOUNT_H__
#define __HIGHCREDITACCOUNT_H__
/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트
 */

//HighCreditAccount 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"
#include "NormalAccount.h"

class HighCreditAccount: public NormalAccount{
	int creditRating;
public:
	HighCreditAccount(int bankID, String name, int balance, int interest, int creditRating)
    :NormalAccount(bankID,name,balance,interest){
		if(creditRating==1){
			this->creditRating=RANK_A;
		}else if(creditRating==2){
			this->creditRating=RANK_B;
		}else{
			this->creditRating=RANK_C;
		}
	}

	virtual void Deposit(int money){
	  NormalAccount::Deposit(money);
	  BankAccount::Deposit(money*creditRating/100);
  }
	virtual void ShowCustomerInfo() const{
  	NormalAccount::ShowCustomerInfo();
    if(creditRating==RANK_A){
      cout<<"신용이자율: RANK_A ("<<creditRating<<")"<<endl;
    }else if(creditRating==RANK_B){
      cout<<"신용이자율: RANK_B ("<<creditRating<<")"<<endl;
    }else{
      cout<<"신용이자율: RANK_C ("<<creditRating<<")"<<endl;
    }
  }
};

#endif