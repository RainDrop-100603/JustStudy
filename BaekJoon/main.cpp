#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

#include "GoodFunction.h"

using namespace std;



int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<int> arrayV;
  int inputN,num;
  cin>>inputN;
  for(int i=0;i<inputN;i++){
    cin>>num;
    arrayV.push_back(num);
  }
  //산술평균
  int sum=0;
  for(int nums:arrayV){
    sum+=nums;
  }
  
  cout<<(sum)/inputN<<endl;
  
  //중앙값
  MergeSort(arrayV,0,inputN);
  cout<<arrayV[inputN/2]<<endl;

  //최빈값
  int count=0;
  int maxCount=0;
  int maxCountNum=arrayV[0];
  int over=0;//같은 사이즈의 개수
  int prevNum=maxCountNum;//이전까지 같았던 수
  int nums;
  for(int i=1;i<inputN;i++){
    nums=arrayV[i];
    if(nums==prevNum){
      count++;
    }else{
      if(maxCount<count){
        maxCount=count;
        maxCountNum=prevNum;
        over=0;
      }else if(maxCount==count&&over==0){
        maxCountNum=nums;
        over++;
      }
      prevNum=nums;
      count=0;
    }
  }
  cout<<maxCountNum<<endl;
  //범위
  cout<<arrayV[inputN-1]-arrayV[0];
  return 0;
}

