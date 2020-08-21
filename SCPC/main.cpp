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
    for(int i=1;i<N+1;i++){
      graph[i].push_back({0,i});
    }
    for(int i=1;i<K+1;i++){
      cin>>from>>to;
      graph[from].push_back(make_pair(i,to)); //first=depth(ith line)
      graph[to].push_back(make_pair(i,from));
    }
    //prepare
      
    //calculate
    for(int i=0;i<m;i++){
      cin>>from>>to;
      int maxdepth(-1);
      int cnt(0);
      pair<int,int> tmpP;
      deque<pair<int,int>> dq;
      dq.push_back({-1,from});  //0~K-1 이므로 항상 -1보다 크다
      //BFS
      //15개에서 13개가 걸렸다는것이 두개를 뺐다는 의미는 아니다. 1개만 빼서 그렇게 만들 수 있다.
      while(!dq.empty()){
        int sz=dq.size(); //get depth of BFS
        for(int i=0;i<sz;i++){
          tmpP=dq.front();
          dq.pop_front();
          auto iter=upper_bound(graph[tmpP.second].begin(),graph[tmpP.second].end(),make_pair(tmpP.first,-1),comp);
          auto iterEnd=graph[tmpP.second].end();
          for(iter;iter!=iterEnd;iter++){
            dq.push_back(*iter);
            if(iter->second==to){
              maxdepth=cnt;
            }
          }
        }
        cnt++;
      }
      if(maxdepth==-1){
        Answer--;
      }else{
        Answer+=K-maxdepth+cnt;
      }
      
    }

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}