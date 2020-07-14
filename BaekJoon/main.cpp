#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

//#include "GoodFunction.h"

using namespace std;

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
    if(right_M==v[2][end-1]){
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
    if(left_M==v[2][middle-1]){
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
  if(flagR){
    v[2][end-1]=max(v[1][end-1],newMax);
  }
  if(flagL){
    v[2][start]=max(v[1][start],newMax);
  }
  v[1][start]=max(currentMax,newMax);
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int testcase;
  long long height;

  //변수

  //계산
  while(true){
    cin>>testcase;
    if(testcase==0){break;}

    vector<vector<long long>> table(3, vector<long long>(testcase)); //0행은 height, 1행의 leftest는 max, 2행의 leftest(rightest)는 lmax(rmax)

    for(int i=0;i<testcase;i++){
      cin>>height;
      table[0][i]=height;
      table[1][i]=height;
      table[2][i]=height;
    }
    
    BK6549(table,0,testcase);

    cout<<table[1][0]<<"\n";




  }
  //초기값
  
  
  //출력
  
  
 
  return 0;
}