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
  int N,K;
  cin>>N>>K;

  //변수
  vector<vector<int>> pascalM=Remainder_nCr(N,10007);

  //계산
  
  //출력
  cout<<pascalM[N][K]<<endl;
  
  return 0;
}

