
#include "important.h"

using namespace std;
/*	목차
	기본적인 약속, 규칙
		이름짓기
		문자열 표현 방법
		헤더 중복선언 방지
		enum-enum class
		bool 자료형 
		cin - cout 
		const 키워드
		임시변수
		매개변수 - 전달인자
		메모리공간 - data - stack - hip	
	포인터, 레퍼런스, 동적할당
		Pointer
		Reference
		연산자 & 과 *
		Call by Reference & Call by Value
		동적 할당 - new
	Class
	연산자 오버로딩
	Template
	입력방식에 따른 속도차이
*/


//기본적인 약속, 규칙
/*기본적인 약속, 규칙
	이름짓기
		공통: '_'사용가능, 첫문자는 영문자
		변수: 첫글자는 소문자, 새로운 뜻마다 대문자
			myClassMate
		상수: 모두 대문자
			COLOR_RED	   						
		함수: 변수와 같으나 첫글자가 대문자
			GetColor() 
	문자열 표현 방법
		""과 '': ""은 문자열 표현에, ''은 문자(1Byte)표현에 사용한다. 한글과 같이 1Byte로 표현 불가능한 문자도 ""사용 
	헤더 중복선언 방지
		#ifndef NAME_: NAME_가 정의되어 있지 않을경우 #endif 까지 실행
			#ifdef NAME_: 반대로 정의되어 있을경우 실행
			#endif: if문을 끝내는 라인
		일반적인 사용:
			#ifndef NAME_DEFINED__
			#define NAME_DEFINED__
			....
			#endif
	enum - enum class
		enum
			열거형 자료형
		enum class
			공부필요
	bool 자료형
		bool은 그 자체로 true, false를 나타내는 1Byte크기의 자료형이며, 실제로 0,1을 의미하는 것은아니다.
			0은 false, 0을 제외한 정수는 true를 나타내긴 하지만 오해하지말자.
			자료형이기 때문에 bool형식의 변수도 선언할 수 있다.
			bool을 출력하거나 정수 형태로 변환할 때는 각각 1, 0으로 변하긴 한다.
	cin - cout
		cin 
			사용시의 버퍼문제
				cin>>string; 과 같이 문자를 입력받을 경우, 문자가 입력 버퍼에 저장된 후 변수에 저장되게 된다.(숫자는 바로 변수에 저장된다)
				이때 입력 버퍼에는 엔터(\n)까지 입력되지만 num에는 \n이 제외되서 들어가게 된다.
**				즉 입력 버퍼에는 \n이 남아있게 되는 것이다.
				이때 cin.getline(string.20)과 같이 \n을 만나기까지 입력을 받는 함수를 사용하면, 해당 함수에 \n이 입력되고 함수가 종료된다.
**			cin.ignore(20,\n) : 20개의 문자 입력 혹은 \n 까지만 입력받고 나머지는 버리는 함수 
??				cin에서 배열길이 이상으로 입력받으면 문제가 생긴다. 해결방법은?
				근데 vector인가 쓰면 안되나?
			cin.ignore(): 아무런 문자도 입력받을수 없으므로 버퍼를 비우는 것과 같은 효과 
??			cin.clear(); 
??			cin.fail(); 
??			cin의 기초적인동작에 대한 조사 
		cout 
			특수문자 출력방법
				특수문자, 서식문자 등을 출력하려면 앞에 \을 붙여준다.
				cout<<"\\n";	은 \n 이 출력된다
			실수 자료형 출력범위
				기본적으로는 소수표현이 필요할경우 6자리만 출력한다.-> 50.0 등으로 나누어 떨어지는 경우 50만 출력한다.
				cout.precision(len) 
					len만큼의 길이를 출력한다. '.' 은 제외하고 카운팅
					한번 선언하면 이후로 계속 적용 
					기본은 6 인듯 
				cout<<fixed;
					cout.precision()이 소수점 아래 범위에 대해서만 설정한다.
				cout.unsetf(ios::fixed);
					cout<<fixed를 해제하고 cout.precision을 다시 전체 출력범위 설정으로 바꾼다.
	const 키워드
		const 변수
			const 변수에 대한 포인터나 참조자 또한 const하게 선언되어야 한다.
			앞 const: 선언되는 변수(포인터)를 상수화 시킨다.
			뒤 const: 선언되는 포인터가 가리키는 값을 바꿀 수 없다.
				const int num = 10;				: 변수 num의 상수화											
				const int* ptr1 = &val1;		: 포인터 ptr1을 통하여 가리키는 것(val1)을 변경할 수 없음
				int* const ptr2 = &val2;		: 포인터 ptr2가 상수화됨( 가리키는 주소가 변하지 않음)
				const int* const ptr3 = &val3;	: 포인터 ptr3가 상수화되며 가리키는 것(val3)을 변경할 수 없음
		const 함수
			const함수는 내부에서 변수의 값을 변경할 수 없다.
			const함수 내부에서는 const함수만 호출이 가능하다. 
	임시변수
		const취급?
	매개변수 및 전달인자
		매개변수
		전달인자
		관계
	Data - Stack- Heap
		Data
			전역변수 및 static변수가 저장되는 영역
??			컴파일 시 저장되며 사라지지 않는 것들
		Stack
			지역변수 및 매개변수가 저장되는 영역
??			컴파일 시 저장되며 사라지는 것들
		Heap	
			프로그램이 실행되는 과정에서 동적할당이 이루어지는 영역.
??			프로그램 실행도중에 생겼다 사라졌다 한다면 heap 사용 	
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
	MyEnum Color(RED);		//??	Color은 MyEnum의 RED라고 초기화?
	cout << Color << endl;
}


//Pointer
/*Pointer
	Pointer 자료형
		주소를 나타내는 "자료형"이다.
			*의 개수는, 포인터가 몇 단계로 이루어져 있는지를 나타낸다.
			*의 개수가 3개라면, ptr1 -> ptr2 -> ptr3 -> 객체(변수) 형태라는 의미다.
		다른 자료형을 대입할 수 없다.
			int형 자료형의 double형 자료형을 대입할 수 없듯이, 포인터 자료형에 임의의 값을 대입할 수 없다.
				int* ptr = &num;	//num의 참조정보를 통해 ptr 초기화
*/
//Reference (참조자)
/*Reference (참조자)
	Reference
		변수에 별명(또다른 이름)을 붙여주는 것이다.
			int &num2 = num1; 에서 num2는 num1의 또다른 이름이다. 즉 num2가 변하면 num1도 변한다
		Ref는 Ref를 참조할 수도 있으며, 참조 횟수의 제한은 없다.
		Ref는 선언과 동시에 객체(변수)로 초기화되어야 한다.
		함수내에서 선언된 Ref는 지역변수와 마찬가지로 함수 종료시 소멸된다.
			지역변수의 Ref를 반환하는 것은, Junk값을 반환하는 것과 다름없다.
	Const Reference
		Ref는 일반적으로 변수에 대해서만 선언 가능하지만, const Ref의 경우 상수에 대해서도 선언 가능하다
			ex) const int &num1 = 30;
			전달인자가 Ref형때일 때 유용하다
				int Func1(const int &num1, const int &num2) 와 같은 함수에서 전달인자에 상수도 넣을 수 있게 된다
		Const Ref의 경우 함수내에서 매개변수의 값을 절대 변경할 수 없다. 
			그렇다면 Ref 형태로 전달받을 이유가 있는가?
				절대 변경할 수 없다는 것이 함수의 안정성을 높여줄 수 있다. 또한 해석에 이점이 잇다.
				참고로 함수내에서 다른 함수를 호출해서 매개변수를 변경하는 것도 불가능하다.
	상수 참조자
		상수 참조자는 변수의 값을 변경할 수 없다.
			원본 변수의 값을 변경하면 참조자의 값도 당연히 바뀐다.
				int num=30;
				const int& num1=num;
				num=40;	//num1=40
				//num1=40;	: const 선언됐으므로 불가능
		상수 변수에 대한 참조자는 상수 참조자만 가능하다.
*/
//연산자 & 과 *
/*연산자 & 과 *
	선언시
		&는 참조자를 선언하겠다는 표현이다.
			우변은 객체(변수) 형태로 표현한다.
		*는 포인터를 선언하겠다는 표현이다.
			&와 *이 같이온다면, 참조자이면서 포인터, 즉 포인터의 참조자를 선언하겠다는 표현이다.
			*의 개수는 참조 가능 횟수를 나타낸다. 포인터의 참조자 선언시 *의 개수도 맞춰주어야 한다.
	그 외 연산시
		&는 객체(변수)의 참조 정보를 나타낸다.
		*은 포인터가 가리키는 공간을 참조(반환?)하는 것이다(주소의 위치에 있는 객체(변수)를 나타낸다.)
			*이 여러개라면 여러번 참조하는 것이다.
	반환형
		참조 표현이 있지 않은 모든 반환형은 임시 객체(변수)로 반환이 된다.
			임시변수가 가리키는 주소는 같지만, 임시변수와 원본변수는 엄연히 다른 변수이다. 가리키는 주소는 같지만 변수자체가 저장된 주소는 다르다.
				포인터 변수의 값을 변경하고 싶다면, 참조형으로 반환해야 한다.
	&과 *의 일관적인 표현
		&은 객체(자료형)이 위치한 주소(공간)을 참조할 수 있는 정보 
		*은 포인터가 가리키는 공간을 참조하겠다는 것이다.
			포인터는 단지 주소를 가리키는 변수이며, *을통해 참조하기 전에는 단순히 변수일 뿐이다.
				int& num1 = num;		//num1의 공간 = num
				int& num1 = *ptr;		//num1의 공간 = 포인터가 가리키는 공간 , num1은 *ptr의 Reference 
				int *ptr1 = &num;		//ptr1의 공간 = num의 공간 	, ptr이 가리키는 위치는 num
				*&ptr1 = &num2;
				&ptr1 = ptr;
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
	int* &pref = ptr;
	int** &dpref = dptr;
	cout << "참조되는 변수가 가지는 *의 개수를 맞춰준다고 생각하면 된다." << endl;
	cout << "int& pref = ptr; 로 초기화시 빌드에러 발생" << endl << endl;
	cout << "ref: " << ref << endl;
	cout << "pref: " << pref << endl;
	cout << "dpref: " << dpref << endl;

}

//동적할당
/*
	People* list = new People[10];
		왼쪽: People이라는 자료형을 가리키는 포인터, 이름은 list
		오른쪽: People 자료형이 10개 들어가도록 동적할당
*/

