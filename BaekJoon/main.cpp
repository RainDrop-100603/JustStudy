#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK1654(){  //unsigned int가 왜 사용되었는지 chk
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//calc  
  sort(v.begin(),v.end());
  unsigned int left(1),right,mid,sum;     ///중요. 범위가 1~2^31-1 까지, 즉 int 범위이지만, mid+1을 할 때 overflow가 발생할 수 있다. 이를 방지하기 위해 unsigned int를 사용했다.
  right=v[n-1];
  while(true){
    sum=0;
    mid=(left+right)/2;
    for(const auto& ele: v){
        sum+=ele/mid;
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
  BK1654();
  
  return 0;
}