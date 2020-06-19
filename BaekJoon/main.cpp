#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>

#include "GoodFunction.h"

using namespace std;

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  int sdoku[9][9];

  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      cin>>sdoku[i][j];
    }
  }

  Sdoku(sdoku);

 for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      cout<<sdoku[i][j]<<' ';
    }
    cout<<"\n";
  }

  return 0;
}

