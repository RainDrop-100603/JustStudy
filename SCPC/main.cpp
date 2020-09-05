#include <iostream>
#include <algorithm>

using namespace std;


int Answer;
int team1[200000];
int team2[200000];
int DP1[3][200000];  // i and i, M,F,B
int DP2[3][199999];  // i and i+1, M,F,B, up
int DP3[3][199999];  // i+1 and i, M,F,B, down

int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
    Answer=0;
    //input
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
      cin>>team1[i];
    }
    for(int i=0;i<n;i++){
      cin>>team2[i];
    }
    //prepare
    sort(team1,team1+n);
    sort(team2,team2+n);
    int uNow,dNow,uNext(team1[0]),dNext(team2[0]);
    for(int i=0;i<n-1;i++){   //N
      uNow=uNext;uNext=team1[i+1];
      dNow=dNext;dNext=team2[i+1];
      DP1[0][i]=abs(uNow-dNow);
      DP2[0][i]=abs(uNow-dNext);
      DP3[0][i]=abs(uNext-dNow);
    }DP1[0][n-1]=abs(uNext-dNext);
    DP1[1][0]=DP1[0][0];DP2[1][0]=DP2[0][0];DP3[1][0]=DP3[0][0];
    for(int i=1;i<n-1;i++){   //F
      DP1[1][i]=DP1[1][i-1]+DP1[0][i];
      DP2[1][i]=DP2[1][i-1]+DP2[0][i];
      DP3[1][i]=DP3[1][i-1]+DP3[0][i];  
    }DP1[1][n-1]=DP1[1][n-2]+DP1[0][n-1];
    DP1[2][n-1]=DP1[0][n-1];DP1[2][n-2]=DP1[2][n-1]+DP1[0][n-2];
    DP2[2][n-2]=DP2[0][n-2];DP3[2][n-2]=DP3[0][n-2];
    for(int i=n-3;i>=0;i--){  //B
      DP1[2][i]=DP1[2][i+1]+DP1[0][i];
      DP2[2][i]=DP2[2][i+1]+DP2[0][i];
      DP3[2][i]=DP3[2][i+1]+DP3[0][i];
    }
    
    //calc

    //output
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << "\n";
	}

	return 0;//Your program should return 0 on normal termination.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////