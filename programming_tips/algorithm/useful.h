#ifndef __USEFUL_H__
#define __USEFUL_H__

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

//"에라스토테네스의 채"와 bitmask를 이용한 prime 구하기 
bool useful_isPrime(vector<unsigned char>& eratosthenes, int num);  //비트가 켜져있는지 확인한다
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num); //비트를 끈다
vector<unsigned char> useful_eratosthenes(int num);

#endif