#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>

using namespace std;
//useful
bool IsPrime(int num);  //소수(Prime Number) 판별
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
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
int getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
pair<long long,long long> EuclidAlgo(long long A,long long B);  //A>B, Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
vector<vector<long long>> FibonacciMatrix(long long m); //Fibonacci identity: 도가뉴 항등식, d'Ocagne's identity, f_m matrix 반환, important 참고

//graph 
void Dijkstra(const vector<map<int,int>>& graph, vector<int>& cost_V, int start);
//int BellmanFord(const vector<map<int,int>>& graph, vector<long long>& cost_V, int start, long long INF);  //0 return = Ok, 1 return = minus cycle

//Segment Tree
template <class T>
T ST_init(vector<T>& a, vector<T>& tree, int node, int start, int end){ //[start,end] 범위 
  if(start==end){
    return tree[node] = a[start];
  }else{
    return tree[node]=ST_init(a,tree,node*2,start,(start+end)/2)+ST_init(a,tree,node*2+1,(start+end)/2+1,end);
  }
}
template <class T>
vector<T> SegmentTree(vector<T>& a){
  long long len=a.size();
  long long N(1);
  while(N<len){
    N*=2;
  }
  vector<T> tree(N*2,-1);  //원래는 N^2-1 이다. 그러나 node는 0이 아닌 1부터 시작하기 때문에 크기를 1 키웠다. 0이상의 정수만을 사용하는 segment tree
  ST_init(a,tree,1,0,len-1);
  return tree;
}
template <class T>
T ST_sum(vector<T>& tree, int node, int start, int end, int left, int right){
  if(left>end||right<start){
    return 0;
  }else if(left<=start && end<=right){
    return tree[node];
  }else{
    return ST_sum(tree, node*2, start, (start+end)/2,left, right)+ST_sum(tree, node*2+1, (start+end)/2+1, end, left, right);
  }
}
template <class T>
  //query


//useful에서 쓰는 함수 
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array(동적할당) 반환
void Merge(int* &array, const int start, const int end);  //Merge를 담당, vector가 배열임을 이용해 변경할 수도 있다.
void MergeSort(int* &array,const int start,const int end);  //MergeSort main 함수 . Merge를 합칠수도 있지만 divide&conquer을 보여주기 위해 남겨둠
void MergeSort(vector<int>& array,const int start,const int end); //vector이용, Merge 통합 버전 


#endif