// class 멤버함수의 호출: 객체.멤버함수() or 주소->멤버함수()

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
			Dervied 소멸자 완료 - Base 생성자 완료
				스택에 생성된 객체의 소멸순서는 생성순서와 반대이다.
??					스택에 생성된 객체: 동적할당되지 않은 객체: 동적할당은 힙에 생성되며 생성된 순서대로 소멸 
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
//class 생성자에서 default값을 설정할경우, header가아닌 cpp파일에서 설정 (혹은 선언이 아닌 정의 부분에서 설정이 맞는 표현일수도 ? 아닌거 같은데.
/*
	프로그램에서 할당과 접근은 별개의 영역이다. 접근을 할 때, 해당 메모리 영역이 할당 받았는지 안받았는지는 신경쓰지 않고 기계적으로 접근한다. 
		즉 char* ptr은 단일char과 char배열을 모두 나타낼 수 있는데, 둘 모두 시작지점은 같기 때문이다.
			또한 둘 모두 char[1]접근을 할 수 있는데, ptr[1]은 단순히 *(ptr+1)을 나타내며 접근에 문제가 없다.
				차이점은 ptr+1의 위치를 할당 받았는지의 여부 뿐이며, 안전한지 불안전한지의 여부 뿐이다. 
		즉 포인터의 자료형만 잘 지정하면, 포인터가 배열을 가리키는지 단일 자료를 가리키는지는 전혀 신경쓸 필요가 없다.
			포인터의 사용할 범위를 할당만 잘 해주면 된다.
*/
//Control class vs Entity Class
/*
	Entity class, 즉 저장되는 자료를 나타내는 class는 복사 생성자나 대입연산자의 필요성이 매우 적다.
		이러한 멤버함수가 불필요할 경우, 함수의 정의를 공백으로 하고, private 부분에 둠으로써 함수의 호출을 막을 수 있다.
			private:
				EasyClass(const EasyClass& empty){}
*/

