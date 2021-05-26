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
void ARCTIC_Input(int& cameraNum, vector<double>& cameraPoint){
  int cameraPointNum;
  cin>>cameraNum>>cameraPointNum;
  cameraPoint.resize(cameraPointNum);
  for(auto& ele:cameraPoint){
    cin>>ele;
  }
}
double ARCTIC_func(int cameraNum, const vector<double>& cameraDistance, const vector<double>& cameraPoint, int left, int right){
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
  return ARCTIC_func(cameraNum,cameraDistance,cameraPoint,left,right);
}
double ARCTIC_Algo(int cameraNum, vector<double> cameraPoint){
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
  double result=ARCTIC_func(cameraNum,cameraDistance,cameraPoint,0,cameraDistance.size());
  //소수점 셋째 자리에서 반올림 
  result=round(result*100)/100;
  //return
  return result;
}
void ARCTIC(){
  // ARCTIC
  /*설명 및 입력
  설명
    남극에는 N 개의 탐사 기지가 있습니다. 
    N 개의 무전기를 구입해 각 탐사 기지에 배치하려 합니다. 
      이 때, 두 탐사 기지 사이의 거리가 D 라고 하면, 무전기의 출력이 D 이상이어야만 통신이 가능합니다
    모든 탐사 기지에는 똑같은 무전기가 지급됩니다.
    탐사 본부가 다른 모든 기지에 연락을 할 수 있기 위해 필요한 무전기의 최소 출력은 얼마일까요?
      탐사 본부는 다른 기지를 통해 간접적으로 연락할 수 있다고 가정합니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (<= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 기지의 수 N (<= 100)이 주어지고, 그 다음 줄에 2개씩의 실수로 각 기지의 좌표 (x,y) 가 주어집니다. 
    기지의 위치는 0 이상 1000 이하의 실수입니다. 이 때 첫 번째 주어지는 기지가 탐사 본부라고 가정합니다.
  출력
    각 테스트 케이스마다, 탐사 본부가 다른 모든 기지에 연락을 할 수 있기 위해 필요한 최소 무전기의 출력을 소숫점 밑 셋째 자리에서 반올림해 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    결정 문제: 출력이 D 일때 통신이 가능한가
      첫번째 기지(본부)부터 시작하여, 연결 가능한 기지를 재귀적으로 연결한다.
        연결된 기지가2개 이상이면, 하나의 기지에만 연결되어도 연결된 것으로 간주한다.
        모든 기지에 연결되었다면 참, 그렇지 않다면 거짓 
      출력D는 이분법을 통해 구함
  */
  /*전략
  전략1
    Decision Problem
    접근방법
      재귀함수(min, max, count)
        기저: count==100만큼 반복한 후 min 반환 
        조건: 출력이 (min+max)/2 일 때, 모든 기지에 연결이 되는가? (n^2)
          구현:
            첫 기지(본부에서 시작)@@@@@@@@@@@@@@@뭔가 표현 더 깔끔학[ ]
            본부에서 거리 D이하인 기지들을 연결된 기지에 포함 (n)
              먼저 연결된 기지부터 순서대로, 연결관계 갱신 (n)
            모든 기지가 연결되면 참
          참: return 재귀함수(mid,right)
          거짓: return 재귀함수(left,mid)
    시간:
      O(100*n^2)
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
   ARCTIC_Input(cameraNum,cameraPoint);
    auto result=ARCTIC_Algo(cameraNum,cameraPoint);
    cout<<fixed;
    cout.precision(2);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 ARCTIC();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}