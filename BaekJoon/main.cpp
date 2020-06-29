#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int Gcd(int big,int small){ 
  return big%small ? Gcd(small,big%small) : small;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  int num;
  cin>>num;
  vector<int> numbers(num);
  for(auto& ele:numbers){
    cin>>ele;
  }

  //변수
  sort(numbers.begin(),numbers.end());    //A0 ~ AN-1
  int gcd;//최대공약수
  int num0=numbers[0];

  //계산
  gcd=numbers[1]-num0;
  for(int i=2;i<num;i++){
    gcd=Gcd(numbers[i]-num0,gcd);
  }

  //출력
  vector<int> resultV;
  for(int i=1;i*i<=gcd;i++){
    if(gcd%i==0){
      resultV.push_back(i);
      resultV.push_back(gcd/i);
    }
  }
  sort(resultV.begin(),resultV.end());
  resultV.erase(unique(resultV.begin(),resultV.end()),resultV.end());
  for(int i=1;i<resultV.size();i++){
    cout<<resultV[i]<<' ';
  }
  

  return 0;
}

