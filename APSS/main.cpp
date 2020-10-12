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
int Poly_DP(vector<vector<int>>& DP,int blockNum,int height){
  int& result=DP[blockNum][height];
  if(result!=-1) return result;
  //substructrue, top=꼭대기에 쌓은 블록의 갯수
  //모드값*곱셈이라 문제가 생김. 
  result=0;
  for(int top=1;top<=blockNum-height+1;top++){
    result=(result+top*Poly_DP(DP,blockNum-top,height-1))%10000000;
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
        기저: func(i.i)=1;
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
    DP[i][1]=1;
  } 
  int result=0;
  for(int i=1;i<=block;i++)
    result+=Poly_DP(DP,block,i);
  return result;
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
