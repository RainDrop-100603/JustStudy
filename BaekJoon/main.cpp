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

void BK10217(){  // Dijkstra
  /*
  문제조건
    입력 파일의 첫 번째 줄에 테스트 케이스의 수를 의미하는 자연수 T가 주어진다. 그 다음에는 T개의 테스트 케이스가 주어진다.
    각 테스트 케이스의 첫 줄에는 공항의 수 N (2 ≤ N ≤ 100), 총 지원비용 M (0 ≤ M ≤ 10,000), 티켓정보의 수 K (0 ≤ K ≤ 10,000)가 공백으로 구분되어 주어진다. 
    이어서 K개의 줄에 걸쳐 각 티켓의 출발공항 u, 도착공항 v (1 ≤ u, v ≤ N, u ≠ v), 비용 c (1 ≤ c ≤ M, 정수), 그리고 소요시간 d (1 ≤ d ≤ 1,000) 가 공백으로 
    구분되어 주어진다. 인천은 언제나 1번 도시이고, LA는 언제나 N번 도시이다
    자료형: 최대크기= #edge*maxTime(or cost)=10,000*1,000(10,000)=10^8 : int
  Dijkstra Algorithm
    first_memOver: 대부분의 정보를 모두 저장해버렸기 때문 -> 일정수준 이전 정보는 삭제해버리는 DP 이용 필요
      lowest time이 목표
      lowest time dijkstra 
        if timeover: backtracking?
      DP table(cost_V)에 여러 data를 저장하자
        갱신이 아닌 누적 저장을 이용
          새로운 값이 들어오면 기존의 모든 값과 비교 
            money와 time이 모두 기존값보다 낮거나 같다 -> 해당 기존값 삭제 후 저장
            의외의 경우는 새로운 값도 저장 
        새로운 자료형 정의
          time과 money를 동시에 비교하여 가장 낮은 값을 priority queue에 저장
    second_memOver: 여전히 많은 정보가 stack과 table에 저장된다.
      오직 time을 기준으로만 비교 -> 가장 먼저 목적지 도착하면 출력(cost는 stack 입력 전에 확인하므로)
    third
      graph를 time 기준으로 정렬
        각 vertex에서 lowest time edge 만을 이용하여 dijkstra
          이 dijkstra는 second에서 한 것과 동일한 dijkstra
          lowest time edge만 넣은 행렬 하나 생성해서 이용
        목적지(N)에 데이터가 갱신되었는지 확인후 다시 dijkstra
        매번 초기화되는것
          graph 원본, lowest time edge만을 저장한 행렬, 행렬이 몇개 저장되었는지 체크하는 cnt(cnt==0->break)
        초기화 되지 않고 누적되는 것
          cost_V행렬
        구현에서 에러떠서 포기 
    fourth  - 인터넷 참고_memOver
      DP table : A[i][j]=K  : i에 j cost로 도달하는데 걸린 시간 
    fifth: 
      cost 는 증가하기만 하고 감소하지 않는다 -> cost,dest,time DP table 생성, 낮은 cost 부터 높은 cost에 대하여 vertex에서 갱신한다.
        mem size: Money range*dest*int(time)=10001*100*4=4MB
        Edge: #edge*int*3=10000*4*3=0.12MB
      A(ij)=k : i cost, 1 to j vertex, k time;
        A(ij)에서 vertex j를 확인하여 갱신 
        cost:i 를 0~M까지 증가시키며 갱신
        마지막에 N행을 확인하여 lowest time이 정답

  */
//input
  int N,M,K,A,B,C,D;
  cin>>N>>M>>K; // #vertex, max Cost, #edge
  vector<pair<int,pair<int,int>>> graph[N+1]; // dest, money, time
  for(int i=0;i<K;i++){
    cin>>A>>B>>C>>D; //from,dest,money,time
    graph[A].push_back({B,{C,D}}); //dest,money,time
  }
//prepare
  int INF=10000*10000+1;  //#edge*maxCost(or Time)+1;
  vector<vector<int>> table(M+1,vector<int>(N+1,INF));//INF: 경로없음, cost,dest,time
  table[0][1]=0;
  int newCost;
//calc
  for(int i=0;i<M;i++){ //money, M일때는 어차피 더이상 이동 불가능 하여 M-1 까지
    for(int j=1;j<=N;j++){  //dest vertex, 0행은 사용하지 않으므로 생략
      if(table[i][j]!=INF){
        for(auto& ele:graph[j]){
          newCost=ele.second.first+i;
          if(newCost<=M){
            table[newCost][ele.first]=min(table[newCost][ele.first],table[i][j]+ele.second.second); //기존 시간과, 새롭게 추가된 시간중 작은값
          }
        }
      }
    }
  }
//output
  int result=INF;
  for(int i=0;i<=M;i++){
    result=min(result,table[i][N]);
  }
  if(result==INF){
    cout<<"Poor KCM\n";
  }else{
    cout<<result<<"\n";
  }
  
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  int T;
  cin>>T;
  while(T--){
    BK10217();
  }
  return 0;
}