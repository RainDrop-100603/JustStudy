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
pair<bool,int> table1[3001];
pair<bool,int> table2[3001];
int deck1[3000];
int deck2[3000];


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
    int K,N;
    cin>>N>>K;  //N:카드의 수, K: 최대 숫자
    for(int i=0;i<N;i++){
      cin>>deck1[i];
    }
    for(int i=0;i<N;i++){
      cin>>deck2[i];
    }
    //prepare
    table1[0]={true,-1}; Answer++;//0: 남은 값 0
    bool first(true);
    int tmp,tmp2;
    for(int i=0;i<N+1;i++){
      auto table=table1;
      if(!first){
        table=table2;
      }
      for(int j=0;j<N;j++){
        tmp=table[i].second();
        tmp2=
      }
    }
    for(int i=1;i<N;i++){
      tmp=table[i][0].second;
      tmp2=deck1[i];
      if(tmp==0){
        table[i+1][0]={true,K-tmp2};
        Answer++;
      }else{
        if(tmp<tmp2){
          table[i+1][0]={false,0};
        }else{
          table[i+1][0]={true,tmp-tmp2};
          Answer++;
        }
      }
    }
    for(int i=1;i<N;i++){
      tmp=table[0][i].second;
      tmp2=deck2[i];
      if(tmp==0){
        table[0][i+1]={true,K-tmp2};
        Answer++;
      }else{
        if(tmp<tmp2){
          table[0][i+1]={false,0};
        }else{
          table[0][i+1]={true,tmp-tmp2};
          Answer++;
        }
      }
    }
    for(int i=1;i<N+1;i++){
      for(int j=0;j<N;j++){
        tmp=table[i][j].second;
        tmp2=deck2[j];
        if(tmp==0){
          table[i][j+1]={true,K-tmp2};
          Answer++;
        }else{
          if(tmp<tmp2){
            table[i][j+1]={false,0};
          }else{
            table[i][j+1]={true,tmp-tmp2};
            Answer++;
          }
        }
      }
      
      
    }
    
    // for(int i=0;i<N+1;i++){
    //   for(int j=0;j<N;j++){
    //     tmp=DPtable[i][j].second-deck2[j];
    //     if(tmp>0){
    //       DPtable[i][j+1]={DPtable[i][j].first,tmp};
    //     }else{
    //       DPtable[i][j+1]={!DPtable[i][j].first,K+tmp};
    //     }
    //   }
    // }
    for(int i=0;i<N+1;i++){
      for(int j=0;j<N+1;j++){
        cout<<"("<<table[i][j].first<<","<<table[i][j].second<<")";
      }
      cout<<"\n";
    }

    //calculate
    
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << " " << (N+1)*(N+1)-Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}