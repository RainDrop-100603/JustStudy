/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

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
pair<bool,int> table[3001][3001];


int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
    //input
    int K,N;
    cin>>N>>K;  //N:카드의 수, K: 최대 숫자
    vector<int> deck1(N),deck2(N);
    for(auto& ele:deck1){
      cin>>ele;
    }
    for(auto& ele:deck2){
      cin>>ele;
    }
    //prepare
    table[0][0]={true,0}; //0: 남은 값 0
    int tmp,tmp2;
    bool key;
    for(int i=0;i<N;i++){
      tmp=table[i][0].second;
      tmp2=deck1[i];
      if(tmp==0){
        key=table[i][0].first;
        table[i+1][0]={!key,K-tmp2};
      }else{
        if(tmp<tmp2){
          table[i+1][0]={!key,K-tmp2};
        }else{
          table[i+1][0]={key,tmp-tmp2};
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