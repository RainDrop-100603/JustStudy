//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void KLIS_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp){
  int itemNum;
  cin>>itemNum>>weight;
  itemName=vector<string>(itemNum);
  itemWeight=itemDesp=vector<int>(itemNum);
  for(int i=0;i<itemNum;i++)
    cin>>itemName[i]>>itemWeight[i]>>itemDesp[i];
}
int KLIS_DP(vector<vector<int>>& DP_desp,vector<int>& itemWeight,vector<int>& itemDesp,int nowChoice,int weightRemain){
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
vector<int> KLIS_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp){
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
void KLIS(){
  /*
  2초, 64MB, 테스트케이스=50
  입력: 수열의 원소의 수(n) 1~500, k(번째 LIS)1~2*10e9, n개의 정수로 이루어진 수열(각 수는 1~100,000, 중복 X), K번째 LIS는 반드시 존재한다(LIS의 개수는 K개 이상)
  출력: 두 줄에 나눠서 K번쨰 LIS 의 길이, 값 출력
  전략1
    Dynamic Programming
      해석: 사전순 K번째 LIS:
              LIS끼리는 당연히 길이가 같다, 따라서 사전순으로 배열하는 것은 어렵지 않다. 
            완전탐색:
              사전순으로 가장 앞인 LIS를 구한다. 길이를 x라 하자
              func(LIS,nth if LIS, idx of Arr)
                 
                

            K번째 LIS를 구하는 방법
              사전순으로 가장먼저인 LIS를 구한다. 여기서 LIS의 길이 또한 알 수 있다. -> O(nlgn)
                이떄 LIS의 
      Ocr1_DP1(이전문자 Y,인식된문자 R)=가능성
        DP: 500*500
      func(sentence 에서 idx 번째 word,실제 word:X)=idx번째 word가 X일 때, idx+1부터 시작하는 sentence의 조건부 확률 최대치
          idx부터 시작하는 sentence의 조건부 확률 최대치 = DP[0][0] 
        DP: 101*500, idx번째 정보는 idx+1 위치에 저장 
        substructure: func(idx,nowWord)=for(nextWord=word range), max, nextPoss[Y][Z]*classifiPoss[Z][R]/Ocr1_DP1(Y,R)*func(idx+1,nextWord)
        기저: idx==sentenceLen: return 1, idx==-1: nextPoss 대신 firstPoss 사용 
        정답: DP_path를 이용한다
    의문점
      Ocr_DP2 있는것이 속도 측면에서 유리한가? 경로를 추적해야 하므로 Ocr_DP2 필요한긴 하지만 속도적인 측면에서 어떤지.
        -> 함수 실행시간이 1이므로 속도측면에서 유리하지 않다. 경로추적은 전용 DP를 추가하여 해결하자
    개선점
      확률 자체보다 확륭리 최대치인 경로를 구하는 것인데, P(R)==DP1의 경우 공통되는 항이므로 없애버리자
      확률을 그대로 사용하면 반드시 상대비교만을 사용해야한다(절대비교를 사용할시 오차 발생)
      0이하의 확률을 곱하다보면 의미없는 수치로 낮아질 수 있다. log로 변환하여 이용하자
    time complexity
      #func(n*m)*func(m)+#Ocr_DP2(n*m^2)*Ocr_DP2(1)+#Ocr1_DP1(n*m)*Ocr1_DP1(m)=O(n*m^2)
    mem complexity
      DP(m*m*m)=O(m^3)
  */
  int testCase;
  cin>>testCase;
  while(testCase--){
    int weight;
    vector<string> itemName;
    vector<int> itemWeight,itemDesp;
    KLIS_Input(weight,itemName,itemWeight,itemDesp);
    vector<int> result=KLIS_Algo(weight,itemWeight,itemDesp);
    cout<<result.front()<<' '<<result.size()-1<<'\n';
    for(auto iter=++result.begin();iter!=result.end();iter++){
      cout<<itemName[*iter]<<'\n';
    }
  }
}

int main(void){
  KLIS();
  return 0;
}