#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

// #include "GoodFunction.h"

using namespace std;

vector<int>& Merge(vector<int> &v1, int start, int end){  //[start,end)
  vector<int>::iterator iterS=v1.begin()+start;         //앞부분의 시작 iter
  vector<int>::iterator iterM=v1.begin()+(end-start)/2; //뒷부분의 끝 iter = 뒷부분의 시작 iter
  vector<int>::iterator iterF=v1.begin()+end;           //뒷부분의 끝 iter
  vector<int>::iterator rotate1=iterS; //앞부분의 rotate
  vector<int>::iterator rotate2=iterM; //뒷부분의 rotate
  vector<int>::iterator mainRotate=iterS; // S까지 sorting이 된 것이다 
  while(!(rotate1==iterM&&rotate2==iterF)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    if(rotate1==iterM){

      continue;
    }else if(rotate2==iterF){

      continue;
    }
  }
  // while(!(v1.empty()&&v2.empty())){
  //   if(v1.empty()){
  //     mergedV.push_back(*v2.begin());
  //     v2.erase(v2.begin());
  //     continue;
  //   }else if(v2.empty()){
  //     mergedV.push_back(*v1.begin());
  //     v1.erase(v1.begin());
  //     continue;
  //   }
    
  //   if(*v1.begin()<*v2.begin()){
  //     mergedV.push_back(*v1.begin());
  //     v1.erase(v1.begin());
  //   }else{
  //     mergedV.push_back(*v2.begin());
  //     v2.erase(v2.begin());
  //   }
  // }
  // v1.swap(mergedV); //참조형으로 반환하고 싶기 때문에 swap 해주었다.
  return v1;
}


vector<int>& MergeSort(vector<int> &v1){
  //divide
  int len=v1.size();
  vector<int> v2;
  vector<int>::iterator iter;
  if(len==1){
    return v1;
  }else{
    for(iter=v1.begin()+len/2;iter!=v1.end();iter++){ //len/2부터 end까지 v2에 복사
      v2.push_back(*iter);
    }
    v1.erase(v1.begin()+len/2,v1.end());
  }

  //merge & conquer
  vector<int> mergedVector;
  mergedVector=Merge(MergeSort(v1),MergeSort(v2));

  v1.swap(mergedVector);
  return v1;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  //입력 받기 및 벡터 형성
  int vectorSize, num;
  cin>>vectorSize;
  vector<int> arrayV;
  for(int i=0;i<vectorSize;i++){
    cin>>num;
    arrayV.push_back(num);
  }
  //sorting
  MergeSort(arrayV);  //참조형식이기 때문에 반환형 불필요
  //출력 
  vector<int>::iterator iter;
  for(int number:arrayV){
    cout<<number<<"\n";
  }
  
  return 0;
}

