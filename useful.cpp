#include "useful.h"

vector<int> GetPrimeVector(int num){
  vector<bool> arr(num+1,true);
  arr[0]=false;arr[1]=false;
  for(int i=2;i<=sqrt(num);i++){  
    if(arr[i]){
      for(int j=i*2;j<=num;j+=i){
        arr[j]=false;
      }
    }
  }
  vector<int> result;
  for(int i=2;i<=num;i++){
    if(arr[i]){
      result.push_back(i);
    }
  }
  return result;
}
int GetGCD(int A, int B){     //유클리드 호제법을 이용한 A와 B의 GCD
  return A%B ? GetGCD(B,A%B) : B; //A=qB+r, r=A%B, GCD(A,B)=GCD(B,r)=GCD(B,A%B), r==0이면 B가 최대공약수 
}
pair<long long,long long> EuclidAlgo(long long A,long long B){      //조건: A>B  ____  Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
  if(B!=0){ //B=r==0이면 A가 최대공약수
    pair<long long,long long> temp=EuclidAlgo(B,A%B);
    return make_pair(temp.second,temp.first-(A/B)*temp.second);
  }else{
    return make_pair(1,0);  // GCD(d,0) = dx+0y=d: 
  }
} 