/*상속과 다형성
	상속의 의미
		상속을 통해 연관된 일련의 클래스에 대해 공통적인 규약을 정의할 수 있다.
			Handler class의 변경이 이루어지지 않고 기능을 추가할 수 있다.
			virtual과 overriding을 이용하면 base class 자료형의 pointer로 dervied class의 멤버에 접근할 수 있다.
			상속이 여러번 이루어져도, 모든 객체를 base class 자료형의 pointer로 나타낼 수 있게 되는 것이다.
			
	함수 overriding (not overloading)
		base class와 dervied class에 동일한 이름과 형태의 멤버함수가 있는 것
			형태: 매개변수의 자료형과 개수도 같아야 한다. 만약 다르다면 overloading 임.
			dervied class의 객체에서는, 현재 class의 멤버함수가 우선적용된다.
		overriding의 경우, 나중에 정의된 것이 처음 정의된 것을 가린다고 생각하자
			가려진 함수는 BASE::Func1과 같은 방법으로 호출 가능하다
		여러번 상속된 경우, 현재 class기준에서 가장 마지막으로 overriding된 함수가 호출된다.
		base class의 함수와 dervied class의 함수는 접근할 수 있는 영역(멤버변수 및 함수: 멤버)가 다르기 때문에 overriding이 의미가 있다.

	상속 관계에서의 Pointer & Reference
		base class 자료형의 pointer는, base를 직접 및 간접(a->b->c에서 a와 c)상속하는 class의 객체를 가리킬 수 있다.
			base->derived->derived2: base* ptr= derived2 object;	
		그러나 base class 자료형의 pointer는 derived class의 멤버에는 접근할 수 없다. 
			컴파일러의 연산가능여부 판단 기준은 pointer의 자료형이므로, base에는 없는 dervied의 멤버에 접근할 수 없는 것이다.
		즉 base class 자료형의 pointer가 derived class의 객체를 가리켜도, derived class의 멤버에는 접근할 수 없는 문제가 발생한다.
			의미가 없어진 셈이다.
		virtual function으로 문제 해결 가능 
		Reference도 Pointer와 동일하게 적용된다.

	virtual function
		선언
			virtual void MyFunc();
			가상함수로 선언된 함수를 overriding하는 함수는, 따로 virtual을 선언하지 않아도 자동으로 가상함수가 된다.
				코드 분석의 용이를 위해 overriding하는 함수에도 virtual을 붙여주는것이 좋다.
		기능
			가상함수 호출시, pointer의 자료형이 아닌, pointer가 가리키는 객체를 기준으로 가장 마지막으로 overriding된 가상함수를 호출한다.
		정의
			정의시에는 따로 virtual을 붙여주지 않는다.
		소멸자
			First -> Second -> Third로 상속되는 class에서, First 자료형 포인터로 Third형을 가리키는 경우, 소멸자도 First만 호출된다.
				소멸자도 가상함수 처리해서 Third -> Second -> First 순서로 호출되게 만든다.
				다른 virtual과 마찬가지로 base class의 소멸자가 virtual 선언되면 dervied class들도 모두 virtual 선언이 자동으로 된다.
					소멸자의 경우 이름이 다름에도(First, Second ...) 자동으로 선언 처리되므로 오해하지 말자 
		Virtual Table
			가상함수를 포함한 클래스는  V-Table을 가지게 된다.
				V-Table은 호출하고자 하는 함수를 구분하는 key, 해당하는 함수의 주소를 나타내는 value로 이루어져 있다.
				오버라이딩 된 함수의 경우, V-Table에는 가장 마지막에 오버라이딩 된 함수가 적혀있게 된다(현재 클래스 기준).
				각 객체에는 해당하는 class의 V-Table의 주소 값이 저장된다.
					First class 포인터가 Second class 객체를 가리킬 때, 포인터는 Second class의 V-Table을 참고하여 가상함수를 호출하는 것이다.

	순수 가상함수 와 추상 클래스
		순수 가상함수 (Pure virtual function)
			함수의 몸체가 정의되지 않은 함수
				=0을 통해 몸체가 정의되지 않았음을 알린다
				virtual void MyFunc() const = 0;
		추상 클래스 (Abstract class)
			객체 생성을 목적으로 정의되지 않는 class
				base class로서의 의미만 가질뿐, 객체의 생성을 목적으로 하지 않는 class에 유용 - 오류 발생 방지 
			가상함수를 순수 가상함수로 선언하여 추상클래스 구현 가능
				순수 가상함수를 지니면 완전하지 않은 class가 되어 객체 생성이 불가능하다.


*/
/*
	Control class: 프로그램 전체의 기능을 담당
					프로그램의 기능 및 흐름 파악 가능
	Entity class: 데이터를 저장하는 클래스
					데이터의 종류 파악 가능 
*/
/*
	형 변환 주의
		money * (1+7/100)은 money * 1과 같다.		int로 적용
		money * (1+7/100.0) 으로 적용해야 한다.	double로 적용
			cout<<typeid(1/100.00).name()<<endl;	:	d(double)
			cout<<typeid(1/100.0).name()<<endl;		:	d(double)
			cout<<typeid(1/100).name()<<endl;			:	i(int)
*/
/*
함수 포인터 변수
	void (*ShowData)(Data*);
	void (*Add)(Data*, int);
	반환형 (*가리키는 함수 이름)(매개변수 자료형);
		함수 포인터 변수가 가리키는 함수를 나중에 정의한다.
		?: 함수를 만드는 것이 아니라, 함수 포인터, 즉 함수의 위치를 알려주는것. 실제 함수는 하나만 만들 수 있다.
				class등에서 사용? 용도가 무엇 
함수 포인터

*/
/*
	멤버 함수의 실제 위치
		객체 내부에는 실제로는 멤버변수만 존재한다. 멤버함수는 객체 외부에 존재한다.
		같은 class의 모든 객체는 하나의 멤버함수를 공유한다.
	다중 상속
		여러개의 함수를 동시에 상속
			class MultiDerived : public BaseOne, protected BaseTwo{...};
		함수 호출의 모호함
			BaseOne과 BaseTwo의 멤버함수명이 같을 경우 어떻게 구분하는가?
				BaseOne::Func1, BaseTwo::Func2와 같은 방식으로 구분
	가상 상속
		다중 상속에서 하나의 객체에 Base가 여러개일 경우 함수 호출의 모호함
				class Derived1: public Base{...};
				class Derived2: public Base{...};
				class FinalDerived: public Derived1, public Derived2{...};
					Base(1)-Derived1-FinalDerived
					Base(2)-Derived2-			''
			FinalDerived 객체는 두 개의 Base 클래스 멤버를 가지게 된다.	
					Base 생성자가 두번 호출된다.
				즉 Derived1과 Derived2는 다른 Base 클래스 멤버를 상속한다.
				어느 클래스를 통해 간접상속한 Base 클래스의 멤버함수를 호출할 것인지 명시해야 한다.
					Derived1::Func, Derived2::Func
		Virtual 을 통해 하나의 Base만 생성되도록 한다.
				class Derived1: virtual public Base{...};
				class Derived2: virtual public Base{...};
				class FinalDerived: public Derived1, public Derived2{...};
					Base-Derived1-FinalDerived
					 ''	-Derived2-			''
			FinalDerived 객체는 하나의 Base 클래스 멤버를 가진다.
					Base 생성자가 한번 호출된다.
				즉 Derived1과 Derived2가 같은 Base 클래스 멤버를 상속하는 것이다.
			
*/

