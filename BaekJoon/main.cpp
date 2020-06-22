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
  
  //입력
  //변수
  int caseNum;
  cin>>caseNum;
  int input;
  for(int i=0;i<caseNum;i++){
    long long array[6]={3,1,1,1,2,2};
    cin>>input;
    int j=6;
    while(j<=input){
      array[j%6]=array[(j+1)%6]+array[(j+5)%6];
      j++;
    }
    cout<<array[input%6]<<"\n";
  }
  
  

  

  return 0;
}

