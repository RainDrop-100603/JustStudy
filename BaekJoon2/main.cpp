#include <iostream>
#include <vector>

using namespace std;

//BK 6549 복습 

//segmentTree
int BK2104_getPivot(vector<int>& arr, vector<int>& segTree,int left, int right,int node, int start, int end){
  //[left,right) is the target range
  //[start,end) is the range now we are looking for
  //case 1
  if(end<=left||right<=start){
    return -1;
  }
  //case 2
  if(left<=start&&end<=right){
    return segTree[node];
  }
  //case 3
  int leftPivot=BK2104_getPivot(arr,segTree,left,right,node*2+1,start,(start+end)/2);
  int rightPivot=BK2104_getPivot(arr,segTree,left,right,node*2+2,(start+end)/2,end);
  if(rightPivot==-1){
    return leftPivot;
  }else if(leftPivot==-1||arr[rightPivot]<arr[leftPivot]){
    return rightPivot;
  }else{
    return leftPivot;
  }
}
int BK2104_buildSegTree(vector<int>& arr,vector<int>& segTree,int node,int left,int right){
  if(left==right-1){
    segTree[node]=left;
  }else{
    int leftPivot=BK2104_buildSegTree(arr,segTree,node*2+1,left,(left+right)/2);
    int rightPivot=BK2104_buildSegTree(arr,segTree,node*2+2,(left+right)/2,right);
    if(leftPivot>rightPivot){
      segTree[node]=leftPivot;
    }else{
      segTree[node]=rightPivot;
    }
  }
  return segTree[node];
}
long long BK2104_getMaxRating(vector<int>& arr, vector<long long>& cache_Sum,vector<int>& segTree, int left, int right){
  //기저
  if(left==right){
    return 0;
  }
  //find pivot
  int pivot=BK2104_getPivot(arr,segTree,left,right,0,0,arr.size());
  //divide conquer
  long long leftPivot=BK2104_getMaxRating(arr,cache_Sum,segTree,left,pivot);
  long long rightPivot=BK2104_getMaxRating(arr,cache_Sum,segTree,pivot+1,right);
  long long leftToRight=(cache_Sum[right]-cache_Sum[left])*arr[pivot];
  return max(leftToRight,max(leftPivot,rightPivot));
}
void BK2104(){
  //부분 배열 고르기
  /*설명 및 입력
  설명
    크기가 N(1≤N≤100,000)인 1차원 배열 A[1], …, A[N]이 있다. 어떤 i, j(1≤i≤j≤N)에 대한 점수는, (A[i]+…+A[j])×Min{A[i], …, A[j]}가 된다. 
    즉, i부터 j까지의 합에다가 i부터 j까지의 최솟값을 곱한 것이 점수가 된다.
    배열이 주어졌을 때, 최대의 점수를 갖는 부분배열을 골라내는 프로그램을 작성하시오.
  입력
    첫째 줄에 정수 N이 주어진다. 다음 줄에는 A[1], …, A[N]을 나타내는 정수들이 주어진다. 각각의 정수들은 음이 아닌 값을 가지며, 1,000,000을 넘지 않는다.
      N<=100,000 이므로, 결과의 최대값은 100,000*1,000,000*1,000,000=10^17, long long~=9*10^18 이므로 long long을 이용한다.
  제한조건
    2초, 128MB
  */
  /*전략
    Divide Conquer
      Pivot, Left, Right로 나누어서 해결 
    stack
  */
  //input
  int N;
  cin>>N;
  vector<int> arr(N);
  for(auto& ele:arr){
    cin>>ele;
  }
  //Sum(a)=sum of [0,a)
  vector<long long> cache_Sum(N+1); //sum(a)= sum of x, which is 0<=x<a;
  for(int i=0;i<N;i++){
    cache_Sum[i+1]=cache_Sum[i]+arr[i];
  }
  //segmentTree, node is pivot(means idx of the lowest)
  int stLen=1;
  while(stLen<N){
    stLen*=2;
  }
  vector<int> segTree(stLen*2);
  BK2104_buildSegTree(arr,segTree,0,0,N);
  //Algo
  cout<<BK2104_getMaxRating(arr,cache_Sum,segTree,0,N);
}

int main(){
  BK2104();
  return 0;
}