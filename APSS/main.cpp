//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void Packing_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp){
  int itemNum;
  cin>>itemNum>>weight;
  itemName=vector<string>(itemNum);
  itemWeight=itemDesp=vector<int>(itemNum);
  for(int i=0;i<itemNum;i++)
    cin>>itemName[i]>>itemWeight[i]>>itemDesp[i];
}
int Packing_DP(vector<vector<int>>& DP_desp,vector<int>& itemWeight,vector<int>& itemDesp,int nowChoice,int weightRemain){
  //기저, nowChoice==N
  if(nowChoice==itemDesp.size()) return 0;
  int& result=DP_desp[nowChoice][weightRemain];
  if(result!=-1) return result;
  //substructrue, 선택하지 않았을경우, 선택했을경우
  result=Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain);
  if(weightRemain>=itemWeight[nowChoice])
    result=max(result,itemDesp[nowChoice]+Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain-itemWeight[nowChoice]));
  return result;
}
vector<int> Packing_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp){
  /*
  2초, 64MB, 테스트케이스 50개
  입력:물건의 수(N)1~100, 캐리어의 용량(W)1~1000, N개의 물건을 이름,부피,절박도 순서로 각 줄에 주어짐, 이름:공백없는 알파벳 대소문자 1~20, 부피와절박도는 1~1000
  출력:첫 줄에는 최대 절박도 합과 가져갈 물건들의 개수 출력, 이후 한 줄마다 각 물건들의 이름을 출력, 조합이 여러개일 경우 하나만 출력한다.
  제한: 절박도 최대=100*1000=100000
  전략1
    Dynamic Programming
      func(직전에 선택한 물건, 남은 캐리어 용량)= 절박도의 합
        DP: size 100*1000, 물건은 순서대로만 선택 가능
        substructure: func(nowChoice,weightRemain)=for(i=nowChoice+1~N), max, func(i,weightRemain-i_weight)
        기저: weightRemain<0
        정답: 경로를 저장한 DP를 이용하여 출력
    개선1
      func내부의 loop를 제거하여 수행시간을 줄인다.
      다음 물건을 선택하느냐/선택하지 않느냐로 구분
        func(이번에 선택할 물건, 남은 캐리어 용량)= 절박도의 합
        기저:이번에 선택할 물건==N
      선택지가 두개뿐이다 -> 이전 기록과 비교하여 선택이 됐는지 비교 가능, 기록 DP 삭제
    time complexity
      #func(NW)*func(1)+=O(NW)
    mem complexity
      #DP(NW)=O(NW)
  */
  //DP 생성
  vector<vector<int>> DP_desp(itemWeight.size(),vector<int>(weight+1,-1));
  //DP 채우기
  int tmp=Packing_DP(DP_desp,itemWeight,itemDesp,0,weight);
  //정답 생성
  vector<int> result;
  result.push_back(tmp);
  int nowPick(0),weightRemain(weight);
  while(nowPick<itemWeight.size()-1){
    //선택했다면, 절박도가 다를것이다.
    if(DP_desp[nowPick][weightRemain]!=DP_desp[nowPick+1][weightRemain]){
      result.push_back(nowPick);
      weightRemain-=itemWeight[nowPick];
    }
    nowPick++;
  }
  if(DP_desp[nowPick][weightRemain]>0)
    result.push_back(nowPick);
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
    for(auto iter=++result.begin();iter!=result.end();iter++){
      cout<<itemName[*iter]<<'\n';
    }
  }
}

int main(void){
  Ocr();
  return 0;
}