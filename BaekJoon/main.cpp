#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

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

  //빈 공간의 위치를 저장하는 vector
  vector<pair<int,int>> empty;          
  for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      if(sdoku[i][j]==0){
        empty.push_back(pair<int,int>(i,j));
      }
    }
  }

  Sdoku(sdoku,empty,0,empty.size());

  cout<<endl;
 for(int i=0;i<9;i++){
    for(int j=0;j<9;j++){
      cout<<sdoku[i][j]<<' ';
    }
    cout<<"\n";
  }

  return 0;
}

