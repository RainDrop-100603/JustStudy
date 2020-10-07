//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

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
bool Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
  //기저, 범위를 벗어나는 경우
  int f_len(file.length());
  if(f_idx==f_len){
    return false;
  }
  //wildcard의 w_idx, file의 f_idx부터 비교한다.
  char& result=DP[w_idx][f_idx];
  //답이 이미 있을경우
  if(result!=-1){
    return result;
  }
  //w_idx==w_len까지, wildcard를 모두 비교하는것이 목표
  int w_len(wildcard.length());
  while(w_idx<w_len&&f_idx<f_len){
    char w_char=wildcard[w_idx];
    if(w_char==file[f_idx]||w_char=='?'){
      w_idx++;f_idx++;
      continue;
    }
    if(w_char=='*'){
      //*에 하나이상 대응
      if(Wildcard_match(wildcard,file,w_idx,f_idx+1,DP)){
        return result;
      }
      //*에 0개 대응
      w_idx++;
      continue;
    }
    //*도 아니고, 두 문자도 다른경우 false;
    result=0;
    return result;
  }
  //f_len은 반드시 모두 매칭되어야 하며, w_len은 마지막 부분이 모두 *라면 모두 매칭되지 않아도 괜찮다.
  if(f_len==f_idx){
    if(w_len!=w_idx){
      for(int i=w_idx;i<w_len;i++){
        if(wildcard[i]!='*'){
          result=0;
          break;
        }
      }
    }
    result=1;
  }else{
    result=0;
  }
  return result;
}
vector<int> WildcardAlgo(string& wildcard,vector<string>& fileArr){
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
        *의 경우: f_idx+1로 재귀
      반환 경우의 수
        w_idx와 f_idx가 마무리 -> return true;
        w_idx만 마무리-> return false;
        f_idx만 마무리-> w_idx에 남은것이 *뿐이라면 true, 다른것도 있다면 false; 
      DP
        반환하기 전에 DP[w_idx][f_idx]에 1(true) 0(false)저장, -1(not initialized)
        DP여부 맨 처음에 확인 
    time complexity
      wildCardLen(100)*fileLen(100)*#file(50)
    mem complexity
      wildcard(100)+DP(100*100)+fileArr(100*50)
  */
  vector<int> result;
  for(int i=0;i<fileArr.size();i++){
    string& file=fileArr[i];
    vector<vector<char>> DP(wildcard.length(),vector<char>(file.length(),-1));
    if(Wildcard_match(wildcard,file,0,0,DP)){
      result.push_back(i);
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
    vector<int> result(WildcardAlgo(wildcard,fileArr));
    for(auto& ele:result){
        cout<<fileArr[ele]<<"\n";
    }
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Wildcard();
  
  return 0;
}
