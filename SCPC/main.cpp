#include <iostream>
#include <vector>
#include <algorithm>
#include <deque>

using namespace std;

/*Question_01
    //input
    int K,N;
    cin>>N>>K;  //N:음식의 수, K: 날짜
    vector<int> arr1(N),arr2(N);
    for(auto& ele:arr1){
      cin>>ele;
    }
    for(auto& ele:arr2){
      cin>>ele;
    }
    //prepare
    sort(arr1.begin(),arr1.end());
    sort(arr2.begin(),arr2.end());
    //calculate
    for(int i=0;i<K;i++){
      Answer=max(Answer,arr1[i]+arr2[K-i-1]);
    }
*/

int Answer;

bool comp(const pair<int,int>& p1,const pair<int,int>& p2){
  return p1.first<p2.first;
}

int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for(test_case = 0; test_case < T; test_case++)
	{
		Answer = 0;
    //input
    int K,N,m,from,to;
    cin>>N>>K>>m;  //N:세로선 , K: 가로이음줄-line
    vector<vector<pair<int,int>>> graph(N+1,vector<pair<int,int>>());
    for(int i=0;i<K;i++){
      cin>>from>>to;
      graph[from].push_back(make_pair(i,to)); //first=depth(ith line)
      graph[to].push_back(make_pair(i,from));
    }
    //prepare
    for(int i=1;i<N+1;i++){
      graph[i].push_back({K,i});  //모든 라인을 스킵하고 내려가는 경우 추가
    }
      
    //calculate
    for(int i=0;i<m;i++){
      cin>>from>>to;
      deque<pair<int,pair<int,int>>> dq;
      dq.push_back({0,{-1,from}});  //first: 스킵한 갯수, 0~K-1 이므로 항상 -1보다 크다.
      //BFS
      int skipped(K+1);
      while(!dq.empty()){
        int sz=dq.size(); //get depth of BFS
        for(int i=0;i<sz;i++){
          auto tmpP=dq.front();
          dq.pop_front();
          auto iter=upper_bound(graph[tmpP.second.second].begin(),graph[tmpP.second.second].end(),make_pair(tmpP.second.first,-1),comp);
          auto iterEnd=graph[tmpP.second.second].end();
          int cnt(0); // skip한 라인
          for(iter;iter!=iterEnd;iter++){
            dq.push_back({tmpP.first+cnt,*iter});
            if(iter->second==to&&iter->first==K){
              skipped=min(skipped,tmpP.first+cnt);
            }
            cnt++;
          }
        }
        
      }
      if(skipped==K+1){
        skipped=-1;
      }
      Answer+=skipped;
      
    }

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}