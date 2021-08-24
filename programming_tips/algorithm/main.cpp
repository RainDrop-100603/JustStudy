#include <iostream>

#include "useful.h"

using namespace std;

int main(){
  string test1("aabaabac");
  auto tmp=useful_getFailure(test1);
  for(auto& ele:tmp){
    cout<<ele<<endl;
  }
  return 0;
}