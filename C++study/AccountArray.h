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
  BankAccount*& operator[](int idx);  // &가 포함되지 않은 반환형은 "Value" 반환이다. 즉 임시변수가 반환된다는 것이다. 포인터의 값을 바꾸고 싶다면 "Reference" 반환을 해야한다.
  BankAccount* operator[](int idx) const;
};


#endif