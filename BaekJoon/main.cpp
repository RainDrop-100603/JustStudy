#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

//#include "GoodFunction.h"

using namespace std;

//timeout
void BK2261(){
//입력
  int pointNum,x,y;
  cin>>pointNum;
  vector<pair<int,int>> v;
  for(int i=0;i<pointNum;i++){
    cin>>x>>y;
    v.push_back(make_pair(x,y));
  }
//준비
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  long long xDiff=v[0].first-v[1].first;
  long long yDiff=v[0].second-v[1].second;
  long long key=xDiff*xDiff+yDiff*yDiff;
//계산
  for(int i=0;i<pointNum;i++){
    for(int j=i+1;j<pointNum;j++){
      xDiff=v[i].first-v[j].first;
      xDiff*=xDiff;
      if(xDiff>key){
        break;
      }
      yDiff=v[i].second-v[j].second;
      yDiff*=yDiff;
      if(yDiff>key){
        break;
      }
      if(xDiff+yDiff<key){
        key=xDiff+yDiff;
      }
    }
  }
//출력
  cout<<key;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  

  //변수
  

  //계산


  
  //출력
  BK2261();
  
 
  return 0;
}