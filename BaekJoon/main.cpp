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

  while(true){
    getline(cin,s,'.');
    if(s[0]=='\n'){
      s=s.substr(1);
    }
    if(s.empty()){
      break;
    }
    v.clear();
    isOK=true;
    for(int i=0;i<s.size();i++){
      tmp=s[i];
      if(tmp=='('){
        v.push_back(true);
      }else if(tmp==')'){
        if(v.empty()){
          isOK=false;
          break;
        }else if(v.back()){
          v.pop_back();
        }else{
          isOK=false;
          break;
        }
      }else if(tmp=='['){
        v.push_back(false);
      }else if(tmp==']'){
        if(v.empty()){
          isOK=false;
          break;
        }else if(!v.back()){
          v.pop_back();
        }else{
          isOK=false;
          break;
        }
      }
    }
    if(!isOK||!v.empty()){
      cout<<"no"<<"\n";
    }else{
      cout<<"yes"<<"\n";
    }
  }
  

  //출력

  
  return 0;
}

