#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK1920(){
//input
  set<int> tree;
  int n,m,num;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>num;
    tree.insert(num);
  }
//calc
  cin>>m;
  set<int>::iterator end(tree.end());
  for(int i=0;i<m;i++){
    cin>>num;
    if(tree.find(num)==end){
      cout<<0<<'\n';
    }else{
      cout<<1<<'\n';
    }
  }
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK1920();
  
  return 0;
}