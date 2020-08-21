#include <iostream>
#include <vector>
#include <algorithm>

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

pair<int,int> graph[1501][2000];  //graph[0]은 버린다.
int graphidx[1501];   //각 node의 원소가 몇 개 있는지 알 수 있다.

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
    for(int i=0;i<K;i++){
      graph[from][graphidx[from]++];
    }
    //prepare
      //table1
    for(int i=1;i<N+1;i++){
      table1[0][i]=i;
    }
    for(int i=1;i<K+1;i++){
      from=line[i-1].first;
      to=line[i-1].second;
      for(int j=1;j<N+1;j++){
        if(table1[i-1][j]==from){
          table1[i][j]=to;
        }else if(table1[i-1][j]==to){
          table1[i][j]=from;
        }else{
          table1[i][j]=table1[i-1][j];
        }
      }
    }
      //table2
    for(int i=1;i<N+1;i++){
      table2[K][i]=i;
    }
    for(int i=K-1;i>=0;i--){
      from=line[i].first;
      to=line[i].second;
      for(int j=1;j<N+1;j++){
        table2[i][j]=table2[i+1][j];
      }
      table2[i][from]=table2[i+1][to];
      table2[i][to]=table2[i+1][from];
    }
    //calculate
    for(int i=0;i<m;i++){
      cin>>from>>to;
      int minAns=K+1;
      for(int j=0;j<K+1;j++){
        int from2=table1[j][from];
        int cnt(0);
        while(j+cnt<=K){
          if(table2[j+cnt][from2]==to){
            minAns=min(minAns,cnt);
            break;
            }
          cnt++;
        }
      }
      if(minAns==K+1){
        minAns=-1;
      }
      Answer+=minAns;
    }

		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}