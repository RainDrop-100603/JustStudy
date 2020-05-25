//#define _CRT_SECURE_NO_WARNINGS

#ifndef __QUESTIONSOL_H__
#define __QUESTIONSOL_H__

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>


using namespace std;


//상수 선언
enum solConstant{
	SOL_NAMELENGTH=100,
	RISK_A=30,
	RISK_B=20,
	RISK_C=10
};

//Class 선언
class Calculator {
private:
	int Cadd;
	int Cmin;
	int Cmul;
	int Cdiv;
public:
	void Init();
	double Add(double a, double b);
	double Div(double a, double b);
	double Min(double a, double b);
	double Mul(double a, double b);
	void ShowOpCount();
};
class Printer {
private:
	char CurrentString[1000];
public:
	void SetString(const char* strings);
	void ShowString();
};
class FruitSeller {
private:
	int APPLE_PRICE;
	int numOfApples;
	int myMoney;
public:
	void InitMembers(int price, int num, int money);
	int SaleApples(int money);
	void ShowSalesResults() const;
};
class FruitBuyer {
	int myMoney;
	int numOfApples;
public:
	void InitMembers(int money);
	void BuyApples(FruitSeller& seller, int money);
	void ShowBuyResults() const;
};
class Point {
	int xpos, ypos;
public:
	Point(int x, int y);
	void ShowPointInfo() const;
};
class Circle {
	Point centerOfCircle;
	int radius;
public:
	Circle(int x, int y, int rad);
	void ShowCircleInfo() const;
};
class Ring {
	Circle circle1;
	Circle circle2;
public:
	Ring(int x1, int y1, int rad1, int x2, int y2, int rad2);
	void ShowRingInfo() const;
};
class NameCard {
	char* name;
	char* company;
	char* phoneNum;
	int rank;
public:
	NameCard(const char* nam, const char* cmpNam, const char* phNum, int rnk);
	NameCard(const NameCard& copy);
	void ShowNameCardnfo();
	~NameCard();
};
class Car {
private:
	int gasolineGauge;
public:
	Car(int gasGauge);
	Car();
	int GetGasGauge();
};
class HybridCar :public Car {
private:
	int electricGauge;
public:
	HybridCar(int gasGauge, int eleGauge);
	HybridCar();
	int GetElectGauge();
};
class HybridWaterCar :public HybridCar {
	int waterGauge;
public:
	HybridWaterCar(int gasGauge, int eleGauge, int watGauge);
	HybridWaterCar();
	void ShowCurrentGauge();
};
class MyFriendInfo {
	char* name;
	int age;
public:
	MyFriendInfo();
	MyFriendInfo(char* name, int age);
	void ShowMyFriendInfo();
	~MyFriendInfo();
};
class MyFriendDetailInfo : public MyFriendInfo {
	char* addr;
	char* phone;
public:
	MyFriendDetailInfo();
	MyFriendDetailInfo(char* name, int age, char* addr, char* phone);
	void ShowMyFriendDetailInfo();
	~MyFriendDetailInfo();
};
class Rectangle{
	int xlength;
	int ylength;
public:
	Rectangle(int xlength, int ylength);
	void ShowAreaInfo();
};
class Square : public Rectangle{
public:
	Square(int xlength);
};
class Book{
	char* title;
	char* isbn;
	int price;
public:
	Book(char* title, char* isbn, int price);
	void ShowBookInfo();
	~Book();
	Book(const Book& book);
	Book& operator=(const Book& book);
};
class EBook : public Book{
	char* DRMKey;
public:
	EBook(char* title, char* isbn, int price, char* DRMKey);
	void ShowEBookInfo();
	~EBook();
	EBook(const EBook& ebook);
	EBook& operator=(const EBook& ebook);
};
class Employee{
	char name[SOL_NAMELENGTH];
public:
	Employee(char* name);
	void ShowYourName() const;
	virtual int GetPay() const = 0;
	virtual void ShowSalaryInfo() const = 0;
};
class PermanentWorker : public Employee{
	int baseSalary;
public:
	PermanentWorker(char* name, int baseSalary);
	virtual int GetPay() const;
	virtual void ShowSalaryInfo() const;
};
class TemporaryWorker : public Employee{
	int workTime;
	int payPerHour;
public:
	TemporaryWorker(char* name, int payPerHour);
	void AddWorkTime(int time);
	virtual int GetPay() const;
	virtual void ShowSalaryInfo() const;
};
class SalesWorker : public PermanentWorker{
	int salesResult;
	double bonusRatio;
public:
	SalesWorker(char *name, int baseSalary, double bonusRatio);
	void AddSalesResult(int sales);
	virtual int GetPay() const;
	virtual void ShowSalaryInfo() const;
};
class ForeignSalesWorker : public SalesWorker{
	int riskPayRatio;
public:
	ForeignSalesWorker(char* name, int baseSalary, double bonusRatio,int riskPayRatio );
	virtual int GetPay() const;
	virtual void ShowSalaryInfo() const;
};
class EmployeeHandler{
	Employee* empList[50];
	int empNum;
public:
	EmployeeHandler();
	void AddEmpList(Employee* emp);
	void ShowAllSalaryInfo() const;
	void ShowTotalSalary() const;
	~EmployeeHandler();
};
class PointOL{
private:
	int xpos, ypos;
public:
	PointOL(int xpos=0, int ypos=0);
	void ShowPosition() const;
	friend PointOL operator+(const PointOL& point1, const PointOL& point2);
	friend PointOL operator-(const PointOL& point1, const PointOL& point2);
	PointOL& operator+=(const PointOL& point);
	PointOL& operator-=(const PointOL& point);
	friend bool operator==(const PointOL& point1, const PointOL& point2);
	friend bool operator!=(const PointOL& point1, const PointOL& point2);
	PointOL operator-();
	friend PointOL operator~(const PointOL& point);
	friend ostream& operator<<(ostream& os,const PointOL& pos);
	friend istream& operator>>(istream& os,const PointOL& pos);
	friend ostream& operator<<(ostream& os,const PointOL* pos);
	void SetPointOL(int xpos, int ypos);
};

