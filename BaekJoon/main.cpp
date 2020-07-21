#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

//#include "GoodFunction.h"

using namespace std;
//정답오류, 원인?
void BK6549(vector<vector<long long>>& v, int start, int end){  //[start,end)
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    BK6549(v,start,middle);
    BK6549(v,middle,end);
  }
  //conquer : Merge
  long long left_H=v[0][middle-1];
  long long left_M=v[2][middle-1];
  long long right_H=v[0][middle];
  long long right_M=v[2][middle];
  long long currentMax=max(v[1][start],v[1][middle]);
  long long newMax;
  int cnt;
  bool flagL=false;
  bool flagR=false;
  if(left_H>right_H){ //오른쪽에서 왼족으로 밀고감
    if(v[3][middle]==3){
      flagR=true;
    }
    cnt=middle-1;
    newMax=right_M;
    while(v[0][cnt]>=right_H){
      newMax+=right_H;
      if(cnt==start){
        flagL=true;
        break;
      }
      cnt--;
    }
  }else{
    if(v[3][start]==3){
      flagL=true;
    }
    cnt=middle;
    newMax=left_M;
    while(v[0][cnt]>=left_H){
      newMax+=left_H;
      if(cnt==end-1){
        flagR=true;
        break;
      }
      cnt++;
    }
  }
  if(flagR&&flagL){
    v[3][start]=3;
    v[2][end-1]=max(v[1][end-1],newMax);
    v[2][start]=max(v[1][start],newMax);
  }else if(flagR){
    v[3][start]=2;
    v[2][end-1]=max(v[1][end-1],newMax);
  }else if(flagL){
    v[3][start]=1;
    v[2][start]=max(v[1][start],newMax);
  }else{
    v[3][start]=0;
  }
  
  v[1][start]=max(currentMax,newMax);
}
//정답은 맞다, 그러나 pop이 너무 자주 사용되어서 시간초과, 정답과 유사하나 구현 방법의 차이 
long long popFunc(vector<int>& v){ //key보다 큰 값을 key로 다듬으며, tmpMax 반환 
  int key;
  long long realMax(0),count(1);
  vector<int>::iterator iter=v.end()-2;
  if(*iter>v.back()){
    key=v.back();
  }else{
    key=-1;
    iter++;
  }
  while(*iter>key&&iter>=v.begin()){
    realMax=max(realMax,(*iter)*count);
    *iter=key;
    iter--;
    count++;
  }
  return realMax;
}
void BK6549_Stack(int times){
  vector<int> v;
  int input,prev(-1);
  long long realMax(0);
  while(times--){
    cin>>input;
    v.push_back(input);
    if(input<prev){
      realMax=max(realMax,popFunc(v));
    }
    prev=input;
  }
  realMax=max(realMax,popFunc(v));
  cout<<realMax<<"\n";
}

long long PopFunc2(vector<int>& v,vector<int>& stack, int idx){
  long long realMax(0),tmpKey;
  int key(v[idx]);
  while(!stack.empty()){
    tmpKey=stack.back();
    if(v[tmpKey]<=key){
      break;
    }
    realMax=max(realMax,v[tmpKey]*(idx-tmpKey));
    stack.pop_back();
  }
  return realMax;
}
void BK6549_Stack2(long long times){
  vector<int> v,stack;
  int input;
  long long realMax(0);
  int prev(-1);

  for(int i=0;i<times;i++){
  //입력
    cin>>input;
    v.push_back(input);
  //계산
    if(input<prev){
      realMax=max(realMax,PopFunc2(v,stack,i));
    }
    stack.push_back(i);
    prev=input;
  }

  long long tmpKey;
  while(!stack.empty()){
    tmpKey=stack.back();
    realMax=max(realMax,v[tmpKey]*(times-tmpKey));
    stack.pop_back();
  }
  
  cout<<realMax<<"\n";
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int testcase;

  //변수

  //계산
  while(true){
    cin>>testcase;
    if(testcase==0){break;}

    BK6549_Stack2(testcase);

  }
  //초기값
  
  
  //출력
  
  
 
  return 0;
}