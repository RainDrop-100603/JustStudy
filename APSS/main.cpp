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

// Decision Problem, 삼분탐색, 차분히 힌트를 찾아서 풀자
void FOSSIL_Input(int& fig1Num,int& fig2Num,vector<pair<double,double>>& figure1,vector<pair<double,double>>& figure2){
  cin>>fig1Num>>fig2Num;
  figure1.resize(fig1Num);
  figure2.resize(fig2Num);
  for(auto& ele: figure1){
    cin>>ele.first>>ele.second;
  }
  for(auto& ele: figure2){
    cin>>ele.first>>ele.second;
  }
}
double FOSSIL_yPos(pair<double,double>& point1,pair<double,double>& point2,double xPos){
  pair<double,double> tmpLo,tmpHi;
  if(point1.first<point2.first){
    tmpLo=point1; tmpHi=point2;
  }else{
    tmpLo=point2; tmpHi=point1;
  }
  if(tmpLo.first<=xPos&&xPos<tmpHi.first){
    double slope=(tmpHi.second-tmpLo.second)/(tmpHi.first-tmpLo.first);
    double yPos=tmpLo.second+slope*(xPos-tmpLo.first);
    return yPos;
  }else{
    return -1;
  }
}
double FOSSIL_yRange(vector<pair<double,double>>& figure1, vector<pair<double,double>>& figure2,double xPos){
  pair<double,double> fig1Range={-1,-1},fig2Range={-1,-1};  //(lo~hi)
  //get yPos for fig1
  for(int i=0;i+1<figure1.size();i++){
    double tmpY=FOSSIL_yPos(figure1[i],figure1[i+1],xPos);
    if(tmpY!=-1){
      if(fig1Range.first==-1){
        fig1Range.first=tmpY;
      }else{
        fig1Range.second=tmpY;
      }
    }
  }
  if(fig1Range.second==-1){
    fig1Range.second=FOSSIL_yPos(figure1.front(),figure1.back(),xPos);
  }
  if(fig1Range.first>fig1Range.second){
    fig1Range=make_pair(fig1Range.second,fig1Range.first);
  }
  //get yPos for fig2
  for(int i=0;i+1<figure2.size();i++){
    double tmpY=FOSSIL_yPos(figure2[i],figure2[i+1],xPos);
    if(tmpY!=-1){
      if(fig2Range.first==-1){
        fig2Range.first=tmpY;
      }else{
        fig2Range.second=tmpY;
      }
    }
  }
  if(fig2Range.second==-1){
    fig2Range.second=FOSSIL_yPos(figure2.front(),figure2.back(),xPos);
  }
  if(fig2Range.first>fig2Range.second){
    fig2Range=make_pair(fig2Range.second,fig2Range.first);
  }
  //return
  double lo=max(fig1Range.first,fig2Range.first),hi=min(fig1Range.second,fig2Range.second);
  return hi-lo;
}
pair<double,double> FOSSIL_getLoHi(vector<pair<double,double>>& figure1, vector<pair<double,double>>& figure2){
  double fig1Leftest(101),fig2Leftest(101),fig1Rightest(-1),fig2Rightest(-1);
  for(auto& ele: figure1){
    fig1Leftest=min(fig1Leftest,ele.first);
    fig1Rightest=max(fig1Rightest,ele.first);
  }
  for(auto& ele: figure2){
    fig2Leftest=min(fig2Leftest,ele.first);
    fig2Rightest=max(fig2Rightest,ele.first);
  }
  return make_pair(max(fig1Leftest,fig2Leftest),min(fig1Rightest,fig2Rightest));
}
double FOSSIL_Algo(int fig1Num,int fig2Num,vector<pair<double,double>> figure1, vector<pair<double,double>> figure2){
  //get lo and hi
  auto tmp=FOSSIL_getLoHi(figure1,figure2);
  double lo(tmp.first),hi(tmp.second);
  //삼분탐색 100회 실행
  for(int i=0;i<100;i++){
    if(FOSSIL_yRange(figure1,figure2,(lo*2+hi)/3)<FOSSIL_yRange(figure1,figure2,(lo+hi*2)/3)){
      lo=(2*lo+hi)/3;
    }else{
      hi=(lo+2*hi)/3;
    }
  }
  //반환 
  double result=FOSSIL_yRange(figure1,figure2,(lo+hi)/2);
  return result < 0 ? 0 : result;
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
    convex hull은 시계반대방향순서로 점을 표현해 나타낼 수 있다.
      ex) 직사각형 ABCD는 (A,B,C,D) -> AB, BC, CD, DA로 이루어진 직사각형 
      문제에서 이미 시계반대방향순서로 점을 표현했다. -> 선분의 연결관계등은 고민할 필요 없다.
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
          해석 1
            convex hull은 내각이 항상 180도 미만이다.
            만약 두 convex hull이 겹친다면, 교점에 존재하는 교선의 최대 각도는 180도이다.
              이때 180도인 경우는 선분이 완전히 겹치는 경우
              즉, 나머지 부분의각도는 모두 180도 미만이므로, 겹치는 부분도 convex hull이다.
                convexhull의 높이는 삼분탐색이 가능한 그래프이다.
          해석 2
            아랫 convex hull의 윗부분은, local maximum이 존재하며 삼분탐색이 가능하다. --(1)
            윗 convex hull의 아랫부분은, local minimum이 존재하며 삼분탐색이 가능하다. --(2)
            이때 겹치는 높이의 그래프는, (1)에서 (2)를 뺀 것의 그래프와 같다.
              즉 삼분탐색이 가능하다.
      3. 겹치는 길이를 구하는 법
          x에 대해, 각 convex hull에서의 내부 범위를 구하고, 두 convexhull에서 겹치는 범위를 구한다.
            x좌표를 포함하는 선분은, 시계 반대 방향으로 돌면서 구하면 된다.
              min(p[n].x,p[n+1].x) <= x position < max(p[n].x,p[n+1].x) -> n과 n+1이 구성하는 선분에 포함됨
  */
  /*전략
  전략1
    삼분탐색
      접근방법
        1. lo,hi를 구한다. 힌트-구하는조건-1을 참고 : O(n+m)
        2. 삼분탐색을 100회 수행한다. 겹치는 길이는 힌트-구하는조건-3을 참고 
            선분 구하기: O(n+m)
            높이 구하기: O(1)
    시간:
      O(100*(n+m));
    크기:
      O(n+m)
    개선 및 보완
      i~i+1번째 ele를 비교하는 함수를 사용할 때, (n-1)~0까지 한번에 비교하게 만들고 싶다면, point[(i+1)%n]처럼 표시하면 된다. 
      책의 방식: 윗껍질 아랫껍질을 분리하여 처리, 시계 반대방향으로 주어짐을 이용
        나의 방식: x좌표에 대한 y좌표의 범위를 각 다각형에서 구해서, 겹치는 y좌표를 통해 높이를 구함 

  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int fig1Num,fig2Num;
    vector<pair<double,double>> figure1,figure2;
    FOSSIL_Input(fig1Num,fig2Num,figure1,figure2);
    auto result=FOSSIL_Algo(fig1Num,fig2Num,figure1,figure2);
    cout<<fixed;
    cout.precision(10);
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

