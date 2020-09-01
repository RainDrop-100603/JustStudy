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
pair<bool,int> table[3001];
int deck[2][3000];


int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;

	for(test_case = 0; test_case  < T; test_case++)
	{
		Answer = 0;
    //input
    int K,N;
    cin>>N>>K;  //N:카드의 수, K: 최대 숫자
    for(int i=0;i<N;i++){
      cin>>deck[0][i];
    }
    for(int i=0;i<N;i++){
      cin>>deck[1][i];
    }
    //prepare
    table[0]={true,0}; Answer++;//0: 남은 값 0
    int newCard;
    for(int i=0;i<N;i++){
      auto tmp=table[i]; 
        newCard=deck[0][i];
        if(!tmp.first){
          table[i+1]={true,K-newCard};
          Answer++;
        }else if(tmp.first&&(tmp.second==0||tmp.second<newCard)){
          table[i+1]={false,K-newCard};
        }else{
          table[i+1]={true,tmp.second-newCard};
          Answer++;
        }
    }
    //calculate
    for(int i=0;i<N;i++){
      for(int j=0;j<=i;j++){
        auto tmp=table[j]; 
        newCard=deck[1][i];
        if(!tmp.first){
          table[j]={true,K-newCard};
          Answer++;
        }else if(tmp.first&&(tmp.second==0||tmp.second<newCard)){
          table[j]={false,K};
        }else{
          table[j]={true,tmp.second-newCard};
          Answer++;
        }
      }
      
      for(int j=i;j<N;j++){
        auto tmp=table[j]; 
        newCard=deck[0][j];
        if(tmp.second<newCard){
          table[j+1]={!tmp.first,K-newCard};
        }else{
          table[j+1]={tmp.first,tmp.second-newCard};
        }
        if(table[j+1].first){
          Answer++;
        }
      }
    }
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << ' ' << (N+1)*(N+1)-Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}