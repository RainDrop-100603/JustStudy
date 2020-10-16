//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Numb3rs_Input(int& dayPast,int& prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
  int townNum;
  cin>>townNum>>dayPast>>prison;
  townGraph=vector<vector<int>>(townNum,vector<int>(townNum));
  for(auto& ele:townGraph)
    for(auto& ele2:ele)
      scanf("%d",&ele2);
  int chkTownNum;
  cin>>chkTownNum;
  chkTown=vector<int>(chkTownNum);
  for(auto& ele:chkTown)
    scanf("%d",&ele);
}
double Numb3rs_DP(vector<vector<int>>& townGraph,vector<int>& degree,vector<vector<double>>& DP, int dayPast, int town){
  double& result=DP[dayPast][town];
  if(result>-0.5) return result;
  //substructrue, preTop=꼭대기 직전 블록의 갯수
  result=0;
  for(int preTown=0;preTown<townGraph.size();preTown++){
    if(townGraph[preTown][town])
      result+=Numb3rs_DP(townGraph,degree,DP,dayPast-1,preTown)/degree[preTown];
  }
  return result;
}
vector<double> Numb3rs_Algo(int dayPast,int prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
  /*
  2초, 64MB, 테스트케이스 50개
  마을의 수(n)2~50, 지난 일수(d) 1~100, 교도소 위치(마을 중 하나), 마을 이름=0~n-1,확률을 계산할 마을의 수(1~n)
  전략1
    Dynamic Programming
      func(지난 날짜, 마을)= 마을을 방문한 경우의 수
        substructure: for(town=0~n-1) func(dayPast,town)=for(preTown=인접마을 of town, from townGraph) sum(func(dayPast-1,preTown))
        기저: prison이 정해져 있으므로, prison인접 마을은 1, prison마을 및 비인접마을은 0으로 초기화,
        정답: 마지막 날짜, 마을의 경우의 수/전체 경우의 수
    Problem 
      경우의 수로 구하는것이 불가능하다.
    time complexity
      #func(nd)*func(n)+=O(d*n^2)
    mem complexity
      #DP_A(nd)=O(nd)
  전략2
    전략1과 같은데 경우의 수가 아닌 확률 계산
  */
  //DP 생성, degree[town]=town에서 갈 수 있는 마을의 경우의 수
  int townNum=townGraph.size();
  vector<vector<double>> DP(dayPast+1,vector<double>(townNum,-1));
  vector<int> degree(townNum);
  for(int i=0;i<townNum;i++){
    for(auto& ele:townGraph[i]){
      degree[i]+=ele;
    }
  }
  //기저 생성
  for(int i=0;i<townNum;i++){
    if(townGraph[prison][i]) DP[1][i]=(double)1/degree[prison];
    else DP[1][i]=0;
  }
  //정답 생성
  vector<double> result;
  for(auto& ele:chkTown)
    result.push_back(Numb3rs_DP(townGraph,degree,DP,dayPast,ele));
  return result;
}
void Numb3rs(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int dayPast,prison;
    vector<vector<int>> townGraph;
    vector<int> chkTown;
    Numb3rs_Input(dayPast,prison,townGraph,chkTown);
    for(auto& ele:Numb3rs_Algo(dayPast,prison,townGraph,chkTown))
      printf("%.8f ",ele);
    cout<<"\n";
  }
}

int main(void){
  Numb3rs();
  return 0;
}