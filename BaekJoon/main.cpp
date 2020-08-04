#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK10816(){
  int n,num,m;
  scanf("%d",&n);
  multiset<int> tree;
  for(int i=0;i<n;i++){
    scanf("%d",&num);
    tree.insert(num);
  }
  scanf("%d",&m);
  for(int i=0;i<m;i++){
    scanf("%d",&num);
    multiset<int>::iterator from=tree.find(num);
    if(from==tree.end()){
      cout<<"0 ";
      continue;
    }
    multiset<int>::iterator to=tree.upper_bound(num);
    cout<<distance(from,to)<<' ';
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