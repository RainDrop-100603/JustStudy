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
  vector<int> arr(N); //input value
  for(int i=0;i<N;i++){
    scanf("%d",&arr[i]);
  }
//prepare
  vector<vector<int>> table(N,vector<int>(N));  //A(ij)==[i,i+j+1) 범위의 value를 만드는데 필요한 cost의 최소값
  int prevMin,newMin;
//calc
  //A(ij)=min(A(ik)+A(i+k+1,j-k-1)+sum(ij)),k=0~j-1,sum(ij)=sum(arr[i]~arr[j])
  for(int j=1;j<N;j++){
    for(int i=0;i<N-j;i++){
      prevMin=INT32_MAX;
      //k=0, k= j-1일때는 추가작업이 없지만, 이외에는 이전 작업을 더해줘여 한다. ex 30 40 40이면 (30+40) + ((30+40)+40) 이런식이다. 만드는데 든 비용 !=길이
      prevMin=min(prevMin,table[i][0]+table[i+1][j-1]);
      for(int k=1;k<j-1;k++){
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
  //printf("%d\n",table[0][N-1]);
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