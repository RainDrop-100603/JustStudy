#include <iostream>
#include <cmath>
#include <vector>
#include <string>

#include "GoodFunction.h"

using namespace std;

class Alphabet{
  int len;
  string word;
public:
  Alphabet(string word,int len):len(len), word(word){}
  Alphabet& operator= (const Alphabet& alp){
    len=alp.len;
    word=alp.word;
    return *this;
  }
  int GetLen() const{
    return len;
  }
  string GetWord() const{
    return word;
  }
  int operator[](const int idx){
    if(idx>0){
      cout<<"out of int idx";
      exit(1);
    }
    return len;
  }
  friend ostream& operator<<(ostream& os,const Alphabet& pos); 
};

ostream& operator<<(ostream& os, const Alphabet& pos){
  os<<pos.word;
  return os;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<Alphabet> alpV;
  //template 특수화를 통해 해결해보자 

  int N;
  string words;
  cin>>N;
  for(int i=0;i<N;i++){
    cin>>words;
    alpV.push_back(Alphabet(words,words.length()));
  }

  MergeSortT<0>(alpV,0,N);

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

  for(int i=0;i<N;i++){
    cout<<alpV[i]<<"\n";
  }
  
  return 0;
}

