//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @*@*@* 지나친 수학적 접근이 문제, 프로그래밍적으로 접근필요, overflow의 다양한 처리법, 함수내에서 한번에 하나의 행동만 
void ZIMBABWE_Input(long long& nowPrice,long long&  mFactor){
  cin>>nowPrice>>mFactor;
}
long long  ZIMBABWE_prevPrice(long long nowPrice){
  return nowPrice-1;
}
int ZIMBABWE_Algo(long long nowPrice,long long mFactor){
  long long result(0);
  while((nowPrice=ZIMBABWE_prevPrice(nowPrice))!=-1){
    if(nowPrice%mFactor==0){
      result++;
    }
  }
  return result%1000000007;
}
void ZIMBABWE(){
  //ZIMBABWE
  /*설명 및 입력
  설명
    계란을 사간 손님이 환불을 요청한다. 단, 가격은 모른다.
      가격표는 플라스틱 판으로 표현한다. 3500 은 3 5 0 0 4개로 표시하는 것이다.
      가격표의 플라스틱판 구성은 바뀌지 않았다. 계란가격이 오름에 따라 순서만 바뀌었다.
      손님의 계란은 m의 배수다.
    현재 계란가격 e와 m이 주어질 때, 손님의 구매했을때의 가격의 경우의 수를 구하라 
      이전 계란 가격은 e보다 항상 작다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 그 후 c줄에 각각 2개의 자연수 e와 m (1 <= e <= 10^14, 2 <= m <= 20)이 주어집니다. 
    현재 계란 가격은 0으로 시작하지 않지만, 이전 계란 가격은 0으로 시작할 수 있습니다.
      long long 범위로 해결 (10^14가 있으므로)
  출력
    경우의 수를 1,000,000,007 로 나눈 나머지를 출력하라 
  제한조건
    2초, 64MB
  */
  /*전략
    결국 모든 경우에 대해 구해야 한다.
      case 1: e에서 시작하여, 다음으로 가장 큰 수를 구하는 함수를 이용한다.
      case 2: 가장 작은 수에서 시작하여, e와 같아질 때 멈춘다. 


  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    long long nowPrice, mFactor;
    ZIMBABWE_Input(nowPrice, mFactor);
    int result=ZIMBABWE_Algo(nowPrice, mFactor);
    cout<<result<<'\n';
  }
}

int main(void){
  ZIMBABWE();
  
  return 0;
}