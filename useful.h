#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*프로그래밍 수행시 도움이 되는 기법
대략적인 시간제한
  초당 1억번의 연산횟수 기준
시간 줄이기
  입출력 횟수를 줄인다 (getline 사용)
  이진 탐색
  인접메모리 사용 : 캐시는 인접메모리를 한번에 가져온다.
  실수 자료형 지양
테스트 검증
  rand를 이용하여 무작위 변수를 input
  표준함수가 구현되어 있다면 Algo와 표준함수와 비교
  표준함수가 없다면, 더 느리지만 확실한 정답의 Algo와 비교 
유용한 표준함수
  사전순 정렬
    lexicographical_compare()
  이진 탐색
    lower_bound(), upper_bound()
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
  실수 자료형
    구조
      자료형 sign exponent mantissa   유효자릿수       상대오차
      float   1     7         23         6         2^-23 ~= 10^-7 
      double  1     11        52         15        2^-52 ~= 10^-16
    실수는 대부분의 경우 오차가 존재한다.
      표현 방식의 차이로 인한 오차
        1을 2진수 실수 표기로 완벽하게 표기할 수 없다. -> 1-2^-23 = 0.99999988079 (10^-7부터 오차 발생,어떤 자료형이든 결국 오차는 발생)
        정수가 들어있는 실수형 변수를 정수로 바로 캐스팅하면 안된다. (위 예시의 경우 0이 되어버린다.)
      상대오차
        float의 경우 2^-23 까지 표현 가능하다 -> 오차의 범위는 2^-23 -> 10진수로 변환시 10^-7 부터 오차 발생
    epsilon의 이용: 
      오차는 연산마다 누적이 되므로, 10^-15가 오차라면(double) 10^-10 정도를 epsilon으로 정할 수 있다.
      1. 절대오차: fabs(a-b)< epsilon  (fabs=실수 절댓값)
      2. 상대오차: fabs(a-b)<= epsilon*max(fabs(a),fabs(b))   //10^-10과 같이 매우작은 값이 0이 아니라고 판정될 수 있다.
      3. 혼합: 절대오차 비교 -> 상대오차 비교
      epsilon은 발생가능한 오차보다는 큰 값으로 정하는것이 좋다.
      비교 연산시 등호를 사용하지 않고, 특정 e값보다 작다면 같은 것으로 간주한다.
        대소비교시 같은 경우를 먼저 확인하고 대소비교
      정수 캐스팅시에도 직접적인 변환을 하지 않고, e값을 더하여 캐스팅하는 기법 이용.
    큰 수에 작은 수를 더할 때는 조심하자 (작은 수가 큰 수의 최소표현값보다 작은경우, 덧셈을 하여도 값이 바뀌지 않는다.)
    코드의 수치적 안정성을 높이자
      중간 연산에서의 작은 오차가 결과에서의 큰 오차를 불러일으키지 않도록 하자.
    추가바람
    실수 자료형의 표현 범위, 특수한 값(무한대, 비정규 수, NaN),fabsf,epsilon
  자주하는 실수
    산술 오버플로우
    배열 범위 밖 원소 접근 (런타임 에러 발생 가능)
    상수 오타 
    스택 오버플로우
    변수 초기화
    자료형의 표현 범위 
    너무 큰 INF 값 (INF+a이 오버플로우가 날 수 있다.)
  NP hard, complete 등 정리
  알고리즘의 정당성 증명
    귀납법 - 0일때 성립, 증가할 때 성립
    귀류법 - 가정과 반대되는 상황을 가정하여 가정이 맞을수밖에 없음을 증명
    비둘기집 원리 - 필연적인 중복 발생
    구성적 증명 - 안정적인 짝 찾기
*/

vector<int> getPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
int  getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
// LCM=A*B/GCD(A*B);
pair<long long,long long> euclidAlgo(long long A,long long B);  //유클리드 알고리즘"Ax+By=gcd(A,B)"의 해(x,y), 조건: A>B,  

