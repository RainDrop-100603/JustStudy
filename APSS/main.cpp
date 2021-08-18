//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

// @* 부분 합, greedy, 간단한 작업을 통해 mod k==0일 경우에도 동일하게 작동하도록 했다, scanf > cin > getline + substr
void CHRISTMAS_Input(int& childrenNum,int& boxNum,vector<int>& boxInfo){
  cin>>boxNum>>childrenNum;
  boxInfo.resize(boxNum);
  for(auto& ele:boxInfo){
    scanf("%d",&ele);
  }
}
void CHRISTMAS_Input2(int& childrenNum,int& boxNum,vector<int>& boxInfo){
  cin>>boxNum>>childrenNum; 
  string tmp;
  size_t idx;
  cin.ignore();
  getline(cin,tmp);
  boxInfo.resize(boxNum);
  for(int i=0;i<boxNum;i++){
    boxInfo[i]=stoi(tmp,&idx);
    tmp=tmp.substr(idx);
  }
}
void CHRISTMAS_Input3(int& childrenNum,int& boxNum,vector<int>& boxInfo){
  cin>>boxNum>>childrenNum;
  boxInfo.resize(boxNum);
  for(auto& ele:boxInfo){
    cin>>ele;
  }
}
int CHRISTMAS_GREEDY(vector<int>& pSum, vector<vector<int>>& modValueIdx, int childrenNum){
  int result=0;
  vector<pair<int,int>> options;  //first=끝나는 위치, second=시작위치
  //mod Value
  for(int i=0;i<modValueIdx.size();i++){
    auto& ele=modValueIdx[i];
    if(ele.size()<2){
      continue;
    }
    for(int j=0; j<ele.size()-1;j++){
      options.push_back(make_pair(ele[j+1],ele[j]+1));
    }
  }
  sort(options.begin(),options.end());
  int tmpEnd=-1;
  for(auto& ele:options){
    if(ele.second>tmpEnd){  //ele.first = end, ele.second = begin
      tmpEnd=ele.first;
      result+=1;
    }
  }
  return result;
}
int CHRISTMAS_GREEDY2(vector<int>& pSum,int childreNum){
  //lastIDx==선물그룹 중 마지막 위치, prePosition[modValue]==modValue가 등장한 마지막 idx
  int lastIdx=-1,result=0;
  vector<int> prevPosition(childreNum,-2);  
  prevPosition[0]=-1;  //mod k==0을 위함
  for(int i=0;i<pSum.size();i++){
    int nowMod=pSum[i];
    if(prevPosition[nowMod]>=lastIdx){
      lastIdx=i;
      result++;
    }
    prevPosition[nowMod]=i;
  }
  return result;
}
int CHRISTMAS_DP(vector<int>& pSum, int childrenNum){

}
pair<int,int> CHRISTMAS_Algo(int childrenNum,int boxNum,vector<int> boxInfo){
  pair<int,int> result; //1번답, 2번답
  //1. 부분 합 mod childrenNum, mod value arr 구하기
  vector<int> partialSumMod(boxNum);
  vector<vector<int>> modValueIdx(childrenNum);
  modValueIdx[0].push_back(-1); //mod가 0일때는 시작위치부터 세야하므로, -1을 추가해준다.
  partialSumMod[0]=boxInfo[0]%childrenNum;
  modValueIdx[boxInfo[0]%childrenNum].push_back(0);
  for(int i=1;i<boxNum;i++){
    int modValue=(partialSumMod[i-1]+boxInfo[i])%childrenNum;
    partialSumMod[i]=modValue;
    modValueIdx[modValue].push_back(i);
  }
  //2. mod value arr을 이용해 정답 1번 구하기
  int q1Result(0); 
    //mod Value가 0일때와 아닐때의 동작이 다르다.
  for(int i=0;i<modValueIdx.size();i++){
    q1Result+=((modValueIdx[i].size()*(modValueIdx[i].size()-1ll))/2)%20091101;
    q1Result%=20091101;
  }
  result.first=q1Result;
  //3. mod value arr을 이용해, 가장 짧은 구간들을 구하여 끝나는 순으로 오름차순 정렬하고, greedy하게 2번답 구하기
  result.second=CHRISTMAS_GREEDY(partialSumMod,modValueIdx,childrenNum);
  //result.second=CHRISTMAS_GREEDY2(partialSumMod,childrenNum);
  //result.second=CHRISTMAS_DP(partialSumMod,modValueIdx,childrenNum);
  return result;
} 
void CHRISTMAS(){
  // TREASURE
  /*설명 및 입력
  설명
    크리스마스를 맞이하여 산타 할아버지는 전세계의 착한 어린이 K명에게 인형을 사주려고 한다. 
      산타 할아버지는 인형을 구입하기 위해서 유명한 인형가게인 "놀이터"에 찾아갔다. 
      놀이터에는 N개의 인형 상자가 한 줄로 진열되어 있고, 각 인형 상자에는 한 개 이상의 인형이 들어 있다. 
      그리고 놀이터에서는 주문의 편의성을 위해 각 상자에 번호를 붙여 놓았고, 
      주문은 "H번 상자부터 T번 상자까지 다 주세요."라고만 할 수 있다. (H ≤ T) 
    산타 할아버지는 한 번 주문할 때마다, 
      주문한 상자에 있는 인형들을 모두 꺼내서 각각을 K명에게 정확히 같은 수만큼 나누어 주고, 
      남는 인형이 없도록 한다.
    1. 한 번 주문할 수 있다면, 가능한 주문 방법은 몇 가지인가?
    2. 여러 번 주문할 수 있다면, 주문이 겹치지 않게 최대 몇 번 주문할 수 있는가? 
      (주문이 겹친다는 것은 어떤 두 주문에 같은 번호의 인형 상자가 포함되는 것을 말한다.)
  입력
    첫 번째 줄에는 테스트 케이스의 개수 T가 주어진다. ( T ≤ 60 )
    각 테스트 케이스의 첫 번째 줄에는 인형 상자의 개수 N과 어린이의 수 K가 주어진다.(1 ≤ N, K ≤ 100000)
    두 번째 줄에는 1번 인형 상자부터 N번 인형 상자까지 각 인형 상자에 들어 있는 인형의 개수 Di가 주어진다. ( 1 ≤ i ≤ N, 1 ≤ Di ≤ 100000 )
  출력
    1번에 대한 답과 2번에 대한 답을 한 줄에 하나의 빈칸으로 나누어 출력한다. 
    1번 답은 매우 클 수 있으므로 20091101로 나눈 나머지를 출력한다.
  제한조건
    10초, 64MB
  */
  /*힌트
    입력은 string방식 혹은 scanf (%d) 이용
      scanf가 더 빠르다 
    범위가 10만이므로, long long 타입을 적절히 사용하자  
    부분 합을 이용하여 풀기
      부분 합에 mod k를 취한다.
      mod 값이 같은 임의의 위치 a,b에 대해, sum([a+1,b]) mod k == 0 이다. 
    mod 값이 같은 것들의 집합을 한번에 구하는 법 -> arr[mod value]=mod value's idx 
      부분합배열을 순회하며, mod값의 idx를 arr에 저장한다. 
    1번답을 구하는 법
      mod값이 같은 위치가 n개 이다 -> 조합 가능한 경우의 수는 nC2 = n(n-1)/2
    2번답을 구하는 법
      mod값이 같은 위치로, 가장 짧은 구간들을 구한 후(n-1개 구간), 마지막 위치를 기준으로 오름차순 정렬한다.
      greedy하게 답을 구한다
    주의: mod k = 0 일때의 동작은 다르므로, 1번답과 2번답을 구할 때 유의하자 
  */
  /*전략
  전략1
    아이디어: 부분 합, greedy
      1. 빠른 입력을 받는다, 부분 합(mod k) 배열, mod value idx 배열을 만든다. -> O(n)
      2. mod 값이 같은 임의의 위치 a,b에 대해, sum([a+1,b]) mod k == 0 임을 이용하여 1번답을 구한다. -> O(k)
      3. 1번답을 먼저끝나는 상자 순서대로 오름차순 정렬하고, greedy하게 2번답을 구한다. -> O(n + nlgn(정렬))
    분석
      time complexity: O(nlgn)
      mem complexity: O(n)
    피드백
      mod k==0일때를 유의하자 
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int childrenNum, boxNum;
    vector<int> boxInfo; 
    CHRISTMAS_Input3(childrenNum,boxNum,boxInfo);
    auto result=CHRISTMAS_Algo(childrenNum,boxNum,boxInfo);
    // cout<<"::::";
    cout<<result.first<<" "<<result.second<<endl;
  }
}

int main(void){
    //clock_t start,end;
    //start=clock();
  CHRISTMAS();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

