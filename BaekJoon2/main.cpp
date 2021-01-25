#include <iostream>
#include <vector>

using namespace std;

//BK 6549 복습 

//최대값이 아닌 범위를 찾아야하며, long long을 사용해야 함을 잊지 말자 
long long BK2104_getMaxRating(vector<int>& arr, vector<long long>& cache_Sum,vector<vector<int>>& cache_Pivot, int left, int right){
  //기저
  if(left==right){
    return 0;
  }
  //find pivot
  int pivot=cache_Pivot[left][right];
  int min=arr[pivot];
  //divide conquer
  long long leftPivot=BK2104_getMaxRating(arr,cache_Sum,cache_Pivot,left,pivot);
  long long rightPivot=BK2104_getMaxRating(arr,cache_Sum,cache_Pivot,pivot+1,right);
  long long leftToRight=(cache_Sum[right]-cache_Sum[left])*min;
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
  //Sum 구해놓기
  vector<long long> cache_Sum(N+1); //sum(a)= sum of x, which is 0<=x<a;
  for(int i=0;i<N;i++){
    cache_Sum[i+1]=cache_Sum[i]+arr[i];
  }
  //Pivot 구해놓기, i<= x < j
  vector<vector<int>> cache_Pivot(N+1,vector<int>(N+1));
  for(int i=0;i<N;i++){
    cache_Pivot[i][i+1]=i;
    for(int j=i+2;j<=N;j++){
      int& pivot=cache_Pivot[i][j]=cache_Pivot[i][j-1];
      if(arr[pivot]>arr[j-1]){
        pivot=j-1;
      }
    }
  }
  //Algo
  cout<<BK2104_getMaxRating(arr,cache_Sum,cache_Pivot,0,N);
}

int main(){
  BK2104();
  return 0;
}