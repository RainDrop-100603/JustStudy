#include <string>
#include <vector>
#include <iostream>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  int N=info.size();
  vector<vector<int>> table(N,vector<int>(2));  //bitmask save
  for(int i=0;i<N;i++){
    string& tmpS=info[i];
    int tmp(0);
    //언어
    switch(tmpS[0]){
      case 'c': tmp+=1; break;
      case 'j': tmp+=2; break;
      case 'p': tmp+=4; break;
    }
    tmp=tmp<<2;
    //직군
    int idx(0);
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'b': tmp+=1; break;
      case 'f': tmp+=2; break;
    }
    tmp=tmp<<2;
    //경력
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'j': tmp+=1; break;
      case 's': tmp+=2; break;
    }
    tmp=tmp<<2;
    //소울푸드
    idx=tmpS.find(' ',idx);
    idx++;
    switch(tmpS[idx]){
      case 'c': tmp+=1; break;
      case 'p': tmp+=2; break;
    }
    table[i][0]=tmp;
    //점수
    idx=tmpS.find(' ',idx);
    idx++;
    table[i][1]=stoi(tmpS.substr(idx));
  }
  int M=query.size();
  for(int i=0;i<M;i++){
    int tmp(0);
    string& tmpS=query[i];
    //언어
    switch(tmpS[0]){
      case 'c': tmp+=1; break;
      case 'j': tmp+=2; break;
      case 'p': tmp+=4; break;
      default: tmp+=7; break;
    }
    tmp=tmp<<2;
    //직군
    int idx(0);
    idx=tmpS.find(' ',idx);
    idx+=5;
    switch(tmpS[idx]){
      case 'b': tmp+=1; break;
      case 'f': tmp+=2; break;
      default: tmp+=3; break;
    }
    tmp=tmp<<2;
    //경력
    idx=tmpS.find(' ',idx);
    idx+=5;
    switch(tmpS[idx]){
      case 'j': tmp+=1; break;
      case 's': tmp+=2; break;
      default: tmp+=3; break;
    }
    tmp=tmp<<2;
    //소울푸드
    idx=tmpS.find(' ',idx);
    idx+=5;
    switch(tmpS[idx]){
      case 'c': tmp+=1; break;
      case 'p': tmp+=2; break;
      default: tmp+=3; break;
    }
    //점수
    idx=tmpS.find(' ',idx);
    idx++;;
    int num=stoi(tmpS.substr(idx));
    //비교
    int count(0);
    for(int j=0;j<N;j++){
      if((tmp&table[j][0])==table[j][0]&&table[j][1]>=num){
        count++;
      }
    }
    answer.push_back(count);
  }
  return answer;
}

int main(){

  string s1="java backend junior pizza 150";
  string s2="python frontend senior chicken 210";
  string s3="python frontend senior chicken 150";
  string s4="cpp backend senior pizza 260";
  string s5="java backend junior chicken 80";
  string s6="python backend senior chicken 50";
  vector<string> info;
  info.push_back(s1);
  info.push_back(s2);
  info.push_back(s3);
  info.push_back(s4);
  info.push_back(s5);
  info.push_back(s6);
  vector<string> query;
  string ss1="java and backend and junior and pizza 100";
  string ss2="python and frontend and senior and chicken 200";
  string ss3="cpp and - and senior and pizza 250";
  string ss4="- and backend and senior and - 150";
  string ss5="- and - and - and chicken 100";
  string ss6="- and - and - and - 150";
  query.push_back(ss1);
  query.push_back(ss2);
  query.push_back(ss3);
  query.push_back(ss4);
  query.push_back(ss5);
  query.push_back(ss6);
  solution(info,query);
  return 0;
}