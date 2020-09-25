#include "useful.h"

vector<int> getPrimeVector(int num){
  //0~num 범위의 bool arr, prime 이라면 true
  vector<bool> arr(num+1,true);
  arr[0]=false;arr[1]=false;
  for(int i=2;i<=sqrt(num);i++){  
    if(arr[i]){
      for(int j=i*2;j<=num;j+=i){
        arr[j]=false;
      }
    }
  }
  //prime number만을 원소로 가진 arr 
  vector<int> result;
  for(int i=2;i<=num;i++){
    if(arr[i]){
      result.push_back(i);
    }
  }
  return result;
}
int getGCD(int A, int B){     //유클리드 호제법을 이용한 A와 B의 GCD
  return A%B ? getGCD(B,A%B) : B; //A=qB+r, r=A%B, GCD(A,B)=GCD(B,r)=GCD(B,A%B), r==0이면 B가 최대공약수 
}
pair<long long,long long> euclidAlgo(long long A,long long B){      //Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
  if(B<A){
    return euclidAlgo(B,A);
  }
  if(B!=0){ //B=r==0이면 A가 최대공약수
    pair<long long,long long> temp=euclidAlgo(B,A%B);
    return make_pair(temp.second,temp.first-(A/B)*temp.second);
  }else{
    return make_pair(1,0);  // GCD(d,0) = dx+0y=d: 
  }
} 
int fastSum(int n){
  //기저
  if(n==1) return 1;
  //홀수
  if(n%2) return fastSum(n-1)+n;
  //짝수
  return 2*fastSum(n/2)+(n/2)*(n/2);
}


/////