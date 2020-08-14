#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>

//#include "GoodFunction.h"

using namespace std;
void BK10942(){
//input
  int N,Q;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d",&N); //N== size of arr
  vector<int> arr(N);  
  for(auto& ele:arr){
    scanf("%d",&ele);
  }
  scanf("%d",&Q); //N== #Question
//prepare
  int from,to,ans;  //(from-1)~(to-1)
  vector<int> p(N);  //palindrome, p(n) == k의 의미는, n부터 좌우 k길이만큼까지가 펜릴 그램이란 의미다. 
                    //n=(from+to)/2 일 때, n-p(n)<=from<to<=n+p(n) 이라면 from~to 는 펜릴그램 구간이다. (from+to)%2==1이라면 p(n+1)==k인지 체크, 우변은 n+1+p(n+1)로 변경
//calc
  //팬릴드롬 행렬 생성

//output
  // for(auto& ele:costMap){
  //   printf("%d %d\n",ele.first,ele.second);
  // }
  for(int i=0;i<Q;i++){
    scanf("%d %d",&from,&to);
    ans=0;
    if((from+to)%2==0){
      if(p[from+to]/2==1){
        ans=1;
      }
    }else{
      if(p[from+to]/2==2){
        ans=1;
      }
    }
    printf("%d\n",ans);
  }

}
int main(){
  //cin.tie(NULL);
  //cin.sync_with_stdio(false);
  
  //입력
  //변수
  //계산
  //출력
//   int N;
//   scanf("%d",&N);
//   while(N--){
    BK10942();
//  }
  
  return 0;
}