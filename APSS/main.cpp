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
void JAEHASAFE_Input(int& target,int& length){
  cin>>target>>length;
}
int JAEHASAFE_Algo(int target,int length){
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
void JAEHASAFE(){
  /*설명 및 입력
  설명
    The safe uses a dial to lock the door, and on the rim of dial are drawn pictures of cute animals instead of numbers. 
      To open the safe, Jaeha mustb rotate the dial to reach certain positions, alternating direction each time.
    Jaeha wants to be careful, so he only rotates the dial one tick at a time.  
      Given a set of dial positions, calculate how many ticks Jaeha has to rotate the dial to open the safe.
  입력
    The input consists of T test cases. 
      The number of test cases T is given in the first line of the input.
    The first line of each test case will contain an integer N(1 ≤ N ≤ 50), the number of positions Jaeha needs to reach. 
    The next N + 1 lines will each contain a dial configuration. 
      A configuration is given by listing the pictures in clockwise order, starting from the topmost picture. 
      Each type of picture is denoted by an alphabet character, therefore each configuration is given as a string. 
      The first configuration shows the current dial. 
    Jaeha will rotate clockwise to reach the second configuration, rotate counterclockwise to reach the third, and so on.
    The number of pictures on a dial will not exceed 10,000.
    Two adjacent configurations given in the input will always be different. 
    It is always possible to open the safe
  출력
    Print exactly one line for each test case.
      The line should contain the minimum number of ticks required to open the safe
  제한조건
    1초, 64MB
  */
  /*힌트
    같은 동물이 나온다고 찾은것이 아니라, 모든 동물의 위차가 맞아야 한다.
      따라서 idx를 하나씩 돌리며 찾으면 10000 * 10000 * 50 이 걸려서 시간내에 찾을 수 없다.
    
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
    JAEHASAFE_Input(target,length);
    auto result=JAEHASAFE_Algo(target,length);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

int main(void){
  //   clock_t start,end;
  //   start=clock();
  JAEHASAFE();
  //   end=clock();;
  //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

