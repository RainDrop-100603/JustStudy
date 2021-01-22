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
int KLIS_DP(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases, int LISidx, int reverse_Seq){
  //LISidx번째 숫자가 reverse_Seq번째로 작은 숫자일 때, LISidx~END 범위에서의 경우의 수
  //기저
  if(LISidx==history.size()-1){ //마지막 순서인 경우: 경우의 수가 항상 1
    return 1;
  }
  auto nowIter=history[LISidx].rbegin()+reverse_Seq;
  int& result=cache_numOfCases[nowIter->first];
  if(result!=-1){
    return result;
  }
  //Algo
  result=0;
  auto nextVector=history[LISidx+1];
  auto tmpIter=lower_bound(nextVector.begin(),nextVector.end(),make_pair(nowIter->first,0));  //idx에 대한 검증
  for(auto nextIter=tmpIter;nextIter!=nextVector.end();nextIter++){
    if(nextIter->second>nowIter->second){
      int tmp=KLIS_DP(history,cache_numOfCases,LISidx+1,distance(nextIter,nextVector.end())-1);
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
vector<int> KLIS_kthLIS(vector<vector<pair<int,int>>>& history, vector<int>& cache_numOfCases,int LISidx, int orderK, pair<int,int> prevPair){
  //기저
  if(LISidx==history.size()){
    return vector<int>();
  }
  //Algo, pair: {idx, value}, 
  for(int reverse_Seq=0;reverse_Seq<history[LISidx].size();reverse_Seq++){
    auto nowPair=*(history[LISidx].rbegin()+reverse_Seq);
    //value chk, reverse_Seq가 커질수록 value는 커진다.
    if(prevPair.second>nowPair.second){
      continue;
    }
    //idx chk는 생략, LIS의 개수>=K이기 때문에, 유효한 idx를 벗어나지 않는다.
    //Algo
    int cases=KLIS_DP(history,cache_numOfCases,LISidx,reverse_Seq);
    if(cases>=orderK||cases==-2){ //-2 means INT32 overflow, always bigger than orderK
      auto tmp=KLIS_kthLIS(history,cache_numOfCases,LISidx+1,orderK,nowPair);
      tmp.push_back(nowPair.second);
      return tmp;
    }else{
      orderK-=cases;
    }
  }
}
void KLIS_funcTest(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases){
  cout<<"=============Test==============\n";
  cout<<"----------history--------------\n";
  for(auto& ele:history){
    for(auto& ele2:ele){
      cout<<ele2.second<<"("<<ele2.first<<") ";
    }
    cout<<"\n";
  }
  cout<<"----------cache_numOfCases--------------\n";
  for(auto& ele:cache_numOfCases){
    cout<< ele<<" ";
  }cout<<"\n";
  cout<<"==========TestEnd==============\n";
}
vector<int> KLIS_Algo(int arrLen,int orderK,vector<int>& array){
  //History 생성, History는 유효하지 않은 값(LIS에 포함되지 않는 값)도 포함되어 있다. 이 경우는 경우의수가 0으로 표기
  vector<vector<pair<int,int>>> history; //history[LISidx][reverse_Seq] = {ArrIdx, value}, reverse_Seq는 뒤에서 부터의 순서, 값이 작은 순서
  vector<int> tmpLIS;
  KLIS_getHistory(array,history,tmpLIS);
  //정답 생성
  vector<int> cache_numOfCases(arrLen,-1);
  vector<int> result= KLIS_kthLIS(history,cache_numOfCases,0,orderK,{0,0}); //pair: {prev idx, prev value}
  reverse(result.begin(),result.end());
  //KLIS_funcTest(history,cache_numOfCases);
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
    특징 
      LIS를 형성할 때, 각 원소가 가질 수 있는 위치는 하나뿐이다. (stack을 이용한 LIS를 잘 생각하면 이해 가능)
      LIS를 구성하는 원소가, 원본 arr에서 뒤에 있는 원소일수록, 사전순으로는 앞에 위치하는 LIS다.
        LIS에서 각 원소가 가질 수 있는 위치는 하나뿐인데, 같은 위치에서 arrIdx가 큰 원소라는 것은, value가 더 작은 원소임을 의미한다. (value가 더 크다면 같은 위치를 가질수가 없다.)
          증명: 임의의 LIS를 잘라서 LIS A , a , b , LIS B 로 만들었다고 하자.
                LIS A, alpha, a, LIS B로 대체하였다고 가정하면, alpha < a < b 이므로, LIS A, alpha, a, b, LIS B 라는 새로운 LIS가 생겨난다.
                따라서 임의의 alpha는 추가될수 없으므로, a 또한 위치를 변경할 수 없으며, 원소의 위치는 고정된다.
    DynamicProgramming
      stack을 이용해 LIS의 길이를 구하는 알고리즘을 이용하여, History를 구한다. -> n*lgn
        History: stack을 이용하여 LIS를 구할때, 각 stack에서의 값이 변하는 것을 history에 기록한다. 
          의의: LIS를 형성할때, 각 원소가 가질 수 있는 위치는 하나뿐이다. History를 통해 모든 원소를 검사하지 않고도 numOfCases를 구할 수 있다.
      History를 이용하여, k번째 LIS를 구한다.
        LIS의 idx번째 원소의 값이 value일 때의, idx부터 시작하는 LIS의 경우의 수 numOfCases에 대해 -> O(1)
          k>= numOfCases: k번째 LIS의 idx번째 원소의 값은 value이다.  ->  idx+1에 대해 같은 작업 수행
          k< numOfCases: idx번째 원소가 value인 LIS는 k번째 LIS보다 사전순으로 앞에서 나온다. ->  History에서 value보다 사전순으로 뒤에 있는 값을 가져오도록 한다.
        nunOfCases: idx-1위치의 {arridx,value}를 가져와서, arridx가 뒤에있고 value가 더 큰 모든 것의 numOfCases를 더한다. -> LIS_len*(n/LIS_len) ~= n 
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