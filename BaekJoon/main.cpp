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

long long popFunc(vector<int>& v, int key){ //key보다 큰 값을 key로 다듬으며, tmpMax 반환 
  long long max1(v.back()),tmpMax(0),tmpKey,prev(v.back());
  vector<int>::iterator iter=v.end()-1;
  while(tmpKey=*iter>key){
    tmpMax=tmpMax+tmpKey*2-prev;
    prev=tmpKey;
    *iter=key;
    max1=max(max1,tmpMax);
  }
  return max1;
}
void BK6549_Stack(int times){
  vector<int> v;
  int input,prev(-1);
  long long max1(0);
  while(times--){
    cin>>input;
    if(input>=prev){
      v.push_back(input);
    }else{
      max1=max(max1,popFunc(v,input));
      v.push_back(input); //그냥 push 후에 체크하게 바꾸자 popFunc 변환 필여
    }
  }
  cout<<max1<<"\n";
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

    BK6549_Stack(testcase);

  }
  //초기값
  
  
  //출력
  
  
 
  return 0;
}