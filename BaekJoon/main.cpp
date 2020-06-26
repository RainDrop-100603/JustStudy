#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  int num1,num2;
  cin>>num1>>num2;

  //변수
  vector<int> primeV=GetPrimeVector(max(num1,num2));          //소수만을 저장하는 벡터
  int primeNum=primeV.size();
  vector<vector<int>> factors(2,vector<int>(primeNum));  //0행은 num1의, 1행은 num2를 구성하는 소수의 개수를 적는다. 
  int tmpPrime;
  int GCfactor=1; //최대공약수
  int LCM=1;  //최소공배수
  int big,small,tmp1,tmp2;

  //계산
    //소인수분해
  for(int i=0;i<primeNum;i++){    
    if(num1!=1||num2!=1){
      tmpPrime=primeV[i];
      while(num1%tmpPrime==0){
        num1/=tmpPrime;
        factors[0][i]++;
      }
      while(num2%tmpPrime==0){
        num2/=tmpPrime;
        factors[1][i]++;
      }
    }
  }
    //최대공약수, 최소공배수
  for(int i=0;i<primeNum;i++){
    tmpPrime=primeV[i];
    tmp1=factors[0][i];
    tmp2=factors[1][i];
    if(tmp1!=0||tmp2!=0){
      big=max(tmp1,tmp2);     //for 최소공배수
      small=min(tmp1,tmp2);   //for 최대공약수
      for(int j=0;j<small;j++){
        GCfactor*=tmpPrime;
      }
      for(int k=0;k<big;k++){
        LCM*=tmpPrime;
      }
    }
  }

  //출력
  cout<<GCfactor<<"\n"<<LCM;
  

  return 0;
}

