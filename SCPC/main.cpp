#include <iostream>
#include <algorithm>
#include <set>

using namespace std;


int Answer;
int cost[200000];
int pay[200000];
int pay2[200000];

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
    for(int i=0;i<n-2;i++){
      pay2[i]=pay[i];
    }
    sort(pay,pay+n-2);
    multiset<int> set1,set2;
    for(int i=0;i<n/2-1;i++){
      set1.insert(pay[i]);
    }
    for(int i=n/2-1;i<n-2;i++){
      set2.insert(pay[i]);
    }
    int mid=*set2.begin();
    cout<<mid<<" ";
    
    int day,value;
    for(int i=0;i<Q;i++){
      cin>>day>>value;
      int from=max(0,day-1),to=min(n-2,day+2);
      int prev,now;
      for(;from<to;from++){
        prev=pay2[from];
        pay2[from]+=value-cost[day];
        now=pay2[from];
        if(prev<mid){
          set1.erase(set1.lower_bound(prev));
          if(now<mid){
            set1.insert(now);
          }else{
            set2.insert(now);
          }
        }else{
          set2.erase(set2.lower_bound(prev));
          if(now<mid){
            set1.insert(now);
          }else{
            set2.insert(now);
          }
        }
        int mid=*set2.begin(); 
      }
      cout<<mid<<" ";
    }
    cout<<endl;
	}

	return 0;//Your program should return 0 on normal termination.
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////