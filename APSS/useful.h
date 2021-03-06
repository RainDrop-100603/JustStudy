#ifndef ____USEFUL_H___
#define ____USEFUL_H___

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

/*프로그래밍 수행시 도움이 되는 기법
*************************푼 문제들을 돌아보며, 테크닉과 useful을 정리하자********************
*************진행상황: 0개*****************************************************************
------------------------------
대략적인 시간제한
  초당 1억번의 연산횟수 기준
------------------------------
시간 줄이기
  입출력 횟수를 줄인다 (getline 사용)
  이진 탐색
  인접메모리 사용 : 캐시는 인접메모리를 한번에 가져온다.
  실수 자료형 지양
  제약이 있는 빠른 함수, fastSum 참고
    짝수만 적용가능한 함수의 경우, 홀수를 다룰때 n-1까지 함수를 적용하고 한단계는 직접 계산하도록 함수를 만들 수 있다(짝수->General)
  시간복잡도는 절대적 지표가 아니다.
    N이 작은경우, 단순한 N^2함수가 복잡한 NlgN보다 빠를 수 있다.
------------------------------
접근 방법
  작은 입력에 대해서만 동작하는 단순한 알고리즘에서 시작하여 큰 입력에서도 작동하도록 develop
  완전탐색에서 시작한다 -> 비둘기집 원리를 이용하여 중복되는 계산이 많다면 DP로 처리 
------------------------------
테스트 검증
  rand를 이용하여 무작위 변수를 input
  표준함수가 구현되어 있다면 Algo와 표준함수와 비교
  표준함수가 없다면, 더 느리지만 확실한 정답의 Algo와 비교 
------------------------------
유용한 표준함수, 방법
  ASCII code 순서 정렬
    <algorithm>의 sort의 기본 정렬(char 비교가 ascii단위이기 때문)
  사전순 정렬
    lexicographical_compare()
  이진 탐색
    lower_bound(), upper_bound()
  주어진 순열의 다음(이전) 순열을 구하는 Algo
    next_permutation(), prev_permutation()
  DP등에서 double로 초기화 할 때 기법
    기대값이 양수라면, -1로 초기화 하고 "ele>-0.5"와 같은 식으로 비교하면, ele가 -1인지 양수인지 알 수 있다.
------------------------------
런타임에러
  배열에 할당된 크기를 넘어서 접근했을 때
  전역 배열의 크기가 메모리 제한을 초과할 때
  지역 배열의 크기가 스택 크기 제한을 넘어갈 때
  0으로 나눌 떄
  라이브러리에서 예외를 발생시켰을 때
  재귀 호출이 너무 깊어질 때
  이미 해제된 메모리를 또 참조할 때
  프로그램(main 함수)이 0이 아닌 수를 반환했을 때
  C/C++에서 반환형이 void가 아닌 main이 아닌 함수에서 아무런 값을 반환하지 않았을 때
------------------------------
알고리즘의 정당성 증명
  귀납법 - 0일때 성립, 증가할 때 성립
  귀류법 - 가정과 반대되는 상황을 가정하여 가정이 맞을수밖에 없음을 증명
  비둘기집 원리 - 필연적인 중복 발생
  구성적 증명 - 안정적인 짝 찾기
------------------------------
string to something
  int stoi(const string& str, size_t* idx, int base=10): string을 앞에서부터 base형식 int로 변환, int 바로 다음 위치를 idx에 저장
    ex) 2001, test: return==2001, idx=4
  ele - '0'과 같은 방식은 0~9의 범위일때만 사용가능하고, 10을 넘어가는 순간 오류가 생긴다. 되도록 stoi를 애용하자
------------------------------
단락 평가 (Short circuit evaluation)
  논리 AND연산자(&&)는 하나라도 false면 false 이므로, 앞선 피연산자가 false로 평가되면 뒤이은 피연산자를 계산하지 않고 즉시 false를 반환한다.
  논리 OR연산자는(||)는 하나라도 true면 true이므로, 앞선 피연산자가 true로 평가되면 뒤이은 피연산자를 계산하지 않고 즉시 true를 반환한다.
  언어마다 차이점이 다소 있을 수 있으니 주의 
------------------------------
간단한 팁
  공백 string을 반환하고 싶다면 return string();
  lower_bound를 통해 pair->first만 비교하고 싶다면, make_pair(value,numeric_limits<int>::min())을 비교 인자로 넣으면 된다.
  재귀함수의 경우, 선 재귀 후 확인, 즉 조건을 서두에서 chk하는것이 좋다. (의도하지 않은 동작 방지) \
  숫자는 str으로 바꾸면 쉽게 접근이 가능하다 
------------------------------
자주하는 실수
  변수 초기화: default를 맹신하지말고 초기화 하자 
  산술 오버플로우::매우 자주 발생하는 오류 
  return이 있는경우, return이 발생하지 않는 경우를 확인 -> 알 수 없는 error 발생원인 
  매개변수의 Default는 두번 선언될 수 없다(.h와 .cpp에서 중복선언 불가능) -> header에서 선언하는게 더 직관적 
  배열 범위 밖 원소 접근 (런타임 에러 발생 가능)
  상수 오타 
  연산자 오타
  스택 오버플로우 (너무 많은 재귀)
  변수 초기화
  자료형의 표현 범위 
  모듈화시 주의사항
    함수의 형태, 변하는 값 등을 명확하게 지정하고 해야 나중에 생각하고 모듈화하기 편하다.
    ex) 정크값을 지울 것인가, 자연스럽게 사용하지 않게 만들 것인가로 나눌수 있는데, 이를 미리 명확하게 정하는게 좋다. 
  너무 큰 INF 값 (INF+a이 오버플로우가 날 수 있다.)
  재귀함수에서 조건을 제대로 충족 시키는 것 뿐 아니라, 답도 제대로 구할 수 있도록 함수를 설계하자
  multiple definition: ifndef-endif 확인, header에 함수의 정의 포함하였는지 확인 
  memset
    memset은 byte단위로 메모리를 초기화한다. 0과 -1의 경우는 int자료형의 경우에도 기댓값과 같지만, 나머지는 그렇지 않다
      int: -1=1111,1111,...,1111,1111, 1=0000,0000,...,0000,0001 /= 0001,0001,...,0001,0001 (byte단위로 초기화 되어 실제값은 1이 아니다.)
  vector v1에서 v1은 "배열의 시작위치"가 아닌, "배열의 시작위치를 가리키는 포인터"이다. 배열의 시작위치는 "&v[0]"이다.
    따라서 move연산이 제대로 이루어졌는지 확인하려면, &v1이 아닌 &v1[0]을 통해 확인해야한다.
  iterator
    distance(from,to)의 결과는 to-from이다. 양방향 반복자일 경우, 음수가 답으로 나올 수 있지만, 순방향 반복자일 경우 음수값이 나올수 없고 정의되지 않은 동작을 한다.
------------------------------
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
  Dynamic Programing
    접근방법
      brute force에서 중복 삭제
      작은 단위에서 큰 단위로 합치기
      큰 단위에서 하나씩 빼기  
    최적화 문제 vs 연산 중복 방지
      최적화 문제: LCS와 같이 여러 가능한 답 중 가장 좋은 답을 찾아내는 방법, optimal substructure
      연산 중복 방지(메모제이션): 조합문제 같이 중복 연산이 많이 이뤄지는 경우 사용, 비둘기집 원리 이용 
      최적화 문제도 연산중복방지를 사용한다. 다만 최적화문제는 입력 자체를 줄이는 데 의미가 있다.
        메모제이션이 연산만 최적화 한다면, 최적화는 optimal substructure을 통해 입력도 최적화한다.
    DP배열 범위유의, 초기값이 기대값 범위에 포함되지 않도록 유의
    참조형으로 호출하면, 다차원 배열일경우 실수를 줄일 수 있다.
    재귀를 이용할경우, 함수 호출 횟수, 함수 자체 복잡도 모두 줄이도록 노력해보자.
    DP최적화
      1.모든 답을 만들고 최적해를 반환하는 완전탐색 알고리즘 설계
      2.남은 선택들의 최적해를 반환하도록 부분문제정의(substructure)를 바꾼다.
      3.이전 선택(남은 선택과 반대되는 의미)에 관련된 정보 중 불필요한 것은 삭제, optimal substructrue는 이전 정보가 필요 없다.
        목표는 가능한 한 중복되는 부분 문제를 많이 만들어 메모제이션을 이용하는 것. 입력의 종류가 줄어들수록 더 많은 부분문제 중복
      4.입력이 배열이거나 문자열인경우, 가능하다면 적절한 변환을 통해 메모제이션
      5.메모제이션 적용 
    DP 테크닉
      마르코프 연쇄: numb3r
        유한개의 상태가 있으며, 매 시간마다 상태가 변경되며, 상태 변경은 현재 상태에만 영향을 받는다(이전상태, 현재 시간등 X)
      은닉 마르코프 모델: OCR
        마르코프 연쇄에 의해 생성된 데이터를, 별도의 (오류가 있는)관찰자를 통해서만 확인가능한 모델
        Viterbi Algorithm: 은닉 마르코프 모델에서, 관측결과가 주어질때 가장 가능성이 높은 실제상태를 계산하는 Algo
      배낭 문제: knapsack problem
        물건의 cost, value 가 정해져 있으며, 제한 cost내에서 최대 value를 얻도록 물건을 고르는 문제 
        각 물건을 최대 하나만 고르는 0/1 문제, 여러개 고를 수 있는 문제, 쪼개서(분수) 넣을 수 있는 fractional knapsack problem - greedy로 해결 가능(직관적임)
    memozation: 입력이 정수가 아닐경우, 배열, 실수 등등 
      bijection function(일대일 대응함수)
        입력을 정수로 변환해주는 일대일 대응함수 -> 정수 메모제이션 
          bool 배열 입력 -> 비트마스크: 정수로 변환 (false true true false == 0110 ==6)
          순열 -> 사전순 번호 
          입력의 범위가 좁은 배열 -> n자리의 k진수라고 생각하자( 4 0 3 A 2 -> 403A2 == 59039, 5자리의 11진수)
  실수 자료형
    주의사항
      float 보다는 double 지향, double까지는 하드웨어 계산으로 속도가 빠른편 (long double은 느림)
      정수를 실수로 바로 캐스팅 하면 안된다(0.99999->0)
      비교연산시 등호를 사용하면 안된다: abs(A-B)<EPS, EPs=10^-6~10^-9 정도
      큰 수를 다룰때 EPS 사용에 조심: 10^11을 다룰때 EPS가 10^-6 이라면, abs(A-B)<EPS 를 사용했을때 A와 B가 항상 같게된다: 상대오차를 이용하도록 하자 
      큰 수에 작은 수를 더할 때 조심하자: double 상대오차 10^15, 10^15를 사용하면 오차가 1의자리에서 발생, 1의자리 이하의 상수를 더해도 유의미한 변화 x(오차범위 이내 변화)
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
    작은 실수 곱셈 연산
      너무 작은 실수는 곱셈시 언더플로우, 값 비교가 어려워 질 수 있다.
      실수값을 로그로 변환하여 연산한다면 연산과 값의 비교가 쉬워진다.
        이때의 로그오차는 어떻게 할 것인가?
        추가바람
    추가바람
    실수 자료형의 표현 범위, 특수한 값(무한대, 비정규 수, NaN),fabsf,epsilon
  NP hard, complete 등 정리
  조합에서 중복 제거  
    원소를 사전순 정렬 -> 중복을 삭제할 수 있다. (조합이므로 순서 중요 X)
    조합 생성시 사전순으로만 생성되도록 -> 추가 작업 없이도 중복이 없다.
  RValue Reference(우측값 참조) &&
    복사를 하지 않고 임시객체(우측값)를 그대로 이용하는것(이동)
    vector<bool> 배열의 경우 범위기반 for 문에서 우측값 참조를 이용해야 한다.
      vector<bool>은 bool container가 아니라, int container에 bitmask로 저장한 것이기 때문에, 접근시 임시값(RValue)를 반환한다.
    Vs LValue
      LValue: 식이 끝난 후에도 존재하는 좌측값, RValue: 식이 끝난 후에도 존재하는 우측값
      LValue ref: & , RVlue ref: &&
      다른 형식의 참조이므로 함수 오버로딩이 가능
        func(int& x), func(int&& x) 오버로딩
  std::move, std::forward 
    move
      LValue 를 RValue로 캐스팅 해준다.
        기존 LValue는 더이상 남아있지 않다(RValue로 바뀌었으므로 사라지는것이 당연하다)
      move 생성자, move 대입연산자 이용 가능
        암묵적으로 생성되지 않는다.
        복사 생성자, 대입연산자가 move 복사, move 대입보다 우선순위가 높으므로 std::move 사용 필요
    forward
      Lvalue는 LValue로, RValue는 RValue로 캐스팅 해준다.
        자동으로 LValue->RValue로 캐스팅 되는것을 막아준다.
  배열 매개변수
    vector를 이용하면 간단하지만 cache로 사용할 경우를 생각하자.
    arr[][axis2][axis3], (*arr)[axis2][axis3]
      arr은 포인터와 같이 적용됨을 알 수 있다.
      다차원 배열을 매개변수로 이용하는 방법. 1차원이 경우 arr[], *arr을 이용하면 되며, 다차원 호출시 *arr에 괄호를 꼭 쳐주어야 한다.
      axis1자리는 값을 지정해도 무시된다(maybe).
      배열의 크기는 axis1만 넘겨줘도 되는가? axis2이상은 넘길때 지정해주므로 안넘겨줘도 되는가?
    axis2,axis3,...,axisN이 필요한 이유
      1차원 배열의 경우 axis1의 단위크기는 자료형의 크기와 같다.
      다차원 배열의 경우 axis1의 단위크기는 자료형의크기*axis2의 길이*axis3의 길이 이다.
      즉 axis2이상의 정보가 없다면, axis[1]에 접근하는것은 불가능하다(다음위치를 알 수가 없기 때문)
    3차원 배열 파라미터 넘기기
      https://zetawiki.com/wiki/C%EC%96%B8%EC%96%B4_3%EC%B0%A8%EC%9B%90_%EB%B0%B0%EC%97%B4_%ED%8C%8C%EB%9D%BC%EB%AF%B8%ED%84%B0%EB%A1%9C_%EB%84%98%EA%B8%B0%EA%B8%B0
    배열 참조로 넘기기
      https://boycoding.tistory.com/217
  cache사용법
    전역변수에서만 사용? cpu 특징?
  아주 큰 숫자(문자열 숫자) 연산
    곱셈: 카라츠바 알고리즘 참고
미완성
  cin과 getline
    https://qastack.kr/programming/21567291/why-does-stdgetline-skip-input-after-a-formatted-extraction
    https://leeusin.tistory.com/418
    cin은 공백에서(스페이스바,개행문자) 자르며, 입력버퍼에 해당 공백을 남겨둔다?(개행 문자만 남는가?). 그러나 해당 공백이 입력에 영향을 주지는 않는다.
    getline은 개행문자에서 자르며, 입력버퍼에 개행문자가 남아있으면 개행문자만 입력되어 버리므로, 입력전 cin.ignore()을 사용한다.
  cin 대신 scanf 이용
    https://eine.tistory.com/entry/CC-%EC%9E%85%EC%B6%9C%EB%A0%A5-%EB%B0%A9%EB%B2%95%EC%97%90-%EB%94%B0%EB%A5%B8-%EC%86%8D%EB%8F%84-%EC%A0%95%EB%A6%AC
    https://m.blog.naver.com/luku756/220985996127
    정리해봐야 알겠지만, cin.tie(NULL); cin.sync_with_stdio(false); 는 싱글스레드 환경에서만 사용가능하고, 임시방편이므로 사용하지 않는 방향으로 하자 
*/

