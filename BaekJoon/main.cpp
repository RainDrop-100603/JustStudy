#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <map>
#include <set>

//#include "GoodFunction.h"

using namespace std;

//timeout
void BK2261(){
//입력
  int pointNum,x,y;
  cin>>pointNum;
  vector<pair<int,int>> v;
  for(int i=0;i<pointNum;i++){
    cin>>x>>y;
    v.push_back(make_pair(x,y));
  }
//준비
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  long long xDiff=v[0].first-v[1].first;
  long long yDiff=v[0].second-v[1].second;
  long long minLen=xDiff*xDiff+yDiff*yDiff;
//계산
  for(int i=0;i<pointNum;i++){
    for(int j=i+1;j<pointNum;j++){
      xDiff=v[i].first-v[j].first;
      xDiff*=xDiff;
      if(xDiff>minLen){
        break;
      }
      yDiff=v[i].second-v[j].second;
      yDiff*=yDiff;
      if(xDiff+yDiff<minLen){
        minLen=xDiff+yDiff;
      }
    }
  }
//출력
  cout<<minLen;
}
void BK2261_2_giveUp(){
//입력
  int pointNum,x,y;
  cin>>pointNum;
  vector<pair<int,int>> v;
  for(int i=0;i<pointNum;i++){
    cin>>x>>y;
    v.push_back(make_pair(x,y));
  }
//준비
  sort(v.begin(),v.end());
  v.erase(unique(v.begin(),v.end()),v.end());
  long long xDiff=v[0].first-v[1].first;
  long long yDiff=v[0].second-v[1].second;
  long long minLen=xDiff*xDiff+yDiff*yDiff;
  // x-tree map: key=x, value=y-tree
  int prev=v[0].first;
  map<int,set<int>> xTree;
  set<int> yTree;
  for(int i=0;i<v.size();i++){
    if(prev==v[i].first){
      yTree.insert(v[i].second);
    }else{
      //xTree.insert(prev,yTree);
    }
  }
//계산
  
//출력
  cout<<minLen; 
}
struct Point{
  int x,y;
  Point(){}
  Point(int x, int y):x(x),y(y){}
  bool operator< (const Point& p) const{
    if(y==p.y){
      return x<p.x;
    }else{
      return y<p.y;
    }
  }
};
bool cmpX(const Point& p1, const Point& p2){
  return p1.x<p2.x;
}
int dist2(const Point& p1, const Point& p2){
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
void BK2261_3_H_LineSweeping(){ //scanf를 사용하므로 유의 
//input and sort
  int n;  // #input 
  scanf("%d",&n);
  Point p;  //point
  vector<Point> a;  //point arr
  for(int i=0;i<n;i++){
    scanf("%d %d",&p.x,&p.y);
    a.push_back(p);
  }
  sort(a.begin(),a.end(),cmpX);

//line sweeping
  set<Point> tree = {a[0],a[1]};
  int ans=dist2(a[0],a[1]);
  int start=0;
  for(int i=2;i<n;i++){
    Point now=a[i];
  //x값 비교
    while(start<i){     
      Point p=a[start];
      if(ans<(p.x-now.x)*(p.x-now.x)){
        tree.erase(p);
        start++;
      }else{
        break;
      }
    }
  //y값 비교
    int d=sqrt(ans)+1;
    Point lowerP(-100000,now.y-d);
    Point upperP(100000,now.y+d); 
    set<Point>::iterator LBiter=tree.lower_bound(lowerP);
    set<Point>::iterator UBiter=tree.upper_bound(upperP);
    for(LBiter;LBiter!=UBiter;LBiter++){
      p=*LBiter;
      if(dist2(p,now)<ans){
        ans=dist2(p,now);
      }
    }
  //입력
    tree.insert(now);
  }
  cout<<ans;
}
int main(){
  // cin.tie(NULL);
  // cin.sync_with_stdio(false);


  //Math3
  

  //입력
  

  //변수
  

  //계산


  
  //출력
  BK2261_3_H_LineSweeping();
  
 
  return 0;
}