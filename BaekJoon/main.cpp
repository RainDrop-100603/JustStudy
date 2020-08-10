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
void BK11066(){
//input
  int N;
  scanf("%d",&N);
  vector<vector<int>> table(N,vector<int>(N));  //A(ij)==(i+1)에서 시작하는 (j+1)길이의 값
  for(int i=0;i<N;i++){
    scanf("%d",&table[i][0]);
  }
//prepare
  int prevMin,newMin;
//calc
  //A(ij)=min(A(ik)~A(i+k,j-k))
  for(int j=1;j<N;j++){
    for(int i=0;i<N-j+1;i++){
      prevMin=INT32_MAX;
      //k=1, k= j-1일때는 추가작업이 없지만, 이외에는 이전 작업을 더해줘여 한다. ex 30 40 40이면 (30+40) + ((30+40)+40) 이런식이다.
      for(int k=0;k<j;k++){
        prevMin=min(prevMin,table[i][k]+table[i+k][j-k]);
      }
      table[i][j]=prevMin; 
    }
  }
//output
  printf("\n\n");
  for(auto& ele:table){
    for(auto& ele2:ele){
      printf("%d ",ele2);
    }
    printf("\n");
  }
  //printf("%d\n",table[1][N]);
}

int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  int N;
  scanf("%d",&N);
  while(N--){
    BK11066();
  }
  
  return 0;
}