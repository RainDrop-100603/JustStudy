#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

#include "GoodFunction.h"

using namespace std;

int dp[1001][1001];
void solution(int n, int k){
  for(int i = 1; i <= n; i++){
        for(int j = 0; j <= n; j++){
            if(i == j || j == 0){
                dp[i][j] = 1;
            }
            else
            	dp[i][j] = (dp[i-1][j] + dp[i-1][j-1]) % 10007;
        }
    }
    cout << dp[n][k];
}

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3

  //입력
  int N,K;
  cin>>N>>K;

  //변수
  vector<bool> isDivided(K);
  int result=1; //결과값

  //계산
  for(int i=0;i<K;i++){
    result*=(N-i);
    for(int j=0;j<K;j++){
      if(!isDivided[j]){
        if(result%(j+1)==0){
          isDivided[j]=true;
          result/=j+1;
        }
      }
    }
    result%=10007;
  }
  //출력
  cout<<result<<endl;
  solution(N,K);

  return 0;
}

