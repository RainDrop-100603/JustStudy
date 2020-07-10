#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  unsigned long long A,B,C;
  cin>>A>>B>>C;
  
  //변수
  int power=log2(B); //2^power<=B<2^(power+1)
  vector<int> table(power+1); //table[i]=(A^(2^i))%C
  unsigned long long tmp;
  table[0]=A%C;
  for(int i=1;i<=power;i++){     
    tmp=table[i-1];
    tmp=tmp*tmp;
    tmp%=C;
    table[i]=tmp;
  }
  long long result=1;

  //계산
  for(int i=power;i>=0;i--){
    if(pow(2,i)<=B){
      result*=table[i];
      result%=C;
      B-=static_cast<int>(pow(2,i));
      // cout<<B<<"\n";
      if(B==0){
        break;
        cout<<"flag";
      }
    }
  }
  
  //출력
  cout<<result;
  
 
  return 0;
}