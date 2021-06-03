//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

// Decision Problem, 이분법, 문제가 안풀리면 수식을 작성해보자 
void WITHDRAWL_Input(int& classNum,int& requiredNum,vector<int>& order,vector<int>& students){
  cin>>classNum>>requiredNum;
  order.resize(classNum);
  students.resize(classNum);
  for(int i=0;i<classNum;i++){
    cin>>order[i]>>students[i];
  }
}
bool WITHDRAWL_decision(int classNum,int requiredNum,vector<int>& order,vector<int>& students, double left, double right){
  double mid=(left+right)/2;
  vector<double> arr;
  // x*분모-분자를 구하기
  for(int i=0;i<classNum;i++){
    arr.push_back(mid*students[i]-order[i]);
  }
  //오름차순 정렬
  sort(arr.begin(),arr.end());
  reverse(arr.begin(),arr.end());
  //requiredNum만큼 넣었을 때 0보다 큰가? (오름차순 정렬이므로 required만큼만 넣으면 된다)
  double sum(0);
  for(int i=0;i<requiredNum;i++){
    sum+=arr[i];
  }
  //sum이 0보다 크거나 같으면 참
  return sum>=0;
}
double WITHDRAWL_Algo(int classNum,int requiredNum,vector<int> order,vector<int> students){
  double left(0),right(1);
  int count=100;
  //Algo, (min,max] 
  while(count--){
    if(WITHDRAWL_decision(classNum,requiredNum,order,students,left,right)){
      right=(left+right)/2;
    }else{
      left=(left+right)/2;
    }
  }
  //return
  return right;
}
void WITHDRAWL(){
  // WITHDRAWL
  /*설명 및 입력
  설명
    백준이네 학교에서는 장학금을 학생의 중간고사 등수와 기말고사 등수에 따라 배정합니다. 
      어떤 학생이 듣는 i번째 과목의 수강생 수가 ci라고 합시다. 
      그리고 이 학생의 i번째 과목 중간 고사 등수가 ri라고 하면, 이 학생의 중간 고사 누적 등수 cumulativeRank 는 다음과 같이 정의됩니다.
      cumulativeRank = sum(ri) / sum(ci)
    수강 철회를 하면 철회한 과목은 중간 고사의 누적 등수 계산에 들어가지 않게 됩니다. 
      다행히 백준이네 학교에서는 수강 철회를 해도 남은 과목이 k 개 이상이라면 장학금을 받을 수 있습니다. 
    백준이가 적절히 과목을 철회했을 때 얻을 수 있는 최소 누적 등수를 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 백준이가 수강하는 과목의 수 n(1 <= n <= 1,000)과 남겨둬야 할 과목의 수 k(1 <= k <= n)가 주어집니다. 
    다음 줄에는 n 개의 정수 쌍 (ri,ci) 이 순서대로 주어집니다. (1 <= ri <= ci <= 1,000)
  출력
    각 줄마다 백준이가 얻을 수 있는 최소의 누적 등수를 출력합니다. 정답과 10-7 이하의 오차가 있는 답은 정답으로 인정됩니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    k개이상의 과목을 선택했을 때, 누적등수의 최솟값을 찾는 문제
    누적 점수가 X일 때, X>Y를 추가하면 X는 작아진다.
      Y1>Y2 이지만, 수강생(Y2)>>수강생(Y1)일때, Y1을 추가한게 더 작을때도 있다
        -> greedy하게 풀 수는 없다.
    k+1개로 k개보다 낮은 점수를 만들 수 있을까? -> 잘 모르니까 일단 생략 
    Decision Problem: k개이상의 과목으로 X점 이하를 만들 수 있는가?
    조합을 생각해보자
      n개중 r래를 선택하여 최저값을 구한다고 하자.
        특정한 법칙을 구하지 못하는 한, nCr번 비교를 해야할 것이다.
        nCr=(n!/(n-r)!)/r!, 상당한 시간이 걸린다.
      Decision Problem 단원의 문제이다.
        현재 값에서, x를 넣으면 정해진 값 y 이하인가? 
    *@*@*@ 책 참고
      직관적으로 풀리지 않을 땐 수식을 작성해보자
      Decision(x)= sum(분모)/sum(분자)<=x
        0<=sum(x*분자-분모)
        즉, x*분자-분모를 정렬하고, 큰 값부터 차례로 더해서 0이상이 나오면 된다.
  */
  /*전략
  전략1
    Decision Problem
    접근방법
      재귀함수: (min, max] (100 반복, nlgn수행시간)
        기저: 반복 100회 -> return max
        조건: 시험점수가 x이하가 나올 수 있는가?
          구현: (nlgn)
            sum(분모)/sum(분자)<=x, 0<=sum(x*분자-분모)
            x*분자-분모 를 정렬한 후, 큰 값부터 더한다.
          참: return 재귀함수(left,mid)
          거짓: return 재귀함수(mid,right)
    시간:
      O(100*nlgn)
    크기:
      O(n)
    개선 및 보완
      책을 참고하였다.
      문제가 직관적으로 풀리지 않으면 수식을 작성하여 풀어보자 
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int classNum,requiredNum;
    vector<int> order,students;
    WITHDRAWL_Input(classNum,requiredNum,order,students);
    auto result=WITHDRAWL_Algo(classNum,requiredNum,order,students);
    cout<<fixed;
    cout.precision(10);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 WITHDRAWL();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}