#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>

//#include "GoodFunction.h"

using namespace std;

void BK12015_H(){ //기저에 깔린 법칙
/*
Longest Increasing Subsequence: LIS
무엇을 key로 정할 것인가. key :left, right로 비교할 것
  LIS의 길이를 key로 한다 가정하자
    이분 탐색에는 lgn*operTime이 소요된다.
    operTime은 nlgn이하여야 한다.
      nlgn시간으로 배열에서 key길이의 IS가 있는지 탐색할 수 있는가?
      key길이의 IS가 있는지 알고싶다면 어떻게 해야 하는가
        key가 LIS의 길이보다 작다면, 모든 경우를 비교하지 않아도 된다.
        key가 LIS의 길이보다 크거나 같다면, 배열의 LIS를 구해야만 key보다 크거나 같은 IS의 존재유무를 판별할 수 있다.
          그러나 배열에서 LIS를 구한다면 그 자체로 답이 된다.
          즉, key를 LIS의 길이로 하는것은 유용하지 않다.
            만약, 배열에서 key길이의 IS를 구하는 것이 n Time에 가능하다면 유용할지도(LIS인지는 판별 불가하지만 key길이의 IS를 구할 수 있는 Algo가 있을까?)
이분탐색 자체가 아니라 이분탐색을 이용한다면?
  Lower bound 와 같이 이분탐색을 이용한 함수를 이용해서 푸는 것일수도 있다.
Lower bound와 vector를 이용한 방법 
  v가 비어있으면 tmp push
  v.back()<tmp 라면 push
  v.back()>=tmp 라면, lower_bound(v.begin(),v.end(),tmp)위치에 tmp push
    LIS를 구하는 것이 아니라 LIS의 길이는 구하는 것이기 때문에 유효한 방법
    LIS의 길이를 구할때, 가장 큰 문제는 분기점을 어떻게 처리하냐는 것이다. 
      분기점은 tmp의 크기가 LIS의 중간정도의 위치에 들어가는 경우를 말한다. 10 20 40에서 7이 들어오면 분기점 생성
    v의 lower bound에 덮어 씌우는 방식을 사용
      분기점이 LIS로 가는 것이 아니라면, 덮어 씌운것은 v.back()을 넘어서지 못한다. 즉 LIS의 길이에는 영향을 주지 못한다.
      분기점이 LIS로 가는 것이라면, 어느 시점에서 덮어 씌운것이 v.back()까지 도달하게 된다. 기존의 LIS후보가 새로운 LIS후보로 교체되는 것이다.
        ex)10 20 40 25 20 30 7 8
          10 -> 10 20 -> 10 20 25 -> 10 20(덮어씌워짐) 25->10 20 25 30 -> 10 20 25 30 -> 7 10 25 30 -> 7 8 25 30
            7 8 은 덮어씌워 졌지만 back()까지 가지 못했다.
        ex)10 20 40 25 20 30 7 8 9 10 11
          ... ->7 8 9 30-> 7 8 9 10 -> 7 8 9 10 11
            10에서 v.back()까지 도달한 후 새로운 LIS로 후보로 변경
        ex)10 20 40 25 20 30 7 8 9 10 70
          ...->7 8 9 10->7 8 9 10 70
            이 경우 10 20 25 30 70, 7 8 9 10 70모두 LIS. 어차피 길이를 구하는 것이므로 상관없다.
*/  
//input
  int N;
  scanf("%d",&N);
//prepare  
//calc
  vector<int> v;
  int tmp;
  v.push_back(0); //원소는 자연수 이므로 항상 0보다 크다
  for(int i=0;i<N;i++){
    scanf("%d",&tmp);
    if(v.back()<tmp){
      v.push_back(tmp);
    }else{
      vector<int>::iterator iter=lower_bound(v.begin(),v.end(),tmp);
      *iter=tmp;
    }
  }
  
  cout<<v.size()-1;
}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
  BK12015_H();

  return 0;
}