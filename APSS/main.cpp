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
#include <queue>

using namespace std;

// @* 원형 연결리스트 혹은 큐 혹은 배열, 배열이 큐보다 훨씬 빠른데 이유가 무엇일까
//    가설1: 배열의 재할당의 경우 캐시를 이용하여 한번에 빠르게 옮길 수 있지만, 큐의 이동은 하나씩만 이루어져 최적화가 어렵다.
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

int main(void){
    clock_t start,end;
    start=clock();
  JOSEPHUS();
    end=clock();;
    cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

