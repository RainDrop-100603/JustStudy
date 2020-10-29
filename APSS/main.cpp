//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Ocr_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp){
  int itemNum;
  cin>>itemNum>>weight;
  itemName=vector<string>(itemNum);
  itemWeight=itemDesp=vector<int>(itemNum);
  for(int i=0;i<itemNum;i++)
    cin>>itemName[i]>>itemWeight[i]>>itemDesp[i];
}
int Ocr_DP(vector<vector<int>>& DP_desp,vector<int>& itemWeight,vector<int>& itemDesp,int nowChoice,int weightRemain){
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
vector<int> Ocr_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp){
  /*
  10초, 64MB, 테스트케이스 50개
  입력: 분석이 끝난 과거 자료의 통계치, 분류기가 인식한 문장으로구성, 자세한 내용은 문제에서 확인
  출력: 한 뭉장마다 한 줄에 주어진 인식 결과에 대해 조건주 출현 확률이 가장 높은 문장을 출력, 같은 확률을 가진 문장이 여러개라면 어떤것을 출력해도 좋다.
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
void Ocr(){
  int wordNum,sentenceNum;
  vector<string> sentenceArr;
  vector<int> firstPoten
  vector<string> itemName;
  vector<int> itemWeight,itemDesp;
  Ocr_Input(weight,itemName,itemWeight,itemDesp);
  vector<int> result=Ocr_Algo(weight,itemWeight,itemDesp);
  cout<<result.front()<<' '<<result.size()-1<<'\n';
  for(auto iter=++result.begin();iter!=result.end();iter++){
    cout<<itemName[*iter]<<'\n';
  }
}

int main(void){
  Ocr();
  return 0;
}