#include <iostream>
#include <vector>
#include <cstring>

using namespace std;


int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  char string[1000001];
  char alp[52];
  int idx;
  fill_n(alp,52,0);
  cin>>string;
  for(int i=0;i<strlen(string);i++){
    idx=string[i];
    if(idx<='Z'){
      idx=idx-'A'+26;
    }else{
      idx=idx-'a';
    }
    alp[idx]++;
  }
  

  return 0;
}

