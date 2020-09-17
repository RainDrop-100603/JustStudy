#include <iostream>
#include <vector>

using namespace std;

/*프로그래밍 수행시 도움이 되는 기법
시간 줄이기
  입출력 횟수를 줄인다 (getline 사용)

*/

vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
int  GetGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
pair<long long,long long> EuclidAlgo(long long A,long long B);  //유클리드 알고리즘"Ax+By=gcd(A,B)"의 해(x,y), 조건: A>B,  

