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

// Decision Problem, 이분법, 자료형 유의
void RATIO_Input(int& playTime,int& winTime){
  cin>>playTime>>winTime;
}
bool RATIO_decision(long long playTime,long long winTime,long long addWin){
  long long totalPlay(playTime+addWin),totalWin(winTime+addWin);
  long long prevWinRate=winTime*100/playTime;
  long long newWinRate=totalWin*100/totalPlay;
  return newWinRate>prevWinRate;
}
int RATIO_Algo(int playTime,int winTime){
  // f(lo)=true, f(hi)=false;
  int lo(2000000000),hi(0); 
  //기저
  if(!RATIO_decision(playTime,winTime,lo)){
    return -1;
  }
  //이분법 100회 실행
  for(int i=0;i<100;i++){
    if(RATIO_decision(playTime,winTime,(lo+hi)/2)){
      lo=(lo+hi)/2;
    }else{
      hi=(lo+hi)/2;
    }
  }
  //반환 
  return lo;
}
void RATIO(){
  // RATIO
  /*설명 및 입력
  설명
    플레이 횟수 : N
    승리 횟수 : M(Z %)
    여기서 Z%의 경우 소수점을 제외한 부분의 승률이다. 즉, 승률이 88.68% 일 경우 Z = 88% 이다.
    N, M이 주어졌을 때, Z를 올리기 위한 최소한의 연승횟수가 필요한지 구하는 프로그램을 작성하라. 
    여기서 답이 되는 연승횟수는 2,000,000,000 이하라고 가정한다.
  입력
    입력의 첫번째 줄에는 테스트 케이스의 개수 T가 입력되고, 다음 줄 부터 한줄에 하나씩 T개의 테스트 케이스가 입력된다.
    테스트케이스는 두 개의 숫자로 이루어진다. 
    처음에 들어오는 숫자는 스파이더를 플레이를 한 횟수N(1<=N<=1,000,000,000)를 의미하며, 나중에 들어온 숫자는 승리한 횟수M(0<=M<=N)를 의미한다.
  출력
    각 테스트 케이스에 대해서 한줄에 승률을 올릴 수 있을 경우 이를 위한 최소한의 연승 수를 출력하며, 불가능할 경우 -1을 출력한다.
  제한조건
    10초, 64MB
  */
  /*힌트
    승률는 O(1)시간으로 구할 수 있다.
      몇번 승리해야 하는지 이분법으로 구하자
        hi=0, lo=2,000,000,000
        반복문 불변식: f(lo)=true, f(hi)=false
      기저: f(lo)의 승률이 증가하지 않는다면, 불가능하므로 -1 ret
    총 플레이횟수는 최대 30억회 이며, 확률계산시 100을 곱해야 하므로, decision연산에 유의 
  */
  /*전략
  전략1
    이분법 & decision problem
    접근방법
      C번 승리하면 승률이 증가하는지 결정하는 decision problem
        C는 이분법을 통해 구할 수 있다.
          반복문 불변식: f(lo)=true, f(hi)=false
        전체 수행시간은 100(이분법)*m이므로 부담되지 않는다.
    시간:
      O(100*m);
    크기:
      O(n)
    개선 및 보완
      static_cast<long long>을 해도 되지만 ,처음부터 전달인자를 long long으로 받아와도 된다.
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int playTime,winTime;
    RATIO_Input(playTime,winTime);
    auto result=RATIO_Algo(playTime,winTime);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 RATIO();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

