
#include "important.h"

using namespace std;

//enum
/* enum
	열거형 자료형
??	enum class에 대한 공부 필요 
		enum은
*/
enum MyEnum
{
	RED = 3, BLUE, BLACK = 7, PINK = 9
};
void enumTest(void) {
	cout << RED << endl;
	cout << MyEnum(1) << endl;
	cout << MyEnum(0) << endl;
	//cout << MyEnum[1] << endl;
	cout << BLUE << endl;
	MyEnum Color(RED);		//??
	cout << Color << endl;
}
//cin 사용시의 버퍼문제
/*cin 사용시의 버퍼문제
	cin>>string; 과 같이 문자를 입력받을 경우, 문자가 입력 버퍼에 저장된 후 변수에 저장되게 된다.(숫자는 바로 변수에 저장된다)
	이때 입력 버퍼에는 엔터(\n)까지 입력되지만 num에는 \n이 제외되서 들어가게 된다.
**	즉 입력 버퍼에는 \n이 남아있게 되는 것이다.
	이때 cin.getline(string.20)과 같이 \n을 만나기까지 입력을 받는 함수를 사용하면, 해당 함수에 \n이 입력되고 함수가 종료된다.

**	cin.ignore(20,\n) : 20개의 문자 입력 혹은 \n 까지만 입력받고 나머지는 버리는 함수 
??						cin에서 배열길이 이상으로 입력받으면 문제가 생긴다. 해결방법은?
						근데 vector인가 쓰면 안되나?
		cin.ignore(): 아무런 문자도 입력받을수 없으므로 버퍼를 비우는 것과 같은 효과 
??	cin.claer(); 
??	cin.fail(); 
??	cin의 기초적인동작에 대한 조사 
*/ 
//키워드 const의 의미 (62p)
/*키워드 const의 의미 
	const 변수에 대한 포인터나 참조자 또한 cosnt하게 선언되어야 한다.
	앞 const: 선언되는 변수(포인터)를 상수화 시킨다.
	뒤 const: 선언되는 포인터가 가리키는 값을 바꿀 수 없다.
			const int num = 10;				: 변수 num의 상수화											
			const int* ptr1 = &val1;		: 포인터 ptr1을 통하여 가리키는 것(val1)을 변경할 수 없음
			int* const ptr2 = &val2;		: 포인터 ptr2가 상수화됨( 가리키는 주소가 변하지 않음)
			const int* const ptr3 = &val3;	: 포인터 ptr3가 상수화되며 가리키는 것(val3)을 변경할 수 없음

*/
//실행중인 프로그램의 메모리 공간 (62p)
/*실행중인 프로그램의 메모리 공간
	데이터: 전역변수 및 static변수가 저장되는 영역
??		컴파일 시 저장되며 사라지지 않는 것들
	스택:	지역변수 및 매개변수가 저장되는 영역
??		컴파일 시 저장되며 사라지는 것들
	힙:		프로그램이 실행되는 과정에서 동적할당이 이루어지는 영역. 사라지기 때문에 stack 사용
??		프로그램 실행도중에 생겼다 사라졌다 함. 따라서 heap 사용 
*/
//Pointer
/*Pointer
??	Double Pointer (Multi Pointer)
		두번이상 참조가 가능한 포인터의 경우 선언시 *을 통해 알려준다.
		만약 한번만 참조를 하면 어떻게 되는가? 
			: 빌드 에러가 발생한다. (초기화 할 수 없다고 나온다)
??	*의 의미: 참조 가능한 횟수를 의미. 프로그램은 값이 포인터 주소인지 실제 값인지 알 수 없으므로 *을 통해 알려준다.
		*을 안붙이면 빌드 단계에서 에러가 나는데, 컴파일러가 막는 것인지 실제 프로그램 실행시에 문제가 생기는 것인지는 모르겠다.
		참조 관계를 제대로 표시하지 않으면 어차피 빌드 단계에서 에러가 나긴 하지만, 그래도 제대로 확인하자
*/
//Reference (참조자)
/*Reference (참조자)
??	Reference의 의미
		변수에 별명(또다른 이름)을 붙여주는 것이다.
		int &num2 = num1; 에서 num2는 num1의 또다른 이름이다. 즉 num2가 변하면 num1도 변한다
		Ref는 Ref를 참조할 수도 있으며, 개수에 제한이 없다.
		Ref는 선언과 동시에 변수로 초기화되어야 한다.
		함수내에서 선언된 Ref는 지역변수와 마찬가지로 함수 종료시 소멸된다.
	Const Reference
		Ref는 일반적으로 변수에 대해서만 선언 가능하지만, const Ref의 경우 상수에 대해서도 선언 가능하다
			ex) const int &num1 = 30;
			전달인자가 Ref형때일 때 유용하다
				int Func1(const int &num1, const int &num2) 와 같은 함수에서 전달인자에 상수도 넣을 수 있게 된다
		Const Ref의 경우 함수내에서 매개변수의 값을 절대 변경할 수 없다. 그렇다면 Ref 형태로 전달받을 이유가 있는가?
				참고로 함수내에서 다른 함수를 호출해서 매개변수를 변경하는 것도 불가능하다.
??			확실하지는 않지만, Class등 객체를 호출할경우 유용하다?
	사용 위치에따른 용도
		ref가 선언단계에서 사용되면, 참조자(별명)의 선언
			ex) int** (&dpref) = dptr;
		ref가 초기화등 연산? 에 사용되면 변수의 주소값 의미  
			ex) int* ptr = &num;
	반환형이 참조형 경우
			int& RetRef(int &ref) 와 같은 형태
			int& ref2 = RetRef(ref); 와 같이 이용 가능
		함수를 통해 새로운 참조자를 선언할 수 있다.
		전달인자로 전달된 매개변수를 Ret해서 초기화하는 방식
			함수 내에서 정의된 변수는 함수종료시 소멸되기 때문에, 이를 Ret하는 것은 Junk값을 Ret하는 것이다.
			전달인자, 매개변수, 새로운 참조자 모두 같은 변수를 나타내지만, 매개변수는 함수 종료시 사라지므로 2개만 남는다.
	상수 변수에 대한 참조자는 상수 참조자이다.
		const int num1 = 20;
		//int &num2 = num1;
		const int &num2 = num1;
		
*/
//Meaning of '&' and '*'
/*Meaning of '&' and '*'
	모든것을 통일하는 표현, 설명(이유)가 있으면 좋겠지만, 반드시 그것을 알아야 할 필요는 없다. 필요로 할 때 방법을 발견하면 되는것이다.
	선언시
		&는 참조자를 선언하겠다는 표현이다.
			우변은 객체(변수) 형태로 표현한다.
		*는 포인터를 선언하겠다는 표현이다.
			&와 *이 같이온다면, 참조자이면서 포인터, 즉 포인터의 참조자를 선언하겠다는 표현이다.
			*의 개수는 참조 가능 횟수를 나타낸다. 포인터의 참조자 선언시 *의 개수도 맞춰주어야 한다.
	그 외 연산시
		&는 객체(변수)의 주소를 나타낸다.
		*은 주소를 참조하겠다는 것이다(주소의 위치에 있는 객체(변수)를 나타낸다.)
			*이 여러개라면 여러번 참조하는 것이다.

xxx	&은 객체나 변수의 주소를 나타낸다.
xx	*은 포인터변수가 가리키는 주소에 있는 객체나 변수를 나타낸다.
x	예시
x		int &num1 = num;	// num1의 주소는 num의 것과 같다는 의미다.(선언하는 변수(객체)의 형태는 이미 좌변에 있으므로 우변에 중복 정의할 필요가 없다
xx		int &num1 = *ptr;	// num1의 주소는 ptr가 가리키는 주소에 있는 변수(객체)와 같다.
xxx		int *ptr1 = &num;	// ptr1이 가리키는 주소에 있는 객체나 변수는 
*/
//Call by Value & Call by Reference (63p)
/*Call by Value & Call by Reference
	Call by Value: 값을 인자로 전달하는 함수의 호출방식
	Call by Reference: 주소 값을 인자로 전달하는 함수의 호출방식
**		함수 외부에 선언된 변수를 "참조"하는 것이 핵심
			아래 함수는 포인터에 대한 연산만 이루어지며 참조하지 않기 때문에, Call by Value로 보는것이 옳다.
			ex)	int* Func1(int* ptr)
					return ptr + 1; 
	주소 값을 이용한 Call by Reference	(int* ptr)
	참조자를 이용한 Call by Reference	(int& num)
		참조자로 선언된 매개변수는 외부 변수의 Ref이므로, 외부 변수에 직접 접근하는 것과 같다.
		매개변수는 지역변수 내에서 선언되었으므로 함수 종료시 소멸된다(별명이 다시 사라진다).
			ex)	void swap(int& num1, int& num2){
					int temp = num1;
					num1 = num2;
					num2 = temp;
				}
*/
void PtrRefTest(void) {
	int num = 10;
	int* ptr = &num;
	int** dptr = &ptr;
	//int* tptr = &ptr;
	cout << "int* tptr = &ptr; 로 초기화시 빌드에러 발생" << endl << endl;
	cout << "ptr: " << ptr << endl;
	cout << "*dptr: " << *dptr << endl;
	cout << "dptr: " << dptr << endl << endl;

	int& ref = num;
	//int& pref = ptr;
	int* (&pref) = ptr;
	int** (&dpref) = dptr;
	cout << "참조되는 변수가 가지는 *의 개수를 맞춰준다고 생각하면 된다." << endl;
	cout << "int& pref = ptr; 로 초기화시 빌드에러 발생" << endl << endl;
	cout << "ref: " << ref << endl;
	cout << "pref: " << pref << endl;
	cout << "dpref: " << dpref << endl;

}
//bool 자료형
/*bool 자료형
	bool은 그 자체로 true, false를 나타내는 1B 자료형이며, 실제로 0,1을 의미하는 것은아니다.
		0은 false, 0을 제외한 정수는 true를 나타내긴 하지만 오해하지말자.
		자료형이기 때문에 bool형식의 변수도 선언할 수 있다.
		bool을 출력하거나 정수 형태로 변환할 때는 각각 1, 0으로 변하긴 한다.
*/
//동적할당
/*
	People* list = new People[10];
		왼쪽: People이라는 자료형을 가리키는 포인터, 이름은 list
		오른쪽: People 자료형이 10개 들어가도록 동적할당
*/
//특수문자 출력
/*	
	특수문자, 서식문자 등을 출력하려면 앞에 \을 붙여준다.
	"\\n"을 출력하면 \n이 출력된다.
*/
//이름짓기
/*이름짓기
	변수: 첫글자는 소문자, 새로운 뜻마다 대문자
	상수: 모두 대문자
	함수: 변수와 같으나 첫글자가 대문자 
*/
/*
class SimpleClass{
	public:
		SimpleClass(){
			cout<<"Hello World"<<endl;
		}
};
	위와 같은 class가 선언되었을 때, 객체 sc1을 생성한다고 하자
		SimpleClass sc1;
		SimpleClass* ptr1=new SimpleClass;
		SimpleClass8 ptr2=new SimpleClass();
		//	SimpleClass sc1();
			이 라인의 경우, 반환형을 SimpleClass로 하는 함수 sc1을 선언한 것인지(함수의 원형 선언), sc1이라는 객체를 초기화한 것인지 구분할 수 없다.
				따라서 객체의 초기화 시에는 이러한 표현을 쓰지않고, 함수의 원형 선언 시에만 사용하기로 한다.
*/

