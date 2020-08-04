#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK1654(){
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//calc  
  sort(v.begin(),v.end());
  int left(1),right,mid,sum,ans;
  right=v[n-1];
  while(true){
    sum=0;
    mid=(left+right)/2;
    for(auto& ele: v){
        sum+=ele/mid;
    }
    if(sum<m){
        right=mid-1;
    }else{
        left=mid+1;
        ans=mid;
    }
    if(left>right){
        break;
    }
  }
  
  printf("%d",ans);
  
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK1654();
  
  return 0;
}