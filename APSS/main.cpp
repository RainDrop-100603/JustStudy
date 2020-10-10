//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void JoinedLISInput(vector<int>& arrA,vector<int>& arrB){
  int lenA,lenB;
  scanf("%d",&lenA);scanf("%d",&lenB);
  arrA=vector<int>(lenA);
  for(int i=0;i<lenA;i++){
    scanf("%d",&arrA[i]);
  }
  arrB=vector<int>(lenB);
  for(int i=0;i<lenB;i++){
    scanf("%d",&arrB[i]);
  }
}
bool joinedLIS_Afirst(vector<int>& arrA,vector<int>& arrB,int idxA,int idxB){
  //out of idx 처리
  if(idxA==arrA.size()){
    return false;
  }else if(idxB==arrB.size()){
    return true;
  }
  //비교
  if(arrA[idxA]!=arrB[idxB]){
    return arrA[idxA]<arrB[idxB];
  }else{
    return arrA[idxA+1]<arrB[idxB+1];
  }
}
int JoinedLISAlgo_1(vector<int>& arrA,vector<int>& arrB){
  vector<long long> result;
  int idxA(0),idxB(0);
  //result의 맨 처음 값 설정
  if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
    result.push_back(arrA[idxA]);
    idxA++;
  }else{
    result.push_back(arrB[idxB]);
    idxB++;
  }
  //남은 값에 대해
  int input; 
  while(idxA<arrA.size()||idxB<arrB.size()){
    if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
      input=arrA[idxA];
      idxA++;
    }else{
      input=arrB[idxB];
      idxB++;
    }
    if(result.back()<input){
      result.push_back(input);
    }else{
      *lower_bound(result.begin(),result.end(),input)=input;
    }
  }
  return result.size();
}
int JoinedLISAlgo_3(vector<int>& arrA,vector<int>& arrB){
  vector<int> result1;
  vector<int> result2;
  result1.push_back(arrA.front());
  result2.push_back(arrB.front());
  //전략 1, 각 arr에 대해 LIS를 만든다
  for(auto& ele:arrA){
    if(result1.back()<ele){
      result1.push_back(ele);
    }else{
      *lower_bound(result1.begin(),result1.end(),ele)=ele;
    }
  }
  for(auto& ele:arrA){
    if(result2.back()<ele){
      result2.push_back(ele);
    }else{
      *lower_bound(result2.begin(),result2.end(),ele)=ele;
    }
  }
  //전략 2, 각 결과에 대해 앞에서부터 greedy
  vector<int> result;

  return result.size();
}
int JoinedLISAlgo_2(vector<int>& arrA,vector<int>& arrB,int idxA, int idxB,vector<vector<int>>& DP){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  각 arr의 원소의 개수는 1~100, 자료형 int
  전략1
    Dynamic Programming
      substructure
        idxA, idxB
      기존 LIS 전략을 쓰되, 입력을 양쪽 arr의 head중 더 작은값을 넣는다.
      LIS 전략
        input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
      input
        각 arr의 head 중 작은 값을 input, 값이 같다면 바로 다음 값을 비교하여 더 작은 값을 input, 둘이 같다면 그냥 첫번째 input
    Problem
      (10 20 30 1 2), (10 20 30)의 길이는 5 이지만, 이 Algo를 이용하면 3이 나온다.
    time complexity
      #arr(n)*lower_bound(lgn)=O(nlgn)
    mem complexity
      #arr(n)=O(n)
  전략2
    Dynamic Programming
      substructure
        idxA, idxB를 입력으로 받는 부분함수
        substructure(idxA,idxB)는 idxA와 idxB가 각 Arr에서 (이전까지)마지막 수 이며, 두 중 큰 수가 JLIS에서 마지막일 것이다.
        DP=n^2
      LIS 전략
        마지막 값 max(arrA[idxA],arrB[idxB])보다 큰 값을 찾아 재귀, 이때 arrA에대해 한번, arrB에 대해서도 한번 한다.
    time complexity
      재귀 n^2* 반복문 n: O(n^3)
    mem complexity
      DP(n^2)+ arrA and B(n): O(n^2)
  전략3
    Stack
      각 arr에 전략 1 적용후(vector 형식으로 생성), 적용한 것들을 가지고 greedy(전략 2)
      LIS 전략:1
        input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
      전략 2
        결과값은 정렬되어 있다 -> 앞에서부터 작은 값을 input
    Problem
      10 20 40 100 400 에서 10 20 30 100 400 으로 변한 결과1
      15 25 30 200 300 인 결과 2가 있다고 하자
      결과 1의 3번째가 40일때가 30일때보다 1 긴데, 30이 최종 값이다. 즉 실제 결과보다 길이가 짧다.
    time complexity
      (arrA(n)+arrB(n))*lower_bound(lgn)=O(nlgn)
    mem complexity
      arrA(n)+arrB(n)+result(2n)=O(n)
  */
  //-1부터 시작해서 각 idx에 1을 더했다.
  int& result=DP[idxA+1][idxB+1];
  if(result!=-1){
    return result;
  }
  //마지막 value를 찾는다.
  long long valueA=(idxA==-1? -9876543210:arrA[idxA]);
  long long valueB=(idxB==-1? -9876543210:arrB[idxB]);
  long long lastEle(max(valueA,valueB));
  //A와 B에 대해 substructure
  result=0;
  for(int i=idxA+1;i<arrA.size();i++){
    if(arrA[i]>lastEle){
      result=max(result,JoinedLISAlgo_2(arrA,arrB,i,idxB,DP));
    }
  }
  for(int i=idxB+1;i<arrB.size();i++){
    if(arrB[i]>lastEle){
      result=max(result,JoinedLISAlgo_2(arrA,arrB,idxA,i,DP));
    }
  }
  result++;
  return result;
}
void JoinedLIS(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> arrA,arrB;
    JoinedLISInput(arrA,arrB);
    //vector<vector<int>> DP(arrA.size()+1,vector<int>(arrB.size()+1,-1));
    printf("%d\n",JoinedLISAlgo_3(arrA,arrB));
  }
}


int main(void){
  JoinedLIS();
  return 0;
}
