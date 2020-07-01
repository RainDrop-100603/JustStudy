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

  //Math3

  //입력
  int testCase;
  cin>>testCase;
  int clothesNum;   //옷의 개수
  string clothesType;  //vector에 저장
  string clothesName;  //버린다

  bool newClothes;
  while(testCase--){

    vector<pair<string,int>> clothesV;  // 옷의 종류, 개수
    newClothes=true;
    cin>>clothesNum;


    for(int j=0;j<clothesNum;j++){
      cin>>clothesName>>clothesType;
      for(auto& ele: clothesV){
        if(ele.first==clothesType){
          ele.second++;
          newClothes=false;
          break;
        }
      }
      if(newClothes){
        clothesV.push_back(make_pair(clothesType,1));
      }
    }

  //계산
    int numOfCases=1;
    for(auto& ele:clothesV){
    numOfCases*=ele.second+1;
    }
    cout<<numOfCases-1<<"\n";

  }

  //변수

  //계산
  
  //출력
 
  
  return 0;
}