//연산자 오버로딩
/*
	연산자 오버로딩
		멤버함수의 의한 오버로딩
				클래스 내부에서: Point operator+(Point& ref){...}
						point3=point1.operator+(point2);
						point3=point1+point2;
		전역함수에 의한 오버로딩
				클래스 내부에서: friend Point operator+(const Point& point1, const Point& point2);	
						(operator+ 함수가 클래스의 private 멤버에 접근할 수 있게 해주는 선언)
						(Point 클래스가 + 연산자에 대해 오버로딩 되어 있음을 알 수 있다)
				클래스 외부에서: Point operator+(const Point& point1, const Point& point2){...}
						point3=operator+(point1,point2);
						point3=point1+point2;
		오버로딩이 불가능한 연산자
				.									:멤버 접근 연산자	
				.*								:멤버 포인터 연산자
				::								:범위 지정 연산자
				?:								:조건 연산자(3항 연산자)
				sizeof						:바이트 단위 크기 계산
				typeid						:RTTI 관련 연산자
				static_cast				:형변환 연산자
				dynamic_cast			:형변환 연산자
				const_cast				:형변환 연산자
				reinterpret_cast	:형변환 연산자
		멤버함수 기반으로만 오버로딩 가능한 연산자
				=									:대입 연산자
				()								:함수 호출 연산자
				[]								:배열 접근 연산자(인덱스 연산자)
				->								:멤버 접근을 위한 포인터 연산자
		주의사항
			본래의 의도를 벗어난 연산자 오버로딩은 좋지 않다.
				+연산자가 곱셈을 나타낸다면?
			연산자의 우선순위와 결합성은 바뀌지 않는다.
			매개변수의 디폴트 값 설정이 불가능하다.
			연산자의 순수 기능까지 빼앗을 수 없다.
				int operator+ 연산자와 같은, 이미 정의되어있는 기본연산자를 재정의하여 기능을 바꿀 수 없다.
		단항 연산자 오버로딩
				피연산자가 한 개인 단항 연산자
					++, --, ~, - ...
				피연산자가 두 개인 이항 연산자
			전위증가 vs 후위증가
				키워드 int를 통해 구분
					전위증가:	pos.operator++();
					후위증가: pos.operator++(int);
						const Point operator++(int){...}
						const Point operator++(Point &ref, int){...}	
				후위증가의 반환형에 const 키워드가 붙은 이유
					C++의 연산 특성을 그대로 반영, 일관성을 유지하기 위해서다
						++(++intVar)와 같은 연산은 허용된다.
						(intVar++)++와 같은 연산은 허용되지 않는다.
							const키워드를 통해 객체의 경우도 아래 연산이 허용되지 않도록 만들었다.
		교환법칙의 성립
			객체*int 형식과 같은 경우, 교환법칙이 성립하지 않는다.
				전역 함수에 의한 오버로딩을 통해, 교환법칙도 성립하게 만든다.
					(멤버)Point operator*(int times){...}
					(전역)Point operator*(int times, Point& ref){...}
		cin, cout의 오버로딩, 그리고 endl (430p 참고)
				아래 함수는 cout의 실제 구조의 일부를 간략하게 표현한 것이다.
					실제는 iostream(header)->std(namespace)->ostream(class)->cout(object) 구조이다.
					함수를 보며 구조를 이해하도록 하자.
			오버로딩 유의사항
				cout은 ostream class의 객체이다.
				ostream class는 이름공간 std안에 선언되어 있으며, 이의 사용을 위해서는 헤더파일 <iostream>을 포함해야 한다.
					iostream(header)->std(namespace)->ostream(class)->cout(object)
						ostream(class): operator <<가 정의되어 있음 
				멤버함수방식 vs 전역함수 방식
					<iostream> 에 정의된 ostream에 오버로딩함수를 추가할 수 없으므로, 전역함수에 의한 방법을 선택해야 한다.
						ostream& operator<< (ostream& os, const Point& pos){
							os<<'['<<xpos<<','<<ypos<<']'<<endl;
							return os;
						}
							ostream의 객체와 내가 정의한 class의 객체(여기선 Point class)가 operator<<의 매개변수 일 때 오버로딩된 함수가 호출된다.
								cout<<pos1 = operator<<(cout, pos1) 에서 cout은 ostream의 객체, pos1은 Point의 객체이므로 오버로딩된 함수를 호출하게 된다.
							ostream에 기본적으로 정의된 operator<<을 이용하여 출력을 구성한다.
				cin
					iostream(header)->std(namespace)->istream(class)->cin(object)
			똑똑한 cin
				cin>>pos.xpos>>pos.ypos(int형식); 와 같은 상황에서 정수를 입력하고 스페이스바(엔터)를 한번이상 치고 다시 정수를 입력하면 각각 입력이 된다.
				cin에 오버로딩된 operator>>가 입력을 문자열 형식으로 받은 뒤, 알아서 공백은 거르고 int로 변형시켜서 입력받는 듯 하다.
		대입연산자('=') 오버로딩
			복사 생성자와의 유사성
				정의하지 않으면 디폴트 복사 생성자(대입 연산자)가 생성된다.
				디폴트는 얕은 복사를 진행한다.
				생성자(연산자)내에서 동적할당을 하거나, 깊은 복사가 필요하다면 직접 정의해야 한다.
			복사 생성자와의 차이점
				호출되는 시점이 다르다
					복사 생성자: 객체가 생성과 동시에 초기화 될 때 호출된다.
					대입 연산자: 이미 생성 및 초기화가 진행된 객체간 대입이 진행될 때 호출된다.
				상속관계가 있을 때 대입연산자
					Dervied의 디폴트 대입 연산자는, Base의 대입 연산자도 호출한다.
					유도 클래스의 대입 연산자 정의에서, 기초 클래스의 대입 연산자 호출문을 삽입하지 않으면 기초클래스의 대입 연산자는 호출되지 않는다.
						이로인해 기초클래스의 멤버는 멤버 대 멤버 복사 대상에서 제외된다.
		배열의 인덱스 연산자 오버로딩
			operator[]도 오버로딩이 가능하다.
				int& operator[](int idx){...}	//반환형은 자료형에 따라서
			const선언을 하면 배열에 저장이 불가능하게되므로, const선언을 하지 않는다.
				그러나, 이 경우 const함수에서 호출이 불가능하다는 단점이 있다.
				const 오버로딩으로 해결 가능.
		const 함수를 이용한 오버로딩
			함수의 const 유무도 오버로딩의 대상이 된다.
				일반적인 호출에서는 const가 없는 함수를, const 함수에서는 const가 있는 함수를 호출하게 된다.
				오버로딩의 조건은 함수의 이름, 매개변수의 개수, 매개변수의 자료형이다. 반환형은 포함되지 않는다.
		new, delete 오버로딩
			new와 delete의 작동원리
				new
					메모리 공간의 할당		  															 : void 형 할당
					생성자 호출																						: 할당된 메모리 공간 초기화
					(할당하고자 하는 자료형에 맞게) 반환된 주소 값의 형 변환 : void 형 포인터를 적절한 포인터로 형 변환 
				delete
					?소멸자 호출
					?메모리 공간의 해제
			오버로딩 대상
				new
					메모리 공간의 할당
				delete
					메모리 공간의 해제
				나머지는 컴파일러가 자동으로 진행한다.
			오버로딩 방법
				void* operator new (size_t size){
					//cout 등 다른 명령어도 추가할 수 있다.
					//아래는 필수
					void* adr= new char[size];	//malloc으로 대체 가능
					return adr;
				}
						다른 연산자 오버로딩과 다르게 선언은 이렇게 고정된다. (size라는 변수명을 바꿀수는 있을 듯 하지만 굳이?)
						필요한 메모리 공간(즉 size의 값)은 컴파일러가 자동으로 계산한다. 
						일반적으로 size_t는 다음과 같의 정의되어 있다.
							typedef unsigned int size_t;
							32비트 OS는 32비트, 64비트 OS는 64비트로 정의되어 있다.
								unsigned int는 64비트 os여도 32비트로 정의되었을수도 있다? unsigned int와 size_t의 차이점?
				void operator delete (void* adr){
					//역시 다른 명령어도 추가할 수 있으며 아래는 필수 
					delete[] adr;	//free로 대체 가능
				}			
			멤버함수 형식임에도 호출이 되는 이유
				멤버함수의 형식으로 선언이 되어도, static로 간주가 된다.
					static은 객체가 선언되지 않아도 호출 가능?
						class에서의 static 복습 
			new[]와 delete[]
				호출: 배열 할당과 소멸시 선언된다.
				정의: size는 컴파일러가 계산해주기 때문에 내용면에서 new, delete와 차이는 없다.
		포인터 연산자 오버로딩
			-> 과 *
			피 연산자가 하나인 단항 연산자의 형태로 오버로딩된다.
				easyClass* operator->(){ return this; }
						easyobject1->ShowData(); 는
						easyobject1.operator->() ShowData() 와 같이 해석이 되는데, operator->()함수는 주소를 반환하기 때문에 ->가 있어야 멤버함수를 호출할 수 있다.
							따라서 ->가 하나 추가되어서, easyobject1.operator->() -> ShowData();와 같이 해석된다.
							무한루프아님? 해석에 있어서만 저런식으로 해석된다는 건가?
					이와같이 주소가 반환되는 함수의 경우, 주소에 직접 접근하여 private한 특성을 무력화 시킬 수 있다.
						const 선언을 통해 참조만 가능하고 변경은 불가능하게 변경할 수 있다. (여전히 private한 특성이 일부 무력화 된 것 같긴 하다.)
				easyClass& operator*(){ return *this; }
		()연산자 오버로딩
			operator()
		Functor
			함수처럼 작동하는 class를 Functor, 혹은 Function object 라고 한다.
				교재486p에서 functor를 통한 bubble sort 예시 
		임시 객체로의 자동 형 변환과 형 변환 연산자(conversion operator)
			같은 객체간의 대입 연산자 사용이 가능함을 알고있다.
			객체와 다른 객체(혹은 자료형) 간의 대입 연산자 적용 또한 가능하다.
				A = B 에서, B의 데이터를 전달인자로 하는 A형 클래스의 생성자를 호출하여, 임시 객체를 만든다. 이후 대입 연산 진행
					A=A'(B의 데이터를 전달인자로 만든 A형 임시객체)
				객체(기본 자료형)의 형 변환이 자동으로 일어난 것이다.
			객체에서 기본자료형으로의 자동 형 변환또한 가능하다.
				operator 자료형 () 로 정의 가능 
					operator int () { return num; }
						객체가 int형으로 형 변환될 때 호출된다. 
				반환형이 없어도 반환이 가능하다는 특징이 있다.

*/		
namespace mystd{
	using namespace std;
	class ostream{
		public:
			ostream& operator<< (char* str){
				printf("%s", str);	//오버로딩을 통해 출력을 구현하고 있다.
				return *this; // cout<<"string"<<123<<endl과 같이 연속적인 사용을 가능하게 하기 위해 반환형을 ostream&으로 구현했다.
			}
			ostream& operator<< (char str){
				printf("%c", str);
				return *this;
			}
			ostream& operator<< (int num){
				printf("%d", num);
				return *this;
			}
			ostream& operator<< (double e){
				printf("%g", e);
				return *this;
			}
			ostream& operator<< (ostream& (*fp)(ostream& ostm)){	//함수포인터: 반환형이 ostream&이고, 매개변수가 ostream&인 어떤 함수가 들어갈 수 있다. 
				fp(*this);	
				/*
				cout<<endl; 일 경우
					*fp는 endl을 가리키게 된다.
					cout.operator<<(endl)
						fp(*this) = endl(*this) = endl(cout)
						객체는 cout이므로, *this는 cout자신이다.
							endl(ostream& cout)가 실행된다.
								cout<<'\n';
								fflush(stdout);
								return cout;
				*/
				return *this;
			}
	};

