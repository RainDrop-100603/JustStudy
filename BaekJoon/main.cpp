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

#include "GoodFunction.h"

using namespace std;

void BK2098(){  // Traveling Salesman Problem (TSP)
  /*
  문제
    첫째 줄에 도시의 수 N이 주어진다. (2 ≤ N ≤ 16) 다음 N개의 줄에는 비용 행렬이 주어진다. 각 행렬의 성분은 1,000,000 이하의 양의 정수이며, 갈 수 없는 경우는 0이 주어진다. 
    W[i][j]는 도시 i에서 j로 가기 위한 비용을 나타낸다.
    항상 순회할 수 있는 경우만 입력으로 주어진다.
  
  */
//input
  int N,prev(0),now,len,cnt;
  cin>>N; // #연산
  cin.get();
  string s;
  vector<vector<int>> table(N,vector<int>(N));
  for(int i=0;i<N;i++){
    cnt=0;
    prev=0;
    getline(cin,s);
    len=s.length();
    for(int j=0;j<len;j++){
      if(s[j]==' '){
        now=j;
        table[i][cnt]=stoi(s.substr(prev,now-prev));
        cnt++;prev=now;
      }
    }
    table[i][cnt]=stoi(s.substr(prev,len-prev));
  }
//prepare

//calc
//output
  for(auto& ele: table){
    for(auto& ele2:ele){
      cout<<ele2<<" ";
    }
    cout<<endl;
  }
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK2098();
  return 0;
}