#include <iostream>

using namespace std;

bool isPrime(int num){
  if(num%2==0){
    if(num==2){
      return true;
    }
    return false;
  }
  if(num==1){
    return false;
  }
  int tstNum=num-2;
  while(tstNum>1){
    if(num%tstNum==0){
      return false;
    }
  }
  return true;
}