	ostream& endl(ostream &ostm){
		ostm<<'\n';	//줄바꿈, cout<<'\n';과 같다.
		fflush(stdout);	//출력 버퍼를 모두 출력하고 비운다.
		return ostm;
	}

	ostream cout;	//cout이 객체임을 알 수 있다.
}
/*
	반환형 에서의 const 선언, const 객체
		반환형에서의 const 선언
			반환시 생성되는 임시 객체를 const로 선언한다
		const 객체
			객체의 저장된 멤버의 변경을 허용하지 않는다.
				따라서 참조자를 선언할 때도 const로 선언해야 한다.
*/

/*
	함수 포인터
*/

/*
	fflush와 입력 버퍼 등 시스템의 구조
		시스템의 구조
			입력스트림(키보드) -> 입력 버퍼(stdin) -> 프로그램 -> 출력버퍼(stdout, stderr) -> 출력스트림(모니터)
		입력의 단계
			입력 버퍼에 엔터(\n)가 들어오기 전 까지 입력 받는다
				scanf를 통해 입력버퍼에서 해당하는 자료형을 프로그램에 넣어준다.
					이때 숫자를 scanf할 경우, \n은 숫자가 아니기 때문에 입력 버퍼에 남아있게 된다.
						이로인해 다음 scanf사용시 원치않은 입력을 받을 수 있다.
						따라서 각 운영체제에 맞는 방식으로 버퍼를 비워주는 것이 필요할 수 있다.
		출력의 단계
			데이터를 출력버퍼에 저장하고 출력한다.
				운영체제에 따라 다르게 작동하기도 한다.
					    int i;
 							printf("12345");
    					for(i=0; i>=0; i++);
   						printf("67890\n");
					위 프로그램의 경우 윈도우는 12345를 출력하고 루프를 돈 후 67890을 출력한다.
						리눅스의 경우는 루프를 모두 돈 후에 1234567890을 한꺼번에 출력한다.
							프로그래머의 의도대로 루프를 돈 후에 67890을 출력하고 싶다면 fflush(stdout)을 통해 출력버퍼를 모두 출력해버리면 된다.
		fflush
			******c표준 라이브러리에서는 출력 스트림에 대해서만 정의되어 있다.*******
				fflush(stdout): stdout의 내용을 모두 출력해버린다 - > 버퍼가 비워진다.
					버퍼가 비워지는 시점은 os마다 다를 수 있다.
						어떤 os에서는 출력 스트림 버퍼에 데이터가 들어오자 마자 꺼내어 출력하는 경우가 있고
						어떤 ost에서는 줄바꿈 캐릭터('\n')가 들어와야 출력을 하기도 한다.
					본인이 기억하기로는 Windows 에서는 stdout와 stderr가 동일하며 출력 스트림에 데이터가 들어오면 바로 출력하지만 (즉 버퍼를 즉시즉시 비우지만), Linux 는 stdout 과 stderr가 별도의 버퍼를 가지고 있으며, stderr는 즉시 비우는 반면, stdout는 개행을 의미하는 문자가 나타날 때까지, 혹은 표준 입출력 버퍼에 다른 이벤트가 벌어질 때까지 데이터를 출력하지 않고 버퍼에 그대로 쌓는다.
						(http://andyader.blogspot.com/2013/09/fflush.html)
				fflush(stdin): fflush는 출력 스트림에 대해서만 정의되어 있기 때문에, os마다 동작이 다르다
					Windows 계열과 POSIX UNIX의 일부 계열: 입력 스트림 버퍼를 비운다.
					LINUX등 다른 OS: 아무런 동작도 하지 않는다.
*/
	
