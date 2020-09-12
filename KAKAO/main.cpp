#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  int N=info.size();
  vector<vector<int>> table(N,vector<int>(5));  //bitmask save
  for(int i=0;i<N;i++){
    string& tmpS=info[i];
    int tmp;
    //언어
    switch(tmpS[0]){
      case 'c': tmp=1; break;
      case 'j': tmp=2; break;
      case 'p': tmp=4; break;
      default: tmp=7; break;
    }
    table[i][0]=tmp;
    //직군
    int idx(0);
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'b': tmp=1; break;
      case 'f': tmp=2; break;
      default: tmp=3; break;
    }
    table[i][1]=tmp;
    //경력
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'j': tmp=1; break;
      case 's': tmp=2; break;
      default: tmp=3; break;
    }
    table[i][2]=tmp;
    //소울푸드
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'c': tmp=1; break;
      case 'p': tmp=2; break;
      default: tmp=3; break;
    }
    table[i][3]=tmp;
    //
    idx=tmpS.find(' ',idx);
    idx++;
    table[i][4]=stoi(tmpS.substr(idx));
  }
  
  return answer;
}

int main(){

  string s1="java backend junior pizza 150";
  string s2="python frontend senior chicken 210";
  string s3="python frontend senior chicken 150";
  cout<<s1[s1.find(' ',5)+1]<<endl;
  return 0;
}