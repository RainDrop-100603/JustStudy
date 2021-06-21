//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

// 정수론
void PASS486_Input(int& number,int& low,int& hi){
  cin>>number>>low>>hi;
}
int PASS486_Divisor(vector<int>& primeArr,int num){
  int count(1),primeCount(0),prime(0);
  //primeArr[num]==0 : num = 0 or 1
  while(int divisor=primeArr[num]){
    if(prime==divisor){
      primeCount++;
    }else{
      count*=primeCount+1;
      primeCount=1;
      prime=divisor;
    }
    num/=divisor;
  }
  count*=primeCount+1;
  return count;
}
int PASS486_DP(vector<int>& primeArr, int num){
  int& result=primeArr[num];
  if(result!=-1){
    return result;
  }
  //Algo
  result=
}
void PASS486_GetPrime(vector<int>& primeArr){
  //arr[i]==i : 소수, arr[i]==소수 : 가장 작은 소인수, arr[i]==0: 0혹은 1 
  int size=primeArr.size();
  int sqrtSize=static_cast<int>(sqrt(size));
  for(int i=2;i<size;i++){
    primeArr[i]=i;
  }
  //에라스토테네스의 채
  for(int i=2;i<=sqrtSize;i++){
    for(int now=i*i;now<size;now++){
      if(primeArr[now]==now){
        primeArr[now]=i;
      }
    }
  }
}
int PASS486_Algo(int number,int low,int hi){
  //애라스토테네스의 채
  vector<int> primeArr(hi+1,0);
  PASS486_GetPrime(primeArr);
  //Algo
  int count=0;
  for(int num=low;num<=hi;num++){
    if(PASS486_Divisor(primeArr,num)==number){
      count++;
    }
  }
  //반환 
  return count;
}
void PASS486(){
  // PASS486
  /*설명 및 입력
  설명
    비밀번호는 [lo,hi] 범위에 존재한다.
    비밀번호는 n개의 약수를 가진다.
    비밀번호의 경우의 수를 구하여라
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c(c <= 50)가 주어집니다. 
    그 후 c줄에 각 3개의 정수로 n (n < 400), lo , hi(1 <= lo <= hi <= 10,000,000)이 주어집니다. 
    hi-lo 는 항상 1백만 이하입니다.
  출력
    각 테스트 케이스마다, 해당 범위 내에 비밀번호가 될 수 있는 숫자가 몇 개인지 출력합니다.
  제한조건
    5초, 128MB
  */
  /*힌트
    소인수 분해를 하고, 약수의 개수를 구하면 된다.
      약수의 개수: 아주 간단함
      소인수 분해: 에라스토테네스의 채를 이용하여 구한다.
    수의 범위는 1천만 이하다.
      에라스토테네스의 채: root(1천만)~=3300
      소인수분해: 최대 log2(1천만)=23
    최대 100만개의 수를 모두 계산해야 하나? 
      일단 풀어보고 최적화를 하든가 하자 
  */
  /*전략
  전략1
    소인수분해
      소인수 분해를 통해 약수를 구하고, 약수의 개수를 구한다.
      소인수분해는 아레스토테네스의 채를 이용한다.
    시간:
      O(1백만*root(1천만)*약수의개수(최대 23개)));
    크기:
      O(1천만*4byte)~=40MB
    개선 및 보완
      시간초과, 200 1000000 2000000 : 2.96875s
      Divisor에서 잦은 호출을 줄임 -> 1.4375s
      Divisor에서 하나씩 구하는게 아니라, DP방식으로 구하자 
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int number,low,hi;
    PASS486_Input(number,low,hi);
    auto result=PASS486_Algo(number,low,hi);
    cout<<result<<endl;
  }
}

int main(void){
   clock_t start,end;
   start=clock();
 PASS486();
   end=clock();;
   cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