class Gun{
private:
	int bullet;
public:
	Gun(int bnum) :bullet(bnum){}
	void Shot(){
		cout<<"BBANG!"<<endl;
		bullet--;
	} 
	int BulletNum() const;
};

class Police{
private:
	int handcuffs;
	Gun* pistol;
public:
	Police(int bnum=0, int bcuff=0)
		:handcuffs(bcuff){
			if(bnum>0){
				pistol=new Gun(bnum);
			}else{
				pistol=NULL;
			}
	}		
	void PutHandCuff(){
		cout<<"SNAP!"<<endl;
		handcuffs--;
	}
	void shot(){
		if(pistol==NULL){
			cout<<"HUT BBANG!"<<endl;
		}else{
			pistol->Shot();
		}
	}		
	~Police(){
		cout<<"called ~Police"<<endl;
		delete pistol;
	}		
	Police(Police& police);
	Police& operator=(const Police& police);
};

typedef PointOL* POINT_PTR;
class BoundCheckPointPtrArray{
	POINT_PTR* arr;
	int arrlen;
	BoundCheckPointPtrArray(const BoundCheckPointPtrArray&){}
	BoundCheckPointPtrArray& operator=(const BoundCheckPointPtrArray&){}
public:
	BoundCheckPointPtrArray(int len);
	POINT_PTR& operator[] (int idx);
	POINT_PTR operator[] (int idx) const;
	int GetArrLen() const;
	~BoundCheckPointPtrArray();
};
class BoundCheck2DIntArray{
	PointOL** matrix2D;	//matrix2D->(PointOL* 포인터 배열)행->(PointOL 배열)열 
	const int row,column; //생성된 행렬의 크기는 바뀌지 않는다.
	int tempRow,tempColumn;	//-1일때는 행지정이 안되어 있을 때 
	int sequence;	//index 찾을 때: 
										//0: 기본상태, index를 불러올 시 tempRow에 행을 저장한다. 1로 증가
										//1: 행 지정된 상태, index를 불러올 시 tempRow에 열을 저장한다. 2로 증가
										//2: 행, 열 모두 지정된 상태. index룰 불러올 시 다시 1로 초기화 (다시 불러오면서 행 지정하므로)
									//출력시: 2 상태일 때만 출력 후 0으로 초기화 
	BoundCheck2DIntArray(const BoundCheck2DIntArray&)
	:	row(0),column(0){}	//const int를 초기화 시켜야 한다.
public:
	BoundCheck2DIntArray(int row, int column);
	~BoundCheck2DIntArray();
	BoundCheck2DIntArray& operator=(const int num);	//matrix[][]에 대입을 하기 위해서 필요하다.
	BoundCheck2DIntArray& operator=(const PointOL& pos);
	// const BoundCheck2DIntArray& operator[](const int row);		//행 정보를 업데이트
	// PointOL& operator[](const int column) const;	//업데이트한 행 정보를 기반으로 위치 찾아 포인트 반환 
	// 위의 두 줄은 참조는 가능하지만 저장이 안된다.
	BoundCheck2DIntArray& operator[](const int idx);	//temp row를 통해 
	friend ostream& operator<<(ostream &os, const BoundCheck2DIntArray& matrix);	//arr[][]을 바로 cout으로 출력하기 위해 필요 
};

class String{
	char* string;
public:
	String(const char* str);
	String(const String& str);
	String& operator=(const String& str);
	~String();
	String operator+(const String& str) const;
	String& operator+=(const String& str);
	bool operator==(const String& str) const;
	friend String& operator<<(ostream& os,const String& str);
	friend String& operator>>(istream& is,const String& str);
};

//Part1
void Question01_1(void);
void Question01_2(void);
void Question01_3(void);
void Question01_4(void);
void Question02_1(void);
void Question02_2(void);
void Question02_3(void);	// 어려웠으니 주석을 잘 읽어보도록 하자. 다만 참조자를 이용해 함수 내부에서 동적할당하는 것은 바람직하지 않다.(delete가 헷갈린다) -> 이제 잘 모르겠다 
void Question02_4(void);

//Part2
void Question03_1(void);
void Question03_2(void);
void Question04_1(void);
void Question04_2(void);
void Question04_3(void);
void Question05_1(void);

//Part3
void Question07_1(void);
void Question07_2(void);
void Question08_1(void);

//Part4
void Question10_1(void);
void Question10_2(void);
void Question10_3(void);
void Question11_1(void);
void Question11_2(void);
void matrixProblem(void);

#endif // !__QUESTIONSOL_H__


