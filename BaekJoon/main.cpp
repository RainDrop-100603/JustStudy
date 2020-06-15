#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

#include "GoodFunction.h"

using namespace std;

class Point{
  int xpos;
  int ypos;
public:
  Point(int xpos=-100001, int ypos=100001):xpos(xpos), ypos(ypos){}
  Point& operator= (const Point& pos){
    xpos=pos.xpos;
    ypos=pos.ypos;
    return *this;
  }
  int operator[] (int idx) const{
    if(idx==0){
      return xpos;
    }else{
      return ypos;
    }
  }
  friend ostream& operator<<(ostream& os,const Point& pos); 
};

ostream& operator<<(ostream& os, const Point& pos){
  os<<pos.xpos<<' '<<pos.ypos;
  return os;
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  vector<Point> pointV;
  int N,X,Y;
  cin>>N;
  for(int i=0;i<N;i++){
    cin>>X>>Y;
    pointV.push_back(Point(X,Y));
  }

  MergeSortT(pointV,0,0,N);

  for(int i=0;i<N;i++){
    cout<<pointV[i]<<"\n";
  }
  return 0;
}