/*
	일반적으로 private는 각 객체의 멤버함수에서만 접근할 수 있다.
		1) 복사생성자의 경우, 매개변수로 참조값을 전달받은 객체의 private값에 접근할 수 있는 것으로 보인다.
		2) friend 선언을 하면 복사가 가능하다. 
*/

//class 상속
/*class 상속
	Handler Class(Control Class): 기능의 처리를 담당하는 클래스
			데이터를 담고 있는 클래스를 제어하는, 실제로 작업을 수행하는 클래스
	상속: 유연성과 확장성 확보
			base-derived
			super-sub
			상위-하위
			부모-자식
	생성자:
		상속에서의 생성자:
			Derived class 생성자는 Base class를 초기화 시킬 의무가 있다.
			일반적으로 Base class의 생성자를 호출해 초기화한다.
??			그렇다면 Dervied class의 생성자는 필수적으로 정의해야하나? 기본생성자가 없나?
				Derived class의 생성자에서 따로 호출하지 않으면, void 생성자를 호출하게 된다.
**		유의점: 
			동적할당이나 배열할당등으로 void생성자를 호출해야만 할 때가 있다. 따라서 void생성자를 반드시 정의해두자
	생성과 소멸 순서:
			Dervied 생성자 호출 - Base 생성자 호출 - Base 생성자 완료 - Dervied 생성자 완료
			Dervied 소멸자
			클래스 생성자 기본값설정
	상속 범위:
		Base Class:
				private:	멤버 함수에서만 접근 가능, 상속시 derived에서 접근불가, base 멤버함수에서만 접근 가능
				protected:	멤버 함수에서만 접근 가능, 상속시 dervied 멤버함수에서 접근 가능
				public:		멤버 함수 및 객체에서 접근 가능
		Derived Class:
			public 상속:
				private - 접근불가:		Derived에서는 접근이 불가능하다. Base의 멤버함수를 통해 변경 가능
				protected - protected: 	Derived의 멤버 함수에서만 접근 가능
				public - public:		멤버 함수 및 객체에서 접근 가능
			protected 상속:
				private - 접근불가
				protected - protected
				public - protected:		멤버함수에서만 접근이 가능하게 되었다.
			private 상속:
				private - 접근불가
				protected - private:	멤버함수에서만 접근이 가능하게 되었으며, 상속시 접근불가하다.
				public - private:		멤버함수에서만 접근이 가능하게 되었으며, 상속시 접근불가하다.
*/
//Pointer에서 요소를 선택할 경우 "->", 객체나 참조자에서 요소를 선택할경우 '.' 이용
//vector

//dev에 있던 것들 정리 