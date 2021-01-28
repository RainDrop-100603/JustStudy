//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

void Dragon_Input(int& nthGen,int& pFrom,int& len){
  cin>>nthGen>>pFrom>>len;
}
vector<char> Dragon_Algo(int nthGen,int pFrom,int len){

void Dragon(){
  //Dragon Curve
  /*설명 및 입력
  설명
    n세대 드래곤 커브 문자열을 구하고 싶습니다. 이 때 문자열 전체를 구하면 너무 기니, 문자열 중 p번째 글자부터 l글자만을 계산하는 프로그램을 작성하세요.
    Dragon curve: FX로 시작 -> FX+YF -> FX+YF+FX-YF
      X->X+YF, Y-> FX-Y (+,- 는 문자 취급)
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <=50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 세 개의 정수로 드래곤 커브의 세대 n (0 <= n <= 50)
      그리고 p 와 l (1 <= p <= 1,000,000,000 , 1 <= l <= 50) 이 주어집니다. n세대의 드래곤 커브 문자열의 길이는 항상 p+l 이상이라고 가정해도 좋습니다.
    int 범위로 해결 가능
  제한조건
    2초, 64MB
  */
  /*전략
    반복되는 수열이 존재한다 -> DP를 통해 길이와 값을 예상 가능
  */
  //test
  vector<char>
  //Sol
  // int testCase;
  // cin>>testCase;
  // while(testCase--){
  //   int nthGen, pFrom, len;
  //   Dragon_Input(nthGen, pFrom, len);
  //   vector<char> result=Dragon_Algo(nthGen, pFrom, len);
  //   for(auto& ele:result){
  //     cout<<ele;
  //   }
  //   cout<<'\n';
  // }
}

int main(void){
  Dragon();
  
  return 0;
}