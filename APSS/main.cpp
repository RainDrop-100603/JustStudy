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

// Decision Problem, 재귀를 이용함, while문을 이용하여 재귀를 대신할 수 있음, input 방식 유의  
void WITHDRAWL_Input(int& cityNum,int& order,vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap){
  cin>>cityNum>>order;
  cityLoc.resize(cityNum);signBegin.resize(cityNum);signGap.resize(cityNum);
  cin.ignore();// \n 제거
  for(int i=0;i<cityNum;i++){
    string tmp;
    size_t idx;
    getline(cin,tmp);
    cityLoc[i]=stoi(tmp,&idx);tmp=tmp.substr(idx);
    signBegin[i]=stoi(tmp,&idx);tmp=tmp.substr(idx);
    signGap[i]=stoi(tmp,&idx);
  }
}
int WITHDRAWL_func(int order, vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap, int left, int right){
  //(left,right], right는 항상 count>=order
  //기저
  if(left+1==right){
    return right;
  }
  //조건
  int mid((left+right)/2);
  long long count(0);
  for(int i=0;i<cityLoc.size();i++){
    int start=cityLoc[i]-signBegin[i];
    if(mid>=start){
      count+=(min(mid,cityLoc[i])-start)/signGap[i]+1;
    }
  }
  //재귀
  if(count>=order){
    right=mid;
  }else{
    left=mid;
  }
  return WITHDRAWL_func(order,cityLoc,signBegin,signGap,left,right);
}
int WITHDRAWL_Algo(int cityNum,int order,vector<int> cityLoc,vector<int> signBegin,vector<int> signGap){
  //Algo, (min,max] 
  int result=WITHDRAWL_func(order,cityLoc,signBegin,signGap,0,8030000);
  //return
  return result;
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

  */
  /*전략
  전략1
    Decision Problem
    접근방법
      재귀함수: (min, max] (lgn 반복, n수행시간)
        기저: min+1==max -> ret max
        조건: 어느 위치 x: (min+max)/2 의 표지판의 개수가 k개 이상인가?
          구현: (n)
            표지판시작위치(Li-Mi)가 x이하인 도시 k개 선택
              sum(i=0~k-1): min((x-Li+Mi)/Gi,Mi/Gi)
          참: return 재귀함수(left,mid)
          거짓: return 재귀함수(mid,right)
    시간:
      O(nlgn)
    크기:
      O(n)
    개선 및 보완
      input2가 input보다 빠르다.
      전략1은 이분법에 대해 재귀를 하였고, 책은 while문을 이용하여 재귀를 대신했다.(while min+1<max)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int cityNum,order;
    vector<int> cityLoc,signBegin,signGap;
    WITHDRAWL_Input(cityNum,order,cityLoc,signBegin,signGap);
    auto result=WITHDRAWL_Algo(cityNum,order,cityLoc,signBegin,signGap);
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