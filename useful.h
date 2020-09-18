#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*프로그래밍 수행시 도움이 되는 기법
시간 줄이기
  입출력 횟수를 줄인다 (getline 사용)
테스트 검증
  rand를 이용하여 무작위 변수를 input
  표준함수가 구현되어 있다면 Algo와 표준함수와 비교
  표준함수가 없다면, 더 느리지만 확실한 정답의 Algo와 비교 
유용한 표준함수
  사전순 정렬
    lexicographical_compare()
유의사항
  오버로딩
    operator오버로딩시 기존 operator가 가지는 성질을 유지해야 일관적인 결과를 기대할 수 있다.
      operator<
        irreflexivity: a<a is always false;
        asymmetry: a<b is true -> b<a is false;
        transitivity: a<b and b<c are true -> a<c is true;
        transtivity of equivalance: if a<b and b<a is true -> a==b, if a==b and b==c -> a==c
  프로모션
    이항연산자들의 두 개의 피연산자가, 서로 자료형이 다르거나 자료형의 범위가 너무 작은 경우 컴파일러가 자동으로 같은 자료형으로 변환하여 연산
      정수형과 실수형: 실수형으로 변환
      양쪽 다 정수형(실수형)일 경우: 보다 넓은 범위를 갖는 자료형으로 변환
      양쪽다 int보다 작은 정수형: 양쪽 다 int 형으로 변환
      unsigned와 signed가 섞여있을경우: unsigned로 변환 
        size_t: .size()의 return 값, unsigned 자료형이다.
          a.size()-1 == -1 일 때, int로 프로모션 되면 2^32-1이 되어버린다.
          미리 size_t를 int 형식으로 casting 하여 에러 방지 
  실수 자료형 사용시 유의
    추가바람
    실수 자료형의 표현 범위, 특수한 값(무한대, 비정규 수, NaN)
  자주하는 실수
    산술 오버플로우
    배열 범위 밖 원소 접근 (런타임 에러 발생 가능)
    상수 오타 
    스택 오버플로우
    변수 초기화
    자료형의 표현 범위 
    너무 큰 INF 값 (INF+a이 오버플로우가 날 수 있다.)
*/

vector<int> getPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
int  getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
pair<long long,long long> euclidAlgo(long long A,long long B);  //유클리드 알고리즘"Ax+By=gcd(A,B)"의 해(x,y), 조건: A>B,  

