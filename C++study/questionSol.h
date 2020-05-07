#ifndef __QUESTIONSOL_H__
#define __QUESTIONSOL_H__

#include <iostream>
#include <cstring>
#include <ctime>
#include <cstdlib>

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
	int GetGasGauge();
};
class HybridCar :public Car {
private:
	int electricGauge;
public:
	HybridCar(int gasGauge, int eleGauge);
	int GetElectGauge();
};
class HybridWaterCar :public HybridCar {
	int waterGauge;
public:
	HybridWaterCar(int gasGauge, int eleGauge, int watGauge);
	void ShowCurrentGauge();
};

//Part1
void Question01_1(void);
void Question01_2(void);
void Question01_3(void);
void Question01_4(void);
void Question02_1(void);
void Question02_2(void);
void Question02_3(void);	// 어려웠으니 주석을 잘 읽어보도록 하자. 다만 참조자를 이용해 함수 내부에서 동적할당하는 것은 바람직하지 않다.(delete가 헷갈린다)
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

#endif // !__QUESTIONSOL_H__