//유용한 함수
vector<int> getPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
int  getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
// LCM=A*B/GCD(A*B);
pair<long long,long long> euclidAlgo(long long A,long long B);  //유클리드 알고리즘"Ax+By=gcd(A,B)"의 해(x,y), 
int fastSum(int n); //1~n까지의 합을 구한다. 분할정복방식

//실수 비교
int cmpDouble_Abs(double a, double b, double absTolerance=(1.0e-8));
int cmpDouble_Rel(double a, double b, double relTolerance=__DBL_EPSILON__);
int cmpDouble_AbsRel(double a, double b, double absTolerance=(1.0e-8), double relTolerance=__DBL_EPSILON__);
int cmpDouble_Ulps(double a, double b, int ulpsTolerance=4);
int cmpDouble_UlpsAbs(double a, double b, int absTolerance=(1.0e-8), int ulpsTolerance=4);


//유용한 테스트
void moveTest_vec();  //move가 제대로 이루어 졌는지 확인하는 방법에 대한 참고 


//미완성 
class longNum{
  //ver0.1, 2020_10_4
  //fanMeeting algospot 문제 실패, 추후 수정 
  //ele=num[idx]*10^idx, sign: true means positive
  vector<int> num;
  bool sign;
public:
  //생성자
  longNum():num(vector<int>()),sign(true){} 
  longNum(const vector<int>& v,bool sign=true):num(v),sign(sign){}
  longNum(vector<int>&& v,bool sign=true):num(move(v)),sign(sign){}
  longNum(const string& s){
    num.reserve(s.length());
    for(auto iter=s.rbegin();iter!=s.rend();iter++){
      num.push_back(*iter-'0');
    }
    //부호결정
    if(num.back()=='-'-'0'){
      num.pop_back();
      sign=false;
    }else{
      sign=true;
    }
  }
  longNum(long long n){
    // 더 낮은 비트수의 자료형, int도 포함된다.
    //sign
    if(n<0){sign=false;n*=-1;}
    else{sign=true;}
    //value
    while(n!=0){
      num.push_back(n%10);
      n/=10;
    }
  }
  ~longNum(){}
  //복사 생성자, 이동 생성자
  longNum(const longNum& lN):num(lN.num),sign(lN.sign){}
  longNum(longNum&& lN):num(move(lN.num)),sign(lN.sign){}
  //대입 연산자 오버로딩
  longNum& operator=(const longNum& lN){num=lN.num;sign=lN.sign;return *this;}
  longNum& operator=(longNum&& lN){num=move(lN.num);sign=lN.sign;return *this;}
  longNum operator+(const longNum& lN)const{
    //부호가 다른경우 sub
    if(sign^lN.sign){
      if(sign){
        return *this-lN.changeSign();
      }else{
        return lN-(this->changeSign());
      }
    }
    //연산
    int thisLen(this->length()),lNLen(lN.length()),Len(max(thisLen,lNLen));
    vector<int> tmp(Len);
    for(int i=0;i<thisLen;i++){
      tmp[i]+=num[i];
    }
    for(int i=0;i<lNLen;i++){
      tmp[i]+=lN[i];
    }
    longNum result(move(tmp),sign);
    result.normalize();
    return result;
  }
  longNum operator-(const longNum& lN)const{
    //부호가 다를경우 add 
    if(sign^lN.sign){
      return *this+lN.changeSign();
    }
    //계산
    int tmpSign;
    int thisLen(this->length()),lNLen(lN.length()),Len(max(thisLen,lNLen));
    vector<int> tmp(Len);
    if(this->absBigger(lN)){
      tmpSign=sign;
      for(int i=0;i<thisLen;i++){
        tmp[i]+=num[i];
      }
      for(int i=0;i<lNLen;i++){
        tmp[i]-=lN[i];
      }
    }else{
      tmpSign=lN.sign;
      for(int i=0;i<thisLen;i++){
        tmp[i]-=num[i];
      }
      for(int i=0;i<lNLen;i++){
        tmp[i]+=lN[i];
      }
    }
    longNum result(move(tmp),tmpSign);
    result.normalize();
    return result;
  } 
  longNum operator*(const longNum& lN)const{
    int lenThis(num.size()),lenA(lN.length());
    vector<int> tmp(vector<int>(lenThis+lenA));
    for(int i=0;i<lenThis;i++){
      for(int j=0;j<lenA;j++){
        tmp[i+j]+=num[i]*lN[j];
      }
    }
    longNum result(move(tmp),!(sign^lN.sign));
    result.normalize();
    return result;
  }
  //연산자 오버로딩
  int& operator[] (int idx){return num[idx];}
  int operator[] (int idx) const{return num[idx];}
  friend ostream& operator<<(ostream& os, const longNum& lN);
  //멤버함수
  int length() const{return num.size();}
  longNum& reverse(){
    vector<int> tmp;
    tmp.reserve(num.size());
    for(auto iter=num.rbegin();iter!=num.rend();iter++){
      tmp.push_back(*iter);
    }
    num=move(tmp);
    return *this;
  }
  longNum sublN(int start, int end) const{
    //[start,end)
    if(start>=end){
      return longNum();
    }
    vector<int> tmp;
    tmp.reserve(end-start);
    start=max(start,0);
    end=min(end,this->length()+1);
    for(int i=start;i<end;i++){
      tmp.push_back(num[i]);
    }
    return longNum(move(tmp),sign);
  }
  void normalize(){
    int len(num.size()),borrow;
    for(int i=0;i<len-1;i++){
      borrow=num[i]/10;
      if(num[i]<0){
        borrow--;
      }
      num[i]-=borrow*10;
      num[i+1]+=borrow;
    }
    //모든 경우에 대응하는 normalize
    while(num.back()>9){
      num.push_back(0);
      borrow=num[len-1]/10;
      if(num[len-1]<0){
        borrow--;
      }
      num[len-1]-=borrow*10;
      num[len]+=borrow;
      len++;
    }
    //끝자리 0 제거
    while(num.size()>1&&num.back()==0){
      num.pop_back();
    }
  }
  longNum& pow10(int exp){
    vector<int> tmp(exp+this->length());
    for(int i=0;i<this->length();i++){
      tmp[i+exp]=num[i];
    }
    num=move(tmp);
    return *this;
  }
  bool absBigger(const longNum& lN)const{
    //절댓값의 크기비교, 같을경우 true
    int Len=this->length();
    if(Len>lN.length()){
      return true;
    }else if(Len<lN.length()){
      return false;
    }else{
      for(int i=Len-1;i>=0;i--){
        if(num[i]>lN[i]){
          return true;
        }else if(num[i>lN[i]]){
          return false;
        }
      }
    }
    //같을경우
    return true;
  }
  longNum changeSign()const{
    return longNum(num,!sign);
  }
  longNum karatsuba(const longNum& lN) const{
    //기저,shortLen(this)<longLen(lN)<50, 
    int longLen(this->length()),shortLen(lN.length());
    if(shortLen>longLen){
      return lN.karatsuba(*this);
    }
    if(shortLen==0||longLen==0){
      return longNum();
    }
    if(longLen<50){
      return this->operator*(lN);
    }
    //divide&conquer
    int divLen((shortLen+1)/2);
    longNum thisLow(this->sublN(0,divLen)),thisHigh(this->sublN(divLen,longLen));
    longNum lNLow(lN.sublN(0,divLen)),lNHigh(lN.sublN(divLen,shortLen));
    //a0 x^2 + a1 x + a2 : x=10^divLen, a0=thisHigh*lNHigh, a1=(this low+high)*(lN low+high)-a0-a2, a2=thisLow*lNLow
    longNum a0(thisHigh.karatsuba(lNHigh));
    longNum a2(thisLow.karatsuba(lNLow));
    longNum a1((thisLow+thisHigh).karatsuba(lNLow+lNHigh)-a0-a2);
    return longNum(a0.pow10(divLen*2)+a1.pow10(divLen)+a2);
  }
  void print_withSpace(){
    if(!sign){
      cout<<"- ";
    }
    for(auto iter=num.rbegin();iter!=num.rend();iter++){
      cout<<*iter<<' ';
    }
  }
  //문제풀이용
  longNum mult_notNorm(const longNum& lN)const{
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    int lenThis(num.size()),lenA(lN.length());
    vector<int> tmp(vector<int>(lenThis+lenA-1));
    for(int i=0;i<lenThis;i++){
      for(int j=0;j<lenA;j++){
        tmp[i+j]+=num[i]*lN[j];
      }
    }
    return longNum(move(tmp),true);
  }
  longNum& sub_notNorm(const longNum& lN){
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    for(int i=0;i<lN.length();i++){
      num[i]-=lN[i];
    }
    return *this;
  }
  longNum& add_notNorm(const longNum& lN){
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    for(int i=0;i<lN.length();i++){
      num[i]+=lN[i];
    }
    return *this;
  }
  longNum karatsuba_notNorm(const longNum& lN)const{
    //기저,shortLen(lN)<longLen(this)<50, normalize하지 않는다.
    int shortLen(lN.length()),longLen(this->length());
    if(shortLen>longLen){
      return lN.karatsuba_notNorm(*this);
    }
    if(shortLen==0||longLen==0){
      return longNum();
    }
    if(longLen<50){
      return this->mult_notNorm(lN);
    }
    //divide&conquer
    int divLen((shortLen+1)/2);
    longNum thisLow(this->sublN(0,divLen)),thisHigh(this->sublN(divLen,longLen));
    longNum lNLow(lN.sublN(0,divLen)),lNHigh(lN.sublN(divLen,shortLen));
    //a0 x^2 + a1 x + a2 : x=10^divLen, a0=thisHigh*lNHigh, a1=(this low+high)*(lN low+high)-a0-a2, a2=thisLow*lNLow
    longNum a0(thisHigh.karatsuba_notNorm(lNHigh));
    longNum a2(thisLow.karatsuba_notNorm(lNLow));
    longNum a1((thisLow.add_notNorm(thisHigh)).karatsuba_notNorm(lNLow.add_notNorm(lNHigh)).sub_notNorm(a0).sub_notNorm(a2));
    return longNum(a0.pow10(divLen*2).add_notNorm(a1.pow10(divLen)).add_notNorm(a2));
  }
  //range based loop(for), operator++부터 추가바람
  //이 경우 operator를 오버로딩할 필요가 없을듯 하다? int*형식이기 때문
  int* begin(){return &num[0];}
  int* end(){return &num[num.size()];}
};
ostream& operator<<(ostream& os, const longNum& lN);
//https://jungwoong.tistory.com/53
//std move, std forward, 이동생성자 공부
//rValue로 전달된 a는 num을 초기화 할때도 rvalue 상태인가? -> lvalue 취급되서 move를 써주어여 한다.
//longNum(vector<int>&& a):num(a){} 가 맞는가, longNum(vector<int>&& a):num(move(a)){} 가 맞는가-> 후자가 맞다.

#endif