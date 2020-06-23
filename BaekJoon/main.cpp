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
  int input;

  //변수
  vector<int> inputNum(number); //입력을 저장하는 곳
  vector<int> count(number);    //count 저장 
  int tmpcount=0; //비교를 위함 

  //입력 
  for(int i=0;i<number;i++){
    cin>>input;
    inputNum[i]=input;
    for(int j=0;j<i;j++){
      if(inputNum[j]<input){
        tmpcount=max(tmpcount,count[j]);
      }
    }
    count[i]=tmpcount+1;
    tmpcount=0;
  }

  //출력
  for(int i=0;i<number;i++){
    tmpcount=max(tmpcount,count[i]);
  }

  cout<<tmpcount<<"\n";

  


  return 0;
}

