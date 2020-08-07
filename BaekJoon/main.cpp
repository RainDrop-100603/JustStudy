#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

//#include "GoodFunction.h"

using namespace std;

void BK1655(){
//input
  int N;
  scanf("%d",&N);
//prepare  
  int mid,tmp,gap;
  multiset<int> leftQ;
  multiset<int> rightQ;
//calc
  //n==1
  scanf("%d",&mid);
  printf("%d\n",mid);
  map<int,int> tree;
  //n>1
  for(int i=0;i<N-1;i++){
    scanf("%d",&tmp);
    if(tmp>mid){
      rightQ.insert(tmp);
      gap=rightQ.size()-leftQ.size();
      while(gap>1){
        leftQ.insert(mid);
        mid=*rightQ.begin();
        rightQ.erase(rightQ.begin());
        gap--;
      }
    }else{
      leftQ.insert(tmp);
      gap=leftQ.size()-rightQ.size();
      while(gap>0){
        rightQ.insert(mid);
        mid=*leftQ.rbegin();
        leftQ.erase(--leftQ.end());
        gap--;
      }
    }
    printf("%d\n",mid);
  }
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK1655();
  
  return 0;
}