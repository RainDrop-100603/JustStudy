//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>
#include <queue>

using namespace std;

// stack을 이용한 간단한 문제
void BRACKETS2_Input(string& inputStr){
  cin>>inputStr;
}
string BRACKETS2_Algo(string& inputStr){
  vector<int> stack;
  for(auto ele: inputStr){
    if(ele=='(' || ele=='{' || ele=='['){
      stack.push_back(ele);
    }else{
      if(ele==')'){
        ele='(';
      }else if(ele=='}'){
        ele='{';
      }else{
        ele='[';
      }
      if(stack.empty() || stack.back() != ele){
        return string("NO");
      }else{
        stack.pop_back();
      }
    }
  }
  if(stack.empty()){
    return string("YES");
  }else{
    return string("NO");
  }
} 
void BRACKETS2(){
  // TREASURE
  /*설명 및 입력
  설명
    Every bracket has a corresponding pair. ( corresponds to ), [ corresponds to ], et cetera.
      Every bracket pair is opened first, and closed later.
      No two pairs "*cross*" each other. For example, [(]) is not well-matched.
    Write a program to help Best White by checking if each of his formulas is well-matched. 
      To make the problem easier, everything other than brackets are removed from the formulas.
  입력
    The first line of the input will contain the number of test cases C (1≤C≤100). 
      Each test is given in a single line as a character string. 
      The strings will only include characters in "[](){}" (quotes for clarity). 
      The length of the string will not exceed 10,000.
  출력
    For each test case, print a single line "YES" when the formula is well-matched; 
      print "NO" otherwise. (quotes for clarity)
  제한조건
    1초, 64MB
  */
  /*힌트
    stack
      ( [ { 는 stack에 저장
      ) ] } 는 stack.top과 매칭되면 stack.pop, 다르다면 return NO
      모든 문자를 완료했을때 stack이 비어있다면 return true, 아니면 return NO
  */
  /*전략
  전략1
    아이디어: 스택
      1. for( i = [string.begin,string.end))
        if string[i]== ( { [ -> stack.push
        else  
          if stack.empty || string[i] match stack.top -> return NO
          else -> stack.pop
      2. if stack.empty -> return YES
          else -> return NO
    분석
      time complexity: O(n)
      mem complexity: O(n)
    피드백
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    string inputStr;
    BRACKETS2_Input(inputStr);
    auto result=BRACKETS2_Algo(inputStr);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

int main(void){
  //   clock_t start,end;
  //   start=clock();
  BRACKETS2();
  //   end=clock();;
  //   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

