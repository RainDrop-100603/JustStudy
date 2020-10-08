//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void WildcardInput(string& wildcard,vector<string>& fileArr){
  int fileNum;
  string tmp;
  cin>>wildcard>>fileNum;
  fileArr.reserve(fileNum);
  for(int i=0;i<fileNum;i++){
    cin>>tmp;
    fileArr.push_back(move(tmp));
  }
}
bool Wildcard_match2(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
  //답이 이미 있을경우
  char& result=DP[w_idx][f_idx];
  if(result!=-1){
    return result;
  }
  //1:1 대응시 다음 idx로 넘어간다.
  int w_len(wildcard.length()),f_len(file.length());
  if(w_idx<w_len&&f_idx<f_len&&(wildcard[w_idx]==file[f_idx]||wildcard[w_idx]=='?')){
    return result=Wildcard_match2(wildcard,file,w_idx+1,f_idx+1,DP);
  }
  //wildcard search가 끝났을 경우, file search도 끝났어야 match가 된 것이다.
  if(w_idx==w_len){
    return result=(f_idx==f_len);
  }
  // *이 있을 경우, *와 대응되는것의 길이가 0인 경우(w_idx+1)와 1이상인 경우(f_idx+1)로 구분, 이때 match함수에는 f_idx==file_len에 대한 조건이 없으므로, 제한조건에 추가한다.
  if(wildcard[w_idx]=='*'){
    if(Wildcard_match2(wildcard,file,w_idx+1,f_idx,DP)||(f_idx<f_len&&Wildcard_match2(wildcard,file,w_idx,f_idx+1,DP))){
      return result=1;
    }
  }
  //나머지 경우에는 문자열과 wildcard가 대응되지 않는다.
  return result=0;
}
vector<string> WildcardAlgo(string& wildcard,vector<string>& fileArr){
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
        *의 다음 문자가 있을경우: 해당 문자를 찾을 때까지 continue -------Problem-------
            다음 문자가 없을경우: return true
    Problem 
      *의 다음문자가 l이라 하자, l이 여러개 있을경우 그만큼 분기를 생성해줘야 한다.
        분기-> 재귀, 재귀: 중복 생성 가능, 중복: DP로 해결
    time complexity
      wildCardLen(N)*#fileArr(50)*fileNameLen(M)^numOf*(L)=50N*M^L
    mem complexity
      100+50*100
  전략 2
    Dynamic Programming
      Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx)
        wildcard의 w_idx와 file의 f_idx 비교
      재귀를 통한 완전 탐색을 기준으로 한다.
        1:1 비교 원칙: 같으면 continue, 다르면 return false
        ?의 경우: 항상 continue
        *의 경우: f_idx+1로 재귀 or w_idx+1로 loop 이어서
      반환 경우의 수
        w_idx와 f_idx가 마무리 -> return true;
        w_idx만 마무리-> return false;
        f_idx만 마무리-> w_idx에 남은것이 *뿐이라면 true, 다른것도 있다면 false; 
      DP
        반환하기 전에 DP[w_idx][f_idx]에 1(true) 0(false)저장, -1(not initialized)
        DP여부 맨 처음에 확인 
    time complexity
      wildCardLen(100)*fileLen(100)*loopInMatch(100) = O(n^3);
    mem complexity
      wildcard(100)+DP(100*100)+fileArr(100*50) = O(n);
  전략 3
    Dynamic Programming
      전략2에서 함수 내 재귀를 없앤다. -> O(n^2)
    time complexity
      wildCardLen*fileLen=O(n^2);
    mem complexity
      same as 전략 2
  */
  vector<string> result;
  for(int i=0;i<fileArr.size();i++){
    string& file=fileArr[i];
    vector<vector<char>> DP(wildcard.length()+1,vector<char>(file.length()+1,-1));
    if(Wildcard_match2(wildcard,file,0,0,DP)){
      result.push_back(file);
    }
  }
  return result;
}
void Wildcard(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string wildcard;
    vector<string> fileArr;
    WildcardInput(wildcard,fileArr);
    vector<string> result(WildcardAlgo(wildcard,fileArr));
    sort(result.begin(),result.end());
    for(auto& ele:result){
        cout<<ele<<"\n";
    }
  }
}


int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Wildcard();
  
  return 0;
}
