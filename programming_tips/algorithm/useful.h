#ifndef __USEFUL_H__
#define __USEFUL_H__

#include <iostream>
#include <vector>

using namespace std;

//"에라스토테네스의 채"를 이용한 prime 구하기 
bool useful_isPrime(vector<unsigned char>& eratosthenes, int num);
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num);
vector<unsigned char> useful_eratosthenes(int num);

#endif