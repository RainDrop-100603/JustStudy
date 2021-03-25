//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// memOver 대비 필요, 특정 조건을 만족하면 바로 ret하게 만들어 수행시간 향상 
void SUSHI_Input(vector<pair<int,int>>& menu, int& budget){
  int menuLen;
  cin>>menuLen>>budget;
  menu.resize(menuLen);
  for(auto& ele: menu){
    cin>>ele.first>>ele.second;
  }
}
int SUSHI_Algo(vector<pair<int,int>> menu,int budget){
  //budget과 menu 100 나누기, menu sort
  for(auto& ele:menu){
    ele.first/=100;
  }
  budget/=100;
  sort(menu.begin(),menu.end());
  //DP생성, 초기화
  vector<int> tmp_cache(201,0);
  for(auto& ele:menu){
    if(ele.first<=budget){
      tmp_cache[ele.first]=ele.second;
    }
  }
  //Algo
  for(int cost=0;cost<=budget;cost++){
    int cand=0;
    for(auto& ele: menu){
      if(cost>ele.first){
        cand=max(cand,tmp_cache[cost-ele.first]+ele.second);
      }
    }
    tmp_cache[cost]=cand;
  }
  //result
  int result=0;
  for(auto& ele:tmp_cache){
    result=max(result,ele);
  }
  return result;
}
void SUSHI(){
  //SUSHI
  /*설명 및 입력
  설명
    회전초밥집에는 n종류의 메뉴가 있는데, 운영진들은 각 메뉴에 대해 선호도를 매겼습니다.
    운영진들은 주어진 예산 안에서 선호도의 합을 최대한으로 하도록 초밥을 먹고 싶습니다. 
    각 종류의 초밥은 무한정으로 공급된다고 가정합시다. 이 때 얻을 수 있는 최대한의 선호도는 얼마일까요?
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c(1 <= c <= 50)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 초밥의 종류 n(1 <= n <= 20)과 운영진들의 예산 m (1 <= m <= 2,147,483,647)이 주어집니다. 
    그 후 n 줄에 각 초밥의 가격과 선호도가 순서대로 주어집니다. 가격은 20,000 이하의 자연수로, 항상 100 의 배수입니다. 선호도는 20 이하의 자연수입니다.
  출력
    각 테스트 케이스별로 한 줄에 가능한 선호도의 최대 합을 출력합니다.
  제한조건
    8초, 64MB
  */
  /*힌트
    예산이 1~int_max이지만, 금액은 항상 100의 배수다. 즉 DP이용시 cache의 크기를 100배 줄일 수 있다.
    가격은 항상 20000원 이하이다. 현재금액에서 20000원보다 낮은 금액은 이용하지 않으므로, sliding window기법으로 mem 절약이 가능하다.
      cost 오름차순으로 정렬해야 한다.
      위 두개를 이용하면, 0~200까지, 총 201만큼의 cache만으로 연산이 가능하다.
        0~199까지 할 경우, 200이 0에 저장되어 순서가 꼬이는 문제가 발생한다.
      작은단위에서 큰 단위로 계산해야한다. 0~budget
      마지막 정해진 금액을 초과할 경우, cache내부에서 가장 큰 값이 정답이다.
      if(DP[x] != 0) -> for(모든 음식 1~n) DP[x+cost] = max(DP[x+cost],DP[x] + value) 
  */
  /*전략
  전략1
    Dynamic Programing
      sliding window 기법을 사용한다.
      작은단위 -> 큰단위 DP
      금액과 예산은 모두 100으로 먼저 나눈뒤 사용한다.
      if(DP[x] != 0) -> for(모든 음식 1~n) DP[x+cost] = max(DP[x+cost],DP[x] + value) 
        cache 크기: 201
        연산시간: 20(메뉴의 갯수)
        연산횟수: 0~21474836 (int_max/100)
    시간:
      4억회
    크기:
      201 byte
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int budget;
    vector<pair<int,int>> menu; 
    SUSHI_Input(menu,budget);
    int result=SUSHI_Algo(menu,budget);
    cout<<result<<'\n';
  }
}

int main(void){
  SUSHI();
  return 0;
}