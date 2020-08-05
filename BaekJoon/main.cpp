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
//calc
  int left,right,mid;  
  left=1;right=v[n-1];
  vector<int>::iterator iterFirst=v.begin();
  vector<int>::iterator iterEnd=v.end();
  vector<int>::iterator iterNow;
  while(true){
    mid=(left+right)/2;
    iterNow=iterFirst;
    for(int i=0;i<m-1;i++){   //first = 1, add m-1
      if(iterNow==iterEnd){
        break;
      }
      iterNow=lower_bound(v.begin(),v.end(),*iterNow+mid);
    }
    if(iterNow==iterEnd){ //End여서는 안된다/
      right=mid-1;
    }else{
      left=mid+1;
    }
    if(left>right){
      break;
    }
  }
  
  printf("%d",left-1);
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