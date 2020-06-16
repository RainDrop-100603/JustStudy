#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "GoodFunction.h"

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<string> stringV;

  int N;
  string wordInput;
  cin>>N;
  for(int i=0;i<N;i++){
    cin>>wordInput;
    stringV.push_back(wordInput);
  }

  MergeSortStrlen(stringV,0,N);
  // MergeSortString(stringV,0,N);

  // int count=1;
  // int prevNum=-100001;
  // int i;
  // for(i=0;i<N;i++){
  //   if(pointV[i][0]==prevNum){
  //     count++;
  //   }else{
  //     if(count>1){
  //       MergeSortT(pointV,1,i-count,i);
  //     }
  //     prevNum=pointV[i][0];
  //     count=1;
  //   }
  // }
  // if(count>1){
  //   MergeSortT(pointV,1,i-count,i);
  // }
  cout<<endl;
  for(int i=0;i<N;i++){
    cout<<stringV[i]<<"\n";
  }
  


  return 0;
}

