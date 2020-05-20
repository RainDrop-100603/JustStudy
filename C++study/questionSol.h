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
	PointOL(int xpos, int ypos);
	void ShowPosition() const;
	friend PointOL operator+(const PointOL& point1, const PointOL& point2);
	friend PointOL operator-(const PointOL& point1, const PointOL& point2);
	PointOL& operator+=(const PointOL& point);
	PointOL& operator-=(const PointOL& point);
	friend bool operator==(const PointOL& point1, const PointOL& point2);
	friend bool operator!=(const PointOL& point1, const PointOL& point2);
	PointOL operator-();
	friend PointOL operator~(const PointOL& point);
	friend ostream& operator<<(ostream& os,PointOL& pos);
	friend istream& operator>>(istream& os,PointOL& pos);
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

#endif // !__QUESTIONSOL_H__


