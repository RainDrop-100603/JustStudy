//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void Poly_Input(int& block){
  cin>>block;
}
int Poly_DP(vector<vector<int>>& DP,int blockNum,int topNum){
  int& result=DP[blockNum][topNum];
  if(result!=-1) return result;
  //substructrue, preTop=꼭대기 직전 블록의 갯수
  result=0;
  for(int preTop=1;preTop<=blockNum-topNum;preTop++){
    result=(result+(topNum+preTop-1)*Poly_DP(DP,blockNum-topNum,preTop))%10000000;
  }
  return result;
}
int Poly_Algo(int block){
  /*
  1초, 64MB, 테스트케이스 50개
  사각형의 개수 1~100, mod 10,000,000
  전략1
    Dynamic Programming
      func(사용한 정사각형의 개수, 높이), x는 가장 위에 쌓을 개수
        substructure: for(height=1~n) func(n,height)= for(x=1~n-height+1) sum(x*func(n-x,height-1))
        기저: func(i.i)=1;func(i,1)=1;
        정답: for(i=1~n) sum(func(n,i))
    Problem
      top*func(...)가 아니고, (top+직전 높이의 가로 개수-1)*func(...)이다.
    time complexity
      #func(n^2)*func(n)+=O(n^3)
    mem complexity
      #DP_A(n^2)=O(n^2)
  전략2
    Dynamic Programming
      func(사용한 정사각형의 개수, 가장 높은 위치(top)의 블록갯수)
        substructure: for(topNum=1~n) func(n,topNum)=for(x=1~n-topNum) sum((topNum+x-1)*func(n-topNum,x))
        기저: func(i,i)=1;
        정답: for(i=1~n) sum(func(n,i))
    time complexity
      #func(n^2)*func(n)+=O(n^3)
    mem complexity
      #DP_A(n^2)=O(n^2)
  */
  //DP 생성 및 계산
  vector<vector<int>> DP(block+1,vector<int>(block+1,-1));
  //기저
  for(int i=1;i<=block;i++){
    DP[i][i]=1;
  } 
  int result=0;
  for(int i=1;i<=block;i++)
    result+=Poly_DP(DP,block,i);
  return result%10000000;
}
void Poly(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int block;
    Poly_Input(block);
    cout<<Poly_Algo(block)<<'\n';
  }
}

int main(void){
  Poly();
  return 0;
}