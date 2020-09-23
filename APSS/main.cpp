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
int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  조합 문제
    12 34 56 과 21 65 43은 같은 조합.
    최대 경우의 수:10C2*8C2*6C2*4C2*2C2/(5!)=2310
  brute force
    재귀
      Algo(frientTable,input toBePush)
        stack에는 한번에 두개씩 들어간다, 이때 두번째 원소는 항상 첫번째 원소보다 크다
        stack의 짝수idx(홀수번째 수)는 오름 차순이다.
          ex) 09 15 27 34 68
      첫번째 위치에는 남은 것 중 가장 앞의것을 input, 두번째 위치는 가능한 모든것 input 후 재귀
        toBePush[idx]=true: idx push 가능
        friend인 경우에만 input
      기저: stack의 크기가 10 -> return 1;
  */
  //기저
  int studentNum(friendTable.size());
  bool isFinish(true);
  for(auto&& ele: toBePush){
    if(ele){
      isFinish=false;
      break;
    }
  }
  if(isFinish){
    return 1;
  }
  //첫번째 원소
  int result(0),first,second;
  for(int i=0;i<studentNum;i++){
    if(toBePush[i]){
      first=i;
      toBePush[first]=false;
      break;
    }
  }
  //두번째원소
  for(int i=first+1;i<studentNum;i++){
    if(toBePush[i]){
      second=i;
      if(friendTable[first][second]){
        toBePush[second]=false;
        result+=PicnicAlgo(friendTable,toBePush);
        toBePush[second]=true;
      }
    }
  }
  toBePush[first]=true;
  return result;
}
void Picnic(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<bool>> friendTable;
    PicnicInput(friendTable);
    vector<bool> toBePush(friendTable.size(),true);
    int result=PicnicAlgo(friendTable,toBePush);
    cout<<result<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Picnic();

  return 0;
}