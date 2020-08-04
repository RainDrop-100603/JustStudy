#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK10816_1(){
  int t=10000000;
    vector<int> v(2*t+1);
    
    int n,m,num;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&num);
        v[num+t]++;
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&num);
        printf("%d ",v[num+t]);
    }
}
void BK10816_2(){
  int n,num,m,d;
  scanf("%d",&n);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
  sort(v.begin(),v.end());
  scanf("%d",&m);
  for(int i=0;i<m;i++){
    scanf("%d",&num);
    d=upper_bound(v.begin(),v.end(),num)-lower_bound(v.begin(),v.end(),num);
    printf("%d ",d);
  }
}

int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK10816();
  
  return 0;
}