/*
	이니셜라이저의 이점
		이니셜라이저를 사용하면 선언과 동시에 초기화가 이뤄지는 형태로 바이너리 코드가 생성된다.
		생성자의 몸체부분에서 대입연산을 통한 초기화를 진행하면, 선언과 초기화를 각각 별도의 문장에서 진행하는 형태로 바이너리 코드가 생성된다.
*/

//디폴트는 일반적으로 선언 부분에서 표현한다.
//객체의 배열을 멤버변수로 가지는 배열 클래스도 정의 가능, 객체의 배열은 객체자체, 객체의 포인터 대상 둘다 가능.
/*
	포인터를 저장하는 배열의 경우, 포인터를 typedef를 통해 따로 선언하면 좋다.
		typedef Point* POINT_PTR;	//POINT_PTR은 Point*을 의미한다.
			Point** ptrarr == POINT_PTR* ptrarr
		 조금 더 직관적일수도 있고 아닐수도 있다. 
		 	전자의 경우 참조 횟수가 더 직관적이다.
			후자의 경우 포인터를 원소로 가지는 배열임을 선언함이 직관적이다.
*/

/*
	스마트 포인터
	스마트한 포인터를 객체로 구현 
		책에서는 자동으로 동적 할당을 해제하며 포인터처럼 작동하는 객체를 구현
	스마트 포인터는 라이브러리의 일부로 구현되어 있으니 필요시 찾아서 쓰자 
*/

/*
	바이트 패딩
		cpu에 접근을 쉽게 하기 위해서, 실제 필요한 공간보다 더 큰 공간을 할당받는 것 -> 성능 향상을 꾀할 수 있다.
		32bit cpu는 4Byte, 64bit cpu는 8Byte일 때 효율이 좋으므로, 해당 크기에 맞게 패딩을 한다.
			패딩하는 위치는 자료형 뒤에 한다.
			1Byte 자료형을 패딩하여 4Byte가 될 경우, 앞 1Byte가 자료, 뒤 3Byte가 패딩이다. 
*/

