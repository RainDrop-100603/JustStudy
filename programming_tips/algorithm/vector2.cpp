#include "vector2.h"

vector2 vector2::pFoot(const vector2& point,const vector2& vec)const {return point+(*this-point).project(vec); } //*this에서 직선ab에 내린 수선의 발
bool vector2::onLine(const vector2& p1, const vector2& p2)const {return cmpDBL((*this-p1).dot(p2-p1),(*this-p1).length()*(p2-p1).length())==0; }   //직선 위
bool vector2::onSegment(const vector2& p1, const vector2& p2)const {return this->onLine(p1,p2)&&min(p1,p2)<=*this&&*this<=max(p1,p2); }  //선분 위
pair<bool,vector2> vector2::lineCross(const vector2& rhs, const vector2& p1, const vector2& p2)const{//직선의 교점, 평행(일치)는 제외
  double det=(rhs-*this).cross(p2-p1);
  if(cmpDBL(det,0)==0) return make_pair(false,vector2()); //평행인 경우
  return make_pair(true,*this+(rhs-*this)*((p1-*this).cross(p2-p1)/det));
}
pair<bool,vector2> vector2::segCross(const vector2& rhs, const vector2& p1, const vector2& p2)const{  //*this-rhs가 p1-p2와의 교점이 있는가
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
  
//polygon 관련
int vector2::isInside(const vector<vector2>& polygon)const{  //this가 polygon 내부에 있는가? 1: 내부, 0: 경계, -1:외부
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
    return 1; //inside
  }else{
    return -1;  //outside
  }
}
  