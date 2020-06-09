#include "GoodFunction.h"

bool IsPrime(int num){
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
    tstNum-=2;
  }
  return true;
}
vector<int> GetPrimeVector(int num){
  num++;
  vector<int> prime;
  vector<int>::iterator iter;
  vector<int>::iterator iterStart;
  vector<int>::iterator iterFinish;
  if(num<=1){
    return prime;
  }
  prime.push_back(2);

  for(int i=2;i<num;i++){
    if(i%2==0){ //2의 배수는 빠르게 거른다.
      continue;
    }
    iterStart=prime.begin();
    iterFinish=prime.end();
    for(iter=iterStart;iter!=iterFinish;iter++){
      if(i%*iter==0){ //숫자를 소수로 하나씩 나눠서, 나누어 떨어지면 break;
        break;        //소수라면 iter==iterFinish가 된다.
      }
    }
    if(iter==iterFinish){
      prime.push_back(i); //소수 i를 prime에 push_back
    }
  }
  return prime;
}

