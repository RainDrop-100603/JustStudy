//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
void PicnicInput(vector<vector<bool>>& friendTable){
  int studentNum,friendNum;
  cin>>studentNum>>friendNum;
  //n*n table로 변경
  for(int i=0;i<studentNum;i++){
    friendTable.push_back(vector<bool>(studentNum));
  }
  int num1,num2;
  for(int i=0;i<friendNum;i++){
    cin>>num1>>num2;
    friendTable[num1][num2]=true;
    friendTable[num2][num1]=true;
  }
}
int PicnicAlgo(vector<vector<bool>>& friendTable,int std1, int std2){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  조합 문제
    12 34 56 과 21 65 43은 같은 조합.
    최대 경우의 수:10C2*8C2*6C2*4C2*2C2/(5!)=2310
  brute force
    재귀

  */
  int result(0),studentNum(friendTable.size());
  
  return result;
}
void Picnic(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<bool>> friendTable;
    PicnicInput(friendTable);
    int result=PicnicAlgo(friendTable,0,1);
    cout<<result<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Picnic();

  return 0;
}