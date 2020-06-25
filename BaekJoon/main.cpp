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

  //DynmaicPrograming

  //입력
  int num, maxWeight;
  cin>>num>>maxWeight;
  vector<pair<int,int>> weightValue(num); //first=weight, second=value
  for(int i=0;i<num;i++){
    cin>>weightValue[i].first>>weightValue[i].second;
  }

  //변수 
  int MW=0;  //maxValue
  bool transbit=true; //위아래 배열을 돌아가면서 사용할건데, transbit=true면 윗 배열, false면 아랫 배열에 값을 저장할 것이라는 뜻
  vector<vector<int>> table(2,vector<int>(maxWeight+1));  //0~maxWeight까지, x열은 무게제한이 x임을 뜻한다. 원소의 값은 조건에서의 value 최대치

  //계산
  for(int i=0;i<num;i++){ //물건의 개수만큼 반복, 최대 들어갈 수 있는 개수는 물건의 개수와 같으므로
    if(transbit==true){
      for(int j=0;j<=maxWeight;j++){  //j는 무개제한
        pair<int,int>& ele=weightValue[i];
          if(j-ele.first<0){
            table[0][j]=max(table[0][j],table[1][j]);  //ele의 무게가 무게제한을 초과해서 넣을 수 없다.
          }else{
            table[0][j]=max(max(table[1][j],table[0][j]),table[1][j-ele.first]+ele.second);
          }
      }
      transbit=false;
    }else{
      for(int j=0;j<=maxWeight;j++){  //j는 무개제한
        pair<int,int>& ele=weightValue[i];
          if(j-ele.first<0){
            table[1][j]=max(table[1][j],table[0][j]);  //ele의 무게가 무게제한을 초과해서 넣을 수 없다.
          }else{
            table[1][j]=max(max(table[1][j],table[0][j]),table[0][j-ele.first]+ele.second);
          }
      }
      transbit=true;
    }
    // for(auto& ele:table){
    //   for(auto& ele2:ele){
    //     cout<<ele2<<' ';
    //   }
    //   cout<<endl;
    // }
    // cout<<endl;
  }
  
  for(auto& ele:table){
    for(auto& ele2:ele){
      if(MW<ele2){
        MW=ele2;
      }
    }
  }
  cout<<MW;
  return 0;
}

