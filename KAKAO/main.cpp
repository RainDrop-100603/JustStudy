#include <string>
#include <vector>

using namespace std;

vector<string> solution(vector<string> orders, vector<int> course) {
  vector<string> answer;
  //prepare
  int N=orders.size();  // 고객의 수
  vector<int> bitMask(N); // 주문을 비트마스크로 변경 A-Z
  for(int i=0;i<N;i++){
    for(auto& ele:orders[i]){
      bitMask[i]+=(1<<(ele-32));
    }
  }
  char M(0);
  for(auto& ele:orders){
    M=max(M,ele.back());  //알파벳중 가장 큰 값을 찾는다.
  }
  M-=32;  //A=0, Z=25
  vector<vector<bool>> bitTable(N,vector<bool>(1<<M));  // 다 비교해버린 table
  for(int i=0;i<N;i++){
    for(int j=0;j<(1<<M);j++){
      if((bitMask[i]&j)==j){
        bitTable[i][j]=true;
      }
    }
  }
  //calc
  vector<int> tmpV;
  for(int i=0;i<N;i++){
    for(int j=0;j<(1<<M);j++){
      if((bitMask[i]&j)==j){
        bitTable[i][j]=true;
      }
    }
  }

  return answer;
}