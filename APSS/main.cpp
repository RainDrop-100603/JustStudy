//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
void QuadTreeInput(string& treeData){
  cin>>treeData;
}
string QuadTreeAlgo(string::iterator& iter){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  전략1
    기저: b or w를 만났을 때, 그대로 반환
    재귀: x를 만났을 때, 이때 상하반전 이므로 순서를 바꿔야 한다. 이때 반환되어 오는 값을 result에 더한다 
      1234 순서가 3412 순서로
    반환: string 값을 합쳐서 반환
    time complexity
      O(N): N 번 호출, 총 길이 N 만큼 문자열 합
    mem complexity
      O(N)
    업데이트
      iterator를 이용하여 전달인자 간소화
  */
  //기저, b and w
  char head=*iter;
  iter++;
  if(head=='b'||head=='w'){
    return string(1,head);
  }
  //Algo, x인 경우
  string tmp[4];
  for(int i=0;i<4;i++){
    tmp[i]=QuadTreeAlgo(iter);
  }
  return string("x")+tmp[2]+tmp[3]+tmp[0]+tmp[1];
}
void QuadTree(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string treeData;
    QuadTreeInput(treeData);
    string::iterator iter=treeData.begin();
    cout<<QuadTreeAlgo(iter)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  QuadTree();

  return 0;
}