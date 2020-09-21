//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;

void BoggleGame(){
  /*
    제한시간 10초 
    brute force
      8방향을 확인하여 단어를 순서대로 만든다 -> R, E, P, E, A, T
        bool boggle(string word, int idx, pair<int,int> point);  //word의 idx번째가 point와 값이 같은지 chk;
      time complexity : 단어의 길이 N 개수 M, M*25*8^(N-1), 지수시간 
    graph
      DFS나 BFS는 brute force와 다를것이 없어보인다.
    DP1
      단어에서 각 원소가 있는 위치를 저장한다 ex) p r e t t y 에서 행렬을 한번만 순회하며 각 원소가 있는 위치를 저장한다.
      맨 처음 위치가 존재한다면, 다음 원소가 기존 원소와 인접하는지 확인 -> 상수 연산하면 되므로 1 cost
        인접하는 경우, 다음 원소 탐색  p->r
        인접하지 않는경우, 같은 원소의 다른위치로 다시  p1->p2
    DP2
      단어의 길이 N -> N 번 순회
        i번째 순회시 i번째에 해당하는 원소를 찾는다.        25
          i-1번째 원소와 인접한지 확인후, 인접하다면 input    <=25
      N번째 원소가 empty가 아니라면, yes 출력 
      time complexity: 625*N
  */
  int testCase,numWords;
  cin>>testCase;
  //2차원 배열이지만 한줄로 간단하게 처리
  vector<char> table(25);  
  for(int i=0;i<5;i++){
    string tmpS;
    cin>>tmpS;
    for(int j=0;j<5;j++){
      table[5*i+j]=tmpS[j];
    }
  }
  //단어 입력
  cin>>numWords;
  vector<string> wordArr(numWords);
  for(auto& ele:wordArr){
    cin>>ele;
  }
  //알고리즘
  for(auto& ele:wordArr){
    //DP[i][k]=x, ele의 i번째 원소의 위치는 x (k는 단순 idx)
    int len=ele.length();
    vector<vector<int>> DP(len);
    //i=0일때 초기조건
    for(int i=0;i<25;i++){
      if(ele[0]==)
    }
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  BoggleGame();

  return 0;
}