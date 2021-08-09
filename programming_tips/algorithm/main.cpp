#include <iostream>

#include "doubleControl.h"

using namespace std;

int main(){
  double a=0.099999999999999936;
  double b=0.099999999999999950;
  doubleControl dblCmp;
  int abs=dblCmp.absolute(a,b);
  int rel=dblCmp.relevance(a,b);
  int absrel=dblCmp.absRel(a,b);
  int ulp=dblCmp.unitInTheLastPlace(a,b);
  int absulp=dblCmp.absULP(a,b);
  cout<<abs<<endl<<rel<<endl<<absrel<<endl<<ulp<<endl<<absulp<<endl;
  cout<<"test";
  return 0;
}