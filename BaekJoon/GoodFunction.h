#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

bool IsPrime(int num);  //소수(Prime Number) 판별
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array(동적할당) 반환
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
void Merge(int* &array, const int start, const int end);  //Merge를 담당, vector가 배열임을 이용해 변경할 수도 있다.
void MergeSort(int* &array,const int start,const int end);  //MergeSort main 함수 . Merge를 합칠수도 있지만 divide&conquer을 보여주기 위해 남겨둠
void MergeSort(vector<int>& array,const int start,const int end); //vector이용, Merge 통합 버전 
template <int idx, class T>
void MergeSortT(vector<T>& array,const int start,const int end){   //T라는 자료형의 idx번째 수에대한 merge sort
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    MergeSortT<idx>(array,start,middle);
    MergeSortT<idx>(array,middle,end);
  }
  //conquer : Merge
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  T tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  T temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    if(temp[idx]<array[rotateBack][idx]||rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
      temp=tempArray[rotateFront-start];
    }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
    }
  }
}
// template<class T> //string에 대한 특수화, 사전 편찬 순 정렬
// void MergeSortT<-1>(vector<T>& array,const int start,const int end){
//   //divide
//   int middle=(end+start)/2; //두 vector사이의 경계 idx;
//   if(end-start==1){
//     return;
//   }else{
//     MergeSortT<-1>(array,start,middle);
//     MergeSortT<-1>(array,middle,end);
//   }
//   //conquer : Merge
//   int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
//   int rotateFront=start;    //앞의 vector의 index
//   int rotateBack=middle;//뒤의 vector의 index
//   T tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
//   for(int i=start;i<middle;i++){
//     tempArray[i-start]=array[i];
//   }
//   T temp=tempArray[0];
//   while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
//     if(temp[idx]<array[rotateBack][idx]||rotateBack==end){
//       array[mainRotate]=temp;
//       rotateFront++;
//       mainRotate++;
//       temp=tempArray[rotateFront-start];
//     }else{
//       array[mainRotate]=array[rotateBack];
//       rotateBack++;
//       mainRotate++; //하나 더 sorted 됐으므로
//     }
//   }
// }


#endif