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
  int number;
  cin>>number;
  int input1,input2;

  //변수
  int array[501]={0}; //array[i]=j, i전깃줄에 j전깃줄이 연결되어 있다.
  int count[501]={0};    //LIS를 위한 count
  int tmpcount=0; //비교를 위함 

  //입력
  for(int i=0;i<number;i++){
    cin>>input1>>input2;
    array[input1]=input2;
  }

  //array
  for(int i=1;i<501;i++){
    if(array[i]!=0){
      for(int j=1;j<i;j++){
        if(array[j]<array[i]){
          tmpcount=max(tmpcount,count[j]);
        }
      }
      count[i]=tmpcount+1;
      tmpcount=0;
    }
    
  }

  //출력
  for(int i=0;i<501;i++){
    tmpcount=max(tmpcount,count[i]);
  }

  cout<<number-tmpcount<<"\n";

  return 0;
}

