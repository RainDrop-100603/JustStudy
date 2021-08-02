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
  double polar()const {return fmod(atan2(x,y)+2*PI, 2*PI); } //x축에서의 각
  double polarFrom(const vector2& rhs)const {return rhs.polar()>this->polar()? this->polar()+2*PI-rhs.polar() : this->polar()-rhs.polar(); } //rhs에서의 각
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }
  int ccw(const vector2& a, const vector2& b)const {return cmpDBL((b-a).cross(*this-a),0); } // 1:counterclockwise, 0: 평행, -1:clockwise
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
vector<vector2> NERDS_1_getEdge(const vector<vector2>& group){
  int groupSize=group.size();
  double PI=vector2().PI;
  int base=0;
  for(;base<groupSize;base++){
    //다른 점과 이루는 직선의 polar구하기
    vector<pair<double,int>> polars;
    for(int i=0;i<groupSize;i++){
      if(i==base){continue; }
      polars.push_back(make_pair((group[i]-group[base]).polar(),i));
    }
    sort(polars.begin(),polars.end());
    //간극의 최대값 구하기
    double tmpMax=0;
    int target;
    for(int i=0;i<polars.size()-1;i++){
      auto tmpValue=polars[i+1].first-polars[i].first;
      if(tmpValue>tmpMax){
        tmpMax=tmpValue;
        target=polars[i].second;
      }
    }
    if(polars.front().first+2*PI-polars.back().first>tmpMax){
      tmpMax=polars.front().first+2*PI-polars.back().first;
      target=polars.back().second;
    }
    //모서리가 될 수 있는지 판별
    if(tmpMax-PI<=vector2().EPSILON){continue; }
    //모서리 구하고 반환, 
    bool isEdge(true);
    for(int i=0;i<groupSize;i++){
      if(i==base||i==target){continue; }
      if(group[i].ccw(base,target)==-1){
        isEdge=false;
        break;
      }
    }
    if(isEdge){
      return vector<vector2>{group[base],group[target]};
    }else{
      return vector<vector2>{group[target],group[base]};
    }
  }
}
vector<vector2> NERDS_1_getPoly(vector<vector2>& group, vector<vector2>& edge){
  vector<vector2> polygon=edge;
  vector2 prev,now(polygon.front());
  while(true){
    prev=now;now=polygon.back();
    vector2 currentValue;
    double currentAngle=1000;
    for(auto& tmpValue: group){
      if(tmpValue==now||tmpValue==prev){continue; }
      double tmpAngle=(tmpValue-now).polarFrom(now-prev);
      if(tmpAngle<currentAngle){
        currentAngle=tmpAngle;
        currentValue=tmpValue;
      }else if(tmpAngle==currentAngle){
        if((currentValue-now).length()<(tmpValue-now).length()){
          currentValue=tmpValue;
        }
      }
    }
    if(currentValue==polygon.front()){
      return polygon;
    }
    polygon.push_back(currentValue);
  }
}
vector<vector2> NERDS_1_cutPoly(vector<vector2>& polygon, vector2 prev, vector2 now){
  vector<vector2> result;
  if(polygon.empty()){
    return result;
  }
  vector2 nowPoint(polygon.back()),prevPoint;
  for(auto& ele:polygon){
    prevPoint=nowPoint;
    nowPoint=ele;
    int prevCCW(prevPoint.ccw(prev,now)),nowCCW(nowPoint.ccw(prev,now));
    if(prevCCW>=0){
      result.push_back(prevPoint);
    }
    if(prevCCW!=0&&nowCCW==-1*prevCCW){
      result.push_back(nowPoint.lineCross(prevPoint,now,prev).second);
    }
  }
  return result;
}
bool NERDS_1_determine(vector<vector2>& notNerdPoly,vector<vector2>& nerdPoly){
  int nerdSize=nerdPoly.size();
  for(int i=0;i<nerdSize;i++){
    vector2 from(nerdPoly[i]),to(nerdPoly[(i+1)%nerdSize]),line(to-from);
    //polar가 -90이상 90미만인지 확인한다.
    if(line.polar()>=vector2{0,1}.polar()&&line.polar()<vector2{0,-1}.polar()){
      continue;
    }
    //notNerdPoly의 원소가 모드 우측에 있는지 확인
    bool isValid(true);
    for(auto& ele: notNerdPoly){
      if(ele.ccw(from,to)==-1){continue; }
      if(ele.ccw(from,to)==0&&ele.position(nerdPoly)==1){continue; }
      isValid=false; 
      break;
    }
    if(isValid){return true; }
  }
  return false;
}
string NERDS_1_Algo(int peopleNum, vector<vector<int>> peopleInfo){
  //nerd와 notNerd를 구분한다
  vector<vector2> nerds,notNerds;
  for(auto& ele: peopleInfo){
    if(ele[0]==0){notNerds.push_back(vector2(ele[1],ele[2])); }
    else{nerds.push_back(vector2(ele[1],ele[2])); }
  }
  //시작 모서리를 구한다. nerds는 모서리
  vector<vector2> nerdEdge,notNerdEdge;
  nerdEdge=NERDS_1_getEdge(nerds);  
  notNerdEdge=NERDS_1_getEdge(notNerds);
  for(auto& ele: nerdEdge){cout<<ele;}cout<<endl;
  for(auto& ele: notNerdEdge){cout<<ele;}cout<<endl;
  //두 다각형을 구한다. nerds는 다각형
  vector<vector2> nerdPoly,notNerdPoly;
  nerdPoly=NERDS_1_getPoly(nerds,nerdEdge);
  notNerdPoly=NERDS_1_getPoly(notNerds,notNerdEdge);
  for(auto& ele: nerdPoly){cout<<ele;}cout<<endl;
  for(auto& ele: notNerdPoly){cout<<ele;}cout<<endl;
  //한 nerd의 모서리-직선에 대해, non-nerd가 모두 왼쪽에 있는지 확인한다.
  if(NERDS_1_determine(notNerdPoly,nerdPoly)){
    return string("THEORY HOLDS");
  }else{
    return string("THEORY IS INVALID");
  }
} 
bool NERDS_2_lineControl(vector<vector2>& nerds,vector<vector2>& notNerds,vector<vector2>& line,vector2 point,bool isNerd){
  if(isNerd){
    line.back()=point;
    //성질을 유지하는지 확인
    for(auto& ele:nerds){
      auto position=ele.ccw(line.front(),line.back());
      if(position==)
    }
    for(auto& ele:notNerds){
      auto position=ele.ccw(line.front(),line.back());
      if(position==){

      }
    }
  }else{

  }
}
string NERDS_2_Algo(int peopleNum, vector<vector<int>> peopleInfo){
  //최초의 직선 생성
  vector2 firstNerd(-1,-1),firstNot(-1,-1),validTest(-1,-1);
  for(auto& ele: peopleInfo){
    if(firstNerd==validTest&&ele[0]==1){
      firstNerd=vector2(ele[1],ele[2]);
    }else if(firstNot==validTest&&ele[0]==0){
      firstNot==vector2(ele[1],ele[2]);
    }
    if(firstNerd!=validTest&&firstNot!=validTest){break; }
  }
  vector<vector2> line{firstNot,firstNerd};
  //추가 입력에 따른 직선 변화
  vector<vector2> nerds,notNerds;
  for(auto& ele:peopleInfo){
    vector2 point(ele[1],ele[2]);
    bool isNerd(ele[0]==1);
    if(isNerd){
      switch(point.ccw(line.front(),line.back())){
        case(-1):
          nerds.push_back(point);
          break;
        case(0):
          if(point<=line.front()){return string("THEORY IS INVALID"); }
          else if(point<=line.back()){line.back()=point;}
          nerds.push_back(point);
          break;
        case(1):
          if(NERDS_2_lineControl(nerds,notNerds,line,point,isNerd)==false){return string("THEORY IS INVALID"); }
          break;
        default:
          cout<<"something error";
          break;
      }
    }else{
      switch(point.ccw(line.front(),line.back())){
        case(1):
          notNerds.push_back(point);
          break;
        case(0):
          if(line.back()<=point){return string("THEORY IS INVALID"); }
          else if(line.front()<=point){line.front()=point;}
          notNerds.push_back(point);
          break;
        case(-1):
          if(NERDS_2_lineControl(nerds,notNerds,line,point,isNerd)==false){return string("THEORY IS INVALID"); }
          break;
        default:
          cout<<"something error";
          break;
      }
    }
  }
  //각도 구하기
  double polar=(line.back()-line.front()).polar();
  if(polar<vector2{0,1}.polar()||polar>=vector2{0,-1}.polar()){return string("THEORY HOLDS"); }
  else{return string("THEORY IS INVALID"); }
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
    nerd와 non-nerd를 그룹지어서, 두 영역을 직선으로 나눌 수 있는지 확인하는 방법이라 생각할 수 있다.
    아이디어1 -> O(n^2 + n^2)
      각 그룹의 최외각의 점들로 단순 볼록다각형을 만든다(최외각의 점의 경우 반드시 단순 볼록 다각형이 된다). -> O(n^2 + n^2)
        최외각의 있는 점 하나를 구하고, edge를 하나 구한다. -> O(n^2)
          최외각의 있는 점은, 기준점에서 다른점으로의 직선의 polar를 구한 뒤, 각 polar의 간극을 구한다.
          2PIE-max(간극)이, 다른 점들이 존재하는 범위이며, 이것이 PIE이하라면 최외각의 점이다
        edge부터 순회하여 다각형을 구한다. -> O(n^2)
      해당 볼록다각형이 접하거나 겹친다면, 두 영역을 나누는 직선이 존재하지 않는다. -> O(n^2)
        한 다각형의 모든 모서리-직선에 대해, 다른 다각형을 자르면 된다.
        개선점
          선분을 기준으로 아래에 non-nerd, 위에 nerd가 있어야하는데, 이 방법은 그것을 구분할 수 없다. 
          개선방법
            nerd의 각 모서리-직선에 대해, non-nerd의 모든점이 직선위에 있거나 우측에 있는 모서리를 찾는다.
              직선위에 있는 경우는,nerd에 포함되는 경우는 제한다.
            이때 모서리 직선의 polar는 270~360도 사이여야 한다.
    아이디어 2 -> O(n^2 * n)
      같은 영역의 속하는 두 점을 임의로 골라 직선을 만든다. -> O(n^2)
      다른 모든점이 해당 직선에 대해 나누어진다면, 두 영역을 나누는 직선이 존재하는 것이다. -> O(n)
        ccw를 이용하면 된다. 
    아이디어 3
      각 영역에서 임의의 한 점을 구하고, 그 점을 이어 직선을 만든다.
      직선의 좌측엔 nerd, 우측엔 non-nerd가 있도록 새로운 직선을 만든다.
        직선에 우측에 위치한 nerd중, 가장 많이 회전해야하는 점을 선택한다(회전의 기준점은, 맨 처음에 선택한 점)
        직선의 좌측에 위치한 non-nerd중, 가장 많이 회전해해야하는 점을 선택한다.
      새로 선택한 점을 통해 새로운 직선을 만든다.
  */
  /*전략
  전략1
    아이디어 2
    시간
      O(n^3)
    크기
      O(n)
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
    auto result=NERDS_1_Algo(peopleNum,peopleInfo);
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

