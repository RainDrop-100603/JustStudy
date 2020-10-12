//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void AsymTiling_Input(int& tileLen){
  cin>>tileLen;
}
int AsymTiling_DP(vector<int>& DP,int tileLen){
  int& result=DP[tileLen];
  if(result!=0) return result;
  return result=(AsymTiling_DP(DP,tileLen-1)+AsymTiling_DP(DP,tileLen-2))%1000000007;
}
int AsymTiling_Algo(int tileLen){
  /*
  1초, 64MB, 테스트케이스 50개
  사각형의 너비 1~100, mod 1,000,000,007
  전략1
    Dynamic Programming
      모든 사각형의 수 - 대칭인 사각형의 수
      뺄셈에서 mod는 항등이다(음수일경우 mod를 더해준다.)
      모든 사각형
        substructure: func(len)=func(len-1)+func(len-2)
        기저: if len<=1, return 1; -> DP[0], DP[1]을 1로 미리 정하면 됨
      대칭 사각형
        if(len%2==1) func2(len)=func(len/2)
        if(len%2==0) func2(len)=func(len/2)+func(len/2-1)
    time complexity
      #func(n)*func(1)+#func2(1)*func2(1)=O(n)
    mem complexity
      #DP_A(n)=O(n)
  */
  //모든 사각형의 경우의 수
  vector<int> DP(tileLen+1);DP[0]=1;DP[1]=1;
  int result=AsymTiling_DP(DP,tileLen);
  //정답
  int modValue=1000000007;
  if(tileLen%2==0)
    result=(result-(DP[tileLen/2]+DP[tileLen/2-1])%modValue+modValue)%modValue;
  else
    result=(result-DP[tileLen/2]+modValue)%modValue;
  return result;
}
void AsymTiling(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int tileLen;
    AsymTiling_Input(tileLen);
    cout<<AsymTiling_Algo(tileLen)<<'\n';
  }
}

int main(void){
  AsymTiling();
  return 0;
}
