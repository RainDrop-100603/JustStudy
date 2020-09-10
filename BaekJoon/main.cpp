#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>

#include "GoodFunction.h"

using namespace std;

void BK11723(){  // 비트마스크
  /*
  비트마스크 : 원소를 비트 단위로 표현한다.
    {0,1,2,3,4} 라는 집합이 있다고 하자.
      {0,1,2}라는 부분집합을 나타내고 싶을 때, int 3개를 이용하여 표현하는 대신 간단하게 11100으로 표현할 수 있다.
        집합의 원소의 개수가 n개라면, 직접적인 표현은 n*int의 크기가 필요하지만 비트마스크는 (1+(n-1)/32) *int의 크기만 이용한다.
    and(&),or(|),xor(^),not(~),shift(>>,<<)
  */
//input
  int M;
  cin>>M; // #연산
  cin.get();  //or cin.ignore(): 개행문자 처리
//prepare
  int S(0); //비트마스크로 표현한 집합, 1~20
  string s;
  int num;
//calc
  while(M--){
    getline(cin,s);
    switch(s[1]){
      case 'd':
        num=stoi(s.substr(4));
        S|=(1<<num);
        break;
      case 'e':
        num=stoi(s.substr(7));
        S&=~(1<<num);
        break;
      case 'h':
        num=stoi(s.substr(6));
        cout<<((S&1<<num)>>num)<<"\n";
        break;
      case 'o':
        num=stoi(s.substr(7));
        S^=(1<<num);
        break;
      case 'l':
        S=(1<<21)-1;
        break;
      case 'm':
        S=0;
        break;
    }
  }
//output
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK11723();
  return 0;
}