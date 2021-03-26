//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @* algo와 algo2의 속도차이에 유의하자(하드웨어적 원인). 속도가 느린 장치에 자주 접근할수록, 속도는 느려진다.
void SUSHI_Input(vector<pair<int,int>>& menu, int& budget){
  int menuLen;
  cin>>menuLen>>budget;
  menu.resize(menuLen);
  for(auto& ele: menu){
    cin>>ele.first>>ele.second;
  }
}
int SUSHI_Algo2(vector<pair<int,int>> menu,int budget){
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
      if(cost>=ele.first){
        cand=max(cand,tmp_cache[(cost-ele.first)%201]+ele.second);
      }
    }
    tmp_cache[cost%201]=cand;
  }
  //result
  int result=0;
  for(auto& ele:tmp_cache){
    result=max(result,ele);
  }
  return result;
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
    if(tmp_cache[cost%201]!=0){
      for(auto& ele:menu){
        if(cost+ele.first<=budget){
          int& value=tmp_cache[(cost+ele.first)%201];
          value=max(value,tmp_cache[cost%201]+ele.second);
        }
      }
    }
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
    sol 유의사항
      algo2가 왜 algo보다 빠를까?
        우선 tmp_cache[]!=0 부분, 배열이 비어있는지 확인하는 부분은 매우 제한적으로 유효하다.(항상 비어있는 부분이 있을때만 유효)
          이 부분을 제거하여도 보편적인 속도에는 큰 차이가 없음을 확인할 수 있다.
        그렇다면 두 algorithm의 구조적차이에서 속도의 차이가 발생함을 알 수 있다.
          algo: tmp_cache[now]에서 tmp_cache[now+cost]부분을 수정한다.
          algo2: tmp_cache[now]부분을 수정하며, tmp_cache[now-cost]에서 값을 불러온다.  
          두 알고리즘 모두 캐시 호출 횟수에서는 차이가 없음을 알 수 있다.
          두 알고리즘 모두 불러오는 캐시의 위치의 분포가 같다(+cost냐 -cost냐 차이이므로 당연히 같다)
          algo의 경우 반복문 호출마다 참조형태로 값을 불러오는데 이는 속도에 큰 영향을 끼치지는 않는다(algo2를 유사한 형식으로 바꿔도 속도차이 x)
          남은 차이는, max함수를 여러 부분에 적용하는지, 한 부분에 적용하는지의 차이다.
            algo2는 tmp_cache[now]에만 max를 적용하면 된다.
            algo는 tmp_cache[now+each cost], 각각의 cost에 대해 max를 적용해야 한다.
            algo는 한번의 6개의 위치를 수정하고, algo2는 한번의 1개의 위치를 수정한다.
              하드웨어적인 특성에서 기인했다고 본다.
          하드웨어적인 특성 
            cpu는 cache에서 계산하여 비교적 속도가 느린 mem 혹은 hdd에 저장한다.
            algo와 algo2는 cache에서 계산하는 횟수는 동일하다
            그러나 algo2는 속도가 느린 저장장치에 1번 접근하는 반면
              algo는 속도가 느린 저장장치에 n번(음식의 갯수)만큼 접근하여 저장해야한다.
            속도의 느린 저장장치에 접근하는 횟수가 많아져, 시간에 더 오래걸린 것이다. 
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