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
  vector<int> near={-6,-5,-4,-1,1,4,5,6};
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
    특징 
      LIS를 형성할 때, 각 원소가 가질 수 있는 위치는 하나뿐이다. (stack을 이용한 LIS를 잘 생각하면 이해 가능)
      LIS를 구성하는 원소가, 원본 arr에서 뒤에 있는 원소일수록, 사전순으로는 앞에 위치하는 LIS다.
        LIS에서 각 원소가 가질 수 있는 위치는 하나뿐인데, 같은 위치에서 arrIdx가 큰 원소라는 것은, value가 더 작은 원소임을 의미한다. (value가 더 크다면 같은 위치를 가질수가 없다.)
          증명: 임의의 LIS를 잘라서 LIS A , a , b , LIS B 로 만들었다고 하자.
                LIS A, alpha, a, LIS B로 대체하였다고 가정하면, alpha < a < b 이므로, LIS A, alpha, a, b, LIS B 라는 새로운 LIS가 생겨난다.
                따라서 임의의 alpha는 추가될수 없으므로, a 또한 위치를 변경할 수 없으며, 원소의 위치는 고정된다.
    DynamicProgramming
      stack을 이용해 LIS의 길이를 구하는 알고리즘을 이용하여, History를 구한다. -> n*lgn
        History: stack을 이용하여 LIS를 구할때, 각 stack에서의 값이 변하는 것을 history에 기록한다. 
          의의: LIS를 형성할때, 각 원소가 가질 수 있는 위치는 하나뿐이다. History를 통해 모든 원소를 검사하지 않고도 numOfCases를 구할 수 있다.
      History를 이용하여, k번째 LIS를 구한다.
        LIS의 idx번째 원소의 값이 value일 때의, idx부터 시작하는 LIS의 경우의 수 numOfCases에 대해 -> O(1)
          k>= numOfCases: k번째 LIS의 idx번째 원소의 값은 value이다.  ->  idx+1에 대해 같은 작업 수행
          k< numOfCases: idx번째 원소가 value인 LIS는 k번째 LIS보다 사전순으로 앞에서 나온다. ->  History에서 value보다 사전순으로 뒤에 있는 값을 가져오도록 한다.
        nunOfCases: idx-1위치의 {arridx,value}를 가져와서, arridx가 뒤에있고 value가 더 큰 모든 것의 numOfCases를 더한다. -> LIS_len*(n/LIS_len) ~= n 
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