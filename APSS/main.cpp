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
int ZIMBABWE_Algo(long long nowPrice,long long mFactor){
  long long result(0);
  //long long을 arr형식으로 변경 
  vector<int> arr_nowPrice;
  while(nowPrice!=0){
    arr_nowPrice.push_back(nowPrice%10);
    nowPrice/=10;
  }
  reverse(arr_nowPrice.begin(),arr_nowPrice.end());
  int len_nowPrice(arr_nowPrice.size());
  //Algo
  while(prev_permutation(arr_nowPrice.begin(),arr_nowPrice.end())){
    long long tmp_int_nowPrice(0);
    for(int i=0;i<len_nowPrice;i++){
      tmp_int_nowPrice+=static_cast<long long>(pow(10,i))*arr_nowPrice[i];
    }
    if(tmp_int_nowPrice%mFactor==0){
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
    결국 모든 경우에 대해 구해야 한다. 최대한 빠르게 모든 경우를 구하는 방법이 필요 
      case 1: e에서 시작하여, 다음으로 가장 큰 수를 구하는 함수를 이용한다.
        가장 마지막 수를 pivot, 해당 위치를 end, 처음으로 pivot보다 큰 수의 위치를 start라 하자
          a[start]와 a[end] 바꾼다.
          a[ent+1] ~ a[start-1]은 가장 큰 숫자가 앞으로 오도록 sorting
      case 2: 가장 작은 수에서 시작하여, e와 같아질 때 멈춘다. 
      case 3: mod는 덧셈이 가능함을 이용해 DP계산을 한다.
        DP가 성립하나? 그냥 mod를 쓰면 되는데?
      case 4: stack을 이용하면, 특정 숫자보다 작은 모든 숫자를 구할 수 있지 않을까?
      case 5: std: prev_permutation 이용


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