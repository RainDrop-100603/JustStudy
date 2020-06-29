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
  int gcd;
  int ring1=numbers[0];

  //계산
  

  //출력
  for(int i=1;i<numbers.size();i++){
    gcd=Gcd(ring1,numbers[i]);
    cout<<ring1/gcd<<'/'<<numbers[i]/gcd<<"\n";
  }

  return 0;
}

