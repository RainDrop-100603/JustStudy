#include <string>
#include <vector>
#include <map>
#include <utility>

using namespace std;

vector<int> solution(vector<string> info, vector<string> query) {
  vector<int> answer;
  int N=info.size();
  multimap<int,int> table;  //bitmask save
  for(int i=0;i<N;i++){
    string& tmpS=info[i];
    int tmp(0);
    int idx(0);
    //언어
    switch(tmpS[0]){
      case 'c': tmp+=1; idx+=4; break;
      case 'j': tmp+=2; idx+=5; break;
      case 'p': tmp+=4; idx+=7; break;
    }
    tmp=tmp<<2;
    //직군
    switch(tmpS[idx]){
      case 'b': tmp+=1; idx+=8; break;
      case 'f': tmp+=2; idx+=9; break;
    }
    tmp=tmp<<2;
    //경력
    switch(tmpS[idx]){
      case 'j': tmp+=1; idx+=7; break;
      case 's': tmp+=2; idx+=7; break;
    }
    tmp=tmp<<2;
    //소울푸드
    switch(tmpS[idx]){
      case 'c': tmp+=1; idx+=8; break;
      case 'p': tmp+=2; idx+=6; break;
    }
    //점수
    int num=stoi(tmpS.substr(idx));
    table.insert({num,tmp});
  }
  int M=query.size();
  answer.reserve(M);
  for(int i=0;i<M;i++){
    int tmp(0);
    int idx(0);
    string& tmpS=query[i];
    //언어
    switch(tmpS[0]){
      case 'c': tmp+=1; idx+=8; break;
      case 'j': tmp+=2; idx+=9; break;
      case 'p': tmp+=4; idx+=11; break;
      case '-': tmp+=7; idx+=6; break;
    }
    tmp=tmp<<2;
    //직군
    switch(tmpS[idx]){
      case 'b': tmp+=1; idx+=12; break;
      case 'f': tmp+=2; idx+=13; break;
      case '-': tmp+=3; idx+=6; break;
    }
    tmp=tmp<<2;
    //경력
    switch(tmpS[idx]){
      case 'j': tmp+=1; idx+=11; break;
      case 's': tmp+=2; idx+=11; break;
      case '-': tmp+=3; idx+=6; break;
    }
    tmp=tmp<<2;
    //소울푸드
    switch(tmpS[idx]){
      case 'c': tmp+=1; idx+=8; break;
      case 'p': tmp+=2; idx+=6; break;
      case '-': tmp+=3; idx+=2; break;
    }
    //점수
    int num=stoi(tmpS.substr(idx));
    //비교
    int count(0);
    auto END=table.end();
    for(auto iter=table.lower_bound(num);iter!=END;iter++){
      if((iter->second&tmp)==iter->second){
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