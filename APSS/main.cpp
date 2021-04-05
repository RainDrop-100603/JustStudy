//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

//https://www.youtube.com/watch?v=x7STjpcKZP8 
//사회복무요원 교육 

// greedy, 증명부분 나중에
void STRJOIN_Input(int& number,vector<int>& warmTime,vector<int>& eatingTime){
  cin>>number;
  warmTime.resize(number);
  for(auto& ele: warmTime){
    cin>>ele;
  }
  eatingTime.resize(number);
  for(auto& ele: eatingTime){
    cin>>ele;
  }
}
int STRJOIN_Algo(int number,const vector<int>& warmTime,const vector<int>& eatingTime){
  //pair로 배열 만들고 내림차순 정렬
  vector<pair<int,int>> food;
  for(int i=0;i<number;i++){
    food.push_back({eatingTime[i],warmTime[i]});
  }
  sort(food.begin(),food.end());  //오름차순
  reverse(food.begin(),food.end()); //뒤집기
  //계산
  int boilBegin(0), result(0);
  for(auto& ele:food){
    result=max(result,boilBegin+ele.first+ele.second);
    boilBegin+=ele.second;
  }
  return result;
}
void STRJOIN(){
  //STRJOIN
  /*설명 및 입력
  설명
    n 개의 문자열들의 길이가 주어질 때 필요한 최소 비용을 찾는 프로그램을 작성하세요.
      문자열을 합치는데 드는 비용: 각 문자열의 길이의 합
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 문자열의 수 n (1 <= n <= 100) 이 주어지며, 다음 줄에는 n 개의 정수로 각 문자열의 길이가 주어집니다. 
    각 문자열의 길이는 1,000 이하의 자연수입니다.
  출력
    각 테스트 케이스마다 한 줄에 모든 문자열을 합칠 때 필요한 최소 비용을 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    최대한 작은 단위로 합치는것이 유리하다
      큰 것을 여러번 합치면, 그만큼 비용이 증가한다.
    한 str에 처음부터 끝까지 합치는 것은 적절하지 못하다
      한 str에 여러번 합치면 결국 길이가 길어지고 비용이 증가한다.
    가장 작은 str 2개를 골라 합친 후, 합쳐진 str을 포함하여 가장 작은 str 2개를 다시 골라 합치는 것을 반복한다.
      합치는 횟수는 n-1로 동일하므로, 합치는 cost를 매번 최소로 하는것이 최적값이다.
      greedy choice property:
        총 결합 횟수는 n-1번이다.
        n개의 원소에 대해, 각 원소x가 결합에 참여하는 횟수를 times(x)라 하자
        greedy하게 선택한 경우 len(x1)<len(x2)에 대해, times(x1)>=times(x2) 이다.
        정답 S 중, len(x1)<len(x2)일때 times(x1)<=times(x2)인 선택이 있다고 하자.
          x1과 x2의 위치를 바꾼 후에도 여전히 정답이라면, greedy한 선택이 정답중 하나임을 알 수 있다.
          정답: l1*t1+l2*t2
          greedy: l1*t2+l2*t1.

            정답 - greedy = (l1-l2)(t1-t2) >=0 
          즉 정답 S중에 greedy한 선택이 있음을 알 수 있다.
      optimal substructure:
        S(n) = S(n-x) + S(x), 이때 S(n-x) + S(x)의 합이 최소가 되도록 한다.
  */
  /*전략
  전략1
    Greedy Algorithm
      음식 먹는 속도로 정렬 nlgn
      오래 걸리는 순서로 greedy n
        result=max(result,데우기 시작한 시간 + 해당 음식의 먹는 시간)
    시간:
      O(NlgN + N) 
    크기:
      O(N)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int number;
    vector<int> warmTime, eatingTime;
    STRJOIN_Input(number,warmTime,eatingTime);
    int result=STRJOIN_Algo(number,warmTime,eatingTime);
    cout<<result<<'\n';
  }
}

int main(void){
  STRJOIN();
  return 0;
}