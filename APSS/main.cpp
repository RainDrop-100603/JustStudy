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

// Decision Problem, 이분법, 최초 lo, hi를 넉넉하게 결정하자
void LOAN_Input(double& loan,int& month,double& interest){
  cin>>loan>>month>>interest;
}
double LOAN_funcValue(double loan,int month,double interest, double pay){
  for(int i=0;i<month;i++){
    loan=loan*(1+interest/1200)-pay;
  }
  return loan;
}
double LOAN_Algo(double loan,int month,double interest){
  // f(lo) <= 0 < f(hi)
  double lo(loan*2),hi(0); 
  //이분법 100회 실행
  for(int i=0;i<100;i++){
    if(LOAN_funcValue(loan,month,interest,(lo+hi)/2)<=0){
      lo=(lo+hi)/2;
    }else{
      hi=(lo+hi)/2;
    }
  }
  //반환 
  return (lo+hi)/2;
}
void LOAN(){
  // LOAN
  /*설명 및 입력
  설명
    대출의 잔금은 대출 기간 동안 다음과 같이 변화합니다.
    ᆞ대출의 잔금은 대출 금액 N원에서 시작합니다.
    ᆞ한 달이 지날 때마다 대출 잔금이 월 이자 (P/12)% 만큼 불어납니다.
    ᆞ이자가 추가된 다음 월 상환액 C를 대출 잔금에서 제합니다.
    M개월 걸려 모든 대출 금액을 갚기 위해서는 한 달에 최소 얼마씩을 갚아야 할까요?
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T(<= 50)가 주어집니다. 
    각 테스트 케이스는 3개의 수 N, M, P(1 <= N <= 100,000,000, 1 <= M <= 120, 0 < P <= 50)으로 주어집니다. 
    N과 P는 실수이며, M은 정수입니다.
  출력
    각 테스트 케이스마다 한 줄에 한 달마다 상환할 금액 C를 출력합니다. 
    10-7 이하의 절대/상대 오차가 있는 답은 정답으로 인정됩니다.
  제한조건
    10초, 64MB
  */
  /*힌트
    A(n+1)=A(n)(1+P/12)-C, A(0)=N, A(M)=0
    수식으로 구하긴 까다로워보인다.
    금액 C를 찍고, m회 돌려보는 방식을 사용해보자
      C는 이분법을 통해 구할 수 있다.
        반복문 불변식: f(lo)<=0<f(hi)
        hi=0(상환불가), lo=2*loan(한달만에 값으려면 최대 1.5*loan, 넉넉하게 2배로 설정)
      전체 수행시간은 100(이분법)*m이므로 부담되지 않는다.
    
  */
  /*전략
  전략1
    이분법
    접근방법
      금액 C를 찍고, m회 돌려보는 방식을 사용해보자
        C는 이분법을 통해 구할 수 있다.
          반복문 불변식: f(lo)<=0<f(hi)
        전체 수행시간은 100(이분법)*m이므로 부담되지 않는다.
    시간:
      O(100*m);
    크기:
      O(n)
    개선 및 보완
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    double loan,interest;
    int month;
    LOAN_Input(loan,month,interest);
    auto result=LOAN_Algo(loan,month,interest);
    cout<<fixed;
    cout.precision(10);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 LOAN();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}