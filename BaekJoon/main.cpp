#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "GoodFunction.h"

using namespace std;

//느려서 틀림, 시간초과 
//퀸이 놓여있는 bool table을 만들자
//새로운 위치에 퀸을 놓을수 있는지 bool table을 통해 체크하는 함수
//이때 이 함수는 대각선만 체크한다.가로세로는 bool table을 통해 체크
//  ㄴ  체크를 bool table이 아닌, bool 보조 table(가로세로 체크 전용)을 만들어서 많은 단계를 건너 뛸 수 있을것 같다.
//    ㄴ  가망없는것은 뛰어넘는 BackTracking에 적합하다. 
//      ㄴ  보조 table은 bool table을 참조해서 값을 업데이트 할 필요가 없다.
//대각선 체크 함수 방법
//  ㄴ  대각선은 똑같이 움직인다. 값의 차의 절대값이 같다면 대각선 관계에 있는 것이다.
//    ㄴ  |x-x1|==|y-y1|, table의 모든 값과 비교해야하는데, 이걸 굳이 N^2 table로 만들 필요가 없을 것 같다.

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int N;
  cin>>N;

  int** table=new int*[N];  //NN 
  for(int i=0;i<N;i++){
    table[i]=new int[N];
  }

  cout<<N_Queen(N,table,0,0);

  for(int i=0;i<N;i++){
    delete[] table[i];
  }
  delete[] table;

  return 0;
}

