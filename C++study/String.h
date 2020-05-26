#ifndef __STRING_H__
#define __STRING_H__
/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//String Class 선언

#include "BankingCommonDec1.h"

class String{
	char* string;
  int len;
public:
	String();// String 배열 선언을 위해 필요 
	String(const char* str);
	String(const String& str);
	String& operator=(const String& str);
	~String();
	String operator+(const String& str) const;
	String& operator+=(const String& str);
	bool operator==(const String& str) const;
	friend ostream& operator<<(ostream& os,const String& str);
	friend istream& operator>>(istream& is,String& str);
};

#endif