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

void BK11279(){
//input
  int N;
  scanf("%d",&N);
//prepare  
//calc
  map<int,int> tree;
  int tmp;
  for(int i=0;i<N;i++){
    scanf("%d",&tmp);
    if(tmp==0){
      if(tree.size()==0){
        printf("%d\n",0);
      }else{
        int first=tree.rbegin()->first;
        int second=tree.rbegin()->second;
        printf("%d\n",first);
        tree.erase(first);
        if(second>1){
          tree.insert(make_pair(first,second-1));
        }
      }
    }else{
      map<int,int>::iterator iter=tree.find(tmp);
      if(iter==tree.end()){
        tree.insert(make_pair(tmp,1));
      }else{
        int first=iter->first;
        int second=iter->second+1;
        tree.erase(first);
        tree.insert(make_pair(first,second));
      }
    }
  }
  
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK11279();
  
  return 0;
}