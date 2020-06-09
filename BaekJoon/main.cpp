#include <iostream>
#include <cmath>

#include "GoodFunction.h"

using namespace std;

void StarDot(int N){
  if(N==1){
    cout<<'*';
  }
  if(N==0){
    cout<<' ';
  }
  if(N>=3){
    StarDot(N/3);StarDot(N/3);StarDot(N/3);cout<<"\n";
    StarDot(N/3);StarDot(0);StarDot(N/3);cout<<"\n";
    StarDot(N/3);StarDot(N/3);StarDot(N/3);cout<<"\n";
  }
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
 int N;
 
  cin>>N;
  StarDot(N);

  return 0;
}

