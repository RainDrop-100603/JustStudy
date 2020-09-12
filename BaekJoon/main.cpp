#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>
#include <set>
#include <map>
#include <list>
#include <deque>
#include <queue>

//#include "GoodFunction.h"

using namespace std;

string numbers[15];
int N,K;
int len[15];  //len of numbers;
int modTable[15][15];

void BK1086(){  // Traveling Salesman Problem (TSP)
  /*
  전역변수 영역


  문제
    첫째 줄에 집합의 수의 개수 N이 주어진다. N은 15보다 작거나 같은 자연수이다. 
    둘째 줄부터 N개의 줄에는 집합에 포함된 수가 주어진다. 각 수의 길이는 길어야 50인 자연수이다. 
    마지막 줄에는 K가 주어진다. K는 100보다 작거나 같은 자연수이다.

    첫째 줄에 정답을 기약분수 형태로 출력한다. p/q꼴로 출력하며, p는 분자, q는 분모이다. 정답이 0인 경우는 0/1로, 1인 경우는 1/1로 출력한다.
  생각
    길이가 50
      int=2^32=10^9, long long=10^19 -> 모든 수는 string 형식으로 저장해야 한다.
      최대 길이는 750이다. 단순히 나누기로 해결이 가능할까?
    예제입력 3 3 2 1 2 -> 출력 1/3 
      321 32 3 21 2 1 ->1/3
    순열의 개수 N!
      N!개 중에서 K로 나누어 떨어지는 수는 총 몇 개인가
    비트마스크, DP랑 무슨 연관성?
    Y=aX+b;
      Y mod X = b;
      Y-c*X mod X = (a-c)X+b mod X = b (a>=c);
      d=10^e 형태가 곱해질경우
        dY=adX+db, dY mod X = db mod X;
      순열을 이어붙이는 것: 10^e를 곱하여 더하는 것
        mod값은 10을 곱할때마다 변한다
        최대 10회까지 순환 가능
        50회의 경우 -> 10회로 나누어서 5번 한다.
        기존반복을 저장해둔다 -> 비트마스크 이용
      Z=dY1+Y2=(a1d+a2)X+bd1+d2
        Z mod X = (bd1+d2) mod X
    입력의 mod값 저장
      순열(붙인것)의 mod값 또한 table에 저장하여 쉽게 계산
      A(ij)=i부터 j를 이어붙인것의 mod 값 
    수의 길이가 50*15=최대 750줄의 자연수 =10^750, long long 으로도 표현 불가
      범위가 너무 켜질경우 string방식으로 처리하는 것도 고려
  해답
    1. 두 개의 DP table을 이용한다, 이때 하나가 비트마스킹을 이용한 table 
      mod table A 에 mod 값을 저장한다.
        A(ij)== i번째수부터 j번째 수 까지 이어붙인 순열의 mod 값
        A(ij)=B(A(im),mj비트마스크)+A(mj) 의 mod
          길이는 미리 저장해둔다.
      mod table B 에 1~9까지의 수를 10^x배한 것의 mod를 저장한다.
        이때 열은 순열을 비트마스크로 나타낸 것이며, 해당 순열의 길이가 x 이다.
          ex) 00110 은 1번째 2번째 수의 길이를 10의 거듭제곱 했을때의 mod를 의미한다.
      알아서 더 디벨롭
    2. 10^x 곱하는 것을 간략하게 줄이기 위한 table 생성
      table:  1~K-1 mod K 값을 저장하고 있다. 행이 증가할때마다 10을 곱하고 mod한 것이라 생각하면 된다. 새로운 mod 값이 first와 같다면 거기서 종료.
      mod table A
        A(ij)== i번째수부터 j번째 수 까지 이어붙인 순열의 mod 값
        A(ij)=table(A(im),mj길이 mod table(A.len))+A(mj) 의 mod
      최대 50자리의 수를 mod할 방법이 필요 
  */
//input
  cin>>N;
  for(int i=0;i<N;i++){
    getline(cin,numbers[i]);
  }
  cin>>K;
//prepare
  for(int i=0;i<N;i++){
    len[i]=numbers[i].length();
  }
  int tmp;
  vector<int> table[K]; //loop chk
  for(int i=0;i<K;i++){
    table[i].push_back(i);
    tmp=i;
    while(true){
      tmp=(tmp*10)%K;
      if(tmp==i){break;}
      table[i].push_back(tmp);
    }
  }
//calc
  for(int i=)
//output
}
int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  BK1086();
  return 0;
}