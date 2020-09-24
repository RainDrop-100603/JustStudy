//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
void ClockSyncInput(vector<int>& clockArr){
  for(int i=0;i<16;i++){
    cin>>clockArr[i];
  }
}
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch){
  /*
  제한시간 10초
  제한메모리 2^16kb=64MB
  전략1
    brute force
      차례대로 가장 적은 스위치와 연결된 시계를 변경하도록 스위치를 조작한다.
      (스위치)를 조작한 후, (시계)가 0인지 확인
        확인은 최종단계에서만 해도 충분하다.
      1. (1,4,9)->(8,9,11,12,13)
      2. (2,3)->(6,10)
      3. (7)->(7)
      4. (8)->(4,5)
      5. (0,6)->(1,3)
      6. (5)->(0,2,14,15)
    time complexity
      linear
    mem complexity
      linear
    구현이 귀찮다
  전략2
    brute force
      모든 스위치는 3회 이하로 눌린다
      4회를 눌렀다는 것은 0회를 눌른것과 같다.
    time complexity
      4^10
    유의사항
      재귀함수 설계시, return하며 답을 만드는 과정을 제대로 만들어야 한다.
      return시 0 혹은 INF 반환, INF를 반환하면 결과에서 무시되므로 상관없다.
        0을반환한다면 유효한 경로에 있는 값들만 result 에 더해지게 되는데, 유효하지 않은 경로는 여전히 INF를 갖고 있기 때문이다.
        프로그램은 순차적으로 실행되기 때문에, 이 경우 참조형식으로 함수를 전달해도 전혀문제가 없다(모든 경우에서 그런진 추가바람)
      마무리바람
  */
  //기저
  if(nowSwitch==10){
    bool finish(true);
    for(auto& ele:clockArr){
      if(ele%12){
        finish=false;
        break;
      }
    }
    return finish? 0: 987654321;
  }
  
  //Algo
  int result=987654321; //INF
  for(int i=0;i<4;i++){
    for(int j=0;j<i;j++){
      for(auto& ele:switchArr[nowSwitch]) clockArr[ele]+=3;
    }
    result=min(result,i+ClockSyncAlgo(clockArr,switchArr,nowSwitch+1));
    for(int j=0;j<i;j++){
      for(auto& ele:switchArr[nowSwitch]) clockArr[ele]-=3;
    }
  }
  return result;
}
void ClockSync(){
  int testCase;
  cin>>testCase;
  vector<vector<int>> switchArr={
    {0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},
    {6,7,8,10,12},{0,2,14,15},{3,14,15},
    {4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}
  };
  while(testCase--){
    vector<int> clockArr(16);
    ClockSyncInput(clockArr);
    int ans=ClockSyncAlgo(clockArr,switchArr,0);
    if(ans<987654321){
      cout<<ans<<"\n";
    }else{
      cout<<"-1\n";      
    }
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  ClockSync();

  return 0;
}