#include <iostream>
#include <vector>
#include <cmath>
#include <string>

#include "GoodFunction.h"

using namespace std;

class Alphabet{
  int len;
  string* word;
public:
  Alphabet(string* word=NULL,int len=0):word(word),len(len){}
  string GetString() const{
    return *word;
  }
  // Alphabet& operator=(const Alphabet& alp){
  //   len=alp.len;
  //   word=new string(*(alp.word));
  //   return *this;
  // }
  
  int operator[](const int idx){
    if(idx!=0){
      cout<<"out of int idx";
      exit(1);
    }
    return len;
  }
  friend ostream& operator<<(ostream& os,const Alphabet& pos); 
};

ostream& operator<<(ostream& os, const Alphabet& pos){
  os<<*pos.word;
  return os;
}


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<Alphabet> alpV;

  int N;
  string wordInput;
  cin>>N;
  for(int i=0;i<N;i++){
    cin>>wordInput;
    string* word=new string(wordInput);
    alpV.push_back(Alphabet(word,word->length()));
  }

  // MergeSortT(alpV,0,0,N);
  MergeSortString(alpV,0,N);

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
    cout<<alpV[i]<<"\n";
  }
  


  return 0;
}

