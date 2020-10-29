//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Ocr_Input(int& wordNum,int& sentenceNum,vector<string>& wordArr,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
  cin>>wordNum>>sentenceNum;
  wordArr.resize(wordNum);
  for(auto& ele:wordArr)
    cin>>ele;
  firstPoss.resize(wordNum);
  for(auto& ele: firstPoss)
    scanf("%lf",&ele);
  nextPoss=classifiPoss=vector<vector<double>>(wordNum,vector<double>(wordNum));
  for(auto& ele: nextPoss)
    for(auto& ele2: ele)
      scanf("%lf",&ele2);
  for(auto& ele: classifiPoss)
    for(auto& ele2: ele)
      scanf("%lf",&ele2);
  sentenceArr.resize(sentenceNum);
  cin.ignore();
  for(auto& ele: sentenceArr)
    getline(cin,ele);
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
vector<string> Ocr_Algo(int& wordNum,int& sentenceNum,vector<string>& wordArr,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
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
  vector<string> wordArr,sentenceArr;   //i, am, a, boy, buy 각 단어 저장, i am a boy 각 문장 저장
  vector<double> firstPoss;    //맨 처음에 각 word가 나올 확률
  vector<vector<double>> nextPoss,classifiPoss; //A(ij)=i단어 다음 j단어가 나올 확률, B(ij)=i단어를 j단어로 분류할 확률
  Ocr_Input(wordNum,sentenceNum,wordArr,firstPoss,nextPoss,classifiPoss,sentenceArr);
  vector<string> result=Ocr_Algo(wordNum,sentenceNum,wordArr,firstPoss,nextPoss,classifiPoss,sentenceArr);
  for(auto& ele:result){
    cout<<ele<<'\n';
  }
}

int main(void){
  Ocr();
  return 0;
}