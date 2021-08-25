#include <iostream>

#include "useful.h"

using namespace std;

int main(){
  string test1("hogwarts"),test2("gwart");
  auto tmp=useful_getFailure(test1);
  for(auto& ele:tmp){
    cout<<ele<<" ";
  }cout<<endl;
  auto tmp2=useful_KmpSearch(test1,test2);
  for(auto& ele2: tmp2){
    cout<<ele2<<" ";
  }cout<<endl;
  return 0;
}