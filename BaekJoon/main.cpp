#include <iostream>
#include <cmath>

#include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int input,input2, sum,sqrtn;
  bool arr[246913];
  fill_n(arr,246912,true);

  while(true){
    cin>>input;
    if(input==0){
      break;
    }
    input2=2*input;
    for(int i=2;i<input2;i++){    
      if(arr[i]){
        sqrtn=sqrt(input2);
        for(int j=2;j<sqrtn+1;j++)
      }
    }
  }

  return 0;
}

