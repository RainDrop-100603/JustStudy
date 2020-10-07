//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;

void WildcardInput(string& wildcard,vector<string>& fileName){
  int fileNum;
  string tmp;
  cin>>wildcard>>fileNum;
  fileName.reserve(fileNum);
  for(int i=0;i<fileNum;i++){
    cin>>tmp;
    fileName.push_back(move(tmp));
  }
}
int WildcardAlgo(string& wildcard,vector<string>& fileName){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  전략1
    Dynamic Programming
    time complexity
    mem complexity
  */
  int result(0);
  return result;
}
void Wildcard(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string wildcard;
    vector<string> fileName;
    WildcardInput(wildcard,fileName);
    cout<<WildcardAlgo(wildcard,fileName)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Wildcard();
  
  return 0;
}