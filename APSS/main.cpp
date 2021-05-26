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

// Decision Problem, 이분법 사용시 유의
void DARPA_Input(int& cameraNum, vector<double>& cameraPoint){
  int cameraPointNum;
  cin>>cameraNum>>cameraPointNum;
  cameraPoint.resize(cameraPointNum);
  for(auto& ele:cameraPoint){
    cin>>ele;
  }
}
double DARPA_func(int cameraNum, const vector<double>& cameraDistance, const vector<double>& cameraPoint, int left, int right){
  //[left,right)
  //기저
  int mid((left+right)/2);
  if(left==mid){
    return cameraDistance[left];
  }
  //조건
  auto now(cameraPoint.begin());
  for(int count=0;count<cameraNum-1;count++){
    now=lower_bound(cameraPoint.begin(),cameraPoint.end(),*now+cameraDistance[mid]);
    if(now==cameraPoint.end()){
      break;
    }
  }
  //재귀
  if(now==cameraPoint.end()){
    right=mid;
  }else{
   left=mid;
  }
  return DARPA_func(cameraNum,cameraDistance,cameraPoint,left,right);
}
double DARPA_Algo(int cameraNum, vector<double> cameraPoint){
  //카메라간 거리의 가능한 값
  vector<double> cameraDistance;
  int cameraPointNum(cameraPoint.size());
  for(int from=0;from<cameraPointNum;from++){
    for(int to=from+1;to<cameraPointNum;to++){
      cameraDistance.push_back(cameraPoint[to]-cameraPoint[from]);
    }
  }
  sort(cameraDistance.begin(),cameraDistance.end());
  cameraDistance.erase(unique(cameraDistance.begin(),cameraDistance.end()),cameraDistance.end());
  //Algo
  double result=DARPA_func(cameraNum,cameraDistance,cameraPoint,0,cameraDistance.size());
  //소수점 셋째 자리에서 반올림 
  result=round(result*100)/100;
  //return
  return result;
}
void DARPA(){
  //DARPA
  /*설명 및 입력
  설명
    DARPA Grand Challenge 는 운전자 없는 차들을 컴퓨터 인공지능으로 조작해 누가 먼저 결승점에 도달하느냐를 가지고 겨루는 인공지능 대회입니다. 
      2004년 DARPA Grand Challenge 의 과제는 사막을 가로지르는 240km 도로를 완주하는 것이었습니다.
    우리는 이 경기를 N 개의 카메라로 중계하려고 합니다. 이 도로에는 카메라를 설치할 수 있는 곳이 M 군데 있습니다. 
      여기에 카메라를 배치하여, 가장 가까운 두 카메라 간의 간격을 최대화하고 싶습니다. 이와 같은 배치를 찾아내는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 이 주어집니다. 
    각 테스트 케이스의 첫 줄에는 카메라의 개수 N (<= 100) 과 설치 가능한 중계소의 수 M (N <= M <= 200) 이 주어집니다. 
    그 다음 줄에는 M 개의 실수로, 카메라를 설치 가능한 곳의 위치가 오름 차순으로 주어집니다. 
    각 위치는 시작점에서부터의 거리로, 240 이하의 실수이며 소숫점 둘째 자리까지 주어질 수 있습니다.
  출력
    각 테스트 케이스마다 가장 가까운 두 카메라 간의 최대 간격을 소수점 셋째 자리에서 반올림해 출력합니다.
  제한조건
    20초, 64MB
  */
  /*힌트
    결정 문제: 거리가 x이상일 때, y이상의 카메라를 설치할 수 있는가?
      거리x는 이분법을 통해 구함
    가능한 카메라의 위치는 정해져 있다 -> 각 카메라포인트간 거리를 모두 특정 행렬에 저장한다.
      이분법에서 거리를 정할 때, 이 값을 이용한다.
  */
  /*전략
  전략1
    Decision Problem
    접근방법
      카메라포인트간의 거리를 모두 구해 "배열1"에 정렬한다. (m^2)
      재귀함수(left,right): 배열1의 [left,right)범위 idx에 대한 이분법. (lg(m^2))
        기저: left==mid(==(left+right)/2)이라면, 해당값을 반환
        조건: arr[mid]인 x에 대해, n개 이상의 카메라를 설치할 수 있는가?   (n*lgm), lgm= time(카메라포인트.lower_bound(이전위치+x))
          참: return 재귀함수(mid,right)
          거짓: return 재귀함수(left,mid)
    시간:
      O(m^2+nlgm*lg(m^2))
    크기:
      O(m^2)
    보완 & 참고
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int cameraNum;
    vector<double> cameraPoint;
    DARPA_Input(cameraNum,cameraPoint);
    auto result=DARPA_Algo(cameraNum,cameraPoint);
    cout<<fixed;
    cout.precision(2);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
  DARPA();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}