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

using namespace std;

// combination, set cover, 책에 더 최적화 하는 방법들이 있다.
void ALLERGY_Input(vector<string>& friendsName, vector<vector<string>>& foodsInfo){
  int foodNum,friendNum;
  cin>>friendNum>>foodNum;
  friendsName.resize(friendNum);
  for(auto& ele: friendsName){
    cin>>ele;
  }
  foodsInfo.resize(foodNum);
  for(auto& food:foodsInfo){
    int count;
    cin>>count;
    for(int i=0;i<count;i++){
      string tmp;
      cin>>tmp;
      food.push_back(tmp);
    }
  }
}
vector<pair<int,long long>> ALLERGY_food_opti(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo){
  //음식 정보를 bitmask로 수정, pair(친구의 수, 친구 정보 bitmask)
  int friendsNum=friendsName.size();
  vector<pair<int,long long>> foods_bitmask;
  for(auto& food:foodsInfo){
    long long bitmask(0);
    for(auto& name: food){
      for(int i=0;i<friendsNum;i++){
        if(name==friendsName[i]){
          bitmask+=(1LL<<i);
          break;
        }
      }
    }
    foods_bitmask.push_back({food.size(),bitmask});
  }
  //정렬, 친구에대해 동일한 음식 제거, 내림차순정렬
  sort(foods_bitmask.begin(),foods_bitmask.end());
  foods_bitmask.erase(unique(foods_bitmask.begin(),foods_bitmask.end()),foods_bitmask.end());
  reverse(foods_bitmask.begin(),foods_bitmask.end());
  //포함관계 음식 제거
  vector<pair<int,long long>> result;
  for(auto& ele: foods_bitmask){
    bool canInput(true);
    for(auto& exist:result){
      if((exist.second|ele.second)==exist.second){
        canInput=false;
        break;
      }
    }
    if(canInput){
      result.push_back(ele);
    }
  }
  //반환
  return result;
}
void ALLERGY_func(const vector<pair<int,long long>>& foods_bitmask,int friendsNum, long long friends_bitmask, int& tmp_min, int prev_count, int food_idx){
  //모든 친구를 충족시킨경우
  if((1LL<<friendsNum)-1==friends_bitmask){
    tmp_min=min(prev_count,tmp_min);
    return;
  }
  //마지막 음식이지만, 모든 친구를 충족하지 못한경우
  if(food_idx==foods_bitmask.size()){
    return;
  }
  //tmp_min보다 커진경우
  if(prev_count>=tmp_min){
    return;
  }
  //음식을 추가하는 경우
  auto nowFood=foods_bitmask[food_idx];
  if((friends_bitmask|nowFood.second)!=friends_bitmask){
    ALLERGY_func(foods_bitmask,friendsNum,friends_bitmask|nowFood.second,tmp_min,prev_count+1,food_idx+1);
  }
  //음식을 추가하지않는 경우
  ALLERGY_func(foods_bitmask,friendsNum,friends_bitmask,tmp_min,prev_count,food_idx+1);
}
int ALLERGY_Algo(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo){
  //음식 정보 최적화
  vector<pair<int,long long>> foods_bitmask=ALLERGY_food_opti(friendsName,foodsInfo);
  //Algo
  int tmp_min(51);
  ALLERGY_func(foods_bitmask,friendsName.size(),0,tmp_min,0,0);
  return tmp_min;
}
void ALLERGY(){
  //ALLERGY
  /*설명 및 입력
  설명
    집들이에 n 명의 친구를 초대하려고 합니다. 
    할 줄 아는 m 가지의 음식 중 무엇을 대접해야 할까를 고민하는데, 친구들은 각각 알러지 때문에 못 먹는 음식들이 있어서 아무 음식이나 해서는 안 됩니다.
    친구들의 정보가 주어질 때 최소한 만들어야 하는 요리의 가지수를 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 T (T <= 50 ) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 친구의 수 n (1 <= n <= 50) 과 할 줄 아는 음식의 수 m (1 <= m <= 50) 이 주어집니다. 
    다음 줄에는 n 개의 문자열로 각 친구의 이름이 주어집니다. 친구의 이름은 10 자 이하의 알파벳 소문자로만 구성된 문자열입니다. 
    그 후 m 줄에 하나씩 각 음식에 대한 정보가 주어집니다. 
    각 음식에 대한 정보는 해당 음식을 먹을 수 있는 친구의 수와 각 친구의 이름으로 주어집니다.
    모든 친구는 하나 이상의 음식을 먹을 수 있다고 가정해도 좋습니다.
  출력
    각 테스트 케이스마다 한 줄에 만들어야 할 최소의 음식 수를 출력합니다.
  제한조건
    5초, 64MB
  */
  /*힌트
    조합 풀이법을 사용하자
      완전탐색을 구현한 후 하나씩 최적화를 진행한다.
    완전탐색
      음식을 순서대로 고르면서, 모든 친구가 포함되었는지 확인한다.
    최적화
      음식목록 최적화
        최대 50개 이므로 bitmask 사용 가능
        많은 인원이 먹을 수 있는 음식대로 내림차순 정렬
        포함관계에 있는 음식 삭제
      음식을 선택할 때, 이미 선택된 음식들의 친구목록에 포함된다면 생략 
        음식을 선택한 후에, 음식 목록을 업데이트 하는 방법도 괜찮다고 보임 - cost가 많이 들 것으로 예상되서 생략 
      가지치기
        현재값과 최대값의 비교
  */
  /*전략
  전략1
    combination search
    시간:
      O(2^N) & optimize 
    크기:
      O(N)
    보완
      \
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<string> friendsName;
    vector<vector<string>> foodsInfo;
    ALLERGY_Input(friendsName,foodsInfo);
    auto result=ALLERGY_Algo(friendsName,foodsInfo);
    cout<<result<<"\n";
  }
}

int main(void){
  // clock_t start,end;
  // start=clock();
  ALLERGY();
  // end=clock();;
  // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}