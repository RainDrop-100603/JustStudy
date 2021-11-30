_Algorithm Tips_
===========
```
- 알고리즘 문제해결 전략
- 보편적인 알고리즘 팁
```

## __목차__
* [__종합 팁__](#종합-팁)
	- [_runtime error_](#runtime-error)
	- [_아이디어_](#아이디어)
	- [_큰 입력_](#큰-입력)
	- [_자주하는 실수_](#자주하는-실수)
* [__조합 문제__](#조합-문제)
	- [_제약 충족 문제(Constraint Satisfaction Problem)_](#제약-충족-문제Constraint-Satisfaction-Problem)
* [__결정 문제(Decision Problem)__](#결정-문제Decision-Problem)
* [__수치해석__](#수치해석) 
	- [_이분법_](#이분법)
	- [_삼분탐색_](#)
	- [_수치적분_](#) 
* __정수론__
	- [_소수판별_](#)
	- [_소인수분해_](#)
	- [_유클리드알고리즘_](#)
	- [_모듈러연산_](#)
	- [_기타_](#) 
* __계산 기하__ 
	- [_벡터_](#)
	- [_다각형_](#) 
	- [_라인스위핑_](#)
* __자료 구조__ 
	- [_구분_](#) 
	- [_tree_](#)
		- [_상호 배타적 집합_](#)
	- [_graph_](#) 
	- [_비트마스크_](#) 
	- [_부분 합_](#)
	- [_동적배열과 연결리스트_](#)
	- [_큐와 스택, 덱_](#)
	- [_문자열 탐색과 매칭_](#)

## 테스트 
>테스트라인 1    
>테스트라인 2   
> - 테스트 특수효과 1
> 	``` 
> 	code block
> 	```
>	- block 2
>		```
>		block2
>		```
> 라인 4

-----	

# [__종합 팁__](#목차)
>## [_runtime error_](#목차)
>* 배열을 점검, 배열의 크기가 0인 경우를 반드시 생각하자 

>## [_아이디어_](#목차)
>* 예외가 너무 많은 아이디어는 지양하자.
>* 문제, 자료를 시각화 하는것이 도움이 될 수 있다.
>* 문제를 앞에서부터 풀 필요는 없다. 뒤에서부터, 혹은 특정 >우선순위부터 다양하게 시도해보자.
>	* sort , de_sort의 관계와 같이, 순차적으로 수행된 작업은 반대로 수행하여 원래 상태로 되돌릴 수 있다. 

>## [_큰 입력_](#목차)
>* 정수형의 경우, scanf로 처리하는 것이 빠르다.
>	* APSS2:CHRISTMAS를 보면, scanf>cin>getline 순으로 빠르다.

>## [_자주하는 실수_](#목차)
>* return 제대로 했는지 확인 

-----

# [__조합 문제__](#목차)
>## [_제약 충족 문제(Constraint Satisfaction Problem)_](#목차)
>* 특정한 제약에 해당하는 답을 찾는 문제
>	* 스도쿠, n-queen
>* 아래 두 조건을 만족하면 대부분 해결된다.
>	* 제약 전파(Constraint Propagation)
>		```
>		- 문제의 제약에 의해, 해답의 일부를 생성하면 또다른 제약이 생긴다.
>		- 해답의 일부를 생성할 때마다 새로운 제약이 계속해서 추가되기 때문에 제약 전파라 불린다.
>		- brute force와 유사하지만, 제약에 의해 계산할 경우의 수가 줄어든다.
>		ex) 스도쿠 
>			빈 칸에 7을 넣으면, 해당 line 과 해당 block에는 7을 넣을 수 없다는 제약이 추가된다.
>		```
>	* 채울 순서 정하기(Variable ordering + Value ordering)
>		```
>		- Variable ordering: 어떤 var을 채울것인가
>		- Value ordering: 선택된 var에 어떤 value를 채울 것인가
>		ex) 스도쿠 
>			Var ordering: 빈공간이 적은 line을 먼저 채운다.
>			Value ordering: 가능한 숫자 중 가장 큰 것으로 채운다.
>		```

>## [_기타 조합문제 해결법_](#목차)
>* algospot 444p
>* TSP, Sudoku 문제의 강력한 해결법 (http://norvig.com/sudoku.html)

-----

# [__결정 문제(Decision Problem)__](#목차)
>* 특정 조건에 대해 예 혹은 아니오의 답만 나오는 문제
>* 최적화 문제를 결정 문제로 바꾸어 해결하는 방법이 존재한다.
>	* 결정문제의 난이도는 최적화 문제보다 쉽거나 같으므로 유용하다.

-----

# [__수치해석__](#목차)
>## [_이분법_](#목차)
>* 탐색 범위를 절반으로 줄여나가며 정답에 근사한 값을 찾는다.
>	* 반복횟수 * O(lgn) 시간에 신뢰할만한 정답을 찾을 수 있다.
>* 이분 탐색 
>	* 탐색 방법
>		```
>		- [lo, hi) 범위에 대해 
>			f(lo) 가 정답에 근사하면 [lo,avg(lo+hi)) 범위로 재귀
>			f(hi) 가 정답에 근사하면 [avg(lo+hi),hi] 범위로 재귀 
>		- 종료 판정 조건을 만족할 때까지 재귀한다.
>		```
>	
>	* 수치적 안정성을 보존하는 탐색
>		```
>		- 수치적 안정성: 연산오류등의 에러가 발생하여도, 정답에 근사한 답을 내놓을 수 있는가
>		- 범위내 특정 값(정수 등)만 탐색: 연산오류로 정답을 거짓이라고 반환하면, 영원히 정답을 찾을 수 없다.
>		- 범위내 모든 값을 탐색: 연산오류가 발생하여도 정답에 근사한 답을 반환한다.
>		```
>* 종료 판정
>	* 횟수 반복
>		```
>		- 이분법을 X번 반복한다. 
>		- 오차 = (|hi - lo| / 2) / (2^x)
>		- 장점: 조건이 단순하다
>				무한루프에 빠질 우려가 없다.
>				수행시간 예측에 용이하다.
>				탐색 범위가 크든 작든 문제가 없다.
>		```
>	* 상대 오차
>		```
>		- 정답과의 오차비율이 상대오차(%) 이내인 답(answer)
>			|sol - answer| < sol * x
>		- 상대 오차 x 에 대해 아래의 경우를 만족한다.
>			(1-x) * hi < avg(lo+hi) < (1+x) * lo 
>			해석: 
>				(1-x) * sol < avg(lo+hi) < (1+x) * sol
>				(1-x) * sol <= (1-x) * hi
>				(1+x) * lo <= (1+x) * sol
>		- 단점: lo와 hi의 부호가 다르거나, 둘 다 음수일 경우등을 고려하면 코드가 복잡해진다.
>		```
>	* 절대 오차
>		```
>		- 정답과의 오차가 절대오차 이내인 답(answer)
>			|sol - answer| < x
>		- 절대 오차 x 에 대해 아래의 경우를 만족한다.
>			|hi-lo| < x
>		- 단점: 다루는 값의 크기가 크다면, 부동소숫점 표현오차로 인해 문제가 발생할 수 있다.
>		```
>* 유의사항
>	* 정답(0)을 따로 처리할 필요는 없다.
>	* avg(lo+hi)를 정답으로 간주한다.
>	* 기저(종료 판정)을 잘못 설정하면 무한루프에 빠질 수 있다.

>## _삼분검색_
		특정한 조건의 함수에서, local maximum(or local minimum)을 찾는 방법
			unimodal function: 하나의 local maximum을 가진다. 극대: mode
			strictly increasing before local maximum
			strictly decreasing after local maximum
		특수조건
			기울기가 0인지점이 있으면 strictly하지 않지만, 해당 지점이 local maximum(minimum)의 값과 같다면 상관없다.
			local maximum이 연속적이다 ; 라고 표현할 수 있다.
		lo, hi, 1/3지점, 2/3지점을 확인하여 범위를 좁혀나간다
			f(1/3지점)>f(2/3지점) -> hi=2/3지점, else: lo=1/3지점 
		오차: 이분법과 동일하며, 매 실행시 범위가 2/3으로 줄어든다.
			x회 반복: (|hi-lo|/2)/((2/3)^x)
		기타
			국소탐색보다 빠르고 수렴판정이 용이하다
			미분할 수 없는 함수에도 이용이 가능하다 
  	수치 적분 알고리즘 
	  	Simpson's method: 주어진 구간의 함수를 2차함수로 근사하여 적분하며, 2차이하의 함수라면 항상 정확한 값을 반환

정수론
  소수판별
	간단한 방법 
	  p*q=n에 대해, 두 수는 각각 root(n)이상, 이하이므로, n에대한 소수판별은 root(n)까지에 대해 확인하면된다.
	  수행시간은 지수시간 알고리즘 이라는데 496p, 4.4절 확인 후 정리 
	에라토스테네스의 채
	  2부터 시작하여, 해당값의 배수를 모두 지워준다. 지워지지 않은 수는 소수이다.
	  i가 대상일때, i*2가 아닌 i*i부터 시작한다. 2~(i-1)까지의 배수는 이미 그전에 모두 지워졌기 때문이다.
	  수행시간은 O(nlog(logn))
	효율적인 알고리즘들은 너무 복잡해서 대회에서는 사용되지 않는다.
  소인수분해
	간단한 방법
	  n을 2~root(n)까지 나눈다. 합성수는 앞선 소수에서 자동으로 걸러지므로 신경쓰지 않아도 된다.
	  혹은 에라토스테네스의 채를 이용하여 소수를 구한후 나눗셈 해준다.
		에라토스테네스의 채를 이용할 때, 해당하는 수의 가장 작은 소수를 기록해두면, 아주 빠르게 소인수 분해가 가능하다.
  유클리드 알고리즘 <euclid, gcd>
	gcd(p,q){return q==0 ? p : gcd(q,p%q)}  (q==0대신 q%p를 해도 되긴 하는데, q==0이 더 직관적)
	p>q인 p와 q의 공약수 집합은, p-q와 q의 공약수 집합과 같다.
	  증명: 공약수 x에 대해, q%x=0 이며 p%x=0 이므로, (p-q)%x=(p%x-q%x)%x=0이다. 모든 공약수 x에대해 성립하므로 공약수 집합은 같다.
	q가 0이 될 때의 p가 최대공약수 이다.
  모듈러 연산 <mod>
	모듈러 덧셈, 뺄셈, 나눗셈은 분배법칙,결합법칙이 성립한다.
	모듈러 나눗셈: a/b % N = a*(b^-1) % N, b^-1 은 b의 곱셈 역원
	모듈러 연산 곱셈 역원
	  N모듈러 연산에서의 곱셈역원 x는, Ax ≡ 1 mod N 로 정의된다. 역원 x는 A^-1로 표기된다.
		N과 서로소인 A만 역원을 가진다.
		  Ax % N = 1 -> Ax = kN + 1 -> Ax - kN = 1 -> N과 A가 서로소여야 해가 1이 나올 수 있다.(베주 항등식?)
	  구하는법
		N이 소수인 경우, A^-1 ≡ A^(N-2) mod N (페르마의 소정리)
		N이 소수가 아닌경우, Ax % N ≡ 1 mod N 이 성립하는 x를 구한다, x의 범위는 0~N-1
		  디오판틴 방정식의 해와 같다. Ax % N ≡ 1 mod N -> Ax = kN + 1 -> Ax - Nk = 1 
			디오판틴 방정식: 일차 부정방정식, ax + by = c (단 x,y는 정수)
  추가적인 알고리즘, 책에서는 설명이 안되어 있지만 필요하면 찾아보자
	확장 유클리드 알고리즘
	  gcd(p,q)=ap+bq로 나타낼 수 있는데, 최대공약수와 더블어 a,b를 반환하는 알고리즘을 의미
	중국인 나머지정리
	  n%3=1, n%5=2, n%6=7 을 만족하는 최소의 n은 얼마인가? 를 해결하는 문제
	루카스의 정리
	  mod를 이용한 nCr 계산, n과 r이 매우 큰 경우에도 계산할 수 있도록 해줌

계산 기하
  벡터: 계산 기하를 다룰 때 필요한 방식
	벡터의 구현 -> pair(x,y)로 구현 가능 
	  직선은 두 벡터로 나타낼 수 있다.
	아예 클래스로 만들어 여러 함수를 미리 구현하면 편하다 (519p참고)
	  비교, 덧셈 뺄셈, 실수곱셈, 길이, 단위벡터
	  x축의 양의방향 으로부터의 반시계방향 각도
	  내적, 외적, 사영
	외적:두 벡터의 외적은 평행사변형의 넓이 -> 응용하면 단순 다각형의 넓이를 구하기 쉽다.
	  외적의 부호: 두 벡터의 방향성(A벡터가 B벡터의 시계방향에 있다)을 알 수 있다.
	직선의 교차
	  직선을 한 점과 방향벡터로 나타내면, 교차를 구하기 편하다.
	선분의 교차
	  4가지 경우, 겹치지 않음, 1점에서 교차, 일부 겹쳐짐, 포함됨 
	코드 15.5: p는 이미 교점 중 하나이다.
	  두 선분이 평행한 경우는 따로 처리
	  두 선분의 교점이 하나인 경우에는, 그 교점이 각 선분의 범위에 존재하는지 확인 
  다각형
	다각형의 형태
	  볼록 다각형(convex polygon): 모든 내각이 180도 미만
		오목 다각형(concave polygon): 180도를 넘는 내각을 가짐
	  단순 다각형(simple polygon): 다각형의 경계가 스스로 교차하지 않음 
	다각형의 면적
	  이때 다각형의 점들은 시계방향(or반시계방향) 으로 주어져야 한다.
	  단순 다각형: 어떤 점 q에 대해 외적 -> 원점으로 하면 더 편하다. (1권 539p참고) 
	어떤 점의 내부/외부 판별 
	  내부에서 우측으로 반직선을 그엇을 때, 변과의 교차점이 홀수면 내부, 짝수면 외부 
		반직선과 변이 평행이면 무시
		반직선이 동시에 두 변과 만나면(꼭짓점), 하나만 만났다고 판단해야함
	  inside 함수: 위에서 말한 것을 모두 고려함 (p는 꼭짓점, q는 점)
		if( p[i].y > q.y != p[(i+1)%n].y > q.y ) -> 교차점 +1: 핵심 if함수
		  반직선과 변이 평행하면, 둘다 false(or true)이므로 무시된다.
		  반직선이 꼭짓점과 만나면, 한 변에서는 false/true, 다른 변에서는 false/false이므로 하나만 카운팅된다.
	polygon clipping
	  두 단순 다각형의 겹치는 면적을 구하는 방법
	  A 다각형의 모서리에 대해, 모서리가 이루는 직선의 왼쪽은 다각형의 영역을 포함한다(다각형이 시계반대방향으로 주어질경우)
		즉, B다각형을 A다각형의 모서리-직선으로 자르면, 그 왼쪽부분은 A다각형에 포함되는 부분, 오른쪽은 제외되는 부분이다.
		따라서 B다각형을 A다각형의 모든 모서리에 대해 모서리-직선으로 자르면, A다각형과 B다각형의 겹치는 영역을 구할 수 있다.
	다각형 만들기
	  여러가지의 점을 모두 포함하는 convex hull을 만들 수 있다.
	  좌측하단 점은 항상 최외각 점임을 이용한다(STL: min_element 이용가능)
	  gift Wrapping - O(n^2): ccw를 이용해 가장 우측인 점을 구하면서 순회한다
		점의 집합 중 꼭짓점이 되는 것을 찾는다(x,y좌표가 가장 작은것을 구하면 된다.)
		다른 모든 점을 순회하며, ccw를 이용하여 다음 꼭짓점을 구한다.
		  최초 next점은 임의로 선택한다.(자기자신만 아니면 됨)
		  꼭짓점과 next점은 직선을 이룬다.
		  다른 점이 직선의 우측에 있다면, 해당 점이 새로운 next점 이다.
		  모든 점에 대해 확인하면, 가장 우측에 있는점이 next점, 즉 다음 꼭짓점이 된다.
	  Graham Scan - O(nlgn): y좌표가 가장 작은 점을 기준으로, 다른 꼭짓점과의 직선의 polar는 항상 증가함을 이용한다.
		시작점은 y좌표가 가장 작은 점으로 한다. y좌표가 같다면 x좌표가 더 작은 점을 사용한다.
		다른 모든점들에 대해, 시작점과 이루는 직선의 각도를 구하고, 작은 순서대로 정렬한다.
		각도가 작은 순서대로, 다음 점으로 선택한다.
		  

  라인 스위핑 (plane sweeping or line sweeping)
	직사각형 합집합의 면적
	다각형 교집합의 넓이 


여러가지 유형의 문제들의 해법
  기본적인 접근방법
	프로그래밍 기법은 정답이 아닌 도구임을 인식하자 (이분법으로 다변수 다항 방정식을 푸는 방법을 떠올려보자)
	수학적인 접근도 생각해보자(의외로 간단한 경우가 있다.)
	벡터적 접근법도 생각해보자 
	추가바람 
  단변수 다항 방정식(변수가 x 하나인 다항 방정식, ax^2+bx+c)
	이분법(근사,한계 많음): 두 극점 사이에는 최대 하나의 근만이 있음, 2차이하 풀기가능, 재귀 
	여러 수치해석 알고리즘 

용어
  ternary search(삼분검색): 삼분 검색 
  unimodal function: 하나의 local maximum만 있는 func
  strictly increasing vs monotonically increasing: 순증가 vs 단조증가, 순증가는 기울기가 0인지점이 없다.
  concave(convex) function: 2차함수같이 위로(아래로) 볼록한 함수
	convex function 정의: 서로 다른 두 점을 직선으로 이었을 때, 이 직선이 그래프 밑으로 내려가지 않는 함수(증명에 이용 가능)

기타 팁
  i~i+1번째 ele를 비교하는 함수를 사용할 때, (n-1)~0까지 한번에 비교하게 만들고 싶다면, point[(i+1)%n]처럼 표시하면 된다. 
	
time complexity 추정
  x<=y인 경우, O(x)<=O(y)임을 이용하자 

=====자료 구조=====
--구분 
	추상형 자료 구조 
		스택
		큐
	탐색형 자료 구조
		해시
		트리
			이진 탐색 트리
			구간 트리
			힙
--tree
	기초적인 정의와 용어 
		상위 개념에서 하위개념으로 뻗어나가는, 계층 구조를 갖는 자료들을 표현하는데 유용하다.
		재귀적인 속성을 지닌다. tree의 child또한 tree 이다. x를 root로하는 subtree이다 라고 표현한다.
		구현 방법: node는 구조체/객체로 표현하고, edge는 포인터를 이용하는 방법이 있다.
		용어 
			node: 자료가 저장된 공간
			edge: node를 연결하는 선
			parent: 상위노드 
			ancestor: parent위로 존재하는 모든 상위node들 
			child: 하위노드
			descendant: child아래로 존재하는 모든 하위node들
			sibling: parent node 가 같은 node들
			root: parent가 없는 최상위 node 
			leaf: child가 없는 최하위 node 
			depth: root에서 특정 node에 도달하기 위해 거쳐야하는 edge의 수
			height: tree의 가장 깊숙히 있는 node의 depth, max(depth(every_node))
		순회 
			root와 root의 children을 모두 순회하는 함수를 만든다.
				각각의 child를 root로 하는 subtree를, 다시 순회하도록 재귀적으로 구성한다. 
				결과적으로 모든 node를 방문할 수 있다.
			방문 순서에 따른 분류
				전위 순회(preorder tarverse): root -> left child -> right child
				중위 순회(inorder tarverse): left child -> root -> right child 
				후위 순회(postorder tarverse): left child -> right child -> root
	binary search tree(BST), 트립(treap)
		개념 
			binary tree, leftsubtree는 모두 root보다 작으며, rightsubtree는 모두 root보다 크다.
		기능
			insert: [입력]에 해당하는 위치를 search하여, 해당 위치에 넣으면 된다.
			delete: 삭제 후에도 BST의 구조를 유지해야 함을 유의하자. 여러가지 방법이 존재한다.
				합치기: 삭제된 root의 왼쪽 subtree의 root를 새로운 root로 하여서, 두 subtree를 합친 후 삭제된 위치에 넣는다.
			X보다 작은 원소 찾기/ K번째 원소 찾기
				뒤에 나오는 트립을 이용한다.
		balanced binary search tree 
			tree가 치우치면(skewed) 연결리스트와 다를 바가 없다.
				어떤 입력이 들어와도 tree가 항상 lgN의 높이를 유지하도록, node들을 옮기기도 하면서 tree를 만든다.
			red-black tree는 대중적으로 쓰이는 balanced binary search tree이다.
				표준 구현 tree는 대부분이 red-black tree를 기반으로 구현한다. 
		treap 
			node에 임의의 우선순위를 부여해, 우선순위가 높은 node가 root에 가깝도록 tree를 만든다. 
				평균적으로 lgN의 높이를 유지하며, balanced binary search tree에 비해 구현이 간단하다.
			custom tree를 구현 할 때 이용하면 유용하다.
				subtree의 원소의 개수를 가지고 있어서, k번째 원소 구하기를 할 수 있다. 
				X보다 작은 원소의 개수를 구할 수 있다. 
			구현
				node 생성(입력) priority를 랜덤으로 생성한다, rand() 등 이용, size = 1 
				insert(입력, root) -> return &root
					priority > root.priority -> 입력을 root로 하고, 기존root를 적절히 split하여 left와 right subtree로 분리 
					priority < root.priority -> left or right subtree에 input
					size += 1
				split(기준, root) -> return pair(&leftnode, &rightnode)
					기준값보다 큰 값과 작은 값으로 subtree를 분리, 재귀적 구현, merge 이용 
				merge(leftnode, rightnode) -> return &root
					left subtree와 right subtree를 merge, 재귀적 구현, priority 고려 
				delete(대상, root)
					재귀로 대상 찾기, delete, merge 
		tree 팁 
			N개의 원소를 가지는, balance tree 생성법 
				tree를 좌에서 우로 세고, 우측끝에 도달하면 다음 depth로 가서 다시 좌에서 우로 센다고 하자.
					0, 12, 34 56, 78 9_10 11_12 13_14 와같은 순서로 세는 것이다. 
				n번째 원소의 child는, 각각 2n+1, 2n+2 번째 child 이다.
				root부터 시작해서 child가 N보다 작은 순서면 추가한다. 
					재귀적 구현
	heap 
		max-heap(min-heap)
			가장 큰(작은) 원소가 root인 tree 
			대부분의 표준 라이브러리에 구현되어 있다.	
			priority queue를 구현하는데 주로 이용된다.	
			heap sort를 구현할 수 있다. heap을 만들고 모두 pop하면, 메모리상에서 오름차순이 된다.
		장점 
			규칙이 단순하여 arr을 통해 구현할 수 있다.
			tree와 time complexity는 동일하더라도, arr을 이용하므로 실제로는 훨씬 빠르다.
		규칙
			root에는 tree에서 가장 큰(작은)원소가 들어간다.
			node idx는 좌상단에서 우하단으로 센다. 0 12 3456 ...
		구현 
			root = heap.front
			node's parent = heap[(node-1)/2]
			node's left child, right child: heap[node*2+1], heap[node*2+2]
			push: heap.push_back(input), leaf-root 갱신 
			pop: swap(root,heap.back), heap.pop_back, root-leaf 갱신 
	segment tree, 펜윅 tree 
		segment tree	
			특정 구간에 대한 정보를 전처리하여, 그들에 대한 질의를 빠르게 대답할 수 있다. 
			RMQ(range minimum query): 구간 최소 쿼리, 자주 사용되서 따로 이름도 있다.
		장점 
			자료가 특별한 규칙이 없어도 segment tree를 만들 수 있다. 
			구현이 간단한편이다.
			arr을 이용하여 속도가 빠르다.
		규칙 
			root는 모든 구간에 대한 전처리 값이다.
			left child는 left ~ mid 구간에 대한 전처리 값이다.
			right child 는 mid+1 ~ right 구간에 대한 전처리 값이다.
			필요한 size = pow(2,ceil(log(input.size)/log(2))) * 2 - 1
				1칸이 비므로, arr[0]을 meaningless value로 이용 가능 
		구현 
			arr[0]=meaningless value, arr[1]=root
			node's left child, right child: arr[node*2], arr[node*2+1]
			init: node = 전처리(left child init, right child init)
			query:
				node표현영역이 target영역에 포함: return arr[node]
				node표현영역이 target영역에 불포함: return arr[0]
				node표현영역이 target영역에 일부포함: return 전처리(left child query, right child query)
			update: 
				insert, delete, value change등이 발생했을 때 수행 
				query와 같은 원리를 적용해서, 변경된 부분을 포함하는 영역만 변경해준다.
	유니온-파인드 자료구조 
	트라이 (문자열을 표현하는 트리)
--graph
--비트마스크
	장점
		빠른 수행시간, 간결한 코드, 적은 메모리 사용량, 연관 배열을 배열로 대체(vector<bool> -> int or long long)
	팁
		켜진 비트의 개수 구하기: 각 컴파일러(visual c++, gcc/g++) 혹은 언어(java)에서 자체적으로 지원한다.
		켜져있는 least significant bit(최하위 비트) 구하기: 컴파일러/언어별로 지원한다. g++의 내장함수는 0에 대해 정의 X 
		최소 원소(2^최하위비트) 구하기: number & -number (2의보수에서 가장 먼저 1이 나오는 위치는, 꺼져있는 최하위 비트의 위치다.)
		최소 원소 지우기: number &= (number-1)
			2의 거듭제곱을 구할 때 유용하다: 2의거듭제곱은 하나의 비트만 켜져있기 때문에, 최소원소를 지우면 0이 된다.
			모든 부분집합 순회하기: for(int subset=pizza;subset;subset=((subset-1)&pizza)): 최소원소를 지우며 순회한다.
		비트하나 단위로 할 필요 없이, 여러개를 묶어서 단위로 사용해도 된다.(n개 비트는 2^n개 상태 표시)
		priority queue에서, 우선순위의 범위가 제한되었을때 이용 가능. least significant bit = 가장 빠른 우선순위 
	유의사항
		연산자 우선순위 주의 
		c++에서 상수는 int로 취급되므로, 적절한 접미사를 사용하자(u: unsigned int, ull: unsigned long long)
		unsigned 자료형을 사용하는것이 좋다.
		비트크기 이상으로 shift left하는것은 정의되어 있지 않다.(unsigned int의 경우 32비트이상 <<하지 않는다.)
--부분 합
	부분 합을 미리계산하여, 평균, 분산등을 빠르게 계산할 수 있으며, 2차원 이상에도 적용할 수 있다.
--동적배열과 연결리스트
--큐와 스택, 덱
	Queue: First In First Out
		push와 pop이 존재하며, 먼저 들어간 데이터가 먼저 나온다.
	Priority Queue: max priority out 
		우선순위가 큰 자료형이 먼저 나온다. 
		max-heap을 이용하여 구현 가능하다. 
--문자열 탐색과 매칭
	문자열 약속: str[i:j]는 str[i]~str[j-1]을 의미한다. i가 비어있으면 0, j가 비어있으면 end 이다.
	KMP search: str1에서 str2를 찾을 때, O(str1.len + str2.len) 시간으로 탐색이 가능하다. 여러 응용또한 가능하다 
		Boyer-Moore: 모든 위치가 아닌, 하나의 위치만 찾아도 된다면 더 유용하다. 
	suffix arr: 길이가 1~n인 접미사들을 사전순대로 정렬해놓은 것이다. O(n(lgn)^2)
		bucket sort를 이용하면 O(nlgn)에 구할 수 있다. 
		suffix arr을 이용하여, 모든 prefix를 구할 수 있다.
	prefix를 구하는 더 나은 방법도 존재한다. 675p 참고 
		
		

수행시간에 영향을 끼치는 것들
  같은 표현을 참조형으로 하느냐는 코드 가독성에서는 의미가 있지만, 수행시간에는 차이가 없다 (APSS-book2-CHRISTMAS참고)
  vector배열에서 어떤 값으로 초기화 하느냐가, 수향시간에 영향을 주진 않는다.(-1 이나 -5나 똑같다)
	APSS-book2-CHRISTMAS에서 int에대해 실험에 보았다. 다만 이것이 general 한지 실험해 보지는 않았다.
  절대적인 영향은 time complexity 이며, time complexity가 같더라도 최적화 정도에 따라 약간의 수행시간 차이는 있다.(APSS-book2-CHRISTMAS: greedy2 vs dp)


======================================== tmp ====================== 
	stack 연산
		increasing stack
			설명: stack에 idx를 저장하며, value[idx_in_stack]은 항상 커지도록(>) 한다. algospot Fence 
			작동: 
				while value[stack.back()] >= value[nowIdx]:
					stack.pop()
				stack.push(nowIdx)
	FenwickTree
		부분합을 구현하는 효율적인 방법이다. 
		성능 
			time complexity: O(nlgn)
				입력 및 수정을 O(lgn)에, 부분합 출력은 O(lgn)에 수행할 수 있다.
				단순 부분합은 입력 및 수정에 O(n), 부분합 출력은 O(1)에 수행된다.
			mem complexity: O(n)
				전체 입력의 길이가 n 이라면, tree는 n+1 만큼의 메모리만 점유한다.
		개념
			tree에서의 idx는 1 ~ N 범위를 이용한다.  
			tree[idx]는 일부 구간의 부분합만을 표현하며, 따라서 부분합(1 ~ idx)가 아닐 수 있다.
				tree[idx] = 부분합(? ~ idx)		//idx번째 값은 반드시 포함한다
			부분합 출력 
				while(idx>0)
					result += tree[idx]
					idx -= (idx & -idx)		//idx의 마지막 비트 제거 
			입력 및 수정 
				while(idx<=tree.size)
					tree[idx]+=input 
					idx += (idx & -idx)		//idx의 마지막 비트 더해주기 

treap, segment tree(RMQ), fenwicktree등은 간단하게 구현해두고, 여러 함수에서 공통적으로 사용하는것이 더 편할듯 하다. 
			
# 상호 배타적 집합(disjoint set)
- 상호 배타적인 집합은, 각 집합간의 공통원소가 없는 관계를 의미한다.
- 유니온-파인드(Union-Find) 자료 구조: 상호 배타적 집합을 다루는 자료구조 
	```
	- 초기화: n개의 원소가 각각의 집합에 포함되도록 초기화
	- Union: 두 원소 a,b가 주어질 때, 두 원소가 속한 집합을 하나로 합친다.
	- Find: 어떤 원소 a가 주어질 때, 이 원소가 속한 집합을 반환한다. 