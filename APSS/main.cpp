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

//vector2에 대한 정리
//polygon생성?

class vector2{  //2차원벡터
public:
  const double PI=2.0*acos(0.0);
  const double EPSILON=1e-11;
  double x,y;
  vector2(double x_=0, double y_=0):x(x_),y(y_){}
  int cmpDBL(double a, double b)const {if(fabs(a-b)<EPSILON){return 0; }else if(a<b){return -1; }else{return 1; } }
  vector2 operator=(const vector2& rhs){x=rhs.x;y=rhs.y; return *this;}
  bool operator==(const vector2& rhs)const {return cmpDBL(x,rhs.x)==0&&cmpDBL(y,rhs.y)==0; }
  bool operator!=(const vector2& rhs)const {return !this->operator==(rhs); }
  bool operator<(const vector2& rhs)const {return this->operator==(rhs) ? false : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  bool operator<=(const vector2& rhs)const {return this->operator==(rhs) ? true : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  bool operator>(const vector2& rhs)const {return !this->operator<=(rhs); }
  bool operator>=(const vector2& rhs)const {return !this->operator<(rhs); }
  vector2 operator+(const vector2& rhs)const {return vector2(x+rhs.x,y+rhs.y); }
  vector2 operator-(const vector2& rhs)const {return vector2(x-rhs.x,y-rhs.y); }
  vector2 operator*(double rhs)const {return vector2(x*rhs,y*rhs); }  //실수 곱
  double length()const {return hypot(x,y); }
  vector2 normalize()const {return vector2(x/length(),y/length()); }
  double polar()const {return fmod(atan2(y,x)+2*PI, 2*PI); } //x축에서의 각
  double polarFrom(const vector2& rhs)const {return rhs.polar()>this->polar()? this->polar()+2*PI-rhs.polar() : this->polar()-rhs.polar(); } //rhs에서의 각
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }
  int ccw(const vector2& from, const vector2& to)const {return cmpDBL((to-from).cross(*this-from),0); } // 1:counterclockwise, 0: 평행, -1:clockwise
  vector2 project(const vector2& rhs)const {return rhs.normalize()*(rhs.normalize().dot(*this)); }
  bool onLine(const vector2& p1, const vector2& p2)const {return cmpDBL((*this-p1).dot(p2-p1),(*this-p1).length()*(p2-p1).length())==0; }   //직선 위
  bool onSegment(const vector2& p1, const vector2& p2)const {return this->onLine(p1,p2)&&min(p1,p2)<=*this&&*this<=max(p1,p2); }  //선분 위
  //기타 함수들  
  vector2 pFoot(const vector2& point,const vector2& vec)const {return point+(*this-point).project(vec); } //*this에서 직선ab에 내린 수선의 발
  int position(const vector<vector2>& polygon)const{  // -1: inside, 0: edge, 1: outside (of polygon)
    int crossCount(0),pSize(polygon.size());
    for(int i=0;i<pSize;i++){
      vector2 p1(polygon[i]),p2(polygon[(i+1)%pSize]);
      if((cmpDBL(p1.y,this->y)==-1)!=(cmpDBL(p2.y,this->y)==-1)){ 
        double crossX=(this->y-p1.y)*(p2.x-p1.x)/(p2.y-p1.y)+p1.x;
        if(cmpDBL(this->x,crossX)==0){return 0; } //on Edge
        if(cmpDBL(this->x,crossX)==-1){crossCount++;}
      }
    }
    if(crossCount%2){
      return -1; //inside
    }else{
      return 1;  //outside
    }
  }
  pair<bool,vector2> lineCross(const vector2& rhs, const vector2& p1, const vector2& p2)const{//직선의 교점, 평행(일치)는 제외
    double det=(rhs-*this).cross(p2-p1);
    if(cmpDBL(det,0)==0) return make_pair(false,vector2()); //평행인 경우
    return make_pair(true,*this+(rhs-*this)*((p1-*this).cross(p2-p1)/det));
  }
  pair<bool,vector2> segCross(const vector2& rhs, const vector2& p1, const vector2& p2)const{  //*this-rhs가 p1-p2와의 교점이 있는가
    //두 직선의 교점을 구하기
    auto tmp=this->lineCross(rhs,p1,p2);
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

// @*@*@* 계산 기하, simple polygon clipping, 배열 접근시, 배열의 크기가 0인 경우도 반드시 생각하자 
//        예외가 많아보이는 방법이라면, 모든 예외를 처리하는것도 좋지만, 더 간단한 방법은 없는지 생각해보자
void NERDS_Input(int& peopleNum, vector<vector<int>>& peopleInfo){
  cin>>peopleNum;
  peopleInfo.resize(peopleNum);
  for(auto& ele:peopleInfo){
    int nerd,foot,type;
    cin>>nerd>>foot>>type;
    ele=vector<int>{nerd,foot,type};
  }
}
vector<vector2> NERDS_getPoly(const vector<vector2>& group){
  //죄하단 점은 반드시 최외각 점이다
  vector2 point=*min_element(group.begin(),group.end());
  //다음 점은 시계방향으로 가장 먼 위치에 있는 점이다.
  vector2 next=group[0];
  for(auto& ele: group){
    if(ele.ccw(point,next)<0){next=ele; continue; }
    if(ele.ccw(point,next)==0&&(ele-point).length()>(next-point).length()){next=ele;}
  }
  //polygon 구하기
  vector<vector2> polygon{point,next};
  while(true){
    point=polygon.back();
    next=group[0];
    for(auto& ele: group){
      if(ele.ccw(point,next)<0){next=ele; continue; }
      if(ele.ccw(point,next)==0&&(ele-point).length()>(next-point).length()){next=ele;}
    }
    if(next==polygon.front()){
      return polygon;
    }
    polygon.push_back(next);
  }
}
bool NERDS_determine1(vector<vector2>& notNerdPoly,vector<vector2>& nerdPoly){
  int nerdSize=nerdPoly.size();
  int notSize=notNerdPoly.size();
  //nerd의 모서리에 대해 비교
  for(int i=0;i<nerdSize;i++){
    vector2 from(nerdPoly[i]),to(nerdPoly[(i+1)%nerdSize]),line(to-from);
    //polar가 -90이상 90미만인지 확인한다.
    if(line.polar()>=vector2(0,1).polar()&&line.polar()<vector2(0,-1).polar()){
      continue;
    }
    //notNerdPoly의 원소가 모두 우측에 있는지 확인
    bool isValid(true);
    for(auto& ele: notNerdPoly){
      if(ele.ccw(from,to)==-1){continue; }
      if(ele.ccw(from,to)==0&&!ele.onLine(from,to)){continue; }
      isValid=false; 
      break;
    }
    if(isValid){return true; }
  }
  //notnerd의 모서리에 대해 비교
  for(int i=0;i<notSize;i++){
    vector2 from(notNerdPoly[i]),to(notNerdPoly[(i+1)%notSize]),line(to-from);
    //polar가 90도 이상 180도 미만인지 확인한다.
    if(line.polar()<vector2(0,1).polar()||line.polar()>=vector2(0,-1).polar()){
      continue;
    }
    //nerdPoly의 원소가 모두 우측에 있는지 확인
    bool isValid(true);
    for(auto& ele: nerdPoly){
      if(ele.ccw(from,to)==-1){continue; }
      if(ele.ccw(from,to)==0&&!ele.onLine(from,to)){continue; }
      isValid=false; 
      break;
    }
    if(isValid){return true; }
  }
  //어느 경우도 없는경우
  return false;
}
bool NERDS_determine2(vector<vector2>& notNerdPoly,vector<vector2>& nerdPoly){
  int nerdSize=nerdPoly.size();
  int notSize=notNerdPoly.size();
  //포함관계 확인 
  for(auto& ele:nerdPoly){
    if(ele.position(notNerdPoly)!=1){return false;}
  }
  for(auto& ele:notNerdPoly){
    if(ele.position(nerdPoly)!=1){return false;}
  }
  //겹치는 선 확인
  for(int i=0;i<nerdSize;i++){
    for(int j=0;j<notSize;j++){
      if(nerdPoly[i].segCross(nerdPoly[(i+1)%nerdSize],notNerdPoly[j],notNerdPoly[(j+1)%notSize]).first){
        return false;
      }
    }
  }
  //아무결격이 없다면 true
  return true;
}
bool NERDS_determine3(vector<vector2>& notNerdPoly,vector<vector2>& nerdPoly){
  int nerdSize=nerdPoly.size();
  int notSize=notNerdPoly.size();
  vector<vector2> minusLine(2);  //기울기가 음수인 직선 저장
  //직선의 기울기들을 구한다.
  vector2 prev,now(notNerdPoly.back()),next(notNerdPoly.front());
  for(int i=0;i<notSize;i++){
    prev=now; now=next; next=notNerdPoly[(i+1)%notSize];
    //직선의 한계 기울기를 구한다. 한계 기울기를 벗어나는 직선은 만들어 질 수 없다.
    double polarMin((now-prev).polar()),polarMax((next-now).polar());
    //가장 왼쪽으로 가는 직선을 구한다.
    vector<vector2> lineLeft{now,nerdPoly[0]},lineRight(lineLeft);
    for(int j=0;j<nerdSize;j++){
      vector2 target=nerdPoly[j];
      //가장 왼쪽으로 가는 직선
      if(target.ccw(now,lineLeft.back()==1)){lineLeft.back()=target;}
      //가장 오른쪽으로 가는 직선
      if(target.ccw(now,lineRight.back()==-1)){lineRight.back()=target;}
    }
    //직선이 유효 범위내에 있는지 확인한다.
    //left일 경우 not nerd 가 좌측에 존재하는지, right일 경우 우측에 존재하는지 확인한다.
    //left가 유효할 경우 직선의 범위는 left.polar()~polarMAX 이다.
    //right가 유효할 경우 직선의 범위는 polarMIN~right.polar()이다.
  }
  //기울기가 plus인 직선이 하나도 없다면, minus인 직선만 있다
  //직선이 우하단을 바라본다면, 좌상단을 바라보도록 변경
  //not nerd가 직선의 좌측에 있다면 true, 우측에 있다면 false 반환
}

string NERDS_Algo(int peopleNum, vector<vector<int>> peopleInfo){
  //nerd와 notNerd를 구분한다
  vector<vector2> nerds,notNerds;
  for(auto& ele: peopleInfo){
    if(ele[0]==0){notNerds.push_back(vector2(ele[1],ele[2])); }
    else{nerds.push_back(vector2(ele[1],ele[2])); }
  }
  //각 영역을 포함하는 convex hull을 구한다.
  vector<vector2> nerdPoly,notNerdPoly;
  nerdPoly=NERDS_getPoly(nerds);  
  notNerdPoly=NERDS_getPoly(notNerds);
  //두 polygon이 겹치지 않는지, 직선의 기울기가 음수일 때 not-nerd polygon이 직선 아래에 존재하는지 확인한다.
  if(NERDS_determine2(notNerdPoly,nerdPoly)&&NERDS_determine3(notNerdPoly,nerdPoly)){
    return string("THEORY HOLDS");
  }else{
    return string("THEORY IS INVALID");
  }
} 
void NERDS(){
  // TREASURE
  /*설명 및 입력
  설명
    Algospot.com's annual programming contest admit only the "true nerds"
    JongMan came up with a theory that whether a person's nerdiness is dependent on a linear combination of two factors: 
      their shoe size and their typing speed per minute. In his theory, the nerd score
    F = A * (shoe size) + B * (typing speed per minute)
      The higher the score, the nerdier the guy is. We intend to set a threshold T; we will only admit people with scores equal to or above T.
    However, will this theory work? To find it out, we grabbed the data from some people we personally know.
      We know their shoe size and typing speeds, and we know whether each of them is a nerd or not.
      Will there be a set of parameters A, B and T which can successfully separate nerds from the others?
    Please note that A, B and T can be arbitrary real numbers.
  입력
    The first line of the input file will contain the number of test cases, C (C = 50). 
      Each test case begins n (6 <= n <= 5,000) with the number of people we personally know. 
        n lines will follow with three nonnegative integers in each line. 
          The first integer is 1 if the person is a nerd, and 0 otherwise. 
          The second number and the third number will represent the person's shoe size and typing speed per minute. 
            These two numbers will be in the range [0, 10000].
    There will be always at least three people from both group of people - nerds and non-nerds. 
      Also, for each group, the two vectors formed by gathering their shoe sizes and typing speed, will be linearly independent. 
      That is, for one group, we make one vector [shoe[0], shoe[1], shoe[2], ..] 
        and another vector [speed[0], speed[1], speed[2], ..] and they will be linearly independent.
  출력
    For each test case, print one line. 
      The line must contain "THEORY HOLDS" if there are one or more set of parameters which satisfies the given data. 
      "THEORY IS INVALID" should be printed in the other case. 
    See the sample output for details.
  제한조건
    3초, 64MB
  */
  /*힌트
    신발 사이즈와 타이핑 스피드를 각각 x,y축이라 생각하면, 각 점을 수평면에 놓을 수 있다.
      F=A*신발사이즈+B*타이핑스피드는, 해당 평면에서의 직선이다.(F=Ax+By)
    nerd와 not-nerd를 그룹지어서, 두 영역을 직선으로 나눌 수 있는지 확인하는 방법이라 생각할 수 있다.
    두 영역을 나눌 때, not-nerd의 점수가 더 높게 나오는 경우도 생각해야한다.
      A>0, B<0 인 경우, 분리만 되면 된다. A<0, B>0인 경우도 마찬가지
      A<0, B<0 인 경우는 모두가 nerd가 아닌경우이다.
      A>0, B>0 인 경우, 직선 아랫부분이 not-nerd, 윗부분이 nerd여야 한다.
      -> 두 polygon을 나눌 수 있는 직선(이때 직선은 각각의 polygon에서의 점을 하나씩 이용한다.)을 만든다
        기울기가 0~90, 180~270 범위인 직선이 하나라도 있다면, A와 B의 부호가 다른 경우이다 : 항상 true
        직선이 모두 위의 기울기에 포함되지 않는다면, 직선 하나를 선택하여 직선 아래에 polygon이 있는지 확인한다.
    단순 볼록 다각형을 만드는 법
      gift wrapping O(n^2)
        최외각의 점을 하나 구한다
          1. 한 점에서 다른 모든 점으로의 직선의 polar를 구한다. 간극의 최댓값이 180도이하라면 최외각 점이다.
          2. 가장 좌측하단에 있는 점은 반드시 최외각 점이다(STL의 min_element를 이용할 수 있다, 우상단 우하단 좌상단도 최외각)
        최외각의 점에서, ccw방향 회전각이 가장 작은것이 다음 점이다.(가장 오른쪽에 있는 점)
          만약 회전각이 같다면, 거리가 더 먼 것을 선택한다.
        처음 위치로 돌아오기까지 반복
      Graham Scan O(nlgn)
    아이디어 1
      각 그룹의 영역을 포함하는 단순 볼록다각형을 만든다. 
      볼록 다각형이 겹치지 않는다면, 두 다각형 사이에는 반드시 직선이 존재한다.
        다각형 간의 포함관계를 먼저 확인하고, 모서리 사이의 교점이 있는지 확인한다.
  */
  /*전략
  전략1
    아이디어1
      각 그룹의 영역을 포함하는 단순 볼록다각형을 만든다. -> O(n^2)
        STL min_element를 이용하여 최외각 점을 구한다. -> O(n)
        반시계 방향으로 점을 구한다(반시계 방향 각도가 가장 작은 것). -> O(n^2)
      두 볼록 다각형이 겹치는지 확인한다.
        포함관계를 확인한다.  -> O(n^2)
        모서리의 겹침을 확인한다. ->O(n^2)
      nerd볼록다각형이 not-nerd볼록다각형보다 value가 큰지(직선의 위쪽에 있는지) 확인한다.
        추가바람
    시간
      O(n^2)
    크기
      O(n)
    피드백
      determine1: 두 영역이 "ㅁㅁ"와 같이 있을 때(왼쪽 너드), 함수는 false를 반환하지만, 실제로는 너드가 위로오도록 직선을 그을 수 있다.
      determine2: not-nerd가 명백히 위에 있는 경우에도 true를 반환한다.
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  cout<<fixed;
  cout.precision(10);
  //각 테스트케이스
  while(testCase--){
    int peopleNum;
    vector<vector<int>> peopleInfo;
    NERDS_Input(peopleNum,peopleInfo);
    auto result=NERDS_Algo(peopleNum,peopleInfo);
    // cout<<"::::";
    cout<<result<<endl;
  }
}

int main(void){
    //clock_t start,end;
    //start=clock();
  NERDS();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

