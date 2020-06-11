#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

// #include "GoodFunction.h"

using namespace std;

void Merge(vector<int> &v1, int start, int end){  //[start,end) sorting 
  int middle=(end+start)/2; //두 vector 사이의 경계 idx
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  vector<int>::iterator iter;
  while(!(rotateFront==middle||rotateBack==end)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    iter=v1.begin();
    if(*(iter+rotateFront)<*(iter+rotateBack)){
      rotateFront++;
      mainRotate++;
    }else{
      v1.insert(iter+mainRotate,*(iter+rotateBack));
      rotateBack++;
      iter=v1.begin()+rotateBack;
      v1.erase(iter); //기존의 원소는 한칸 뒤로 밀리게 된다. 이 원소는 위치를 이동했으므로 삭제해준다.
      mainRotate++; //하나 더 sorted 됐으므로
      rotateFront++;  //1칸 밀리게 됨
      middle++;    //1칸 밀리게 됨
    }
  }
  return;
}


void MergeSort(vector<int> &v1,int start,int end){
  //divide
  int middle=(end+start)/2;
  if(end-start==1){
    return;
  }else{
    MergeSort(v1,start,middle);
    MergeSort(v1,middle,end);
  }
  //conquer
  Merge(v1,start,end);
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
  MergeSort(arrayV,0,vectorSize);  //참조형식이기 때문에 반환형 불필요
  //출력 
  for(int number:arrayV){
    cout<<number<<"\n";
  }

  
  return 0;
}

