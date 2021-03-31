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


// greedy, 증명부분에 더 신경쓰자
void MATCHORDER_Input(int& number,vector<int>& ourRating,vector<int>& enemyRating){
  cin>>number;
  enemyRating.resize(number);
  for(auto& ele: enemyRating){
    cin>>ele;
  }
  ourRating.resize(number);
  for(auto& ele: ourRating){
    cin>>ele;
  }
}
int MATCHORDER_Algo(int number,vector<int> ourRating,vector<int> enemyRating){
  //배열 정렬
  sort(ourRating.begin(),ourRating.end());
  sort(enemyRating.begin(),enemyRating.end());
  //계산
  int result(0),enemyIdx(0);
  auto lowerValue=ourRating.begin();
  while(lowerValue!=ourRating.end()){
    lowerValue=lower_bound(lowerValue,ourRating.end(),enemyRating[enemyIdx]);
    if(lowerValue==ourRating.end()){
      break;
    }
    lowerValue++;
    result++;
    enemyIdx++;
  }
  return result;
}
void MATCHORDER(){
  //MATCHORDER
  /*설명 및 입력
  설명
    각 팀은 n명씩의 프로 코더들로 구성되어 있으며, 결승전에서는 각 선수가 한 번씩 출전해 1:1 경기를 벌여 더 많은 승리를 가져가는 팀이 최종적으로 우승하게 됩니다. 
    1:1 승부에서는 항상 레이팅이 더 높은 선수가 승리하고, 레이팅이 같을 경우 우리 선수가 승리한다고 가정합시다.
    상대방 팀 선수들의 순서를 알고 있을 때, 어느 순서대로 선수들을 내보내야 승수를 최대화할 수 있을까요?
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 각 테스트 케이스의 첫 줄에는 각 팀 선수의 수 N(1≤N≤100)가 주어집니다. 
    그 다음 줄에는 N개의 정수로 러시아팀 각 선수의 레이팅이 출전 순서대로 주어지며, 그 다음 줄에는 N개의 정수로 한국팀 각 선수의 레이팅이 무순으로 주어집니다. 
    모든 레이팅은 1 이상 4000 이하의 정수입니다.입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 각 팀 선수의 수 N(1≤N≤100)가 주어집니다. 
    그 다음 줄에는 N개의 정수로 러시아팀 각 선수의 레이팅이 출전 순서대로 주어지며, 그 다음 줄에는 N개의 정수로 한국팀 각 선수의 레이팅이 무순으로 주어집니다. 
    모든 레이팅은 1 이상 4000 이하의 정수입니다.
  출력
    각 테스트 케이스마다 한 줄에 한국팀이 얻을 수 있는 최대 승수를 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    Greedy하게 풀 수 있다.
      우리선수의 rating을 오름차순으로 정렬하고, 상대 선수의 rating도 오름차순으로 정렬한다.
        상대 선수의 rating을 순회하며, rating이 상대선수보다 같거나 높은 우리선수중 최초의 선수를 각각 매칭시킨다.
        매칭 성공횟수가 승리횟수이다.
      증명
        greedy choice property:
          greedy하게 선택되지 않은 답 S1이 있다고 가정하자 
            a1:b1, a2:b2관계로 대응된다. a1 <= b1, a2 ? b2, b2 <= b1
          greedy하게 선택되었지만 답인지는 모르는 S2 
            a1:b2, a2:b1관계로 대응한다. a1 <= b2, a2 ? b1, b2 <= b1
          a1에 대해, b1이 b2로 바뀌어도 승패관계는 변하지 않는다.
          a2에 대해
            a2<= b2일 경우, a2 <= b2 <= b1이므로, b1 b2가 바뀌어도 승패관계가 변하지 않는다.
            a2>= b2일 경우 b1>=b2 이지만 b1>=a2가 될 수는 없는데, a2에대한 패배가 승으로 바뀔 경우, S2>=S1이므로, S1이 답이라고 가정한 것에 어긋난다.
          즉 greedy한 답 S1이 있는경우 greedy한 선택 S2도 답이라는것을 알 수 있다.
        optimal substructure:
          greedy choice property를 통해 greedy하게 선택된 답 S가있음을 알 수 있고, 
            S= greedy(x) + S(without x) (greedy(x)==임의의 원소 x에 대해, greedy한 선택을 할 경우의 승, 패) 로 구성되므로 optimal substructure임을 알 수 있다. 
  */
  /*전략
  전략1
    Greedy Algorithm
      상대 선수의 rating과 아군의 rating을 모두 오름차순 정렬
        NlgN time
      상대선수보다 같거나 높은 아군의 rating을 greedy하게 선택한다
        선택한 갯수가 승 수 
        lgN time
    시간:
      O(NlgN + NlgN + lgN) 
    크기:
      O(N)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int number;
    vector<int> ourRating, enemyRating;
    MATCHORDER_Input(number,ourRating,enemyRating);
    int result=MATCHORDER_Algo(number,ourRating,enemyRating);
    cout<<result<<'\n';
  }
}

int main(void){
  MATCHORDER();
  return 0;
}