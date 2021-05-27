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

// Decision Problem
void CANADATRIP_Input(int& cityNum,int& order,vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap){
  cin>>cityNum>>order;
  cityLoc.resize(cityNum);signBegin.resize(cityNum);signGap.resize(cityNum);
  cin.ignore();// \n 제거
  for(int i=0;i<cityNum;i++){
    string tmp;
    size_t idx;
    getline(cin,tmp);
    cityLoc[i]=stoi(tmp,&idx);
    signBegin[i]=stoi(tmp.substr(idx),&idx);
    signGap[i]=stoi(tmp.substr(idx),&idx);
  }
}
double CANADATRIP_func(int order, vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap, int left, int right){
  //(left,right], right는 항상 참
  //기저
  if(left+1==right){
    return right;
  }
  //조건
  int mid((left+right)/2),count(0);
  for(int i=0;i<cityLoc.size();i++){
    count+=max(0,min((mid-cityLoc[i]+signBegin[i])/signGap[i],signBegin[i]/signGap[i]));
  }
  cout<<"mid: "<<mid<<" count: "<<count<<endl;
  //재귀
  if(count>=order){
    right=mid;
  }else{
    left=mid;
  }
  return CANADATRIP_func(order,cityLoc,signBegin,signGap,left,right);
}
double CANADATRIP_Algo(int cityNum,int order,vector<int> cityLoc,vector<int> signBegin,vector<int> signGap){
  //Algo, (min,max] 
  int result=CANADATRIP_func(order,cityLoc,signBegin,signGap,0,8030000);
  //return
  return result;
}
void CANADATRIP(){
  // CANADATRIP
  /*설명 및 입력
  설명
    캐나다의 1번 고속도로는 세계에서 가장 긴 고속도로 중 하나로, 캐나다의 동쪽 끝에서 서쪽 끝까지 있는 모든 주요 도시를 연결합니다. 
      동건이는 이 고속도로를 타고 캐나다의 서쪽 끝 빅토리아에서 동쪽 끝 세인트 존까지 8,030km 를 달리기로 마음먹었습니다.
    이 고속도로는 N개의 주요 도시를 지나치는데, i번째 도시까지의 거리를 나타내는 표지판은 도시에 도착하기 Mi미터 전부터 시작해서 도시에 도착할 때까지 Gi미터 간격으로 설치되어 있습니다.
      즉 일반적으로 표시판의 개수는 Mi/Gi 이다.
    시작점으로부터 각 도시까지의 거리 Li와 Mi, Gi가 주어질 때, 시작점으로부터 여행하면서 동건이가 보게 되는 K번째 표지판의 위치를 계산하는 프로그램을 작성하세요. 
      한 위치에 표지판이 여러 개 있을 경우에도 각각의 표지판을 따로 세기로 합니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 도시의 수 N (1 <= N <= 5000) 과 K (1 <= K <= 2^31-1) 가 주어집니다. 
    그 후 N줄에는 각 3개의 정수로 Li, Mi, Gi (1 <= Gi <= Mi <= Li <= 8,030,000) 가 주어집니다. 
    Mi는 항상 Gi의 배수입니다. K는 항상 총 표지판의 수 이하입니다.
    입출력 데이터의 양이 많으니 빠른 입출력 방법을 사용하시기 바랍니다.
  출력
    각 테스트 케이스마다 한 줄에 K번째 표지판의 위치를 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    k의 최대값은 2^32~= 20억이며, 표지판의 개수는 최대 400억이다. 즉 하나하나 구해선 답을 구할 수 없다.
    결정문제: 어느 위치(x)의 표지판의 개수가 k개 이상인가?
      표지판시작위치(Li-Mi)가 x이하인 도시 k개 선택
        sum(i=0~k-1): min((x-Li+Mi)/Gi,Mi/Gi)
      이분법: 실수가 아닌 정수이므로, 정확한 위치를 구할때까지만 재귀 
  */
  /*전략
  전략1
    Decision Problem
    접근방법
      재귀함수: (min, max] (lgn 반복, n수행시간)
        기저: min+1==max -> ret max
        조건: 어느 위치 x: (min+max)/2 의 표지판의 개수가 k개 이상인가?
          구현: (n)
            표지판시작위치(Li-Mi)가 x이하인 도시 k개 선택
              sum(i=0~k-1): min((x-Li+Mi)/Gi,Mi/Gi)
          참: return 재귀함수(left,mid)
          거짓: return 재귀함수(mid,right)
    시간:
      O(nlgn)
    크기:
      O(n)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int cityNum,order;
    vector<int> cityLoc,signBegin,signGap;
    CANADATRIP_Input(cityNum,order,cityLoc,signBegin,signGap);
    auto result=CANADATRIP_Algo(cityNum,order,cityLoc,signBegin,signGap);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 CANADATRIP();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}