//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void Numb3rs_Input(int& townNum,int& dayPast,int& prison,vector<vector<int>>& townGraph,int& chkTownNum,vector<int>& chkTown){
  cin>>townNum>>dayPast>>prison;
  for(auto& ele:townGraph)
    for(auto& ele2:ele)
      scanf("%d",&ele2);
  cin>>chkTownNum;
  for(auto& ele:chkTown)
    scanf("%d",&ele);
}
int Numb3rs_DP(vector<vector<int>>& townGraph,vector<vector<int>>& DP, int dayPast, int town){
  int& result=DP[dayPast][town];
  if(result!=-1) return result;
  //substructrue, preTop=꼭대기 직전 블록의 갯수
  result=0;
  for(int preTop=1;preTop<=blockNum-topNum;preTop++){
    result=(result+(topNum+preTop-1)*Poly_DP(DP,blockNum-topNum,preTop))%10000000;
  }
  return result;
}
vector<double> Numb3rs_Algo(int townNum,int dayPast,int prison,vector<vector<int>>& townGraph,int chkTownNum,vector<int>& chkTown){
  /*
  2초, 64MB, 테스트케이스 50개
  마을의 수(N)2~50, 지난 일수 1~100, 교도소 위치(마을 중 하나), 마을 이름=0~N -1,확률을 계산할 마을의 수(1~N)
  전략1
    Dynamic Programming
      func(지난 날짜, 마을)= 마을을 방문한 경우의 수
        substructure: for(town=0~N-1) func(dayPast,town)=for(preTown=인접마을 of town, from townGraph) sum(func(dayPast-1,preTown))
        기저: prison이 정해져 있으므로, prison인접 마을은 1, prison마을 및 비인접마을은 0으로 초기화 
        정답: 마지막 날짜, 마을의 경우의 수/전체 경우의 수
    time complexity
      #func(n^2)*func(n)+=O(n^3)
    mem complexity
      #DP_A(n^2)=O(n^2)
  */
  //DP 생성
  vector<vector<int>> DP(dayPast+1,vector<int>(townNum,-1));
  //기저 생성
  for(int i=0;i<townNum;i++){
    if(townGraph[prison][i]) DP[1][i]=1;
    else DP[1][i]=0;
  }
  //DP 완성, sum= 마지막 날짜의 경우의 수 
  int sum=0;
  for(int i=0;i<townNum;i++)
    sum+=Numb3rs_DP(townGraph,DP,dayPast,i);
  //정답 생성
  vector<double> result;
  for(auto& ele:chkTown)
    result.push_back(static_cast<double>(DP[dayPast][ele])/sum);
  return result;
}
void Numb3rs(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int townNum,dayPast,prison,chkTownNum;
    vector<vector<int>> townGraph(townNum,vector<int>(townNum));
    vector<int> chkTown(chkTownNum);
    Numb3rs_Input(townNum,dayPast,prison,townGraph,chkTownNum,chkTown);
    for(auto& ele:Numb3rs_Algo(townNum,dayPast,prison,townGraph,chkTownNum,chkTown))
      printf("%.8f ",ele);
    cout<<"\n";
  }
}

int main(void){
  Numb3rs();
  return 0;
}