#include "sol.h"

void GRADUATION_Input(int& classNum,int& classTarget,int& semesterNum,int& classLimit,vector<int>& preClass,vector<int>& semesterInfo){
  cin>>classNum>>classTarget>>semesterNum>>classLimit;
  //선수강 과목을 비트마스크로 저장 
  preClass.resize(classNum);
  for(auto& ele: preClass){
    int preNum,tmp;
    ele=0;
    cin>>preNum;
    for(int i=0;i<preNum;i++){
      cin>>tmp;
      ele|=(1<<tmp);
    }
  }
  //학기에 개설되는 과목을 비트마스크로 저장
  semesterInfo.resize(semesterNum);
  for(auto& ele: semesterInfo){
    int classOpen,tmp;
    ele=0;
    cin>>classOpen;
    for(int i=0;i<classOpen;i++){
      cin>>tmp;
      ele|=(1<<tmp);
    }
  }
}
vector<int> GRADUATION_getCombination(int option,int bitmaskLen, int select){
  //bitmask를 집합으로 바꿔준다
  vector<int> set;
  for(int i=0;i<bitmaskLen;i++){
    if((1<<i)&option){
      set.push_back(i);
    }
  }
  //모든 조합 찾기
  int total=__builtin_popcount(option);
    //조합을 위한 key 만들기(0과1로 이루어진 순열, 같은 숫자끼리는 구별하지 않으므로 ,조합과 같다)
  vector<int> key;
  for(int i=0;i<select;i++){key.push_back(1);}
  for(int i=0;i<total-select;i++){key.push_back(0);}
    //조합 생성 
  vector<int> combinations;
  do{
    int tmp=0;
    for(int i=0;i<total;i++){
      if(key[i]==1){tmp|=(1<<set[i]);}
    }
    combinations.push_back(tmp);
  }while(prev_permutation(key.begin(),key.end()));
  return combinations;
}
int GRADUATION_func1(int classNum,int classTarget,int semesterNum,int classLimit,vector<int>& preClass,vector<int>& semesterInfo,int classTaken,int semesterCount,int thisSemester){
  //기저
  if(__builtin_popcount(classTaken)>=classTarget){return semesterCount;}
  if(thisSemester==semesterNum){return semesterNum+1;}
  //모든 경우의 수 만들기 
  int option=semesterInfo[thisSemester];
    //수강한 과목 제외
  option&= ~classTaken;
    //선수강 과목 확인
  for(int i=0;i<classNum;i++){
    if(((1<<i)&option)>0){
      if((classTaken&preClass[i])!=preClass[i]){
        option-=(1<<i);
      }
    }
  }
  //각 경우 선택 후 반환
  int optionNum=__builtin_popcount(option);
  int semesterMin=GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken,semesterCount,thisSemester+1);
  if(optionNum==0){
    return semesterMin;
  }else if(optionNum<=classLimit){
    return min(semesterMin,GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken|option,semesterCount+1,thisSemester+1));
  }else{
    vector<int> choices=GRADUATION_getCombination(option,classNum,classLimit);
    for(auto choice:choices){
      semesterMin=min(semesterMin,GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken|choice,semesterCount+1,thisSemester+1));
    }
    return semesterMin;
  }     
}
string GRADUATION_Algo(int classNum,int classTarget,int semesterNum,int classLimit,vector<int> preClass,vector<int> semesterInfo){
  //재귀함수
  int classTaken(0),semesterCount(0),thisSemester(0);
  int semesterMin=GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken,semesterCount,thisSemester);
  //반환
  if(semesterMin>semesterNum){
    return string("IMPOSSIBLE");
  }else{
    return to_string(semesterMin);
  }
} 
void GRADUATION(){
  // TREASURE
  /*설명 및 입력
  설명
    졸업 필수 학점을 채우려면 전공 과목 N 개 중 K 개 이상을 수강해야 합니다. 
      그런데 각 과목은 해당 과목의 선수과목을 미리 수강했어야만 수강할 수 있으며, 
      각 학기마다 모든 과목이 개설되는 것이 아니기 때문에 문제가 복잡해졌습니다. 
      어떻게 해야 최소 학기에 졸업을 할 수 있을까요?
    각 과목의 정보와 앞으로 M 학기 동안 개설될 과목의 목록이 주어질 때, 
      태우가 최소 몇 학기를 다녀야 졸업할 수 있는지 계산하는 프로그램을 작성하세요. 
      한 과목도 수강하지 않는 학기는 휴학한 것으로 하며, 다닌 학기 수에 포함되지 않습니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 
      각 테스트 케이스의 첫 줄에는 전공 과목의 수 N (1 <= N <= 12), 들어야 할 과목의 수 K (0 <= K <= N), 
      학기의 수 M (1 <= M <= 10) 과 태우가 한 학기에 최대로 들을 수 있는 과목의 수 L (1 <= L <= 10)이 주어집니다. 
      각 과목에는 0부터 N-1 까지의 번호가 매겨져 있습니다.
    그 후 N 줄에 0번 과목부터 순서대로 각 과목의 정보가 주어집니다. 
      이 줄에는 해당 과목의 선수 과목의 수 Ri (0 <= Ri <= N-1) 가 처음 주어지고, 
      그 후 Ri 개의 정수로 선수 과목의 번호가 주어집니다.
    그 후 M 줄에는 이번 학기부터 순서대로 각 학기의 정보가 주어집니다. 
      각 줄에는 해당 학기에 개설되는 과목의 숫자 Ci (1 <= Ci <= 10) 가 주어지고, 
      그 후 Ci 개의 정수로 개설되는 과목의 번호들이 주어집니다.
  출력
    각 테스트 케이스마다 한 줄에 태우가 다녀야 할 최소 학기 수를 출력합니다. 
    M 학기 내에 졸업할 수 없는 경우 IMPOSSIBLE을 출력합니다.
  제한조건
    3초, 64MB
  */
  /*힌트
    비트마스크를 이용할 수 있다. -> 메모리를 덜 쓴다 
    선수강 과목이 연쇄적으로 이어질 수 있다 (A -> B -> C)
    학기를 들을 수 있는 경우에도, 안듣고 넘어갈 수 있음을 유의하자 
  */
  /*전략
  전략1
    아이디어: 완전탐색, 가지치기
      변수: 현재학기, 최대학기, 수강학기, 수강과목, 수강가능과목수, 개설과목,학기별 개설과목, 선수강과목
      재귀:  
        기저: 수강과목의 갯수>=기준 -> 수강학기 반환
              현재학기 > 최대학기 -> 최대학기+1 반환
        수행: 현재학기, 학기별 개설과목, 수강과목, 수강가능과목수, 선수강과목을 고려하여 모든 경우의 수를 만든다.
              수업을 듣지 않는경우, 듣는경우 모두 고려하여 최솟값을 구한다.
      결과: 수강학기가 최대학기 이하이면 수강힉기 반환, 최대학기 초과하면 IMPOSSIBLE 출력 
    분석
      time complexity: O((n Combination n/2)*M*2^N) = 4000k, M*2^N은 동적계획법의 경우인데, x<y 일 경우 O(x)<O(y)임을 이용했다.
      mem complexity: O(n), 비트마스크 사용으로 용량이 작다 
    피드백
      time complexity 구하는 법
      수강할 수 있음에도 안하고 넘어가는 경우 유의 
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int classNum,classTarget,semesterNum,classLimit;
    vector<int> preClass, semesterInfo; 
    GRADUATION_Input(classNum,classTarget,semesterNum,classLimit,preClass, semesterInfo);
    auto result=GRADUATION_Algo(classNum,classTarget,semesterNum,classLimit,preClass, semesterInfo);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

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
void CHRISTMAS_randInput(int& childrenNum,int& boxNum,vector<int>& boxInfo,int childFix, int boxFix){
  childrenNum=childFix;
  boxNum=boxFix;
  boxInfo.resize(boxNum);
  for(auto& ele: boxInfo){
    ele=rand()+1;
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
int CHRISTMAS_GREEDY2_opti(vector<int>& pSum,int childreNum){
  //lastIDx==선물그룹 중 마지막 위치, prePosition[modValue]==modValue가 등장한 마지막 idx
  int lastIdx=0,result=0;
  vector<int> prev(childreNum,-1);  
  prev[0]=0;  //mod k==0을 위함
  for(int i=0;i<pSum.size();i++){
    int& prevIdx=prev[pSum[i]];
    if(prevIdx>=lastIdx){
      lastIdx=i;
      result++;
    }
    prevIdx=i;
  }
  return result;
}
int CHRISTMAS_DP(vector<int>& pSum, int childrenNum){
  vector<int> prev(childrenNum,-1); 
  vector<int> result(pSum.size(),-1);
  prev[0]=0;  //mod Value가 0이면 prev가 없어도 mod Value가 0인 구간을 만들 수 있다.
  for(int i=0;i<pSum.size();i++){
    int& now=result[i];
    //초기화
    if(i>0){
      now=result[i-1];
    }else{
      now=0;
    }
    //연산, pSum[i]==pSum[j] -> sum(i+1 ~ j) mod k == 0
    int& prevIdx=prev[pSum[i]];
    if(prevIdx!=-1){
      now=max(now,result[prevIdx]+1);
    }
    //prev갱신
    prevIdx=i;
  }
  return result.back();
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
  //result.second=CHRISTMAS_GREEDY(partialSumMod,modValueIdx,childrenNum);
  //result.second=CHRISTMAS_GREEDY2(partialSumMod,childrenNum);
  //result.second=CHRISTMAS_GREEDY2_opti(partialSumMod,childrenNum);
  result.second=CHRISTMAS_DP(partialSumMod,childrenNum);
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
    //CHRISTMAS_Input(childrenNum,boxNum,boxInfo);
    CHRISTMAS_randInput(childrenNum,boxNum,boxInfo,131,10000000);
    auto result=CHRISTMAS_Algo(childrenNum,boxNum,boxInfo);
    // cout<<"::::";
    cout<<result.first<<" "<<result.second<<endl;
  }
}

void JOSEPHUS_Input(int& num, int& move){
  cin>>num>>move;
}
pair<int,int> JOSEPHUS_Algo(int num, int move){
  pair<int,int> result;
  //queue를 이용한 방식
  // queue<int> q;
  // for(int i=1;i<=num;i++){
  //   q.push(i);
  // }
  // while(q.size()>2){
  //   q.pop();
  //   int moving=(move-1)%q.size();
  //   for(int i=0;i<moving;i++){
  //     q.push(q.front());
  //     q.pop();
  //   }
  // }
  // result.first=min(q.front(),q.back());
  // result.second=max(q.front(),q.back());
  //array를 이용한 방식
  vector<int> arr(num);
  for(int i=0;i<num;i++){
    arr[i]=i;
  }
  int nowIdx=0;
  while(arr.size()>2){
    arr.erase(arr.begin()+nowIdx);
    nowIdx=(nowIdx+move-1)%arr.size();
  }
  result.first=min(arr.front(),arr.back())+1;
  result.second=max(arr.front(),arr.back())+1;
  //반환
  return result;
} 
void JOSEPHUS(){
  // TREASURE
  /*설명 및 입력
  설명
    조세푸스 문제
    N명의 사람이 있다.
      두명이 남을때까지, 한명씩 자살한다.
      한 사람이 자살하면, 시계방향으로 K번째에 있는 사람이 다음으로 자살한다.
    마지막 두 명중 하나가 되기 위해서는, 처음 사람으로부터 몇 자리 떨어진 곳에 있어야 하는가?
  입력
    입력의 첫 번째 줄에는 테스트 케이스의 개수 C (C≤50)가 주어집니다. 
    각 테스트 케이스는 두 개의 정수 N, K로 주어집니다(3≤N≤1000, 1≤K≤1000).
  출력
    각 테스트 케이스에 두 개의 정수로, 마지막 살아남는 두 사람의 번호를 오름차순으로 출력합니다. 
    첫 번째로 자살하는 병사의 번호가 1이며, 다른 사람들의 번호는 첫 번째 병사에서부터 시계 방향으로 정해집니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    원형 연결리스트, 큐, 배열을 이용할 수 있다.
      원형 연결리스트 - K번 순회 한 위치
      큐 - K번 pop-push한 후 front
      배열 - (idx+K)%배열크기 
    K보다 큐/배열의 크기가 작다면, K대신 K%크기 만큼만 이동해도 된다.
    배열과 큐의 속도차이는 어떻게 될까? 
  */
  /*전략
  전략1
    아이디어: 큐
      1. 큐에 모든 idx를 넣는다. -> O(n)
      2. 두명이 남을 때 까지 아래 수행을 반복한다. sum(2~n-1) = O(n^2) (한번 수행할때 최대 이동횟수 = 큐의 크기 -> 2 ~ min(k-1,n-1))
          queue의 front dequeue
          queue의 front를 queue의 back으로 (K-1)%q.size() 번 옮김 
    분석
      time complexity: O(n^2)
      mem complexity: O(n)
    피드백
  전략2
    아이디어: 배열
      1. 배열에 모든 idx를 넣는다. 시작 idx를 0으로 정한다. -> O(n)
      2. 두명이 남을 때 까지 아래 수행을 반복한다. sum(2~n-1) = O(n^2) (한번 수항할때 최대 재할당 횟수 = 배열의 크기 -> 2 ~ n-1)
          시작 idx를 지운다
          시작 idx를 갱신한다. idx=(idx+K-1)%arr.size()
    분석
      time complexity: O(n^2)
      mem complexity: O(n)
    피드백
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int num, move;
    //JOSEPHUS_Input(num, move);
    num=5000; move=rand()+1;
    auto result=JOSEPHUS_Algo(num, move);
    // cout<<"::::";
    cout<<result.first<<" "<<result.second<<endl;
  }
}

void BRACKETS2_Input(string& inputStr){
  cin>>inputStr;
}
string BRACKETS2_Algo(string& inputStr){
  vector<int> stack;
  for(auto ele: inputStr){
    if(ele=='(' || ele=='{' || ele=='['){
      stack.push_back(ele);
    }else{
      if(ele==')'){
        ele='(';
      }else if(ele=='}'){
        ele='{';
      }else{
        ele='[';
      }
      if(stack.empty() || stack.back() != ele){
        return string("NO");
      }else{
        stack.pop_back();
      }
    }
  }
  if(stack.empty()){
    return string("YES");
  }else{
    return string("NO");
  }
} 
void BRACKETS2(){
  // TREASURE
  /*설명 및 입력
  설명
    Every bracket has a corresponding pair. ( corresponds to ), [ corresponds to ], et cetera.
      Every bracket pair is opened first, and closed later.
      No two pairs "*cross*" each other. For example, [(]) is not well-matched.
    Write a program to help Best White by checking if each of his formulas is well-matched. 
      To make the problem easier, everything other than brackets are removed from the formulas.
  입력
    The first line of the input will contain the number of test cases C (1≤C≤100). 
      Each test is given in a single line as a character string. 
      The strings will only include characters in "[](){}" (quotes for clarity). 
      The length of the string will not exceed 10,000.
  출력
    For each test case, print a single line "YES" when the formula is well-matched; 
      print "NO" otherwise. (quotes for clarity)
  제한조건
    1초, 64MB
  */
  /*힌트
    stack
      ( [ { 는 stack에 저장
      ) ] } 는 stack.top과 매칭되면 stack.pop, 다르다면 return NO
      모든 문자를 완료했을때 stack이 비어있다면 return true, 아니면 return NO
  */
  /*전략
  전략1
    아이디어: 스택
      1. for( i = [string.begin,string.end))
        if string[i]== ( { [ -> stack.push
        else  
          if stack.empty || string[i] match stack.top -> return NO
          else -> stack.pop
      2. if stack.empty -> return YES
          else -> return NO
    분석
      time complexity: O(n)
      mem complexity: O(n)
    피드백
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    string inputStr;
    BRACKETS2_Input(inputStr);
    auto result=BRACKETS2_Algo(inputStr);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

void ITES_Input(int& target,int& length){
  cin>>target>>length;
}
int ITES_Algo(int target,int length){
  //준비 및 초기화
  queue<int> q;
  int qSum(0),result(0);
  unsigned int num(1983);
  //순회
  for(int idx=0;idx<=length;idx++){
    int input=num%10000+1;
    q.push(input);
    qSum+=input;
    while(qSum>target){
      qSum-=q.front();
      q.pop();
    }
    if(qSum==target){
      result++;
    }
    num=num*214013 + 2531011;
  }
  return result;
} 
void ITES(){
  /*설명 및 입력
  설명
    수환이는 외계에서 날아오는 전파를 연구하는 범세계 대규모 프로젝트, ITES@home에 참가하고 있습니다. 
      외계에서 날아오는 전파는 전처리를 거쳐 각 숫자가 [1,10000] 범위 안에 들어가는 자연수 수열로 주어지는데, 
      이 전파가 과연 단순한 노이즈인지 아니면 의미 있는 패턴을 가지고 있는 것인지를 파악하고 싶습니다. 
    수환이는 전파의 부분 수열 중에 합이 K인 것이 유독 많다는 것을 눈치챘습니다. 
      부분 수열이란 연속된 수열의 일부를 말합니다. 
      예를 들어 수열 {1,4,2,1,4,3,1,6} 에서 합이 7 인 부분 수열은 모두 5개 있습니다. 
      {1,4,2} , {4,2,1} , {2,1,4}, {4,3}, {1,6} 이 부분 수열들은 서로 겹쳐도 된다는 데 유의합시다.
    K가 외계인에게 의미 있는 숫자일까요? 
      수환이의 가설을 확인하기 위해, 길이 N인 신호 기록이 주어질 때 합이 K인 부분 수열이 몇 개나 있는지 계산하는 프로그램을 작성하세요.
  입력
    입력의 크기가 큰 관계로, 이 문제에서는 신호 기록을 입력받는 대신 다음과 같은 식을 통해 프로그램 내에서 직접 생성합니다.
      A[0] = 1983
      A[i] = (A[i-1] * 214013 + 2531011) % 2^32
      이 때 i(1 <= i <= N)번째 입력 신호는 A[i-1] % 10000 + 1입니다. 
    문제의 해법은 입력을 생성하는 방식과는 아무 상관이 없습니다. 이 규칙에 따르면 첫 5개의 신호는 각각 1984, 8791, 4770, 7665, 3188입니다.
  출력
    입력 파일의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 20)가 주어지고, 그 후 C 줄에 각 2개의 정수로 K(1 <= K <= 5,000,000) 과 N(1 <= N <= 50,000,000) 이 주어집니다.
  제한조건
    15초, 64MB
  */
  /*힌트
    부분 수열은 연속되는 숫자이므로, 연속되는 숫자가 K를 넘으면 무의미하다.
    stack을 이용하여, stack내부의 숫자가 7 이하로 유지되도록 하면 된다.
    매번 stack내부의 숫자를 더하지 말고, stack내부의 합을 기록한 숫자를 이용하자(부분합 일부 채용)
    수열과 입력신호가 다름을 유의하자 
    mod 2^32는, 33비트 부터는 모두 잘라내는 것을 의미한다.
      이때 unsigned int는 32비트까지만 사용하므로, unsigned int를 사용하면 자동으로 mod 2^32를 취한 것과 같다.
  */
  /*전략
  전략1
    아이디어: 스택
      변수: queue, num(1983), queueSum(0), result(0)
      1. for( i = [0,N] )
        queue.push(num)
        queueSum+=num;
        while(queueSum>K){
          queueSum-=queue.front
          queue.pop
        }
        if(queueSum==K)
          result+=+
        num=number(idx,num);
    분석
      time complexity: O(N)
      mem complexity: O(N)
    피드백
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int target,length;
    ITES_Input(target,length);
    auto result=ITES_Algo(target,length);
    // cout<<"::::";
    cout<<result<<endl;
  }
}
