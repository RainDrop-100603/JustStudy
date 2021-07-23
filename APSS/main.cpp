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
string NERDS_Algo(int peopleNum, vector<vector<int>> peopleInfo){
  //섬을 보물영역의 모서리에 대해 자른다.
  bool result;
  //잘라진 섬의 넓이를 구한다.
  if(result){
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
    nerd와 non-nerd를 그룹지어서, 두 영역을 직선으로 나눌 수 있는지 확인하는 방법
      아이디어
        신발 사이즈를 x축, 타이핑 스피드를 y축이라 하자
          F=A*신발사이즈+B*타이핑스피드는, 해당 평면에서의 직선이다.(F=Ax+By)
        즉, nerd그룹과 non-nerd그룹을 구한 후, 두 영역이 어떤 직선으로 나눠질 수 있는지를 파악하면 된다.
      구현
        두 영역을 구하는 방법
        두 영역을 나누는 직선을 구하는 방법
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
  정답
    벡터를 이용한다
    방법
      다각형의 꼭짓점을 시계 반대방향으로 정렬한다(문제에서 주어짐)
      섬을 보물영역의 한 모서리로 자른다. 자른영역의 왼쪽 부분이 새로운 섬의 영역이다. -> O(n) * n times
        시계반대 반대방향이기 때문에, 왼쪽 영역이 보물영역을 포함한다
      모든 모서리에 대해 수행하면, 보물 영역 내부의 섬의 크기가 구해진다. -> O(n)
    시간: O(n^2)
    크기: O(n)
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