/*
	template
		함수 템플릿
			선언 
				template <typename T>
				T Add(T num1, T num2){...}
					typename은 class 라는 표현으로 대체 가능
					T는 템플릿 매개변수라 한다.
					T대신 다른 문자 사용 가능 
				template <class T1, class T2>
					둘 이상의 형(type)에 대해서도 선언이 가능하다
				
			호출
				Add<int>(15,20);
					<자료형>을 통해 T가 무엇으로 대체될 것인지 알려준다.
						<자료형> 을 생략하면 자동으로 컴파일러가 변형해주기도 한다. 그러나 명확한 경우가 아니고선 자료형을 명시하는 것이 좋을 듯 하다.
							후에 나오는 클래스 템플릿의 경우 <자료형> 생략이 불가능 하기 때문에, 습관적으로 모두 포함하는 것이 좋다. 
						int Add<int> (int num1, int num2){...} 와 같이 함수가 생성된다고 생각하자 
					함수는 호출될 때 마다 생성되는 것이 아니고, 컴파일 때 모두 생성된다.
						즉 컴파일 타임에 손해는 있지만, 실행 시간에는 손해가 없다. 
					이렇게 만들어진 함수를 템플릿 함수 (혹은 생성된 함수: Generated Func) 라고 한다.
					일반 함수와 겹칠 경우에는 일반 함수가 우선적으로 호출된다.
						겹치는 것은 바람직한 구현 방법은 아니다. 
			특수화
				template <class T>
				T Max(T data1, T data2){...}
				template<>
				char* Max<char*>(char* data1, char* data2){...}
				template<>
				const char* Max(const char* data1, const char* data2){...}
					char*과 const char*에 대해 특수화를 한 모습이다. 
					<자료형>은 역시 생략해도 되고 안해도 되지만, 가독성을 위해 해주는 것이 좋다. 

		클래스 템플릿
			함수 템플릿과 정의 방법이 같다.
				멤버함수를 분리하여 정의할 때, template <class T>를 빼먹지 말자
			특수화
				T를 원하는 자료형으로 교체하여 정의한다.
					template <class T>					//클래스 템플릿
					class SoSimple{...};
					template <>									//특수화, T가 사라졌으므로 class T를 생략하였다.
					class SoSimple<int>{...};
				<class T>라는 표현은, 뒤이어 오는 정의에 T라는 템플릿 매개변수가 사용될 것임을 미리 알리는 것이다. 즉 T가 사용되지 않는다면 필요 없다.
				두개 이상의 형에 대해 템플릿이 선언됐을 경우에, 부분 특수화와 전체 특수화 모두 가능하다.
					전체 특수화가 부분 특수화보다 우선시된다.
						template	<class T1, classT2>
							class SoSimple{...};
						template <class T1>												//부분특수화
							class SoSimple<T1, int>{...};
						template <>																//전체특수화
							class SoSimple<double, int>{...};

		템플릿 매개변수에 변수가 오는 경우
			비슷한 유형의 자료형(클래스)를 구분할 필요가 있을 때 사용한다.
					template <class T, int len>
					class SimpleArr{...};
						SimpleArr<int, 9>	arr1;
							SimpleArr<int, 7> arr2;	
				arr1과 arr2는 각각 다른 템플릿 클래스이므로 서로 대입연산할 수 없게 된다.
				len을 생성자를 통해 입력했다면, 두 객체는 대입연산이 가능했을 것이고, 에러방지를 위해 프로그램이 복잡해질 것이다.
				템플릿 클래스는 컴파일 타임에 생성되어야 하므로, len에 상수가 아닌 변수가 오는 것은 불가능 해 보인다.
		
		템플릿 매개변수의 디폴트 값 지정이 가능하다
			template <class T1 = double, class T2, int, int len = 7>

		static 지역변수, 멤버변수
			각각 다른 템플릿 함수는, 독립적인 static 지역변수를 가진다.
			각각 다른 템플릿 클래스는, 독립적인 static 멤버변수를 가진다. 
				static 멤버변수의 초기화도 특수화가 가능하다
					template<>
					long SimpleStaticMem<long>::mem=5;

		템플릿의 파일분리(선언(헤더)와 정의(소스))
			템플릿 클래스, 템플릿 함수는 컴파일 타임에 생성이 된다.
			 즉, 컴파일시 템플릿의 선언 뿐 아니라 정의도 필요하다는 것이다.
			 일반적인 방식으로 헤더만 포함시키면, 소스가 포함되어 있지 않기 때문에 템플릿 클래스(함수)를 컴파일 할 수 없고, 에러가 발생하게 된다.
			해결방법
				헤더와 소스파일을 모두 포함시킨다.
				헤더에 소스와 정의를 모두 포함한다
					확장자를 .hpp와 같이 헤더와 소스를 합친듯한 표현을 사용해도 된다.
					프로그램 파일은 디코딩이 필요한 파일이 아니다. 따라서 직접 포함시킨다면 어떤 확장자를 써도 상관이 없다.
						소스파일의 경우에는 컴파일러가 지원하는 것을 써야하는 것 같다.
							GCC의 경우에는 .c, .cc, .cpp, .c++, .cp, .cxx 등등을 지원한다고 한다. 자세한것은 컴파일러에 대한 공부 필요.
						
*/
/*
	형 변환
		int num = int(3.14)
		int num = (int)3.14
			두 형 변환문은 완전히 일치한다.
*/
// 매개변수에서 arr[] 과 *arr은 완전히 같은 표현인듯 하다. 단지 배열임을 알려주기 위해 []표현을 쓰는듯
// 따라서 전달인자로 전달할 때, arr[10]과 같이 전달할 필요 없이, arr(포인터형식)으로 전달하면 된다.

/*
	입력방식에 따른 속도차이
		scanf, getchar(*), cin 등은 모두 입력 속도가 다르다.
			단순하게 생각해도, 대상이 하나인 getchar, 대상을 지정하는 scanf, 대상에 따라 알아서 오버로딩된 cin을 비교하면 cin이 제일 느리다.
				입력이나 출력이 많아지면 "cin.tie(NULL)과 ios::sync_with_stdio(false)"을 쓰거나 scanf, printf 를 쓰는게 좋다.
			"\n"이 endl보다 훨씬 빠르다 
	cin.tie(NULL)과 sync_with_stdio(false)	
		sync_with_stdio
			ios::sync_with_stdio 와 cin.sync_with_stdio의 차이? -> 같은거같은데
			c의 stdio와 c++의 iostream을 동기화 시켜주는 역할을 한다.
				false를 통해 해제하면, stdio와 iostream의 버퍼를 모두 사용하는 것이 아닌, c++만의 독립적인 버퍼를 사용하게 된다.
					c의 버퍼들과 병행하여 사용할 수 업게 되며(stdio 입출력 사용 불가라는 소린듯), 대신 사용하는 버퍼들이 줄어들어 속도가 빨라진다.
		cin.tie
			cout과 cin은 기본적으로 tie되어 있다.
				cout을 하면 기본적으로 바로 출력(flush)를 하게 된다. 그로인해 출력또한 cin과 cout 순서대로 보인다
					cin.tie(NULL)을 통해 untie하면, cout buffer는 출력(flush) 혹은 버퍼가 모두 찼을때만 비워지게 된다(출력장치에 출력). 그로인해 cin과 cout이 순서대로 보이지 않을 수 있다.
					버퍼를 필요시만 비우기 때문에 속도가 빠르다. 
	
		

https://codecollector.tistory.com/381

백준-입출력속도비교
https://www.acmicpc.net/blog/view/56
https://www.acmicpc.net/blog/view/57

알고스팟 - 언어별 input method 비교
https://algospot.com/forum/read/2496/
백준저지 -  1920번 문제 질문
https://www.acmicpc.net/board/view/9022
cpp reference - sync_with_stdio
http://en.cppreference.com/w/cpp/io/ios_base/sync_with_stdio
stackoverflow - sync_with_stdio, cout.tie등에 대한 질문에 대한 답변
https://stackoverflow.com/questions/31162367/significance-of-ios-basesync-with-stdiofalse-cin-tienull
출처: https://eine.tistory.com/entry/CC-입출력-방법에-따른-속도-정리 [아인스트라세의 SW 블로그]
*/


