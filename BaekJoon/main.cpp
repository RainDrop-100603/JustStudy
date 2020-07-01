#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  

  //변수
  string s;
  s.reserve(100);
  vector<bool> v; 
  v.reserve(100);
  bool isOK=true;
  char tmp;
  
  //계산

  getline(cin,s,'.');
  while(!s.empty()){
    v.clear();
    isOK=true;
    int len=s.size();
    for(int i=0;i<len;i++){
      tmp=s[i];
      if(tmp=='('){
        v.push_back(true);
      }else if(tmp==')'){
        if(v.back()){
          v.pop_back();
        }else{
          isOK=false;
          break;
        }
      }else if(tmp=='['){
        v.push_back(false);
      }else if(tmp==']'){
        if(!v.back()){
          v.pop_back();
        }else{
          isOK=false;
          break;
        }
      }
    }
    if(isOK){
      cout<<"yes"<<"\n";
    }else{
      cout<<"no"<<"\n";
    }
    s.clear();
    getline(cin,s,'.');
    if(s[0]=='\n'){
      s=s.substr(1);
    }
  }
  

  //출력

  
  return 0;
}

