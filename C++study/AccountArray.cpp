/*
 * Banking System Ver 0.8
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//AccountArray 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"
#include "AccountArray.h"

AccountArray::AccountArray(){
  accountArr=new BankAccount*[MAXACCOUNT];
}
AccountArray::~AccountArray(){
  delete accountArr;
}
BankAccount* AccountArray::operator[](int idx){
  return accountArr[idx];
}

// class AccountArray{
//   BankAccount** accountArr;
// private:
//   AccountArray();
//   ~AccountArray();
//   BankAccount* operator[](int idx);
// };
