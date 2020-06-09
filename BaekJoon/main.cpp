#include <iostream>
#include <cmath>

#include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int T, N, lowPrime, primeCount;
  vector<int> primeV = GetPrimeVector(10001);
  bool primeArr[10001];
  vector<int>::iterator iter;
  for(iter=primeV.begin();iter!=primeV.end();iter++){
    primeArr[*iter]=true;
  }
  primeCount=primeV.end()-primeV.begin();
  cin>>T;
  for(int i=0;i<T;i++){
    cin>>N;
    for(iter=primeV.begin();iter!=primeV.end();iter++){
      if(*iter<=N/2){
        if(primeArr[N-*iter]){
          lowPrime=*iter;
        }
      }
    }
    cout<<lowPrime<<' '<<N-lowPrime<<"\n";
  }


  return 0;
}

