#ifndef __USEFUL_H__
#define __USEFUL_H__

#include <algorithm>
#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

//한칸 띄운것은, 직접적으로 사용할 일이 없는 것들

//"에라스토테네스의 채"와 bitmask를 이용한 prime 구하기
// num까지의 숫자들의 소수 여부를 구하고 싶다면, 에라스토테세의 채를 먼저 구한 후, isPrime(num,eratosthenes)함수를
// 이용한다. 소수를 단 한번만 구하면 된다면, isPrime(num)을 이용한다. (자동으로 eratosthenes를 구해준다.). 여러개의
// 소수를 확인할 때는 비효율적이다.
bool useful_isPrime(
    int num,
    const vector<unsigned char>& eratosthenes = {});  // num이 소수인지 확인한다. eratosthenes는 기본적으로 비워둔다.
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num);  //비트를 끈다
vector<unsigned char> useful_eratosthenes(int num);  // unsigned char 비트마스크를 이용한 에라스토테네스의 채

//순열과 조합
vector<vector<int>> useful_getPermutation(const vector<int> set);        //오름차순 순서 정렬
vector<vector<int>> useful_getCombination(vector<int> set, int select);  // setSize C select, 오름차순 순서 정렬

//문자열
vector<int> useful_KmpSearch(string& base, string& target);  // target이 base의 substr 이라면, 시작 idx를 모두 반환한다.
vector<int> useful_getFailure(string& str);  // str의 접두사와 접미사가 얼마나 겹치는지 반환, tomato는 to 2개가 겹치는
                                             // 것
vector<int> useful_getSuffixArr(
    string& str);  // str의 접미사들을 사전순으로 반환한다. arr[i] = i~end 접미사의 사전순 순위
struct useful_Comparator {
    const vector<int>& group;
    int t;
    useful_Comparator(const vector<int>& _group, int _t) : group(_group), t(_t) {}
    bool operator()(int a, int b) {
        if (group[a] != group[b]) {
            return group[a] < group[b];
        }
        return group[a + t] < group[b + t];
    }
};

#endif