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
vector<int> WildcardAlgo(string& wildcard,vector<string>& fileName){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  문자열의 길이는 1~100, 알파벳 대소문자, ?, *로 구성, 공백 없음 
  ?는 문자 하나를 대응, *는 길이 0이상의 문자열 대응
  파일명의 수 1~50개
  전략1
    brtue force
        1:1 비교 원칙: 같으면 continue, 다르면 return false
        ?의 경우: 항상 continue
        *의 경우: 
            *의 다음 문자가 있을경우: 해당 문자를 찾을 때까지 continue
                다음 문자가 없을경우: return true
    Problem 
        *의 다음문자가 l이라 하자, l이 여러개 있을경우 그만큼 분기를 생성해줘야 한다.
            분기-> 재귀 
    time complexity
        wildCardLen(N)*#fileName(50)*fileNameLen(100)=5000N
    mem complexity
        N+50*100
    
  */
  vector<int> result();
  for(int i=0;i<fileName.size();i++){
    string& file=fileName[i];
    int fileLen=file.length();
    for(int j=0;j<fileLen;j++){
        
    }
  }
  return result;
}
void Wildcard(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string wildcard;
    vector<string> fileName;
    WildcardInput(wildcard,fileName);
    vector<int> result(WildcardAlgo(wildcard,fileName));
    for(auto& ele:result){
        cout<<fileName[ele]<<"\n";
    }
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Wildcard();
  
  return 0;
}
