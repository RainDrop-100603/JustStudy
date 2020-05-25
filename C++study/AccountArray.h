#ifndef __ACCOUNTARRAY_H__
#define __ACCOUNTARRAY_H__
/*
 * Banking System Ver 0.8
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//AccountArray 클래스의 선언과 정의

#include "BankingCommonDec1.h"
#include "BankAccount.h"

class AccountArray{
  BankAccount** accountArr;
public:
  AccountArray();
  ~AccountArray();
  BankAccount* operator[](int idx);
};


#endif