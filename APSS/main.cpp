//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void PImem_Input(string& s){
  cin>>s;
}
int PImem_hard(string& numbers,int start,int len){
  //기저
  if(start+len>numbers.size()) return 12345;
  int begin(start+1),end(start+len);
  //난이도 1
  bool result(true);
  for(int i=begin;i<end;i++){
    if(numbers[i]!=numbers[i-1]) result=false;
  }
  if(result) return 1;
  //난이도 2
  result=true;
  int gap=numbers[start+1]-numbers[start];
  if(gap!=1&&gap!=-1) result=false;
  for(int i=begin;i<end;i++){
    if(numbers[i]-numbers[i-1]!=gap) result=false;
  }
  if(result) return 2;
  //난이도 4
  result=true;
  for(int i=start+2;i<end;i++){
    if(numbers[i]!=numbers[i-2]) result=false;
  }
  if(result) return 4;
  //난이도 5
  result=true;
  gap=numbers[start+1]-numbers[start];
  for(int i=begin;i<end;i++){
    if(numbers[i]-numbers[i-1]!=gap) result=false;
  }
  if(result) return 5;
  //나머지
  return 10;
}
int PImem_Algo(string& numbers, vector<int>& DP, int start){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  테스트 케이스 50개
  각 숫자들의 길이는 8~10000, 0~9
  전략1
    Dynamic Programming
      substructure
        Algo(DP,start)=min(hard(s,start,3)+Algo(DP,start+3),hard(s,start,4)+Algo(DP,start+4),hard(s,start,5)+Algo(DP,start+5));
          Algo(DP,start)=start에서 마지막까지 외울때의 값,DP이용
          hard(s,start,len)=string s에서 start부터 길이 len인 조각의 난이도
        제한조건
          최대값은 10000/3*10이므로, search완료는 0 반환, out of idx와 같은 것은 12,345 반환
    time complexity
      #Algo(n)*Algo(1)*hard(1)
    mem complexity
      #arr(n)=O(n)
  */
  //기저, search 완료, out of idx
  if(start==numbers.size()) return 0;
  if(start>numbers.size()) return 12345;
  //메모제이션
  int& result=DP[start];
  if(result!=0) return result;
  //substructure
  int sub3=PImem_hard(numbers,start,3)+PImem_Algo(numbers,DP,start+3);
  int sub4=PImem_hard(numbers,start,4)+PImem_Algo(numbers,DP,start+4);
  int sub5=PImem_hard(numbers,start,5)+PImem_Algo(numbers,DP,start+5);
  return result=min(sub3,min(sub4,sub5));
}
void PImem(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string numbers;
    PImem_Input(numbers);
    vector<int> DP(numbers.size());
    printf("%d\n",PImem_Algo(numbers,DP,0));
  }
}

int main(void){
  PImem();
  return 0;
}
