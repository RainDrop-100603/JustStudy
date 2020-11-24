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
  // //기저, nowChoice==N
  // if(nowChoice==itemDesp.size()) return 0;
  // int& result=DP_desp[nowChoice][weightRemain];
  // if(result!=-1) return result;
  // //substructrue, 선택하지 않았을경우, 선택했을경우
  // result=Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain);
  // if(weightRemain>=itemWeight[nowChoice])
  //   result=max(result,itemDesp[nowChoice]+Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain-itemWeight[nowChoice]));
  // return result;
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
  // vector<vector<int>> DP_desp(itemWeight.size(),vector<int>(weight+1,-1));
  // //DP 채우기
  // int tmp=Packing_DP(DP_desp,itemWeight,itemDesp,0,weight);
  // //정답 생성
  // vector<int> result;
  // result.push_back(tmp);
  // int nowPick(0),weightRemain(weight);
  // while(nowPick<itemWeight.size()-1){
  //   //선택했다면, 절박도가 다를것이다.
  //   if(DP_desp[nowPick][weightRemain]!=DP_desp[nowPick+1][weightRemain]){
  //     result.push_back(nowPick);
  //     weightRemain-=itemWeight[nowPick];
  //   }
  //   nowPick++;
  // }
  // if(DP_desp[nowPick][weightRemain]>0)
  //   result.push_back(nowPick);
  // return result;
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
              LIS생성 정보를 담는 History를 만든다
                History[i][j]=idx, LIS에서 i번째 순서, i행에서 j번째로 입력된, 행렬에서 idx번째 숫자
                마지막 행렬의 마지막 열보다 idx가 큰 값은 삭제한다(LIS에 영향을 끼치지 않는 값들이다)
                법칙
                  i행에 있는 모든 수는 i+1행에 있는 모든 수보다 작다
                  한 행에서, j번째 열에 있는 수는 j+1번째 열에 있는 수보다 크다.
                  LIS에서 idx는 행이 증가할수록 반드시 커지게 된다.(작아지면 순서가 뒤바낀것을 의미)
              History를 이용한 완전탐색
                각 행에서 가장 뒤에있는(가장 큰 열) 값들을 이어붙이면, 사전순으로 가장 앞인 LIS다.
                이후 idx는 계속 커져야 한다는 법칙을 유지하면서, 뒤에서부터 idx를 줄여나가면 된다.
            k가 20억 까지 이므로, O(lgn)으로 search해야한다.
              LIS에서 idx번째 수가 정해졌을때, idx+1부터의 경우의 수는 O(n) : DP이용
                DP생성, O(n)개를 지정하는데, 각 값 초기화에는 lg(t: means tiny) 시간 소요.
              DP를 이용하여 O(lgK)로 search 가능
                func(LIS idx, order, k) return result(str)
                  order=0 , 사전순이므로 0부터 시작
                  if cases>k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,k);
                  if cases=k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,0); 
                    if k==0  -> return arr[History[LIS idx].back()]+func(LIS idx+1,0,0);
                  if cases<k -> return func(LIS idx, order+1, k-cases);
      KLIS_GetLIS(arr, History)
        History[LIS idx][order]=idx of Arr
          LIS의 길이를 구하는 식을 사용할 때 생성
          order가 낮으면 사전순으로 더 앞이 되도록 설정하자
      KLIS_DP(LIS idx, order)= #cases
        DP: LIS len * arr len
      string func(LIS idx, order, k) = LIS idx ~ LIS END 범위에 대해, k번째 LIS return
        substructure: func(LIS idx, order, k), #cases=KLIS_DP(LIS idx, order)
                  if k==0  -> return arr[History[LIS idx].back()]+func(LIS idx+1,0,0);
                  if cases>k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,k);
                  if cases=k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,0); 
                  if cases<k -> return func(LIS idx, order+1, k-cases);
        기저: if LIS idx== idx len -> return ;  //공백을 return 하여 operator+ 가능한가? 아니면 조건단에서 처리해버리나?
    time complexity
      GetLIS(#n*lgn)+DP(#n*lgn)+func(#n)
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
  //KLIS();
  
  return 0;
}