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


// @*@*@* 계산 기하, 여러개의 점으로 convex hull 만드는법, convex hull을 나누느 직선이 있는지 구하는 법
//        두 convex hull을 나누는 직선의 범위를 구하는 법, 원의 각도에서 포함관계를 구하는 법
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
  if(optionNum==0){
    return GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken,semesterCount,thisSemester+1);
  }else if(optionNum<=classLimit){
    return GRADUATION_func1(classNum,classTarget,semesterNum,classLimit,preClass,semesterInfo,classTaken|option,semesterCount+1,thisSemester+1);
  }else{
    vector<int> choices=GRADUATION_getCombination(option,classNum,classLimit);
    int semesterMin=100;
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
  */
  /*전략
  전략1
    아이디어: 완전탐색, 가지치기
      변수: 현재학기, 최대학기, 수강학기, 수강과목, 수강가능과목수, 개설과목,학기별 개설과목, 선수강과목
      재귀:  
        기저: 수강과목의 갯수>=기준 -> 수강학기 반환
              현재학기 > 최대학기 -> 최대학기+1 반환
        수행: 현재학기, 학기별 개설과목, 수강과목, 수강가능과목수, 선수강과목을 고려하여 모든 경우의 수를 만든다.
              각 경우의 수를 선택하여 현재학기+1,수강학기+1로 재귀한다. 반환값들 중 최솟값을 선택하여 반환한다.
                경우의 수가 0이라면, 현재학기+1로 재귀하고, 해당값을 반환한다.
      결과: 수강학기가 최대학기 이하이면 수강힉기 반환, 최대학기 초과하면 IMPOSSIBLE 출력 
    분석
      time complexity: 측정하기가 어렵다
      mem complexity: O(n), 비트마스크 사용으로 용량이 작다 
    피드백
      오답
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

int main(void){
    //clock_t start,end;
    //start=clock();
  GRADUATION();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

