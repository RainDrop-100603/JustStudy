#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK2110(){ 
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//prepare  
  sort(v.begin(),v.end());
  int prev=v[0];
  int now;
  vector<int> d(n-1);     //이웃 집과의 거리를 저장한 배열 
  for(int i=0;i<n-1;i++){
    now=v[i+1];
    d[i]=now-prev;
    prev=now;
  }
  sort(d.begin(),d.end());  
//calc
  int dist,left,right,mid;
  left=0;right=n-1;
  vector<int>::iterator iterFirst=v.begin();
  vector<int>::iterator iterEnd=v.end();
  vector<int>::iterator iterNow;
  while(true){
    dist=d[(left+right)/2];
    iterNow=iterFirst;
    int i=0;
    for(i=0;i<m;i++){
      if(iterNow==iterEnd){
        break;
      }
      iterNow=lower_bound(v.begin(),v.end(),*iterNow+dist);
    }
    if(iterNow==iterEnd){ //End여서는 안된다/
      right=(left+right)/2-1;
    }else{
      left=(left+right)/2+1;
    }
    if(left>right){
      break;
    }
  }

  printf("%d",d[left-1]);
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK2110();
  
  return 0;
}