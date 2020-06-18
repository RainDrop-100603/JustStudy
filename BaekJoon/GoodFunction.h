#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <string>

using namespace std;

bool IsPrime(int num);  //소수(Prime Number) 판별
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array(동적할당) 반환
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
void Merge(int* &array, const int start, const int end);  //Merge를 담당, vector가 배열임을 이용해 변경할 수도 있다.
void MergeSort(int* &array,const int start,const int end);  //MergeSort main 함수 . Merge를 합칠수도 있지만 divide&conquer을 보여주기 위해 남겨둠
void MergeSort(vector<int>& array,const int start,const int end); //vector이용, Merge 통합 버전 
template <class T>
void MergeSortT(vector<T>& array,const int idx,const int start,const int end){   //T라는 자료형의 idx번째 수에대한 merge sort
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    MergeSortT(array,idx,start,middle);
    MergeSortT(array,idx,middle,end);
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
    temp=tempArray[rotateFront-start];
    if(rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
    }else{
      if(temp[idx]<=array[rotateBack][idx]){
        array[mainRotate]=temp;
        rotateFront++;
        mainRotate++;
      }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
      }
    }
  }
}
int Combi_nCr(int n, int r);
bool ChkDuplicate(int x, int depth, int* num);  //num의 depth-1번째 까지 수에서, x와 겹치는 것이 있는지 확인
void PrintAllCombi(int n, int r, int depth, int* num);//nCr 조합, depth번째 수, 수를 저장하는 num, digit=0: 가장 앞에 수(167:digit 0 -> 1);
void PrintAllCombi2(int n, int r, int depth, int* num, int start);//N과 M(2) 문제 
void PrintAllCombi3(int n, int r, int depth, int* num);//N과 M(3) 문제 
void PrintAllCombi4(int n, int r, int depth, int* num, int start);//N과 M(4) 문제
int N_Queen(int N,int** table,int row, int count);  //N_Queen문제, count는 N번째 Queen을 말함 

// void MergeSortString(vector<string>& array,const int start,const int end){   //갈이가 같은 string vector를 [start,end) 까지 sorting
//   //divide
//   int middle=(end+start)/2; // [start,middle),[middle,end)로 divide
//   if(end-start==1){         //  크기가 1일 때까지 divide
//     return;
//   }else{
//     MergeSortString(array,start,middle);
//     MergeSortString(array,middle,end);
//   }

//   //conquer : Merge
//   int mainRotate=start;     // [start,mainRotate) 까지 sorted, mainRotate==end가 되면 sorting [start,end)까지 sorting 완료
//   int rotateFront=start;    //앞의 vector: [start,middle)의 index
//   int rotateBack=middle;    //뒤의 vector: [middle,end) 의 index
//   vector<string> stringV;  //앞의 vector를 저장한 임시 배열,
//   for(int i=start;i<middle;i++){
//     stringV.push_back(array[i]);
//   }
//   string front=stringV[0];    //앞 vector의 원소 front와 뒤 vector의 원소 back을 비교하여 merge
//   string back;
//   while(!(rotateFront==middle)){ //앞 vector의 merge가 끝나면 merge finish 
//     front=stringV[rotateFront-start];
//     if(rotateBack==end){         //뒤 vector가 merge가 끝나면 남은 앞 vector 모두 merge 
//       array[mainRotate]=front;
//       rotateFront++;
//       mainRotate++;
//     }else{
//       back=array[rotateBack];
//       if(front.compare(back)!=1){   //길이가 같을 때 기준, 작거나 같다(사전에서 앞쪽)
//         array[mainRotate]=front;
//         rotateFront++;
//         mainRotate++;
//       }else{
//       array[mainRotate]=back;
//       rotateBack++;
//       mainRotate++; 
//       }
//     }
//   }
// }

#endif