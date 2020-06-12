#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

// #include "GoodFunction.h"

using namespace std;



int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int inputN,input;
  cin>>inputN;
  int array[10001];
  for(int i=0;i<inputN;i++){
    cin>>input;
    array[input]++;
  }
  for(int i=1;i<10001;i++){
    for(int j=0;j<array[i];j++){
      cout<<i<<"\n";
    }
  }

  
  return 0;
}

