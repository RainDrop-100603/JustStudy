#include <iostream>

#include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<int> inputV;
  int input;
  int Maxinput=-1;
  cin>>input;
  while(input!=0){        //input을 벡터로 받았다.
    if(input>Maxinput){
      Maxinput=input;
    }
    inputV.push_back(input);
    cin>>input;
  }
  
  vector<int> primeV= GetPrimeVector(Maxinput*2+1);   //[0,2n+1) 범위의 소수 벡터 반환

  vector<int>::iterator iter;
  vector<int>::iterator iterS=inputV.begin();
  vector<int>::iterator iterF=inputV.end();
  vector<int>::iterator iter2;
  vector<int>::iterator iter2S=primeV.begin();
  vector<int>::iterator iter2F=primeV.end();
  for(iter=iterS;iter!=iterF;iter++){
    int numS=*iter;
    int numF=2*numS;
    int count=0;;  //개수
    for(iter2=iter2S;iter2!=iter2F;iter2++){
      int num=*iter2;
      if(num<=numS){
        continue;
      }else if(num>numF){
        break;
      }
      count++;
    }
    cout<<count<<"\n";
  }



  return 0;
}

