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

    첫째 줄에 정답을 기약분수 형태로 출력한다. p/q꼴로 출력하며, p는 분자, q는 분모이다. 정답이 0인 경우는 0/1로, 1인 경우는 1/1로 출력한다.
  해답
    길이가 50
      int=2^32=10^9, long long=10^19 -> 모든 수는 string 형식으로 저장해야 한다.
      최대 길이는 750이다. 단순히 나누기로 해결이 가능할까?
      새로운 자료형을 만들어보자
    예제입력 3 3 2 1 2 -> 출력 1/3 
      321 32 3 21 2 1 ->1/3
    순열의 개수 N!
      N!개 중에서 K로 나누어 떨어지는 수는 총 몇 개인가
    비
    
    
    수의 길이가 50*15=최대 750줄의 자연수 =10^750, long long 으로도 표현 불가
      범위가 너무 켜질경우 string방식으로 처리하는 것도 고려
  
  */
//input
  int prev(0),now,len,cnt;
  cin>>N; // #집합의 수
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