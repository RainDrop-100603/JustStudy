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
#include <queue>

using namespace std;

// stack을 이용한 간단한 문제, unsigend int를 이용한 mod 처리
void NAMING_Input(int& target,int& length){
  cin>>target>>length;
}
int NAMING_Algo(int target,int length){
  //준비 및 초기화
  queue<int> q;
  int qSum(0),result(0);
  unsigned int num(1983);
  //순회
  for(int idx=0;idx<=length;idx++){
    int input=num%10000+1;
    q.push(input);
    qSum+=input;
    while(qSum>target){
      qSum-=q.front();
      q.pop();
    }
    if(qSum==target){
      result++;
    }
    num=num*214013 + 2531011;
  }
  return result;
} 
void NAMING(){
  /*설명 및 입력
  설명
    수환이는 외계에서 날아오는 전파를 연구하는 범세계 대규모 프로젝트, NAMING@home에 참가하고 있습니다. 
      외계에서 날아오는 전파는 전처리를 거쳐 각 숫자가 [1,10000] 범위 안에 들어가는 자연수 수열로 주어지는데, 
      이 전파가 과연 단순한 노이즈인지 아니면 의미 있는 패턴을 가지고 있는 것인지를 파악하고 싶습니다. 
    수환이는 전파의 부분 수열 중에 합이 K인 것이 유독 많다는 것을 눈치챘습니다. 
      부분 수열이란 연속된 수열의 일부를 말합니다. 
      예를 들어 수열 {1,4,2,1,4,3,1,6} 에서 합이 7 인 부분 수열은 모두 5개 있습니다. 
      {1,4,2} , {4,2,1} , {2,1,4}, {4,3}, {1,6} 이 부분 수열들은 서로 겹쳐도 된다는 데 유의합시다.
    K가 외계인에게 의미 있는 숫자일까요? 
      수환이의 가설을 확인하기 위해, 길이 N인 신호 기록이 주어질 때 합이 K인 부분 수열이 몇 개나 있는지 계산하는 프로그램을 작성하세요.
  입력
    입력의 크기가 큰 관계로, 이 문제에서는 신호 기록을 입력받는 대신 다음과 같은 식을 통해 프로그램 내에서 직접 생성합니다.
      A[0] = 1983
      A[i] = (A[i-1] * 214013 + 2531011) % 2^32
      이 때 i(1 <= i <= N)번째 입력 신호는 A[i-1] % 10000 + 1입니다. 
    문제의 해법은 입력을 생성하는 방식과는 아무 상관이 없습니다. 이 규칙에 따르면 첫 5개의 신호는 각각 1984, 8791, 4770, 7665, 3188입니다.
  출력
    입력 파일의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 20)가 주어지고, 그 후 C 줄에 각 2개의 정수로 K(1 <= K <= 5,000,000) 과 N(1 <= N <= 50,000,000) 이 주어집니다.
  제한조건
    15초, 64MB
  */
  /*힌트
    부분 수열은 연속되는 숫자이므로, 연속되는 숫자가 K를 넘으면 무의미하다.
    stack을 이용하여, stack내부의 숫자가 7 이하로 유지되도록 하면 된다.
    매번 stack내부의 숫자를 더하지 말고, stack내부의 합을 기록한 숫자를 이용하자(부분합 일부 채용)
    수열과 입력신호가 다름을 유의하자 
    mod 2^32는, 33비트 부터는 모두 잘라내는 것을 의미한다.
      이때 unsigned int는 32비트까지만 사용하므로, unsigned int를 사용하면 자동으로 mod 2^32를 취한 것과 같다.
  */
  /*전략
  전략1
    아이디어: 스택
      변수: queue, num(1983), queueSum(0), result(0)
      1. for( i = [0,N] )
        queue.push(num)
        queueSum+=num;
        while(queueSum>K){
          queueSum-=queue.front
          queue.pop
        }
        if(queueSum==K)
          result+=+
        num=number(idx,num);
    분석
      time complexity: O(N)
      mem complexity: O(N)
    피드백
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int target,length;
    NAMING_Input(target,length);
    auto result=NAMING_Algo(target,length);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

int main(void){
  //   clock_t start,end;
  //   start=clock();
  NAMING();
  //   end=clock();;
  //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

