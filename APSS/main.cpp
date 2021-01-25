//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void BoggleInput(vector<char>& probTable, vector<string>& wordArr){
  for(int i=0;i<5;i++){
    string tmpS;
    cin>>tmpS;
    for(int j=0;j<5;j++){
      probTable[5*i+j]=tmpS[j];
    }
  }
  int wordNum;
  cin>>wordNum;
  for(int i=0;i<wordNum;i++){
    string tmpS;
    cin>>tmpS;
    wordArr.push_back(tmpS);
  }
}
vector<int> Boggle_Algo2(vector<char>& probTable, vector<string>& wordArr){
  vector<int> result;
  //인접 8칸을 의미
  vector<int> commonNear={-6,-5,-4,-1,1,4,5,6};
  vector<int> rEdgeNear={-6,-5,-1,4,5};
  vector<int> lEdgeNear={-5,-4,1,5,6};
  //알고리즘
  for(auto& ele:wordArr){
    //DP[i][k]=x, ele(문장)의 i번째 원소로 k가 사용될 수 있는가(x==1 or 0)
    int len=ele.length();
    vector<vector<int>> DP(len,vector<int>(25));
    //0번째 원소 초기조건
    for(int j=0;j<25;j++){
      if(ele[0]==probTable[j]){
        DP[0][j]=1;
      }
    }
    //1~len-1번째 원소
    for(int i=1;i<len;i++){
      //probTable 순회
      for(int j=0;j<25;j++){
        if(ele[i]==probTable[j]){
          vector<int> near;
          if(j%5==1){
            near=lEdgeNear;
          }else if(j%5==0){
            near=rEdgeNear;
          }else{
            near=commonNear;
          }
          for(auto& ele: near){
            if(j+ele>=0&&j+ele<25&&DP[i-1][j+ele]==1){
              DP[i][j]=1;
              break;
            }
          }
        }
      }
    }
    //결과, 0=no, 1=yes
    int tmpResult(0);
    for(auto& ele2:DP[len-1]){
      if(ele2==1){
        tmpResult=1;
        break;
      }
    }
    result.push_back(tmpResult);
  }
  return result;
}

void BoggleGame(){
  /*실험조건
    10초, 64MB, 테스트케이스=50
    입력: 5*5 table, #word n: 1~10, each word
    출력: each word + YES or NO(table에 word가 있는가?)
  */
  /*전략1
    문제점
      1. Runtime Error -> 메모리 초과???
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
      단어의 길이 len -> len 번 순회
        i번째 순회시 i번째에 해당하는 원소를 찾는다.        25
          i-1번째 원소와 인접한지 확인후, 인접하다면 input    <=25
      N번째 원소가 empty가 아니라면, yes 출력 
      time complexity: 625*len*N
  */
  /*전략2
    문제점ㄴ
      2차원 배열이 아닌 1차원 배열 25칸에 저장한것은, 좌우모서리에서 인접 원소 chk에 문제가 발생한다. -> 코딩으로 해결보자 일단
    특징 
      지나간 글자를 다시 지나갈 수 있다, 즉 history가 중요하지 않으므로 Dynamic Programming를 이용할 수 있다.
    DynamicProgramming
      2차원 배열 DP(wordLen*25)를 이용한다. table에는 25개의 값이 있다.
        DP[i][j]=x : j 가 word의 i번째 원소가 될 수 있다면, x==1
    mem complexity
      25*10(maxWordLen)
    time complexity
      #word*10(wordLen)*25(#ele)*8(near ele chk)
  */

  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<char> probTable(25);
    vector<string> wordArr;
    BoggleInput(probTable, wordArr);
    //int testCase=50;
    //BoggleRandInput(probTable,wordArr);
    //vector<int> result=BoggleAlgo(probTable, wordArr); 
    vector<int> result=Boggle_Algo2(probTable,wordArr);
    for(int i=0;i<result.size();i++){
      cout<<wordArr[i]<<" ";
      if(result[i]){
        cout<<"YES\n";
      }else{
        cout<<"NO\n";
      }
    }
  }
}

int main(void){
  BoggleGame();
  
  return 0;
}