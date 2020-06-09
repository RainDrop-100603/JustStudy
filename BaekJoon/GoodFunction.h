#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>

using namespace std;

bool IsPrime(int num);  //소수(Prime Number) 판별
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array 반환 

#endif