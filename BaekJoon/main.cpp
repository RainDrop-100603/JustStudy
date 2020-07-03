#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;



int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  int testCase;
  cin>>testCase;
  int num,target; //num은 개수, target는 궁금한 문서의 현재위치=입력받은 순서 
  int priority; //우선순위

  //변수
  PriorityQueue q(9);
  int result=1; //인쇄되는 순서


  //계산
  while(testCase--){
    //입력 및 초기화
    result=1;
    q.clear();
    cin>>num>>target;
    for(int i=0;i<num;i++){
      cin>>priority;
      q.push(make_pair(i,priority));
    }
    //계산
    while(q.prioirtyPop().first!=target){
      result++;
    }
    cout<<result<<"\n";
  }
  
  //출력
  // 1 0일 때 무한루프 
 
  return 0;
}

