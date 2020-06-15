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
  Alphabet(int len=0,string word=NULL):len(len), word(word){}
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
  friend ostream& operator<<(ostream& os,const Alphabet& pos); 
};

ostream& operator<<(ostream& os, const Alphabet& pos){
  os<<pos.word;
  return os;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<Alphabet> pointV;
  //template 특수화를 통해 해결해보자 

  int N;
  string words;
  Alphabet(4,words);
  Alphabet[0];
  cin>>N;
  for(int i=0;i<N;i++){
    cin>>X>>Y;
    pointV.push_back(Alphabet(X,Y));
  }

  MergeSortT(pointV,0,0,N);

  int count=1;
  int prevNum=-100001;
  int i;
  for(i=0;i<N;i++){
    if(pointV[i][0]==prevNum){
      count++;
    }else{
      if(count>1){
        MergeSortT(pointV,1,i-count,i);
      }
      prevNum=pointV[i][0];
      count=1;
    }
  }
  if(count>1){
    MergeSortT(pointV,1,i-count,i);
  }

  for(int i=0;i<N;i++){
    cout<<pointV[i]<<"\n";
  }
  
  return 0;
}

