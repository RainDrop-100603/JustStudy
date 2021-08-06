#ifndef __VECTOR2_H__
#define __VECTOR2_H__

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;

class vector2{  //2차원벡터
public: 
  //변수와 상수
  const double PI=2.0*acos(0.0);
  const double EPSILON=1e-11;
  double x,y;
  int cmpDBL(double a, double b)const {if(fabs(a-b)<EPSILON){return 0; }else if(a<b){return -1; }else{return 1; } }
  //생성자
  vector2(double x_=0, double y_=0):x(x_),y(y_){}
  vector2 operator=(const vector2& rhs){x=rhs.x;y=rhs.y; return *this;}
  //연산자 오버로딩  
  bool operator==(const vector2& rhs)const {return cmpDBL(x,rhs.x)==0&&cmpDBL(y,rhs.y)==0; }
  bool operator!=(const vector2& rhs)const {return !this->operator==(rhs); }
  bool operator<(const vector2& rhs)const {return this->operator==(rhs) ? false : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  bool operator<=(const vector2& rhs)const {return this->operator==(rhs) ? true : (cmpDBL(x,rhs.x)==0 ? y<rhs.y : x<rhs.x); }
  bool operator>(const vector2& rhs)const {return !this->operator<=(rhs); }
  bool operator>=(const vector2& rhs)const {return !this->operator<(rhs); }
  vector2 operator+(const vector2& rhs)const {return vector2(x+rhs.x,y+rhs.y); }
  vector2 operator-(const vector2& rhs)const {return vector2(x-rhs.x,y-rhs.y); }
  vector2 operator*(double rhs)const {return vector2(x*rhs,y*rhs); }  // 벡터와 실수의 곱
  //간단한 특성 
  double length()const {return hypot(x,y); }
  vector2 normalize()const {return vector2(x/length(),y/length()); }  
  double polar()const {return fmod(atan2(y,x)+2*PI, 2*PI); } //x축에서의 각, 0~2PI
  double polar2()const {return atan2(y,x); }  //x축에서의 각, -PI~PI
  double polarFrom(const vector2& rhs)const {return rhs.polar()>this->polar()? this->polar()+2*PI-rhs.polar() : this->polar()-rhs.polar(); } //rhs에서의 각
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }  
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }  
  int ccw(const vector2& from, const vector2& to)const {return cmpDBL((to-from).cross(*this-from),0); } // 1:counterclockwise, 0: 평행, -1:clockwise
  vector2 project(const vector2& rhs)const {return rhs.normalize()*(rhs.normalize().dot(*this)); }  //rhs로의 projection
  vector2 vector2::pFoot(const vector2& p1,const vector2& p2)const {return p1+(*this-p1).project(p2-p1); } //*this에서 직선ab에 내린 수선의 발
  //기타 함수들, cpp 파일에 정의 
  bool onLine(const vector2& p1, const vector2& p2)const;   //this가 직선 위에 존재하는가
  bool onSegment(const vector2& p1, const vector2& p2)const;  //this가 선분 위에 존재하는가
  pair<bool,vector2> lineCross(const vector2& rhs, const vector2& p1, const vector2& p2)const;  //this-rhs와 p1-p2직선간의 교점이 존재하는가(평행 제외)
  pair<bool,vector2> segCross(const vector2& rhs, const vector2& p1, const vector2& p2)const;  //this-rhs와 p1-p2선분과의 교점이 존재하는가(평행 제외)
  int isInside(const vector<vector2>& polygon)const;  //this가 polygon 내부에 있는가? 1: 내부, 0: 경계, -1:외부
  //전역함수 오버로딩
  friend ostream& operator<<(ostream& os, const vector2& vec);
};
ostream& operator<<(ostream& os, const vector2& vec){
  os<<"("<<vec.x<<","<<vec.y<<")";
  return os;
}

#endif



