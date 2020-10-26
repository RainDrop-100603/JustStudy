//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Packing_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp){
  int itemNum;
  cin>>itemNum>>weight;
  itemName=vector<string>(itemNum+1);
  itemWeight=vector<int>(itemNum+1);
  itemDesp=vector<int>(itemNum+1);
  for(int i=1;i<=itemNum;i++){
    cin>>itemName[i]>>itemWeight[i]>>itemDesp[i];
  }
}
int Packing_DP(vector<vector<int>>& DP_desp,vector<vector<int>>& DP_choice,vector<int>& itemWeight,vector<int>& itemDesp,int prevChoice,int weightRemain){
  //기저, weightRemain<1, prevChoice==N
  if(weightRemain<0) return -987654321;
  if(prevChoice==itemWeight.size()-1) return 0;
  int& result=DP_desp[prevChoice][weightRemain];
  if(result!=-1) return result;
  //substructrue
  result=0;
  int& nextPick=DP_choice[prevChoice][weightRemain];
  int tmp;
  for(int nextChoice=prevChoice+1;nextChoice<DP_desp.size();nextChoice++){
    tmp=itemDesp[nextChoice]+Packing_DP(DP_desp,DP_choice,itemWeight,itemDesp,nextChoice,weightRemain-itemWeight[nextChoice]);
    if(tmp>result){
      nextPick=nextChoice;
      result=tmp;
    }
  }
  return result;
}
vector<int> Packing_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp){
  /*
  2초, 64MB, 테스트케이스 50개
  입력:물건의 수(N)1~100, 캐리어의 용량(W)1~1000, N개의 물건을 이름,부피,절박도 순서로 각 줄에 주어짐, 이름:공백없는 알파벳 대소문자 1~20, 부피와절박도는 1~1000
  출력:첫 줄에는 최대 절박도 합과 가져갈 물건들의 개수 출력, 이후 한 줄마다 각 물건들의 이름을 출력, 조합이 여러개일 경우 하나만 출력한다.
  전략1
    Dynamic Programming
      func(직전에 선택한 물건, 남은 캐리어 용량)= 절박도의 합
        DP: size 100*1000, 물건은 순서대로만 선택 가능
        substructure: func(prevChoice,weightRemain)=for(i=prevChoice+1~N), max, func(i,weightRemain-i_weight)
        기저: weightRemain<1, prevChoice=N
        정답: 경로를 저장한 DP를 이용하여 출력
    time complexity
      #func(NW)*func(N)+=O(N^2*W)
    mem complexity
      #DP(NW)=O(NW)
  */
  //DP 생성
  int itemNum=itemWeight.size()-1;
  vector<vector<int>> DP_desp(itemNum+1,vector<int>(weight+1,-1));
  vector<vector<int>> DP_choice=DP_desp;
  //DP 채우기
  int tmp=Packing_DP(DP_desp,DP_choice,itemWeight,itemDesp,0,weight);
  //정답 생성
  vector<int> result;
  result.push_back(tmp);
  int nextPick=DP_choice[0][weight];
  while(nextPick!=-1){
    result.push_back(nextPick);
    nextPick=DP_choice[nextPick][weight-itemWeight[nextPick]];
  }
  return result;
}
void Packing(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int weight;
    vector<string> itemName;
    vector<int> itemWeight,itemDesp;
    Packing_Input(weight,itemName,itemWeight,itemDesp);
    vector<int> result=Packing_Algo(weight,itemWeight,itemDesp);
    cout<<result.front()<<' '<<result.size()-1<<'\n';
    for(auto iter=++result.begin();iter<result.end();iter++){
      cout<<itemName[*iter]<<'\n';
    }
  }
}

int main(void){
  Packing();
  return 0;
}