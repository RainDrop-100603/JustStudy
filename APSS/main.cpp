//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
void ClockSyncInput(vector<int>& clockArr){
  for(int i=0;i<16;i++){
    cin>>clockArr[i];
  }
}
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchClock){
  /*
  제한시간 10초
  제한메모리 2^16kb=64MB
  전략1
    brute force
    time complexity
    mem complexity
  */
  //기저
  //Algo
  int result(-1);
  return result;
}
void ClockSync(){
  int testCase;
  cin>>testCase;
  vector<vector<int>> switchClock={
    {0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},
    {6,7,8,10,12},{0,2,14,15},{3,14,15},
    {4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}
  };
  while(testCase--){
    vector<int> clockArr(16);
    ClockSyncInput(clockArr);
    cout<<ClockSyncAlgo(clockArr,switchClock)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  ClockSync();

  return 0;
}