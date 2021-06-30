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

class vector2{  //2차원벡터
  const double PI=2.0*acos(0.0);
public:
  double x,y;
  vector2(double x_=0, double y_=0):x(x_),y(y_){}
  vector2 operator=(const vector2& rhs){x=rhs.x;y=rhs.y; return *this;}
  bool operator==(const vector2& rhs)const {return x==rhs.x&&y==rhs.y; }
  bool operator<(const vector2& rhs)const {return x!=rhs.x ? x<rhs.x : y<rhs.y; }
  vector2 operator+(const vector2& rhs)const {return vector2(x+rhs.x,y+rhs.y); }
  vector2 operator-(const vector2& rhs)const {return vector2(x-rhs.x,y-rhs.y); }
  vector2 operator*(double rhs)const {return vector2(x*rhs,y*rhs); }  //실수 곱
  double length()const {return hypot(x,y); }
  vector2 normalize()const {return vector2(x/length(),y/length()); }
  vector2 polar()const {return fmod(atan2(x,y)+2*PI, 2*PI); }
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }
  vector2 project(const vector2& rhs)const {return rhs.normalize()*(rhs.normalize().dot(*this)); }
  //기타 함수들
  vector2 pFoot(const vector2& point,const vector2& vec)const {return point+(*this-point).project(vec); } //*this에서 직선ab에 내린 수선의 발
  bool isInside(const vector<vector2>& polygon){  //*this가 polygon 내부에 있는가
    int crossCount,pSize(polygon.size());
    for(int i=0;i<pSize;i++){
      vector2 p1(polygon[i]),p2(polygon[(i+1)%pSize]);
      if(p1.y>this->y != p2.y>this->y){ 
        double crossX=(this->y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
        if(this->x<crossX){crossCount++;}
      }
    }
    return crossCount%2>0;
  }
  //전역함수 오버로딩
  friend ostream& operator<<(ostream& os, vector2& vec);
};
ostream& operator<<(ostream& os, vector2& vec){
  os<<"("<<vec.x<<","<<vec.y<<")";
  return os;
}
// 계산 기하, vector의 이용, double이용시 오차범위 항상 유의
void TREASURE_Input(int& xPos,int& yPos,int& dx,int& dy,int& num,vector<int>& centerX,vector<int>& centerY,vector<int>& radius){
  cin>>xPos>>yPos>>dx>>dy>>num;
  centerX.resize(num);centerY.resize(num);radius.resize(num);
  for(int i=0;i<num;i++){
    cin>>centerX[i]>>centerY[i]>>radius[i];
  }
}
vector2 TREASURE_lineSym(vector2 point1,vector2 a,vector2 b){
  //point1을 직선 ab에대해 선대칭 이동한다.
  vector2 crossPoint=point1.pFoot(a,b-a);
  return point1+(crossPoint-point1)*2;
}
pair<int,vector2> TREASURE_ifMet(vector<int>& centerX,vector<int>& centerY,vector<int>& radius,vector2 ballPoint, vector2 ballVector){
  double minDist=1000.0;
  int circleIdx=-1;
  for(int i=0;i<centerX.size();i++){
    //새로운 공까지의 거리 구하기, 피타고라스 정리, 스치고 가는것도 포함하는듯
    vector2 center(centerX[i],centerY[i]);
    vector2 pFoot=center.pFoot(ballPoint,ballVector);
    double rad=radius[i];
    double lenShort=(center-pFoot).length();
    if(lenShort>rad+1.0+1e-9||ballVector.dot(center-ballPoint)<=1e-9){
      continue;
    }
    double lenLong=(pFoot-ballPoint).length();
    double distance=lenLong-sqrt(pow(rad+1,2)-pow(lenShort,2));
    //공이 범위를 벗어난 경우 
    // vector2 newBall=ballPoint+ballVector*distance;
    // if(newBall.x>99+1e-7||newBall.x<1-1e-7||newBall.y>99+1e-7||newBall.y<1-1e-7){
    //   continue;
    // }
    //가장 가까운 위치인가?
    if(distance<minDist){
      minDist=distance;
      circleIdx=i;
    }
  }
  return make_pair(circleIdx,ballPoint+ballVector*minDist);
}
vector<int> TREASURE_func(vector<int>& centerX,vector<int>& centerY,vector<int>& radius,vector2 ballPoint, vector2 ballVector, int count){
  //기저, count만큼 반복
  if(count==0){
    return vector<int>();
  }
  //원과 만나는 벡터 중 가장 가까운 벡터를 구한다.
  pair<int,vector2> tmp=TREASURE_ifMet(centerX,centerY,radius,ballPoint,ballVector);
  // pair<int,vector2> tmp2=TREASURE_ifMet(centerX,centerY,radius,ballPoint,ballVector);
  // vector2 tmp3=tmp.second-tmp2.second;
  // cout<<tmp.first<<":"<<tmp2.first<<tmp.second<<":"<<tmp2.second<<":"<<tmp3<<endl;;
  int circleIdx=tmp.first;
  vector2 newBallPoint=tmp.second;
  if(circleIdx==-1){  //벽과 만났다.
    return vector<int>();
  }
  // 새로운 핀볼의 위치와 방향벡터를 구한다.
  vector2 center(centerX[circleIdx],centerY[circleIdx]);
  vector2 newBallVector=TREASURE_lineSym(ballPoint,center,newBallPoint)-newBallPoint;
  newBallVector=newBallVector.normalize();
  //재귀, 정답을 반대로 저장함에 유위하자
  vector<int> result=TREASURE_func(centerX,centerY,radius,newBallPoint,newBallVector,count-1);
  result.push_back(circleIdx);
  return result;
}
vector<int> TREASURE_Algo(int xPos,int yPos,int dx,int dy,int num,vector<int> centerX,vector<int> centerY,vector<int> radius){
  //재귀함수 구현
  vector2 ballPoint(xPos,yPos),ballVector(dx,dy); 
  ballVector=ballVector.normalize();
  int count=100;
  vector<int> result=TREASURE_func(centerX,centerY,radius,ballPoint,ballVector,count);
  reverse(result.begin(),result.end());
  return result;
}
void TREASURE(){
  // TREASURE
  /*설명 및 입력
  설명
    섬의 지도가 위 그림과 같이 N개의 점을 갖는 다각형으로 주어질 때, 
      보물이 묻혀 있을 수 있는 곳은 두 점 (x1,y1)과 (x2,y2) 를 서로 대칭인 꼭지점으로 갖고, 
      네 변이 모두 x축 혹은 y축에 평행한 직사각형 내부입니다. 
    우리는 이 직사각형 내에 포함된 육지를 전부 조사하고 싶습니다. 
    우리가 조사해야 할 부분의 넓이를 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 다섯 개의 정수로 직사각형의 꼭지점의 좌표 x1 , y1 , x2 , y2 (0 <= x1 < x2 <= 100,0 <= y1 < y2 <= 100) 
      그리고 섬의 지도를 나타내는 다각형 꼭지점의 수 N (3 <= N <= 100) 이 주어집니다. 
      그 후 N 줄에 각 2개의 정수로 각 꼭지점의 좌표 Xi , Yi (0 <= Xi, Yi <= 100) 가 주어집니다. 
      꼭지점은 시계 반대 방향으로 주어지며, 마지막 점은 첫 번째 점과 연결되어 있습니다.
    주어진 섬의 면적이 0이거나, 섬의 경계선이 자기 자신과 교차하거나 겹치는 경우는 없습니다.
  출력
    각 테스트 케이스마다 한 줄에 조사해야 할 육지의 넓이를 출력합니다. 
    10-7 이하의 절대/상대 오차를 갖는 답은 정답으로 인정됩니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    섬은 단순 다각형(simple polygon)이다.
    조사해야할 부분의 모양
      1. 하나의 단순 다각형
      2. 여러개의 단순 다각형
    꼭짓점을 이용한 방법
      조사해야할 부분의 꼭짓점
        1. 섬과 직사각형 영역의 교점
        2. 섬 내부의 점
      꼭짓점을 어떻게 이어서 모양을 만들어야하나?
    선분을 이용한 방법
      보물 영역과 섬 영역의 경우의 수
        1. 섬 영역이 보물 영역을 완전히 포함 -> 꼭짓점 4개가 섬에 포함됨
        2. 영역이 일부 겹치면서, 하나의 단순 다각형 영역을 이룸
        3. 영역이 일부 겹치면서, 여러개의 단순 다각형 영역을 이룸
      구현방법
        1. 모든 섬의 꼭짓점이 보물영역 바깥에 있다면, 섬 영역이 보물영역을 완전히 포함한다.
        2. 만약 포함되는 꼭짓점이 있다면, 해당 영역에서 시작하여 겹치는 부분을 찾아낸다.
          2-1. 계속하여 다음 꼭짓점을 순회하며 찾는다. 이때 보물 영역과의 교점이 생긴다면, 해당 부분을 꼭짓점으로 한다.
            2-1-1. 다음 꼭짓점이 직전 꼭짓점과 같은 선분에 있다면, 그대로 꼭짓점을 추가한다.
            2-1-2. 다음 꼭짓점이 직전 꼭짓점과 다른 선분에 있다면, 그 선분까지 이어지도록 꼭짓점을 추가한다.
  */
  /*전략
  전략1
    벡터의 이용
      1. 각 원의 중심과 직선 사이의 거리를 구한다. -> O(n)
          거리가 원의반지름+1 이하라면 만나는 것이다.
      2. 만나는 원 중 가장 가까운 것을 찾는다. 수선의발, 반지름+1, 피타고라스의 정리를 이용한다. -> O(n)
          만나는 원이 없거나, 만나는 위치가 범위 밖이라면 벽을 만난 것이다.
      3. 핀볼이 멈춘 지점의 벡터를 구한다. 원의중심에서 직선으로 수선의 발을 내리면 된다.
      4. 핀볼의 시작위치를, 수선의 발에 대해 선대칭이동한다. 이것이 핀볼이 다시 이동할 방향이다.
      5. 벽을 만나거나 100회 반복할때까지 반복한다. -> O(100)
    시간
      O(100n)
    크기
      O(1)
    개선 및 보완
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(14);
  //각 테스트케이스
  while(testCase--){
    int xPos,yPos,dx,dy,num;
    vector<int> centerX,centerY,radius;
    TREASURE_Input(xPos,yPos,dx,dy,num,centerX,centerY,radius);
    auto result=TREASURE_Algo(xPos,yPos,dx,dy,num,centerX,centerY,radius);
    //cout<<"::::";
    for(int i=0;i<result.size();i++){
      if(i) cout<<" ";
      cout<<result[i];
    }cout<<endl;
  }
}

int main(void){
    //clock_t start,end;
    //start=clock();
  TREASURE();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}




