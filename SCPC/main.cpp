#include <iostream>
#include <algorithm>

using namespace std;


long long Answer;
int team1[200000];
int team2[200000];

int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
    //input
    int n;
    cin>>n;
    for(int i=0;i<n;i++){
      cin>>team1[i];
    }
    for(int i=0;i<n;i++){
      cin>>team2[i];
    }
    if(n==1){
      cout << "Case #" << test_case+1 << "\n";
		  cout << 0 << "\n";
      continue;
    }
    //prepare
    sort(team1,team1+n);sort(team2,team2+n);
    //calc
    long long prev1,prev2,now1(team1[0]),now2(team2[0]),tmp(abs(now1-now2)),gap(tmp),gap1(0),gap2(0),N1(-tmp),N2(-tmp),tmp1,tmp2;
    Answer=tmp;
    for(int i=1;i<n;i++){
      prev1=now1;prev2=now2;now1=team1[i];now2=team2[i];
      tmp=abs(now1-now2);
      Answer+=tmp;
      gap=max(gap,tmp);
      
      tmp1=abs(now1-prev2);
      N1+=tmp-tmp1;
      N1=max(N1,-tmp);
      gap1=max(gap1,N1);
      tmp2=abs(now2-prev1);
      N2+=tmp-tmp2;
      N2=max(N2,-tmp);
      gap2=max(gap2,N2);
    }
    gap=max(gap,max(gap1,gap2));
    Answer-=gap;
    //output
		cout << "Case #" << test_case+1 << "\n";
		cout << Answer << "\n";
	}

	return 0;//Your program should return 0 on normal termination.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////