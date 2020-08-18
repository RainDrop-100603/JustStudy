#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>

//#include "GoodFunction.h"

using namespace std;
void BK10942(){
//input
  int N,Q;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d",&N); //N== size of arr
  vector<int> arr(N);  
  for(auto& ele:arr){
    scanf("%d",&ele);
  }
  scanf("%d",&Q); //N== #Question
//prepare
  int from,to,ans;  //(from-1)~(to-1)
  vector<int> pO(N);  //palindrome, p(n) == k: n-k ~ n+K . odd range
  vector<int> pE(N);  //palindrome, p(n) == k: n-k ~ n+k-1 . even range
  list<int> listO;  //odd range을 임시저장하는 list: ex 0 1 2 3 4
  list<int> listE;  //even range를 임시저장하는 list: ex 0 1 2 3 4 5
//calc
  //팬릴드롬 행렬 생성
  if(arr[1]==arr[0]){
    listE.push_back(1);
  }
  for(int i=2;i<N;i++){
    //odd range chk
    for(auto iter=listO.begin();iter!=listO.end();iter++){
      int d=*iter;
      int from=i-d*2-2;
      if(from>-1&&arr[from]==arr[i]){
        (*iter)++;
      }else{
        pO[i-d-1]=d;
        iter=listO.erase(iter);
      }
    }
    if(arr[i]==arr[i-2]){
      listO.push_back(1);
    }
    //even range chk
    for(auto iter=listE.begin();iter!=listE.end();iter++){
      int d=*iter;
      int from=i-d*2-1;
      if(from>-1&&arr[from]==arr[i]){
        (*iter)++;
      }else{
        pE[i-d]=d;
        iter=listE.erase(iter);
      }
    }
    if(arr[i]==arr[i-1]){
      listE.push_back(1);
    }
  }
  //list를 비우는 작업 
  for(auto iter=listO.begin();iter!=listO.end();iter++){
    pO[N-*iter-1]=*iter;
  }
  for(auto iter=listE.begin();iter!=listE.end();iter++){
    pE[N-*iter]=*iter;
  }

//output
  for(auto& ele:pO){
    printf("%d ",ele);
  }printf("\n");
  for(auto& ele:pE){
    printf("%d ",ele);
  }printf("\n");
  // for(int i=0;i<Q;i++){
  //   scanf("%d %d",&from,&to);
  //   ans=0;
  //   if((from+to)%2==0){
  //     if(p[from+to]/2==1){
  //       ans=1;
  //     }
  //   }else{
  //     if(p[from+to]/2==2){
  //       ans=1;
  //     }
  //   }
  //   printf("%d\n",ans);
  // }

}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
//   int N;
//   scanf("%d",&N);
//   while(N--){
    BK10942();
//  }
  
  return 0;
}