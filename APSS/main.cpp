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
};

// 정수론, 유클리드 알고리즘 최대공약수를 이용
void PINBALL_Input(int& num,vector<int>& recipe,vector<int>& used){
  cin>>num;
  recipe.resize(num);
  for(auto& ele:recipe){
    cin>>ele;
  }
  used.resize(num);
  for(auto& ele:used){
    cin>>ele;
  }
}
int PINBALL_getGCD(int p,int q){
  return q==0 ? p : PINBALL_getGCD(q,p%q);
}
vector<int> PINBALL_Algo(int num,vector<int> recipe,vector<int> used){
  //get ratio and factor
  vector<int> ratio(recipe);
  int factor=0;
  for(int i=0;i<num;i++){
    factor=PINBALL_getGCD(factor,recipe[i]);
  }
  for(auto& ele:ratio){
    ele/=factor;
  }
  //get new factor
  int newFactor=0;
  for(int i=0;i<num;i++){
    int tmp=ceil(static_cast<double>(used[i])/ratio[i]);
    newFactor=max(newFactor,tmp);
  }
  newFactor=max(newFactor,factor);
  //get result
  vector<int> result(num);
  for(int i=0;i<num;i++){
    result[i]=ratio[i]*newFactor-used[i];
  } 
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
        시작점부터 교점까지의 좌표가 가장 작은 것이 가장 먼저 만나는 점이다.
          시작점-원의 중심 벡터를 a라 하자, 핀볼의 경로는 벡터 b
          벡터a를 벡터b에 projection, 원의 중심과 벡터b의 거리를 구하고, 원의 반지름을 이용한 피타고라스의 정리(그림그려보자)
          길이를 알고나면, 교점도 알 수 있다. 
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
      1. 각 원의 중심과 벡터 사이의 거리를 구한다. -> O(n)
      2. 만나는 원 중 가장 가까운 것을 찾는다. projection과 피타고라스의 정리를 이용한다. -> O(n)
          만나는 원이 없거나, 만나는 위치가 범위 밖이라면 벽을 만난 것이다.
      3. 원과 벡터의 교점을 구한다. 단위벡터에 root(거리)를 곱하면 된다. -> O(1)
      4. 시작점을, 원의 중심과 교점을 잇는 벡터에 대해 선대칭 이동한다. -> O(1)
      5. 원과의 교점과 선대칭이동된 점이 이루는 벡터가 새로운 벡터이다.
      6. 벽을 만나거나 100회 반복할때까지 반복한다. -> O(100)
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
    int xPos,yPos,dx,dy,N;
    vector<int> centerX,centerY,radius;
    PINBALL_Input(num,recipe,used);
    auto result=PINBALL_Algo(num,recipe,used);
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

