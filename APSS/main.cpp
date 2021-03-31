//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

//https://www.youtube.com/watch?v=x7STjpcKZP8 
//사회복무요원 교육 

// greedy, 증명부분에 더 신경쓰자
void LUNCHBOX_Input(int& number,vector<int>& warmTime,vector<int>& eatingTime){
  cin>>number;
  warmTime.resize(number);
  for(auto& ele: warmTime){
    cin>>ele;
  }
  eatingTime.resize(number);
  for(auto& ele: eatingTime){
    cin>>ele;
  }
}
int LUNCHBOX_Algo(int number,const vector<int>& warmTime,const vector<int>& eatingTime){
  //pair로 배열 만들고 정렬
  vector<pair<int,int>> food;
  for(int i=0;i<number;i++){
    food.push_back({warmTime[i],eatingTime[i]});
  }
  sort(food.begin(),food.end());
  //계산
  int result(0),enemyIdx(0);
  auto lowerValue=warmTime.begin();
  while(lowerValue!=warmTime.end()){
    lowerValue=lower_bound(lowerValue,warmTime.end(),eatingTime[enemyIdx]);
    if(lowerValue==warmTime.end()){
      break;
    }
    lowerValue++;
    result++;
    enemyIdx++;
  }
  return result;
}
void LUNCHBOX(){
  //LUNCHBOX
  /*설명 및 입력
  설명
    they provided different N lunch boxes. and put all lunch boxes to a refrigerator.
    Specifically, i-th lunch box needs Mi seconds to microwave and Ei seconds to eat.
    Ainu7 needs to schedule microwave usage order to minimize lunch time. 
    Lunch time is defined as the duration from the beginning of microwaving of any lunch box to the end of eating for all participants.
  입력
    The first line of the input contains one integer T, the number of test cases.
    Each test case consists of three lines. The first line of each test case contains N(1≤N≤10000), the number of the participants.
    N integers will follow on the second line. They represent M1, M2, ⋯, MN.
    Similarly, N integers will follow on the third line, representing E1, E2, ⋯, EN.
  출력
    For each test case, print the minimized lunch time in one line. It is guaranteed that the answer is always strictly less than 231.
  제한조건
    5초, 64MB
  */
  /*힌트
    번역
      N개의 도시락, 각각의 데우는 시간 M, 먹는시간 E
      데우기 시작인 이후, 다 먹으면 끝난다.
      최소시간을 구하라
    데우는 시간은 모두 동일하다
      데우면서 먹을수 있다.
      즉 데우는 시간은 절약이 불가하지만 ,먹는 시간은 절약이 가능하다.
      먼저 데울 음식은 오래먹는 음식, 나중에 데울 음식은 빨리 먹는 음식을 경우가 유리하다.
    먹는 시간이 긴 음식을 먼저 데우는것이 유리하다? -> greedy
      greedy choice property:
        정답 S에대해, 음식 f1의 데우기시작시간 m1, 먹는시간 e1, 데우는 시간 b1, f2에 대해서 m2,e2,b2 이때 m1<m2, e1<=e2, b1 ? b2
          greedy하게 선택한다면, m1에 f2를 선택하여 e2, m2에 f1을 선택하여 e1
        최소시간을 T라 하자
        f1과 f2의 데우는 시작시간을 바꾸어 보자 
          case 1: m1+e1+b1<T, m2+e2+b2<T 일 경우, m1+e2+b2<T (b/c m2+e2+b2<T, m1<m2), m2+(b2-b1)+e1+b1<T (b/c m2+e2+b2<T, e1<=e2)
          case 2: m1+e1+b1=T, m2+e2<T 일 경우, m1+e2<T, m2+e1<T
          case 3: m1+e1+b1<T, m2+e2=T 일 경우, m1+e2<T, m2+e2<T 
          case 4: m1+e1+b1=T, m2+e2=T 일 경우, m1+e2<T, m2+e1<=T
        즉 어느 경우에도 최대시간 T는 변함이 없으므로, greedy한 선택은 정답 중 하나이다.
      optimal substructure
        부분 영역에서 greedy한 choice는 최적값(최소시간)을 도출한다.(greedy choice property)
        부분 영역에서의 최적값의 합은 전체 영역에서의 최적값과 같다.
        부분 영역에서 greedy한 choice를 하는 것은, 전체 영역의 최적값을 도출한다.
  */
  /*전략
  전략1
    Greedy Algorithm
      음식 먹는 속도로 정렬 nlgn
      오래 걸리는 순서로 greedy n
        result=max(result,데우기 시작한 시간 + 해당 음식의 먹는 시간)
    시간:
      O(NlgN + N) 
    크기:
      O(N)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int number;
    vector<int> warmTime, eatingTime;
    LUNCHBOX_Input(number,warmTime,eatingTime);
    int result=LUNCHBOX_Algo(number,warmTime,eatingTime);
    cout<<result<<'\n';
  }
}

int main(void){
  LUNCHBOX();
  return 0;
}