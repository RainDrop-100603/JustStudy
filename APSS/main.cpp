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
int ZIMBABWE_DP(vector<vector<int>>& DP_ZIMBABWE, long long used_bitmask,int mfactor_remain){
  //주어진 원소들을 무작위로 정렬하여 만든수를, mod했을때의 분류 
  //기저
  int& result=DP_ZIMBABWE[used_bitmask][mfactor_remain];
  if(result!=-1){
    return result;
  }
  //Algo

}
int ZIMBABWE_func1(vector<vector<int>>& DP_ZIMBABWE,vector<int>& arr_element,vector<int>& arr_price, long long used_bitmask,int mfactor_remain){
  //Algo
  int result(0), order(arr_price.size()-1);
  long long chk_bitmask=1<<order;  //차수가 높은순, 즉 왼쪽부터 
  while(chk_bitmask!=0){  //if 0, all element chked
    if((chk_bitmask&used_bitmask)==0){  //0 means not used
      int ele_now(arr_price[order]);
      for(auto& ele:arr_element){
        if(ele==ele_now){
          break;
        }
      }
      result+=ZIMBABWE_func1(DP_ZIMBABWE,arr_element,arr_price,used_bitmask|chk_bitmask,mfactor_remain)
      break;
    }
    chk_bitmask>>1;
    order--;
  }
  return result;
}
int ZIMBABWE_Algo(long long nowPrice,long long mFactor){
  //arr_price(nowPrice를 배열로 변경), arr_element(원소들을 오름차순 정렬)
  vector<int> arr_price;
  while(nowPrice!=0){
    arr_price.push_back(nowPrice%10);
    nowPrice/=10;
  }
  reverse(arr_price.begin(),arr_price.end());
  vector<int> arr_element(arr_price);
  sort(arr_element.begin(),arr_element.end());
  //DP생성
  vector<vector<int>> DP_ZIMBABWE(1<<arr_element.size(),vector<int>(mFactor,-1));
  //결과 return
  return ZIMBABWE_func1(DP_ZIMBABWE,arr_element,arr_price,0,0);
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
  전략1
    결국 모든 경우에 대해 구해야 한다. 최대한 빠르게 모든 경우를 구하는 방법이 필요 
        정말 모든 경우에 대해 구해야 할까? 
      case 1: e에서 시작하여, 다음으로 가장 큰 수를 구하는 함수를 이용한다.
        가장 마지막 수를 pivot, 해당 위치를 end, 처음으로 pivot보다 큰 수의 위치를 start라 하자
          a[start]와 a[end] 바꾼다.
          a[ent+1] ~ a[start-1]은 가장 큰 숫자가 앞으로 오도록 sorting
      case 2: 가장 작은 수에서 시작하여, e와 같아질 때 멈춘다. 
      case 3: mod는 덧셈이 가능함을 이용해 DP계산을 한다.
        DP가 성립하나? 그냥 mod를 쓰면 되는데?
      case 4: stack을 이용하면, 특정 숫자보다 작은 모든 숫자를 구할 수 있지 않을까?
      case 5: std: prev_permutation 이용
  전략2 
    mod는 덧셈이 가능하다. 같은 mod를 가진 것들끼리 하나로 묶고, 한번에 연산하면 연산을 줄일 수 있다.
      길이가 x인 문자열의, 나머지가 y인 DP를 만들 수 있다.
        DP[x][y] = (DP[x-1][a] + static_cast<long long>(pow(10,x-1)*a))%mod , a=0~ mod -1. mod=modValue, DP[0][a]=0;
      근데 처음 가격보다 낮은 건 어떻게 계산하지?
        1.분리방법: 맨 앞자리가 처음과 같으면 수동으로 계산하고, 처음과 다르면(작으면) 첫 값을 고정하고 모든 경우 계산
          -> 99999876543210과 같은 경우, 최대 13!/4! ~= 2.6억회 


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