/*
	입력의 개수를 알 수 없는 경우(미리 정해지지 않은 경우)
	cin.eof()
	https://takeknowledge.tistory.com/20
*/


//vector
/*
	vector
		vector는 배열과 동일하게 작동한다.
			표준에 정의되어 있다.
			배열처럼 원소의 값을 바꾸는 것등 모두 가능하다.
			심지어 포인터도 반환이 가능하다고 한다. iterator를 쓸 뿐 
		vector container
			스택과 비슷한 구조
			push.back, pop.back가 일어난다.
				맨 뒤쪽에서 삽입과 삭제를 한다.
		#include <vector>
		선언
			vector<자료형> var;
				template기반임을 알 수 있다.
			여러 생성자
				vector<int> v;
					비어있는 벡터 생성
				vector<int> v(5);
					기본값(int의 경우 0)으로 초기화된 5개의 원소를 가지는 벡터
				vector<int> v(5,2);
					2로 초기화된 5개의 원소를 가지는 벡터
				vector<int> v2(v1);
					v2는 복사생성자를 통해 v1을 복사해 생성
			연산자
				vector 자체끼리의 대소비교 가능? 기준은?
		멤버함수
			v.assign(5,2)
				2의 값으로 5개의 원소 할당
			v.at(idx)
				idx번의 원소를 참조하며, v[idx]보다 속도는 느리지만, 범위를 점검하므로 안전하다.
			v.front()
				첫번째 원소 참조
			v.back()
				마지막 원소 참조
			v.clear()
				모든 원소를 제거
				메모리는 그대로다
				즉, size는 줄어들지만 capacity는 그대로다.
			v.push_back(7)
				마지막 원소 뒤에 원소 7을 삽입한다.
				capacity가 부족하면 자동으로 확장한다.
					이때 선형으로 확장되는 것이 아니고, 기존메모리 크기의 2배만큼 확장된다.
			v.pop_back()
				마지막 원소를 제거한다.
			v.reserve(n)
				n개의 원소를 저장할 위치를 예약합니다(미리 동적할당)
					capacity를 늘린다는 의미인가?
			v.resize(n)
				컨테이너의 크기를 n으로 변경한다.
				더 커졌을 경우, 새로운범위? 는 default 값으로 초기화한다(int만 0?, 객체의 경우는?)
			v.resize(n,3)
				컨테이너의 크기를 n으로 변경한다.
				더 커졌을 경우, 새로운범위? 는 3으로 초기화한다.
				객체를 넣을 경우, 인자를 전달해 객체의 생성자를 호출하는가? 벡터 생성시에도 확인 필요 
			v.size()
				원소의 개수를 반환
			v.capacity()
				할당된 공간(메모리)의 크기를 반환
			v2.swap(v1)
				v1과 v2의 원소와 capacity를 모두 바꿔준다.
				v1의 capacity를 없애고 싶을때(즉 할당해제하고 싶을때), v2를 capacity가 0인 임시객체로 만들어 스왑을 해주면 된다.
					vector<int>().swap(v1);
			v.insert(2,3,4)
				2번째 위치에 3개의 4값을 삽입합니다.
					뒤에 있는것들은 3만큼 위치가 밀리게된다.
			v.insert(2,3)
				2번째 위치에 3값을 삽입합니다.
				삽입한곳(2)의 iterator을 반환합니다.
			v.erase(iter)
				iter가 가리키는 원소를 제거합니다.
				size만 줄어들고 capacity는 그대로입니다.
			v.erase(start, end)
				[start,end) 범위의 인자를 삭제한다.
					[2,5)면 2~4의 원소를 삭제한다는 것이다
				size만 줄어들고 capacity는 그대로입니다.
			v.empty()
				vector의 size가 0이면 true를 반환한다.
				capacity와는 관계가 없다.
			iterator
				v.begin()
					첫번째 원소를 가리킴
				v.end()
					마지막 원소의 다음을 가리킴
				v.rbegin()
					reverse begin(거꾸로 해서 첫번째 원소, 즉 마지막 원소? 를 가리킴)
		공간 할당 (capacity)
			capacity는 선형으로 커지지 않고, 기존 크기의 2배수로 증가한다.
				즉 처음에 크기를 5로 초기화 시킨 vector는, 자동으로 확장될 시 capacity가 10이된다.
			capacity를 증가시키면, 메모리를 이어서 할당하는 것이 아니고 새롭게 메모리를 할당하여 원소들을 전부 복사하는 형태이다
				기존에는 복사비용이 컸지만, std::move 라는 것이 도입되며 메모리 증가에 대한 비용(복사비용)이 상당히 작아졌다.
		멤버형식
			iterator - 반복자형식
				vector<int>::iterator iter;
				vector에서의 포인터를 나타내는듯 하다.
					for(iter=v.begin();iter!=v.end();iter++){...}
				iterator가 무효화 되는 경우(더 알아보자 )
					vector의 capacity를 변경하는 모든 삽입 작업
					push_back: 해당 vector를 가리키는 모든 반복자가 무효화된다.
						capacity가 변경될 때문 무효화 될 수는 있다. 그러나 조건부로 무효화 되는 것 자체가 코드에는 넣으면 안 된다는 뜻이다. 
					erase: 삭제된 요소의 뒤에있는 요소를 가리키는 반복자들은 무효화된다.
			reverse_iterator - 역 반복자 형식
			value_type - 원소의 형식
			size_type - 원소의 개수의 형식 
				반복문에서 int i=0; 을 사용하는 것처럼, vector는 size_type i = 0; 을 사용한다.
					int를 사용해도 결과에 차이는 없는 듯 하다.
*/

/*
	ASCII CODE를 int로 바꾸는 법
		ASCII code에서 숫자는 형적으로 증가한다
		'0'=x 라면, '7' = x+7이다
		따라서 '(char형 숫자)'-'0'=(int 형 숫자) 와 같이 int형으로 바꿀 수 있다.
*/

/*
	전역변수, 지역변수로 선언할 수 있는 배열의 크기는 한계가 있다.
	크기의 한계는 컴파일러, 하드웨어에 따라 최대 개수가 다르다.
	필요한 크기가 크다면 동적할당을 이용하자.
	꼭 큰 배열이 필요한 것이 아니라면 사용을 지양하자.
*/

//c++ string class

//assert : 에러시 종료

//dev에 있던 것들 정리 