#include <iostream>
#include <cmath>

#include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int M, N;
  cin>>M>>N;

  vector<int> primeV=GetPrimeVector(N);
  vector<int>::iterator iter;
  vector<int>::iterator iterS=primeV.begin();
  vector<int>::iterator iterF=primeV.end();
  for(iter=iterS;iter!=iterF;iter++){
    if(*iter>=M){
      cout<<*iter<<"\n";
    }
  }

  return 0;
}

