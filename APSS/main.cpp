//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;


//1. overflow -> -2로 처리 
//2. history의 잡 값이 runtimeError 유발 
//3. 연상하는것이 너무 어렵다. 수학적으로 증명을 해야하거나, 비 직관적이다.
void KLIS_Input(int& arrLen,int& orderK,vector<int>& array){
  cin>>arrLen>>orderK;
  array=vector<int>(arrLen);
  for(auto& ele:array)
    cin>>ele;
}
void KLIS_getHistory(vector<int>& array, vector<vector<pair<int,int>>>& history, vector<int>& tmpLIS, int idx=0){
  //모든 ele에 대해 검토가 완료됐을때
  if(idx==array.size()){
    return;
  }
  //Algo, last==임시LIS의 가장 뒤의 원소
  int now(array[idx]),last(idx==0 ? -1 : tmpLIS.back());
  if(now>last){
    tmpLIS.push_back(now);
    history.push_back(vector<pair<int,int>>(1,make_pair(idx,now)));
  }else{
    int pointIdx=distance(tmpLIS.begin(),lower_bound(tmpLIS.begin(),tmpLIS.end(),now));
    tmpLIS[pointIdx]=now;
    history[pointIdx].push_back(make_pair(idx,now));
  }
  KLIS_getHistory(array, history, tmpLIS, idx+1);
} 
int KLIS_DP(vector<vector<pair<int,int>>>& history,vector<int>& DP_KLIS, int LISidx, int RVSSeq){
  //LISidx번째 숫자가 RVSSeq번째로 작은 숫자일 때, LISidx~END 범위에서의 경우의 수
  //기저
  if(LISidx==history.size()-1){ //마지막 순서인 경우: 경우의 수가 항상 1
    return 1;
  }
  auto nowIter=history[LISidx].rbegin()+RVSSeq;
  int& result=DP_KLIS[nowIter->first];
  if(result!=-1){
    return result;
  }
  //Algo
  result=0;
  auto nextVector=history[LISidx+1];
  auto tmpIter=lower_bound(nextVector.begin(),nextVector.end(),make_pair(nowIter->first,0));  //idx에 대한 검증
  for(auto nextIter=tmpIter;nextIter!=nextVector.end();nextIter++){
    if(nextIter->second>nowIter->second){
      int tmp=KLIS_DP(history,DP_KLIS,LISidx+1,distance(nextIter,nextVector.end())-1);
      if(tmp!=-2){
        result+=tmp;
        if(result<=0){  //overflow
          result=-2;
          break;
        }
      }else{
        result=-2;
        break;
      }
    }else{
      break;  //같은 LISidx를 가지는 value는 Arridx가 커질수록 작아지므로, value가 최초로 작아진 시점 이후로는 모두 다 작다. value에 대한 검증
    }
  }
  return result;
}
vector<int> KLIS_kthLIS(vector<vector<pair<int,int>>>& history, vector<int>& DP_KLIS,int LISidx, int RVSSeq, int orderK){
  //LISidx번째 숫자가 RVSSeq번째로 작은 숫자일 때, LISidx~END 범위에서의 경우의 수를 이용한 함수
  auto nowIter=history[LISidx].rbegin()+RVSSeq;
  //마지막 원소인 경우
  if(orderK==1&&LISidx==history.size()-1){
    return vector<int>(1,nowIter->second);
  }
  //Algo
  int cases=KLIS_DP(history,DP_KLIS,LISidx,RVSSeq);
  if(cases==0){
    return KLIS_kthLIS(history,DP_KLIS,LISidx,RVSSeq+1,orderK);
  }
  if(cases>=orderK||cases==-2){
    auto nextIter=history[LISidx+1].rbegin();
    while(nowIter->second>nextIter->second){
      nextIter++;
    }
    int nextRVSSeq=distance(history[LISidx+1].rbegin(),nextIter);
    auto tmpResult=KLIS_kthLIS(history,DP_KLIS,LISidx+1,nextRVSSeq,orderK);
    tmpResult.push_back(nowIter->second);
    return tmpResult;
  }else{
    return KLIS_kthLIS(history,DP_KLIS,LISidx,RVSSeq+1,orderK-cases);
  }
}
void KLIS_funcTest(vector<vector<pair<int,int>>>& history,vector<int>& DP_KLIS){
  cout<<"=============Test==============\n";
  cout<<"----------history--------------\n";
  for(auto& ele:history){
    for(auto& ele2:ele){
      cout<<ele2.second<<"("<<ele2.first<<") ";
    }
    cout<<"\n";
  }
  cout<<"----------DP_KLIS--------------\n";
  for(auto& ele:DP_KLIS){
    cout<< ele<<" ";
  }cout<<"\n";
  cout<<"==========TestEnd==============\n";
}
vector<int> KLIS_Algo(int arrLen,int orderK,vector<int>& array){
  //History 생성, History는 유효하지 않은 값(LIS에 포함되지 않는 값)도 포함되어 있다. 이 경우는 경우의수가 0으로 표기
  vector<vector<pair<int,int>>> history; //history[LISidx][RVSSeq] = {ArrIdx, value}, RVSSeq는 뒤에서 부터의 순서, 값이 작은 순서
  vector<int> tmpLIS;
  KLIS_getHistory(array,history,tmpLIS);
  //정답 생성
  vector<int> DP_KLIS(arrLen,-1);
  vector<int> result= KLIS_kthLIS(history,DP_KLIS,0,0,orderK); 
  reverse(result.begin(),result.end());
  //KLIS_funcTest(history,DP_KLIS);
  return result; 
}
void KLIS(){
  /*실험 조건
  2초, 64MB, 테스트케이스=50
  입력: #eleOfAr n: 1~500, k(th LIS): 1~INT32MAX, #LIS >= k
  출력: 두 줄에 나눠서 K번쨰 LIS 의 길이, 값 출력
  */
  /*전략1_fail
    문제점: 
      1. overflow -> -2로 처리 
      2. history의 잡 값이 runtimeError 유발 
      3. 연상하는것이 너무 어렵다. 수학적으로 증명을 해야하거나, 비 직관적이다.
    바탕이 되는 최적화 문제를 푼다. : 이때 최적해를 세야한다는 것을 감안하고 문제를 풀자.
    최적화 문제의 최적해를 세는 문제를 푼다.
    답의 수를 기반으로 답안을 재구성한다.
    Dynamic Programming
      해결법
        LIS생성 정보를 담는 History를 만든다. H(ij)=arr idx : nlgn
          arr idx는 arr에서의 idx를 말한다. 즉 ele의 value가 아니라, arr에서의 위치를 History에 저장하는 것이다.
        arr idx 번째 원소가 사용될 경우, 해당원소이후의 경우의 수를 저장하는 DP배열을 만든다.: 각 lgn, 최대 nlgn
          어떤 원소가 LIS에서 등장한다면, 해당 원소는 항상 LIS에서 같은 idx번째에 등장한다. 이를 이용한 DP
          미리 생성하지 않고 이용할 때 호출하도록 만든다.
          A라는 ele가 등장 했다면, LIS에서 특정위치(A_idx)의 값이 A로 고정되었다는 뜻이다. 이때 A_idx+1의 값은 아직 고정이 아니므로, 경우의 수가 생기게 되는 것이다.
          DP생성시, arr idx가 더 큰 최초 위치부터 (lower bound를 이용하여 위치찾기) 탐색하여, 값이 arr idx보다 처음으로 더 작아지는 위치에서 끝낸다.
        History와 DP를 이용하여 KLIS를 탐색한다. 최대 n
          History의 i행에서, 열이 클 수록 작은 수 이므로, 큰 열 부터 이용하여 탐색한다.
            currentK=k에서 시작, 열이 큰것부터 탐색해야 하므로 reverse iterator을 이용하여 탐색한다(jIter == R iter).
            if(DP(H(ij))<currentK) -> H(ij)번째 수는 포함되지 않는다.다음 열을 탐색한다. currentK-=DP(H(ij));, jIter++;
            else -> H(ij)번째 수는 포함된다.해당 값을 result에 push한 후, History에서 행을 넘어간다. i++; , result.push_back(arr(H(ij)));
        오버플로우 해결
          K는 항상 int_MAX이하의 크기이다.
          오버플로우를 -2로 처리하면, -2인 경우 항상 해당 원소가 포함되어야한다는 것을 알 수 있다.
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
  /*전략2
    DynamicProgramming
      

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