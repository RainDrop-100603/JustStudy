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
  
  int inputNum;
  cin>>inputNum;
  vector<int> arrayV(inputNum);
  for(auto& ele:arrayV){
    cin>>ele;
  }
  int AddSubMulDiv[4];  
  for(auto& ele:AddSubMulDiv){
    cin>>ele;
  }

  int max=-1000000001;
  int min=1000000001;

  GetMaxMin(arrayV,AddSubMulDiv,max,min,0,arrayV[0]); //idx번째까지의 결과(sum)와 idx+1번째 수를 계산. idx=arrayV.len()이면 max min 체크

  cout<<max<<"\n"<<min;


  return 0;
}

