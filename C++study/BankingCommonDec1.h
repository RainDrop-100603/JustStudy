#ifndef __BANKINGCOMMONDEC1_H__
#define __BANKINGCOMMONDEC1_H__
/*
 * Banking System Ver 0.9
 * 작성자: rain
 * 내 용: 열혈 cpp OOP 단계별 프로젝트 
 */

//공통헤더 및 상수선언들

#include <iostream>
#include <cstring>

using namespace std;

namespace Constant{
	const int MAXACCOUNT=10;
	const int STRLENGTH=100;
	const int NAMELENGTH=100;
}

enum CreditRating {
	RANK_A = 7,
	RANK_B = 4,
	RANK_C = 2
};



#endif