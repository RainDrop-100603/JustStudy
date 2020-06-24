#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

void DivideAndConquer(vector<vector<int>>& table, int start, int end){
  //divide
  int middle=(end+start)/2;
  if(end-start==1){
    return;
  }else{
    DivideAndConquer(table,start,middle);
    DivideAndConquer(table,middle,end);
  }

  //conquer
  int leftOpti=table[0][start];
  int leftLT=table[1][start];
  int leftRT=table[1][middle-1];
  int rightOpti=table[0][middle];
  int rightLT=table[1][middle];
  int rightRT=table[1][end-1];

  int newOpti=max(leftRT+rightLT,max(leftOpti,rightOpti));
  if(newOpti==leftOpti){
    // table[0][start]=leftOpti;
    // table[1][start]=leftLT;
    table[1][end-1]=leftRT+rightLT+rightRT-rightOpti;
  }else if(newOpti==rightOpti){
    table[0][start]=rightOpti;
    table[1][start]=leftLT+leftRT-leftOpti+rightLT;
    table[1][end-1]=rightRT;
  }else{
    table[0][start]=newOpti;
    table[1][start]=newOpti+leftLT-leftOpti;
    table[1][end-1]=newOpti+rightRT-rightOpti;
  }
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //DynmaicPrograming

  //입력
  int num;
  cin>>num;
  vector<int> number(num);

  for(int i=0;i<num;i++){
    cin>>number[i];
  }

  //변수 
  vector<vector<int>> table(2,number); //0은 opti, 1은 leftest 2는 rightest

  DivideAndConquer(table,0,num);  //[0,num)까지 정렬  
  
  cout<<table[0][0];

  return 0;
}

