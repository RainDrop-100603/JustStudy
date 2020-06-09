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
bool* GetPrimeArray(int num){
  num++;
  bool* array=new bool[num+1];
  fill_n(array,num+1,true);
  array[0]=false;
  array[1]=false;
  for(int i=2;i<sqrt(num);i++){
    if(array[i]){
      for(int j=i*2;j<num+1;j+=i){
        if(array[j]){
          array[j]=false;
        }
      }
    }
  }
  return array;
}
vector<int> GetPrimeVector(int num){
  vector<int> prime;
  bool* array= GetPrimeArray(num);
  for(int i=0;i<num+1;i++){
    if(array[i]){
      prime.push_back(i);
    }
  }
  return prime;
}
