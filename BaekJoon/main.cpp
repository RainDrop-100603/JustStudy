#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "GoodFunction.h"

using namespace std;

//느려서 틀림, 시간초과 

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int N;
  cin>>N;

  int** table=new int*[N];  //NN 
  for(int i=0;i<N;i++){
    table[i]=new int[N];
  }

  cout<<N_Queen(N,table,0,0);

  for(int i=0;i<N;i++){
    delete[] table[i];
  }
  delete[] table;

  return 0;
}

