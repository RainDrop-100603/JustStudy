#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

class PriorityQueue{
  vector<pair<int,int>> q;    //first= value, second=priority
  int idx=0;
  vector<int> priority; //prioirty 개수 저장, 0~priority
public:
  PriorityQueue(int maxpriority){
    priority=vector<int>(maxpriority+1);
  }
  PriorityQueue& push(pair<int,int> p){
    q.push_back(p);
    priority[p.second]++;
    return *this;
  }
  int size(){
    return q.size()-idx;
  }
  bool empty(){
    if(this->size()<1){
      return true;
    }else{
      return false;
    }
  }
  pair<int,int> pop(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      priority[q[idx].second]--;
      return q[idx++];
    }
  }
  int maxPriority(){
    int len=priority.size();
    for(int i=len;i>0;i--){
      if(priority[i]){
        return i;
      }
    }
    return 0;
  }
  pair<int,int> prioirtyPop(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      int maxP=maxPriority();
      while(this->front().second!=maxP){
        this->push(this->pop());
      }
      return this->pop();
    }
  }
  pair<int,int> front(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      return q[idx];
    }
  }
  pair<int,int> back(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      return q.back();
    }
  }
  void clear(){
    q.clear();
    for(auto& ele:priority){
      ele=0;
    }
  }
  
};

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

