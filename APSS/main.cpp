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

// KMP search 변형문제, circular shift
void JAEHASAFE_Input(vector<string>& config){
  int configNum;
  cin>>configNum;
  config.resize(configNum+1);
  for(auto& ele: config){
    cin>>ele;
  }
}
vector<int> JAEHASAFE_getFailure(const string& str){
  vector<int> result(str.length()+1,0);
  int match=0;
  for(int idx=1;idx<str.length();idx++){
    while(match>0&&str[idx]!=str[match]){
      match=result[match];
    }
    if(str[idx]==str[match]){
      match++;
      result[idx+1]=match;
    }
  }
  return result;
}
int JAEHASAFE_KmpSearch(const string& base, const string& target){
  vector<int> failure=JAEHASAFE_getFailure(target);
  int match=0,strLen=base.length();
  for(int idx=0;idx<strLen*2-1;idx++){
    while(match>0&&base[idx%strLen]!=target[match]){
      match=failure[match];
    }
    if(base[idx%strLen]==target[match]){
      match++;
      if(match==strLen){
        return idx-match+1;
      }
    }
  }
}
int JAEHASAFE_Algo(const vector<string>& config){
  int result(0),strLen(config[0].length()); //strlen==금고의 알파벳 개수 
  for(int i=0;i<config.size()-1;i++){
    if(i%2){  
      result+=JAEHASAFE_KmpSearch(config[i],config[i+1]); //ccw
    }else{
      result+=JAEHASAFE_KmpSearch(config[i+1],config[i]); //clockwise
    }
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
    KMP search를 이용하여 시작위치를 찾을 수 있다.
      circular shift: 
        다이얼의 일치상태를 비교하려면 항상 n개(다이얼의 원소의 수)를 비교해야한다.
          KMP search에서 idx를 두배로 늘리고, 넘어가는 부분은 mod 처리한다.
      시계 방향으로 돌리는것은 KMPresult.front()번 회전
      반시계 방향은 n - KMPresult.back()번 회전
  */
  /*전략
  전략1
    아이디어: KMP search
      KMP search를 M번 수행하여 시작위치를 찾는다. M * O(2N)
        항상 N개를 비교해야하므로, idx를 넘어가는 부분은 mod 처리한다.
        시계방향: KMP result . front
        반시계방향: N - KMP result . back
      
    분석
      time complexity: O(MN) <= 50 * 2 * 10000 
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
    vector<string> config;
    JAEHASAFE_Input(config);
    auto result=JAEHASAFE_Algo(config);
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

