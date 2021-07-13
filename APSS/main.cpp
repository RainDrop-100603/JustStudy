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
private:
  const double PI=2.0*acos(0.0);
  const double EPSILON=1e-11;
  int cmpDBL(double a, double b)const {
    if(fabs(a-b)<EPSILON){return 0; }
    else if(a<b){return -1; }
    else{return 1; }
  }
public:
  double x,y;
  vector2(double x_=0, double y_=0):x(x_),y(y_){}
  vector2 operator=(const vector2& rhs){x=rhs.x;y=rhs.y; return *this;}
  bool operator==(const vector2& rhs)const {return cmpDBL(x,rhs.x)==0&&cmpDBL(y,rhs.y)==0; }
  bool operator!=(const vector2& rhs)const {return !this->operator==(rhs); }
  bool operator<(const vector2& rhs)const {return this->operator==(rhs) ? false : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  bool operator<=(const vector2& rhs)const {return this->operator==(rhs) ? true : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  vector2 operator+(const vector2& rhs)const {return vector2(x+rhs.x,y+rhs.y); }
  vector2 operator-(const vector2& rhs)const {return vector2(x-rhs.x,y-rhs.y); }
  vector2 operator*(double rhs)const {return vector2(x*rhs,y*rhs); }  //실수 곱
  double length()const {return hypot(x,y); }
  vector2 normalize()const {return vector2(x/length(),y/length()); }
  vector2 polar()const {return fmod(atan2(x,y)+2*PI, 2*PI); }
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }
  vector2 project(const vector2& rhs)const {return rhs.normalize()*(rhs.normalize().dot(*this)); }
  bool onLine(const vector2& p1, const vector2& p2)const {return cmpDBL((*this-p1).dot(p2-p1),(*this-p1).length()*(p2-p1).length())==0; }   //직선 위
  bool onSegment(const vector2& p1, const vector2& p2)const {return this->onLine(p1,p2)&&min(p1,p2)<=*this&&*this<=max(p1,p2); }  //선분 위
  //기타 함수들
  vector2 pFoot(const vector2& point,const vector2& vec)const {return point+(*this-point).project(vec); } //*this에서 직선ab에 내린 수선의 발
  bool onEdge(const vector<vector2>& polygon)const{
    int pSize=polygon.size();
    for(int i=0;i<pSize;i++){
      if(this->onSegment(polygon[i],polygon[(i+1)%pSize])){
        return true;
      }
    }
    return false;
  }
  bool isInside(const vector<vector2>& polygon)const{  //*this가 polygon 내부에 있는가, 경계 포함 x
    if(this->onEdge(polygon)) {return false; }
    int crossCount(0),pSize(polygon.size());
    for(int i=0;i<pSize;i++){
      vector2 p1(polygon[i]),p2(polygon[(i+1)%pSize]);
      if((cmpDBL(p1.y,this->y)==-1)!=(cmpDBL(p2.y,this->y)==-1)){ 
        double crossX=(this->y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
        if(cmpDBL(this->x,crossX)==-1){crossCount++;}
      }
    }
    return crossCount%2>0;
  }
  bool isOutside(const vector<vector2>& polygon)const{return !(this->isInside(polygon)||this->onEdge(polygon)); }
  pair<bool,vector2> lineIntersection(const vector2& rhs, const vector2& p1, const vector2& p2)const{
    double det=(rhs-*this).cross(p2-p1);
    if(cmpDBL(det,0)==0) return make_pair(false,vector2()); //평행인 경우
    return make_pair(true,*this+(rhs-*this)*((p1-*this).cross(p2-p1)/det));
  }
  pair<bool,vector2> isCross(const vector2& rhs, const vector2& p1, const vector2& p2)const{  //*this-rhs가 p1-p2와의 교점이 있는가
    //두 직선의 교점을 구하기
    auto tmp=this->lineIntersection(rhs,p1,p2);
    if(!tmp.first){
      return make_pair(false,vector2());
    }
    vector2 crossPoint=tmp.second;
    //두 직선의 교점이 선분위에 있는지 확인 
    if(crossPoint.onSegment(p1,p2)&&crossPoint.onSegment(*this,rhs)){
      return make_pair(true,crossPoint);
    }else{
      return make_pair(false,vector2());
    }
  }
  //전역함수 오버로딩
  friend ostream& operator<<(ostream& os, const vector2& vec);
};
ostream& operator<<(ostream& os, const vector2& vec){
  os<<"("<<vec.x<<","<<vec.y<<")";
  return os;
}

// 계산 기하, vector의 이용, double이용시 오차범위 항상 유의
void TREASURE_Input(vector<vector2>& polygon, vector<vector2>& treasure){
  int x1,y1,x2,y2,N;
  cin>>x1>>y1>>x2>>y2>>N;
  treasure.push_back(vector2(x1,y1));treasure.push_back(vector2(x2,y1));
  treasure.push_back(vector2(x2,y2));treasure.push_back(vector2(x1,y2));
  polygon.resize(N);
  for(auto& ele:polygon){
    cin>>ele.x>>ele.y;
  }
}
double TREASURE_areaSize(vector<vector2>& polygon){
  int pSize=polygon.size();
  if(pSize<3){
    return 0;
  }
  double result=0;
  for(int i=0;i<pSize;i++){
    result+=polygon[i].cross(polygon[(i+1)%pSize]);
  }
  return result/2;
}
int TREASURE_pos(vector<vector2>& polygon, vector<vector2>& treasure, int idx){
  vector2 now=polygon[idx];
  vector2 next=polygon[(idx+1)%polygon.size()];
  if(now.onEdge(treasure)){
    if(next.isOutside(treasure)){
      return 1; //바깥으로 나가는 점
    }else{
      return -1;  //모서리에 머무르거나, 내부로 들어가는 점
    }
  }
  return 0; //경계에 있지 않고, 내부 혹은 외부에 있는 점 
}
vector<vector2> TREASURE_newPoly(vector<vector2>& polygon, vector<vector2>& treasure){
  int pSize=polygon.size();
  vector<vector2> newPoly;
  newPoly.push_back(polygon[0]);
  for(int idx=0;idx<pSize;idx++){
    vector2 now=polygon[idx];
    vector2 next=polygon[(idx+1)%pSize];
    vector<vector2> crossPoints;
    //treasure와의 교점을 구한다.
    for(int i=0;i<4;i++){
      auto tmp=now.isCross(next,treasure[i],treasure[(i+1)%4]);
      if(tmp.first){
        crossPoints.push_back(tmp.second);
      }
    }
    //가까운 순서대로 정리
    if(crossPoints.size()==2&&(now-crossPoints.front()).length()>(now-crossPoints.back()).length()){
      vector2 last=crossPoints.back();
      crossPoints.pop_back();
      crossPoints.insert(crossPoints.begin(),last);
    }
    crossPoints.insert(crossPoints.begin(),now);
    //순서대로 newPoly에 추가
    for(auto& ele:crossPoints){
      if(newPoly.back()!=ele){
        newPoly.push_back(ele);
      }
    }
  }
  if(newPoly.size()>=2){
    if(newPoly.front()==newPoly.back()){
      newPoly.pop_back();
    }
  }
  // newPoly.erase(unique(newPoly.begin(),newPoly.end())); //treasure의 모서리와 같이, 같은 점이 이어져서 나타나면 제거
  //newPoly의 시작점이, 내부에서 외부로 가는 경계의 점이 되도록 하자
  int npSize=newPoly.size();
  int idx=0;
  for(;idx<npSize;idx++){
    if(TREASURE_pos(newPoly,treasure,idx)==1){
      break;
    }
  }
  vector<vector2> result;
  for(int i=0;i<npSize;i++){
    result.push_back(newPoly[(i+idx)%npSize]);
  }
  return result;
}
vector<vector2> TREASURE_outsidePoly(vector<vector2>& polygon,vector<vector2> treasure,int begin,int end){
  //기본 polygon 생성
  vector<vector2> result;
  int pSize=polygon.size();
  for(int i=begin;i<=end;i++){
    result.push_back(polygon[i%pSize]);
  }
  //result[last]의 다음 위치로 와야할 treasure의 꼭짓점을 찾는다.
  vector2 last=result.back();
  int startPoint;
  for(int i=0;i<4;i++){
    if(last.onLine(treasure[i],treasure[(i+1)%4])){
      startPoint=i;
      break;
    }
  }
  //꼭짓점이 포함되면 추가한다.
  for(int i=0;i<4;i++){
    if(treasure[(startPoint+4-i)%4].isInside(result)){
      result.push_back(treasure[(i+startPoint+4-i)%4]);
    }
  }
  return result;
}
double TREASURE_Algo(vector<vector2> polygon, vector<vector2> treasure){
  //newPolygon에 교점도 모두 포함시키기 시작점은 내부에서 외부로 나가는 경계의 점이다.
  vector<vector2> newPolygon=TREASURE_newPoly(polygon, treasure);
  //서로 겹치는지 확인
  bool isDupl(false);
  for(int i=0;i<4;i++){
    if(treasure[i].isInside(polygon)){
      isDupl=true;
      break;
    }
  }
  for(int i=0;i<polygon.size();i++){
    if(polygon[i].isInside(treasure)){
      isDupl=true;
      break;
    }
  }
  if(!isDupl){
    return 0;
  }
  //겹치긴 하지만 교점이 없다면, 하나가 다른 하나를 완전히 포함 
  if(polygon.size()==newPolygon.size()){
    return min(TREASURE_areaSize(treasure),TREASURE_areaSize(polygon));
  }
  //제거해야하는 outsidePolygon을 구한다
  int polySize=newPolygon.size();
  int begin(-1);
  vector<vector<vector2>> outsidePoly;
  for(int idx=0;idx<=polySize;idx++){  
    if(newPolygon[idx%polySize].onEdge(treasure)){
      if(begin != -1){
        outsidePoly.push_back(TREASURE_outsidePoly(newPolygon,treasure,begin,idx));
        begin = -1;
      }
      if(TREASURE_pos(newPolygon,treasure,idx%polySize)==1){
        begin = idx;
      }
    }
  }
  //결과계산
  double result=TREASURE_areaSize(polygon);
  for(auto& ele: outsidePoly){
    result-=TREASURE_areaSize(ele);
  }
  // for(auto& ele: newPolygon){
  //   cout<<ele;
  // }cout<<endl;
  // double resultttt=0;
  // for(auto& ele: outsidePoly){
  //   resultttt+=TREASURE_areaSize(ele);
  // }
  // cout<<TREASURE_areaSize(polygon)<<":"<<resultttt<<endl;
  // for(auto& ele:outsidePoly){
  //   for(auto& ele2:ele){
  //     cout<<ele2;
  //   }
  //   cout<<endl;
  // }
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
    1)보물영역 내부에 포함되는 다각형 영역을 찾는 방법
      1. 하나의 단순 다각형
      2. 여러개의 단순 다각형
    2)섬의 영역에서, 보물영역 외부에 있는 다각형들을 제거하는 방법
      섬 내부의 다각형은 구할 필요가 없다.
      구현방법
        섬과 보물영역의 교점도 꼭짓점으로 추가해준다.
        섬의 시작점은, 보물영역 내부에서 외부로 이어지는 선분의 꼭짓점 중 하나로 한다. -> O(n)
          다음 꼭짓점이 외부면 나가는것, 경계거나 내부면 들어가는 것 
        섬의 꼭짓점을 반시계 방향으로 순회한다. -> O(n)
          보물영역 외부에 있는 섬의 영역polygon을 구한다.
            보물영역 내부에서 외부로 나가는 교점을 시작으로, 외부에서 내부로 들어가는 교점을 끝으로 하는 polygon을 구한다.
            해당 polygon의 마지막 점에서, polygon내부에 포함되는, 보물영역의 꼭짓점을 시계방향으로 추가한다. -> O(4)
        섬의 영역에서 보물영역 외부에 있는 영역을 빼준다.
  */
  /*전략
  전략1
    벡터를 이용한다.
    2)섬의 영역에서, 보물영역 외부에 있는 다각형들을 제거하는 방법
    시간
      O(n)
    크기
      O(n)
    개선 및 보완
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    vector<vector2> polygon,treasure;
    TREASURE_Input(polygon,treasure);
    auto result=TREASURE_Algo(polygon,treasure);
    cout<<"::::";
    cout<<result<<endl;
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




// 10
// 5 5 15 15 4
// 0 10
// 10 0
// 20 10
// 10 20
// 5 5 15 15 4
// 20 5
// 30 5
// 30 15
// 20 15
// 5 5 15 15 4
// 15 10
// 20 5
// 25 10
// 20 15
// 5 5 15 15 4
// 15 10
// 14 11
// 13 10
// 14 9
// 5 5 15 15 4
// 15 5
// 25 5
// 25 15
// 15 15
// 5 5 15 15 4
// 15 8
// 15 12
// 12 12
// 12 8
// 5 5 15 15 4
// 7 7
// 9 7
// 9 9
// 7 9
// 5 5 15 15 4
// 0 0
// 20 0
// 20 20
// 0 20
// 5 5 15 15 5
// 5 5
// 15 5
// 20 10
// 15 15
// 5 15
// 5 5 15 15 5
// 5 5
// 15 5
// 10 10
// 15 15
// 5 15

// sol
// 100, 0, 0, 2, 0, 12, 4, 100, 100, 75