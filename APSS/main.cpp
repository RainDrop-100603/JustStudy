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

// Decision Problem, 이분법, 자료형 유의
void FOSSIL_Input(int& playTime,int& winTime){
  cin>>playTime>>winTime;
}
bool FOSSIL_decision(long long playTime,long long winTime,long long addWin){
  long long totalPlay(playTime+addWin),totalWin(winTime+addWin);
  long long prevWinRate=winTime*100/playTime;
  long long newWinRate=totalWin*100/totalPlay;
  return newWinRate>prevWinRate;
}
int FOSSIL_Algo(int playTime,int winTime){
  // f(lo)=true, f(hi)=false;
  int lo(2000000000),hi(0); 
  //기저
  if(!FOSSIL_decision(playTime,winTime,lo)){
    return -1;
  }
  //이분법 100회 실행
  for(int i=0;i<100;i++){
    if(FOSSIL_decision(playTime,winTime,(lo+hi)/2)){
      lo=(lo+hi)/2;
    }else{
      hi=(lo+hi)/2;
    }
  }
  //반환 
  return lo;
}
void FOSSIL(){
  // FOSSIL
  /*설명 및 입력
  설명
    아마추어 고생물학자인 후연이는 서로 다른 환경에서 자라는 두 종류의 꽃 A 와 B 에 대해 각각의 꽃가루가 발견된 위치들을 지도상에 다음 그림과 같이 표시해 보았습니다.
    이 지도에서는 y 좌표가 증가하는 방향이 북쪽, x 좌표가 증가하는 방향이 동쪽입니다. 
    후연이는 각 꽃의 서식지를 예측하기 위해, 해당 화석이 발견된 위치들을 감싸는 최소의 볼록 다각형을 위 그림에 표시된 것과 같이 구했습니다. 
      이 다각형들을 볼록 껍질(convex hull) 이라고 부릅니다.
    후연이는 이 두 개의 볼록 껍질이 서로 겹치는 부분은 과거에 온도 변화가 심했을 것이라는 가설을 세웠습니다. 
      이 부분이 얼마나 넓은지 확인하기 위해 이 겹치는 부분 중 남북 방향 폭이 가장 넓은 위치를 찾고자 합니다. 
      예를 들어 위 그림에서는 점선으로 표현된 곳에서 남북 방향의 폭이 가장 넓습니다.
    두 개의 볼록 껍질이 주어질 때 겹치는 부분의 남북 최대 폭을 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 
    각 테스트 케이스는 세 줄로 주어집니다. 첫 줄에는 두 볼록 껍질에 포함된 점의 수 n 과 m (1 <= n,m <= 100) 이 주어집니다. 
    다음 줄에는 2n 개의 실수로 첫 번째 볼록 껍질에 포함된 점의 좌표 (x,y) 가 시계 반대 방향 순서대로 주어집니다. 
    그 다음 줄에는 2m 개의 실수로 두 번째 볼록 껍질에 포함된 점의 좌표 (x,y) 가 시계 반대 방향 순서대로 주어집니다. 
    각 좌표는 [0,100] 범위의 실수로, 소수점 밑 최대 2자리까지만 주어집니다.
    한 테스트 케이스에는 같은 점이 두 번 들어오지 않으며, 한 직선 위에 있는 세 점이 주어지는 일도 없습니다. 
      주어진 두 다각형의 모든 내각은 180도 미만입니다.
  출력
    각 테스트 케이스마다 한 줄에, 두 볼록 껍질이 겹치는 부분의 남북 최대 폭을 출력합니다. 
    만약 두 볼록 껍질이 겹치지 않을 경우 0 을 출력합니다. 정답과 10-7 이하의 절대/상대 오차를 갖는 답은 정답으로 인정됩니다.
    10초, 64MB
  */
  /*힌트
    convex hull에서 겹치는 부분은 한군데에서만 겹친다(여러군데에서 겹치지 않는다)
      교점이 단 두개이며, lo와 hi로 규정할 수 있다.
      lo와 hi는 영점이므로, 삼분탐색으로 max를 구할 수 있다.
    구하는 조건
      1. lo와 hi를 구해야한다.
          겹치는 점이 여러개일 수 있다.
          lo와 hi는, 각 convex hull의 좌우 끝 점 중, 더 안쪽에 있는 값으로 한다(가장바깥이 아닌, 바깥에서 2번째 위치의 점)
            lo와 hi사이에 어떤 x좌표에 대해서도, 두 convex hull에 x에 대응하는 값이 존재한다.
            즉, 거리를 구할 수 있다.
          lo와 hi가 음수값일수도 있다.
            음수값이어도, 그래프의 모양이 조건을 충족한다면 삼분탐색에는지장이 없다.
            local maximum이 음수일 경우, 겹치지 않는다는 것을 알 수 있을 뿐이다.
      2. 두 convex hull에 대해, 항상 삼분탐색을 이용할 수 있는가
          convex hull은 내각이 항상 180도 이하이다.
          만약 두 convex hull이 겹친다면, 교점에 존재하는 교선의 최대 각도는 180도이다.
            이때 180도인 경우는 선분이 완전히 겹치는 경우
            설명 추가
          결론적으로, 겹치는 부분도 convex hull이다.
      2. 겹침을 어떻게 알아낼 것인가?

      2. 어떤 x좌표에 대해, 각 convex hull에서 어떤 선분이 관여되는지를 알아야한다.
          이때, 한 x좌표에 대해 각 convex hull은 2개의 선분이 관여되거나, 0개의 선분(양 끝)이 관여될 수 있다.
            2개의 선분이 관여된다면, 
      3. convex hull에 대한 고찰
          선분의 합으로 나타낼 수 있다.
            각 선분은, 두 점의 관계로 나타낼 수 있다.
          -> 시작점부터 반시계방향으로 돌아가며 순서대로 점을 표시하면 된다.
            ex: ABCD라는 사각형은, (A,B,C,D) 로 표시할 수 있다.
      4. 다양한 형태의 겹침, x에 따른 겹침길이의 그래프
          일부분이 겹침
            중심이 먼 겹침 - 마름모 두개가 끝에만 겹친것을 상상하자
              -> 볼록한 부분끼리의 만남 -> 연속적이며, 삼분탐색의 조건을 만족한다, (local maximum이 연속적일 수 있다.)
            중심이 가까운 겹침 - 정사각형과, 45도 돌아간 정사각형이 겹친 모습을 상상하자 
              -> convex hull의 특징을 생각하면 삼분탐색을 사용할 수 있다.
          포함관계
            -> 더 작은 convexhull의 세로길이, 삼분탐색의 조건을 만족한다. (local maximum이 연속적일 수 있다.)
          겹치지않는다.
            -> 그래도 convex hull의 모습을 생각하면, local maximum이 음수일지 언정 삼분탐색은 사용할 수 있는 모양이다.

  */
  /*전략
  전략1
    이분법 & decision problem
    접근방법
      C번 승리하면 승률이 증가하는지 결정하는 decision problem
        C는 이분법을 통해 구할 수 있다.
          반복문 불변식: f(lo)=true, f(hi)=false
        전체 수행시간은 100(이분법)*m이므로 부담되지 않는다.
    시간:
      O(100*m);
    크기:
      O(n)
    개선 및 보완
      static_cast<long long>을 해도 되지만 ,처음부터 전달인자를 long long으로 받아와도 된다.
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int playTime,winTime;
    FOSSIL_Input(playTime,winTime);
    auto result=FOSSIL_Algo(playTime,winTime);
    cout<<result<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 FOSSIL();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

