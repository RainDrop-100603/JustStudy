#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;



int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int testCase,num; 
  string oper,element;
  cin>>testCase;
  
  //변수
  DequeLL2 deque;
  int operlen;
  bool error;
  int dequelen;
  // string::size_type sz;
  int toBePop=0;
  
  //계산
  while(testCase--){
    cin>>oper>>num>>element;
    
    //입력부
    deque.clear();
    // sz=0;
    // for(int i=0;i<num;i++){
    //   element=element.substr(sz+1);
    //   deque.Push_back(stoi(element,&sz));
    // }
    if(element.size()>2){
      for(int i=1;i<element.size();i++){
        if(element[i]>='0'&&element[i]<='9'){
          toBePop*=10;
          toBePop+=element[i]-'0';
        }else{
          deque.Push_back(toBePop);
          toBePop=0;
        }
      }
    }
    
    //연산부
    error=false;
    operlen=oper.size();
    for(int i=0;i<operlen;i++){
      if(oper[i]=='R'){
        deque.changeSignal();
      }else{
        if(deque.Pop_front()==-1){
          error=true;
          break;
        }
      }
    }

    //츌력부
    if(error){
      cout<<"error"<<"\n";
      continue;
    }else{
      dequelen=deque.Size();
      cout<<'[';
      if(dequelen>0){
        cout<<deque.Pop_front();
        for(int i=0;i<dequelen-1;i++){
          cout<<','<<deque.Pop_front();
        }
      }
      cout<<']'<<"\n";
    }
  }

  
  //출력
  
 
  return 0;
}