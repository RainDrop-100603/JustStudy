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
pair<int,int> line[2000]; //줄의 시작과 끝 점
int table1[1500][2000]; //A(ji)=i에서 j개 줄을 타서 도착하는 위치
int table2[1500][2000]; //B(ji)=i에서 j번째 줄부터 타서 도착하는 위치


int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for(test_case = 0; test_case  < T; test_case++)
	{
		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
    //input
    int K,N,m,from,to;
    cin>>N>>K>>m;  //N:세로선 , K: 가로이음줄-line
    for(int i=0;i<K;i++){
      cin>>from>>to;
      line[i]=make_pair(from,to);
    }
    //prepare
      //table1
    for(int i=0;i<N;i++){
      table1[0][i]=i;
    }
    table1[0][line[0].first]=line[0].second;  //first : from, second: to
    for(int i=1;i<K;i++){
      from=line[i].first;
      to=line[i].second;
      for(int j=0;j<N;j++){
        if(table1[i-1][j]==from){
          table1[i][j]=to;
        }else{
          table1[i][j]=table1[i-1][j];
        }
      }
    }
      //table2
    for(int i=0;i<N;i++){
      table2[K-1][i]=i;
    }
    table2[K-1][line[K-1].first]=line[K-1].second;
    for(int i=K-2;i>=0;i--){
      from=line[i].first;
      to=line[i].second;
      for(int j=0;j<N;j++){
        table2[i][j]=table2[i+1][j];
      }
      table2[i][from]=table2[i+1][to];
    }
    //calculate
    
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << " " << (N+1)*(N+1)-Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}