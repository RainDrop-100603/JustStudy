#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>

//#include "GoodFunction.h"

using namespace std;

int graph[16][16];
int DP[16][1<<16];  //current, visited
int N, END;  //#vertex, 모든경로 방문: (1<<N)-1
int INF=16*1000000+1;

void BK1086(){  // Traveling Salesman Problem (TSP)
  /*
  전역변수 영역


  문제
    첫째 줄에 집합의 수의 개수 N이 주어진다. N은 15보다 작거나 같은 자연수이다. 
    둘째 줄부터 N개의 줄에는 집합에 포함된 수가 주어진다. 각 수의 길이는 길어야 50인 자연수이다. 
    마지막 줄에는 K가 주어진다. K는 100보다 작거나 같은 자연수이다.
  Priority Queue에 cost, 경로를 저장 -> 최대 15!*int*2 필요->mem over
  1. 모든 경우, DP 아님, cost: 현재까지의 cost 의미
    DP를 통해 원점에서 시작하여 끝 경로까지
      visited==END -> return;
      for(int i=1;i<N;i++); 
        if(visited&(1<<i));
          if graph[current][i]==0 -> continue;
          else: -> DP[i][visited+(1<<i)]=min(this,DP[current][visited]+graph[current][i]); TSP(i,visited+(1<<i));
  2. DP로 변경, cost: 끝 경로가지의 cost 의미
  */
//input
  int prev(0),now,len,cnt;
  cin>>N; // #연산
  cin.get();
  string s;
  for(int i=0;i<N;i++){
    cnt=0;
    prev=0;
    getline(cin,s);
    len=s.length();
    for(int j=0;j<len;j++){
      if(s[j]==' '){
        now=j;
        graph[i][cnt]=stoi(s.substr(prev,now-prev));
        cnt++;prev=now;
      }
    }
    graph[i][cnt]=stoi(s.substr(prev,len-prev));
  }
//prepare
  END=(1<<N)-1;
//calc
  cout<<TSP(0,1); //INF를 출력하면 경로 없음 
//output
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK2098();
  return 0;
}