#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int N;
  cin>>N;

  vector<bool> colQueen(N);       //열       
  vector<bool> lineRDQueen(2*N-1);  //오른쪽 아래로 가는 대각선, F(n)=F(y-x+N);
  vector<bool> lineLDQueen(2*N-1);  //왼쪽 아래로 가는 대각선, F(n)=F(x+y)
  // vector<Queen> currentQ;

  cout<<N_Queen(N,colQueen,lineRDQueen,lineLDQueen,0);

  /*  
    기존의 알고리즘은 i행을 체크한 후, i+1행부터 N-1행까지 모두 체크해버렸다.
      문제는 재귀를 쓰면, i+1행 체크할때는 i+2행부터 N-1행까지 모두 체크한다는 것이다
        즉 N-1행은 총 N번 체크해버리는 것이다.
    새로운 알고리즘은 i행을 체크한 후, i+1행만 체크하게 변경했다.
  */

  return 0;
}

