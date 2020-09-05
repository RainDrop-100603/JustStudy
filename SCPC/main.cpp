#include <iostream>
#include <algorithm>
#include <set>

using namespace std;

int cost[200000];
int pay[200000];


int main(int argc, char** argv)
{
  cin.tie(NULL);
  cin.sync_with_stdio(false);
	int T, test_case;
	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
    //input
    int n,K,Q;
    cin>>n>>K>>Q;
    for(int i=0;i<n;i++){
      cin>>cost[i];
    }
    //prepare
    fill_n(pay,n-2,0);
    pay[0]=cost[0]+cost[1];
    pay[1]=cost[1];
    for(int i=2;i<n;i++){
      pay[i-2]+=cost[i];
      pay[i-1]+=cost[i];
      pay[i]+=cost[i];
    }
    multiset<int> set;
    for(int i=0;i<n-2;i++){
      set.insert(pay[i]);
    }
    multiset<int>::iterator iter;
    iter=set.begin();
    for(int i=0;i<(set.size()+1)/2;i++){
      iter++;
    }
    cout<<*iter<<" ";
    
    int day,value;
    for(int i=0;i<Q;i++){
      cin>>day>>value;
      day--;
      int from=max(0,day-2);
      int prev,now;
      for(;from<=day;from++){
        prev=pay[from];
        pay[from]+=value-cost[day];
        now=pay[from];
        cost[day]=value;
        set.insert(now);
        set.erase(set.lower_bound(prev));
      }
      iter=set.begin();
      for(int i=0;i<(set.size()+1)/2;i++){
        iter++;
      }
      cout<<*iter<<" ";
    }
    cout<<endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////