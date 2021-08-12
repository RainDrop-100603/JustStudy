#ifndef __USEFUL_H__
#define __USEFUL_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

//"에라스토테네스의 채"와 bitmask를 이용한 prime 구하기 
bool useful_isPrime(vector<unsigned char>& eratosthenes, int num);  //비트가 켜져있는지 확인한다
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num); //비트를 끈다
vector<unsigned char> useful_eratosthenes(int num);

//순열과 조합
vector<vector<int>> useful_getPermutation(vector<int> set); //오름차순 순서 정렬
vector<vector<int>> useful_getCombination(vector<int> set, int select);  // setSize C select, 오름차순 순서 정렬

#endif