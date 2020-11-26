//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void KLIS_Input(int& arrLen,int& orderK,vector<int>& array){
  cin>>arrLen>>orderK;
  array=vector<int>(arrLen);
  for(auto& ele:array)
    cin>>ele;
}
void KLIS_LIShistory(vector<int>& array, vector<vector<int>>& history, vector<int>& tmpLIS, int idx){
  if(idx==array.size()){
    return;
  }
  if(idx==0){
    tmpLIS.push_back(array[idx]);
    history.push_back(vector<int>(1,idx));
  }else{
    int last(tmpLIS.back()),now(array[idx]);
    if(now>last){
      tmpLIS.push_back(array[idx]);
      history.push_back(vector<int>(1,idx));
    }else{
      int pointIdx=distance(tmpLIS.begin(),lower_bound(tmpLIS.begin(),tmpLIS.end(),now));
      tmpLIS[pointIdx]=now;
      history[pointIdx].push_back(idx);
    }
  }
  KLIS_LIShistory(array, history, tmpLIS, idx+1);
}
void KLIS_getLIS(vector<int>& array, vector<vector<int>>& history){
  //history 원형 생성
  vector<int> tmpLIS;
  KLIS_LIShistory(array,history,tmpLIS,0);
  //history 정리
  int lastIdx=history.back().back();
  for(auto& ele:history){
    while(ele.back()>lastIdx){
      ele.pop_back();
    }
  }
  for(auto& ele:history){ //열의 idx가 낮은것=사전순 앞순서 ; 가 되도록 reverse
    reverse(ele.begin(),ele.end());
  }
} 
int KLIS_DP(vector<vector<int>>& history,vector<int>& DP_KLIS, int idx, int idxOrder){
  if(idx==history.size()-1){
    return 1;
  }
  int& result=DP_KLIS[history[idx][idxOrder]];
  if(result!=-1){
    return result;
  }
  //Algo
  result=0;
  int nowArrIdx=history[idx][idxOrder];
  int nextIdxOrder=0;
  for(auto& ele:history[idx+1]){
    if(ele>nowArrIdx){
      result+=KLIS_DP(history,DP_KLIS,idx+1,nextIdxOrder);
    }else{
      break;
    }
    nextIdxOrder++;
  }
  return result;
}
vector<int> KLIS_kthLIS(vector<int>& array, vector<vector<int>>& history, vector<int>& DP_KLIS,int idx, int idxOrder, int orderK){
  if(idx==history.size()){
    return vector<int>();
  }
  if(orderK==0){
    auto tmpResult=KLIS_kthLIS(array,history,DP_KLIS,idx+1,-1,0);
    tmpResult.push_back(array[history[idx].back()]);
    return tmpResult;
  }
  int cases=KLIS_DP(history,DP_KLIS,idx,idxOrder);
  if(cases>orderK){
    //lowerbound로 위치 잡아주자
    auto tmp=history[idx+1];
    int nextIdxOrder=distance(tmp.begin(),lower_bound(tmp.begin(),tmp.end(),history[idx][idxOrder])); //이거 에러 일으킬꺼같은데 잘 생각해보자 
    auto tmpResult=KLIS_kthLIS(array,history,DP_KLIS,idx+1,nextIdxOrder,orderK);
    tmpResult.push_back(array[history[idx][idxOrder]]);
    return tmpResult;
  }else if(cases==orderK){
    auto tmpResult=KLIS_kthLIS(array,history,DP_KLIS,idx+1,-1,0);
    tmpResult.push_back(array[history[idx].back()]);
    return tmpResult;
  }else{
    return KLIS_kthLIS(array,history,DP_KLIS,idx,idxOrder+1,orderK-cases);
  }
  
}
vector<int> KLIS_Algo(int& arrLen,int& orderK,vector<int>& array){
  //History 생성
  vector<vector<int>> history;
  KLIS_getLIS(array,history);
  //정답 생성
  vector<int> DP_KLIS(arrLen,-1);
  vector<int> result=KLIS_kthLIS(array,history,DP_KLIS,0,0,orderK);  //result는 역순이다
  reverse(result.begin(),result.end());
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
      KLIS_DP(LIS idx, order,History)= #cases
        DP: LIS len * arr len
        DP개선: History[LIS idx][order]를 통해 길이를 arrlen(O(n))으로 줄일 수 있다.
      vector<int> func(LIS idx, order, k) = LIS idx ~ LIS END 범위에 대해, k번째 LIS return
        substructure: func(LIS idx, order, k), #cases=KLIS_DP(LIS idx, order)
                  if k==0  -> return arr[History[LIS idx].back()]+func(LIS idx+1,0,0);
                  if cases>k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,k);
                  if cases=k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,0); 
                  if cases<k -> return func(LIS idx, order+1, k-cases);
        기저: if LIS idx== idx len -> return vector<int>();  
    time complexity
      GetLIS(#n*lgn)+DP(#n*lgn)+func(#n*4)
    mem complexity
      GetLIS(#n)+DP(#n)
  */
  int testCase;
  cin>>testCase;
  while(testCase--){
    int arrLen,orderK;
    vector<int> array;
    KLIS_Input(arrLen,orderK,array);
    vector<int> result=KLIS_Algo(arrLen,orderK,array);
    cout<<result.size()<<'\n';
    for(auto& ele:result)
      cout<<ele<<' ';
    cout<<'\n';
  }
}

int main(void){
  KLIS();
  
  return 0;
}