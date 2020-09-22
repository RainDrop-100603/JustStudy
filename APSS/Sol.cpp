#include "Sol.h"

void BogglerandInput(vector<char>& probTable, vector<string>& wordArr){
  for(int i=0;i<25;i++){
    probTable[i]=rand()%26+'A';
  }
  int len=rand()%10+1;
  for(int i=0;i<len;i++){
    int numLen=rand()%10+1;
    string tmp;
    for(int j=0;j<numLen;j++){
      tmp.push_back(rand()%26+'A');
    }
    wordArr.push_back(tmp);
  }
}
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
  string tmpS;
  for(int i=0;i<wordNum;i++){
    cin>>tmpS;
    wordArr.push_back(tmpS);
  }
}
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr){
  /*
    제한시간 10초, 제한 메모리 2^16Kb=64MB
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
  vector<int> result;
  //인접 8칸을 의미
  vector<int> near={-6,-5,-4,-1,1,4,5,6};
  //알고리즘
  for(auto& ele:wordArr){
    //DP[i][k]=x, ele의 i번째 원소와 겹치는 위치들 x 
    int len=ele.length();
    vector<vector<int>> DP(len);
    //0번째 원소 초기조건
    for(int j=0;j<25;j++){
      if(ele[0]==probTable[j]){
        DP[0].push_back(j);
      }
    }
    //1~len-1번째 원소
    for(int i=1;i<len;i++){
      //probTable 순회
      for(int j=0;j<25;j++){
        if(ele[i]==probTable[j]){
          for(auto& ele2: DP[i-1]){
            int gap=ele2-j;
            for(auto& ele3:near){
              if(gap==ele3){
                DP[i].push_back(j);
              }
            }
          }
        }
      }
    }
    //결과, 0=no, 1=yes
    if(DP.back().empty()){
      result.push_back(0);
    }else{
      result.push_back(1);
    }
  }
  return result;
}
void BoggleGame(){
  // int testCase;
  // cin>>testCase;
  int testCase=50;
  while(testCase--){
    vector<char> probTable(25);
    vector<string> wordArr;
    //BoggleInput(probTable, wordArr);
    BogglerandInput(probTable,wordArr);
    vector<int> result=BoggleAlgo(probTable, wordArr); 
    int len=result.size();
    for(int i=0;i<len;i++){
      cout<<wordArr[i]<<" ";
      if(result[i]){
        cout<<"YES\n";
      }else{
        cout<<"NO\n";
      }
    }
  }
}
