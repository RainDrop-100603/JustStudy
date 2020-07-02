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
public:
  PriorityQueue& push(pair<int,int>& p){
    q.push_back(p);
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
      return q[idx++];
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
};

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  int n,k;
  cin>>n>>k;

  //변수
  Queue q;
  for(int i=1;i<=n;i++){
    q.push(i);
  }


  //계산
  cout<<'<';
  while(--n){
    for(int i=1;i<k;i++){
      q.push(q.pop());
    }
    cout<<q.pop()<<", ";
  }
  cout<<q.pop()<<'>';

  
  //출력
 
  return 0;
}

