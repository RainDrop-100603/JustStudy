//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Packing_Input(int& dayPast,int& prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
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
double Packing_DP(vector<vector<int>>& townGraph,vector<int>& degree,vector<vector<double>>& DP, int dayPast, int town){
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
vector<double> Packing_Algo(int dayPast,int prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
  /*
  2초, 64MB, 테스트케이스 50개
  입력:물건의 수(N)1~100, 캐리어의 용량(W)1~1000, N개의 물건을 이름,부피,절박도 순서로 각 줄에 주어짐, 이름:공백없는 알파벳 대소문자 1~20, 부피와절박도는 1~1000
  출력:첫 줄에는 최대 절박도 합과 가져갈 물건들의 개수 출력, 이후 한 줄마다 각 물건들의 이름을 출력, 조합이 여러개일 경우 하나만 출력한다.
  전략1
    Dynamic Programming
      func(이전에 선택한 물건, 남은 캐리어 용량)= 절박도의 합
        DP: size 100*1000, 물건은 순서대로만 선택 가능
        substructure: func(n,w)=for(i=n+1~N), max, func(i,w-i_weight)
        기저: W<1, n>N
        정답: 경로를 저장한 DP를 이용하여 출력
    time complexity
      #func(nw)*func(n)+=O(d*n^2)
    mem complexity
      #DP_A(nd)=O(nd)
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
void Packing(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int dayPast,prison;
    vector<vector<int>> townGraph;
    vector<int> chkTown;
    Packing_Input(dayPast,prison,townGraph,chkTown);
    for(auto& ele:Packing_Algo(dayPast,prison,townGraph,chkTown))
      printf("%.8f ",ele);
    cout<<"\n";
  }
}

int main(void){
  Packing();
  return 0;
}