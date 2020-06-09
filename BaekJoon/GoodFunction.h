#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>

using namespace std;

bool IsPrime(int num);  //소수(Prime Number) 판별
bool* &GetPrimeTable(int num);  //[0,num) 범위의 Prime Number Table을 구한다. 0빼면 계산이 귀찮아서 그냥 넣었다. 미완성
vector<int> GetPrimeVector(int num);  //[0,num) 범위의 소수를 저장하는 vector<int>를 반환
int HowManyPrime(int num1, int num2, vector<int> &prime);// [num1,num2) 범위의 소수의 개수를 반환

#endif