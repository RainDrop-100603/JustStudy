#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK2805(){ 
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//calc  
  sort(v.begin(),v.end());
  long long left(1),right,mid,sum;    //m의 범위가 int_max의 근접해서, sum이 int 범위를 초과할 수 있기 때문에 long long 사용 
  right=v[n-1];
  while(true){
    sum=0;
    mid=(left+right)/2;
    for(const auto& ele: v){
      if(ele>mid){
        sum+=ele-mid;
      } 
    }
    if(sum<m){
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
  BK2805();
  
  return 0;
}