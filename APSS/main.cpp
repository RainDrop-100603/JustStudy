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
  vector2 pFoot(const vector2& point,const vector2& vec)const {return point+(*this-point).project(vec); }//*this에서 직선ab에 내린 수선의 발
  //전역함수 오버로딩
  friend ostream& operator<<(ostream& os, vector2& vec);
};
ostream& operator<<(ostream& os, vector2& vec){
  os<<"("<<vec.x<<","<<vec.y<<")";
  return os;
}

// 정수론, 유클리드 알고리즘 최대공약수를 이용
void PINBALL_Input(int& xPos,int& yPos,int& dx,int& dy,int& num,vector<int>& centerX,vector<int>& centerY,vector<int>& radius){
  cin>>xPos>>yPos>>dx>>dy>>num;
  centerX.resize(num);centerY.resize(num);radius.resize(num);
  for(int i=0;i<num;i++){
    cin>>centerX[i]>>centerY[i]>>radius[i];
  }
}
vector2 PINBALL_lineSym(vector2 point1,vector2 a,vector2 b){
  //point1을 직선 ab에대해 선대칭 이동한다.
  vector2 crossPoint=point1.pFoot(a,b-a);
  return point1+(crossPoint-point1)*2;
}
double PINBALL_ifMet(vector2 center,double radius,vector2 ballPoint,vector2 ballVector){
  vector2 pFoot=center.pFoot(ballPoint,ballVector);
  double lenShort=(center-pFoot).length();
  //만나지 않는경우
  if(lenShort>=radius+1.0||ballVector.dot(center-ballPoint)<=0){
    return 0;
  }
  //길이 계산
  double lenLong=(pFoot-ballPoint).length();
  double distance=lenLong-sqrt(pow(radius+1,2)-pow(lenShort,2));
  vector2 newBall=ballPoint+ballVector*distance;
  //공이 범위를 벗어난 경우 
  if(newBall.x>=99||newBall.x<=1||newBall.y>=99||newBall.y<=1){
    return 0;
  }
  return distance;
}
vector<int> PINBALL_func(vector<int>& centerX,vector<int>& centerY,vector<int>& radius,vector2 ballPoint, vector2 ballVector, int count){
  cout<<count<<":"<<ballPoint<<":"<<ballVector<<":"<<endl;
  //기저, count만큼 반복
  if(count==0){
    return vector<int>();
  }
  //원과 만나는 벡터 중 가장 가까운 벡터를 구한다.
  double minDist=1000.0;
  int circleIdx=-1;
  for(int i=0;i<centerX.size();i++){
    if(int distance=PINBALL_ifMet(vector2(centerX[i],centerY[i]),radius[i],ballPoint,ballVector)){
      if(distance<minDist){
        minDist=distance;
        circleIdx=i;
      }
    }
  }
  if(circleIdx==-1){  //벽과 만났다.
    return vector<int>();
  }
  // 새로운 핀볼의 위치와 방향벡터를 구한다.
  vector2 center(centerX[circleIdx],centerY[circleIdx]);
  vector2 newBallPoint=ballPoint+ballVector*minDist;
  vector2 newBallVector=PINBALL_lineSym(ballPoint,center,newBallPoint)-newBallPoint;
  newBallVector=newBallVector.normalize();
  //재귀, 정답을 반대로 저장함에 유위하자
  vector<int> result=PINBALL_func(centerX,centerY,radius,newBallPoint,newBallVector,count-1);
  result.push_back(circleIdx);
  return result;
}
vector<int> PINBALL_Algo(int xPos,int yPos,int dx,int dy,int num,vector<int> centerX,vector<int> centerY,vector<int> radius){
  //재귀함수 구현
  vector2 ballPoint(xPos,yPos),ballVector(dx,dy); 
  ballVector=ballVector.normalize();
  int count=100;
  vector<int> result=PINBALL_func(centerX,centerY,radius,ballPoint,ballVector,count);
  reverse(result.begin(),result.end());
  return result;
}
void PINBALL(){
  // PINBALL
  /*설명 및 입력
  설명
    동혁이는 새로 나온 핀볼 게임을 하고 있습니다. 
      이 핀볼 게임은 아주 큰 게임판에 여러 개의 장애물을 놓고, 밖에서 공을 던져 가장 많은 장애물을 맞추는 것을 목표로 합니다. 
    공과 장애물은 완전한 원형이며, 공은 장애물에 부딪히면 항상 입사각과 반사각이 같도록 정반사됩니다. 
      장애물은 게임판에 고정되어 있기 때문에 움직이지 않습니다.
    장애물들의 위치와 크기가 주어지고, 공의 위치와 방향이 주어질 때 공이 부딪히는 장애물들의 번호를 계산하는 프로그램을 작성하세요. 
      공은 반지름 1인 원이며, 항상 직선으로 움직인다고 가정합니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C(C <= 50)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 5개의 정수 x, y, dx, dy, N 이 주어집니다. 
      이 때 x, y (0 <= x, y <= 100)는 현재 공 중심의 위치를 나타내며, dx, dy (-10 <= dx, dy <= 10)는 공의 방향을 나타냅니다. 
      이 때 공은 현재 (x,y) 에서 (x+dx, y+dy)를 향해 일직선으로 굴러가고 있습니다. 
    N(0 <= N <= 50)은 장애물의 개수를 나타내며, 각 장애물에는 0번부터 N-1번까지의 번호가 매겨져 있습니다. 
      그 다음 N줄에는 0번부터 각 장애물의 정보가 3개의 정수 x_i, y_i, r_i 로 주어집니다. 
      (0 <= x_i, y_i, r_i <= 100) 이 때 i번 장애물은 (x_i, y_i)을 중심으로 한 반지름 r_i인 원 형태를 하고 있습니다.
  장애물은 게임판 밖에 걸쳐 있을 수도 있습니다. 
    두 장애물 사이의 거리가 2 이하인 경우는 없습니다. 
    시작 위치에서 공은 장애물과 겹쳐 있거나 닿아 있지 않습니다.
  공은 게임판의 벽에 닿는 순간 게임판에서 떨어진다고 가정합니다. 
    입력에 공이 게임판의 벽과 장애물에 동시에 닿는 경우는 주어지지 않습니다.
  출력
    각 테스트 케이스마다 한 줄에 공이 닿는 순서대로 각 장애물의 번호를 출력합니다. 
      만약 공이 장애물에 100번 넘게 부딪힐 경우 첫 100번 부딪히는 장애물의 번호만을 출력합니다.
    주어진 입력에서 장애물의 크기나 위치가 10^-7 만큼 변하더라도 답은 변하지 않는다고 가정해도 좋습니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    시작점을 어떻게 구현하는가
      힌트
        벡터를 구할때 시작점을 (0,0)으로 두고 계산하면 벡터만으로 계산이 된다.
    원과 벡터가 만나는지를 구할 수 있어야 한다.
      힌트
        가장 처음 만나는 원을 구하는 방법
        원을 만나지 않는다는 것은, 벽을 만난다는 것과 같다.
          원을 만났더라도, 이때의 좌표가 범위(0~100)를 벗어나면, 벽을 만난것으로 판단한다.
      방법1
        원의 중심과 벡터와의 거리를 구한다. -> 원과 만나는지 알 수 있다.
          거리는 1+원의 반지름 이하여야 한다.
        시작점부터 교점까지의 좌표가 가장 작은 것이 가장 먼저 만나는 점이다.
          시작점-원의 중심 벡터를 a라 하자, 핀볼의 경로는 벡터 b
          벡터a를 벡터b에 projection, 원의 중심과 벡터b의 거리를 구하고, 원의 반지름+1을 이용한 피타고라스의 정리(그림그려보자)
            핀볼의 이동거리와 새로운 중심을 구할 수 있다.
          원과 핀볼의 교점도 구할 수 있다. (필요할지는 모르겠다)
            핀볼의 새로운 중심에서 원의 중심을 향한 벡터를 c라 하자
            벡터 a와 벡터 c를 더하면, 핀볼의 시작점에서 핀볼과 원의 교점으로 향하는 벡터다. 
        모든 원에 대해 수행하면 된다.
    입사각과 반사각이 같도록 튕겨나가는 것을 구현해야 한다.
      힌트
        두 벡터 사이의 각도를 구하는 방법
        벡터를 특정 각도만큼 회전시키는 방법
      방법1
        벡터에 대해 점을 선대칭으로 이동시킨다.
        원과의 교점과, 대칭이동된 점을 잇는 벡터를 구하면 된다.
    함수 자체는 재귀를 이용하면 된다.
      벽을 만나거나 count=100이 되면 stop
    풀이법
      1. 가장 먼저 만나는 원을 구한다. 원이 없거나 범위를 벗어난다면 벽이다.
      2. 원과의 교점과 입사각을 구하고, 입사각과 반사각이 같도록 교점에서 벡터를 회전시킨다. 이후 1을 반복    
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
  //각 테스트케이스
  while(testCase--){
    int xPos,yPos,dx,dy,num;
    vector<int> centerX,centerY,radius;
    PINBALL_Input(xPos,yPos,dx,dy,num,centerX,centerY,radius);
    auto result=PINBALL_Algo(xPos,yPos,dx,dy,num,centerX,centerY,radius);
    //cout<<"::::";
    for(auto& ele:result){
      cout<<ele<<" ";
    }cout<<endl;
  }
}

int main(void){
    //clock_t start,end;
    //start=clock();
  PINBALL();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

