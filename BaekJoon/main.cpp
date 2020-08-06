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

void PrintIter(map<int,int>::iterator& iter,map<int,int>& tree){
  cout<<iter->first<<'\n';
  if(iter->second==1){
    tree.erase(iter);
  }else{
    iter->second-=1;
  }
}
void BK11286(){
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
        map<int,int>::iterator iterP=tree.lower_bound(0); //양수에서 가장 작은 수
        if(iterP==tree.begin()){  //양수만 있는 경우
          PrintIter(iterP,tree);
        }else if(iterP==tree.end()){  //음수만 있는 경우 
          PrintIter(--tree.end(),tree);
        }else{
          map<int,int>::iterator iterM=--tree.lower_bound(0);             //음수에서 가장 0에 가까운 수 
          if(iterP->first+iterM->first<0){
            PrintIter(iterP,tree);
          }else{
            PrintIter(iterM,tree);
          }
        }
      }
    //tmp!=0 
    }else{
      map<int,int>::iterator iter=tree.find(tmp);
      if(iter==tree.end()){
        tree.insert(make_pair(tmp,1));
      }else{
        iter->second+=1;
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
  BK11286();
  
  return 0;
}