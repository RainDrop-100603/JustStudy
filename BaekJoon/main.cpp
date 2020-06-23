#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //DynmaicPrograming

  //입력
  int height;
  cin>>height;
  //변수
  int cost;
  pair<int,int> sum(0,0);       //X의 값 , first= X and X-1's second(==without X-2), second = X and X-2
  pair<int,int> sumPrev(0,0);   //X-1
  pair<int,int> sumPPrev(0,0);  //X-2
  
  for(int i=0;i<height;i++){
    cin>>cost;
    sumPPrev=sumPrev;
    sumPrev=sum;

    sum.first=cost+sumPrev.second;
    sum.second=cost+max(sumPPrev.first,sumPPrev.second);
  }
  
  cout<<max(sum.first,sum.second);

  return 0;
}

