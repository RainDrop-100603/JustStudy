#include "questionSol.h"

//귀찮아서 선언
char* getString(){
	//띄어쓰기는 받을 수 없다.
	char buffer[100];
	cin>>buffer;
	char* str = new char[strlen(buffer)+1];
	strcpy(str,buffer);
	return str;
}

//특정 solution에서 필요한 전역함수, 변수 선언부
namespace Part1 {
	void swap(int* num1, int* num2) {
		int temp;
		temp = *num1;
		*num1 = *num2;
		*num2 = temp;
	}
	void swap(char* char1, char* char2) {
		char temp;
		temp = *char1;
		*char1 = *char2;
		*char2 = temp;
	}
	void swap(double* num1, double* num2) {
		double temp;
		temp = *num1;
		*num1 = *num2;
		*num2 = temp;
	}
	int BoxVolume(int length, int width, int height) {
		return length * height * width;
	}
	int BoxVolume(int length, int width) {
		return length * width;
	}
	int BoxVolume(int length) {
		return length;
	}
	void RefFunc(int &num1, int&num2){
		cout << "num1= " << num1 << endl;
		cout << "num2= " << num2 << endl;
		num1++;
		num2 = (-num2);
		cout << "num1은 1 증가하고 num2는 부호가 바뀌었다." << endl;
		cout << "num1= " << num1 << endl;
		cout << "num2= " << num2 << endl;
	}
	void SwapPointer(int* (&ptr1), int* (&ptr2)) {
		cout << "Before Swap		" << "*ptr1: " << *ptr1 << "		*ptr2: " << *ptr2 << endl;
		int* temp = ptr1;
		ptr1 = ptr2;
		ptr2 = temp;
		cout << "After Swap		" << "*ptr1: " << *ptr1 << "		*ptr2: " << *ptr2 << endl;
	}
	typedef struct __Point {
		int xpos;
		int ypos;
	}Point;
	Point& PntAdder(const Point& p1, const Point& p2) {
		Point* exam = new Point;
		exam->xpos = p1.xpos + p2.xpos;
		exam->ypos = p1.ypos + p2.ypos;
		return *exam;
	}
}
namespace Part2 {
	struct Point {
		int xpos = 0;
		int ypos = 0;
		void MovePos(int x, int y) {
			xpos += x;
			ypos += y;
		}
		void AddPoint(const Point& pos) {
			xpos += pos.xpos;
			ypos += pos.ypos;
		}
		void ShowPosition() {
			cout << "(" << xpos << ", " << ypos << ")" << endl;
		}
	};
	namespace COMP_POS {
		enum {
			CLERK, SENIOR, ASSIST, MANAGER
		};
		void PosTrans(int pos) {
			switch (pos) {
			case CLERK:
				cout << "사원" << endl;
				return;
			case SENIOR:
				cout << "주임" << endl;
				return;
			case ASSIST:
				cout << "대리" << endl;
				return;
			case MANAGER:
				cout << "과장" << endl;
				return;
			default:
				cout << "잘못된 직급이 저장되었습니다." << endl;
			}
		}
	}
}

//Class 멤버함수
void Calculator::Init() {
	Cadd = 0;
	Cmin = 0;
	Cdiv = 0;
	Cmul = 0;
}
double Calculator::Add(double a, double b) {
	Cadd += 1;
	return a + b;
}
double Calculator::Min(double a, double b) {
	Cmin += 1;
	return a - b;
}
double Calculator::Mul(double a, double b) {
	Cmul += 1;
	return a * b;
}
double Calculator::Div(double a, double b) {
	Cdiv += 1;
	return a / b;
}
void Calculator::ShowOpCount() {
	cout << "덧셈: " << Cadd << "  뺄셈: " << Cmin << "  곱셈: " << Cmul << "  나눗셈: " << Cdiv << endl;
}
void Printer::SetString(const char* strings) {
	//strcpy_s(CurrentString, sizeof(CurrentString), strings);
    strcpy(CurrentString, strings);
}
void Printer::ShowString() {
	cout << CurrentString << endl;
}
void FruitSeller::InitMembers(int price, int num, int money) {
	APPLE_PRICE = price;
	numOfApples = num;
	myMoney = money;
}
int FruitSeller::SaleApples(int money) {
	myMoney += money;
	int num = money / 1000;
	numOfApples -= num;
	return num;
}
void FruitSeller::ShowSalesResults() const {
	cout << "판매 수익: " << myMoney << endl;
	cout << "남은 사과: " << numOfApples << endl << endl;
}
void FruitBuyer::InitMembers(int money) {
	myMoney = money;
	numOfApples = 0;
}
void FruitBuyer::BuyApples(FruitSeller& seller, int money) {
	if (money < 0) {
		cout << "0원 이상 입력해 주십시오" << endl;
		return;
	}
	int num = money / 1000;
	if (money != num * 1000) {
		cout << "1000원 단위로 입력해 주십시오" << endl;
		return;
	}
	if (myMoney < money) {
		cout << "잔액이 " << myMoney << "원 입니다. " << num << "개의 사과를 살 수 없습니다." << endl;
		return;
	}
	seller.SaleApples(money);
	myMoney -= money;
	numOfApples += num;
}
void FruitBuyer::ShowBuyResults() const {
	cout << "현재 잔액: " << myMoney << endl;
	cout << "사과 개수: " << numOfApples << endl << endl;
}
Point::Point(int x, int y): xpos(x),ypos(y){}
void Point::ShowPointInfo() const {
	cout << "point: (" << xpos << "," << ypos << ")" << endl;
}
Circle::Circle(int x, int y, int rad):centerOfCircle(x,y),radius(rad){}
void Circle::ShowCircleInfo() const {
	centerOfCircle.ShowPointInfo();
	cout << "radius: " << radius << endl;
}
Ring::Ring(int x1, int y1, int rad1, int x2, int y2, int rad2): circle1(x1,y1,rad1),circle2(x2,y2,rad2){}
void Ring::ShowRingInfo() const {
	cout << "Inner Circle Info..." << endl;
	circle1.ShowCircleInfo();
	cout << "Outer Circle Info..." << endl;
	circle2.ShowCircleInfo();
}
NameCard::NameCard(const char* nam, const char* cmpNam, const char* phNum, int rnk)
	: rank(rnk)
{
	int len;
	len = strlen(nam) + 1;
	name = new char[len];
	//	strcpy_s(name, len, nam);
	strcpy(name, nam);

	len = strlen(cmpNam) + 1;
	company = new char[len];
	//	strcpy_s(company, len, cmpNam);
	strcpy(company, cmpNam);

	len = strlen(phNum) + 1;
	phoneNum = new char[len];
	//	strcpy_s(phoneNum, len, phNum);
	strcpy(phoneNum, phNum);
}
NameCard::NameCard(const NameCard& copy)
	: rank(copy.rank)
{
	name = new char[strlen(copy.name) + 1];
	strcpy(name, copy.name);

	company = new char[strlen(copy.company) + 1];
	strcpy(company, copy.company);

	phoneNum = new char[strlen(copy.phoneNum) + 1];
	strcpy(phoneNum, copy.phoneNum);
}
void NameCard::ShowNameCardnfo() {
	cout << "이름: " << name << endl;
	cout << "회사: " << company << endl;
	cout << "전화번호: " << phoneNum << endl;
	cout << "직급: ";
	Part2::COMP_POS::PosTrans(rank);
	cout << endl;
}
NameCard::~NameCard() {
	delete[] name;
	delete[] company;
	delete[] phoneNum;
}
int Car::GetGasGauge() {
	return gasolineGauge;
}
Car::Car()
	:gasolineGauge(-1){}
Car::Car(int gasGauge)
	:gasolineGauge(gasGauge){}
int HybridCar::GetElectGauge() {
	return electricGauge;
}
HybridCar::HybridCar()
	:electricGauge(-1){}
HybridCar::HybridCar(int gasGauge, int eleGauge)
	:Car(gasGauge),electricGauge(eleGauge){}
void HybridWaterCar::ShowCurrentGauge() {
	cout << "잔여 가솔린: " << GetGasGauge() << endl;
	cout << "잔여 전기량: " << GetElectGauge() << endl;
	cout << "잔여 워터량: " << waterGauge << endl;
}
HybridWaterCar::HybridWaterCar()
	:waterGauge(-1){}
HybridWaterCar::HybridWaterCar(int gasGauge, int eleGauge, int watGauge)
	:HybridCar(gasGauge,eleGauge),waterGauge(watGauge){}
MyFriendInfo::MyFriendInfo()
	:name(NULL), age(-1){}
MyFriendInfo::MyFriendInfo(char* name, int age)
	:age(age)
	{
		this->name = new char[strlen(name)+1];
		strcpy(this->name, name);
	}
void MyFriendInfo::ShowMyFriendInfo(){
	cout<<"이름: "<<name<<endl;
	cout<<"나이: "<<age<<endl;
}
MyFriendInfo::~MyFriendInfo(){
	delete[] name;
}
MyFriendDetailInfo::MyFriendDetailInfo()
	:addr(NULL), phone(NULL){}
MyFriendDetailInfo::MyFriendDetailInfo(char* name, int age, char* addr, char* phone)
	:MyFriendInfo(name, age)
	{
		this->addr = new char[strlen(addr)+1];
		strcpy(this->addr, addr);
		this->phone = new char[strlen(phone)+1];
		strcpy(this->phone, phone);
	}
void MyFriendDetailInfo::ShowMyFriendDetailInfo(){
	ShowMyFriendInfo();
	cout<<"주소: "<<addr<<endl;
	cout<<"전화: "<<phone<<endl<<endl;
}
MyFriendDetailInfo::~MyFriendDetailInfo(){
	delete[] addr;
	delete[] phone;
}
Rectangle::Rectangle(int xlength=-1, int ylength=-1)
	:xlength(xlength), ylength(ylength){}
void Rectangle::ShowAreaInfo(){
	cout<<"면적: "<<xlength * ylength <<endl;
}
Square::Square(int xlength)
	:Rectangle(xlength,xlength){}

Book::Book(char* title, char* isbn, int price)
	:price(price){
		this->title=new char[strlen(title)+1];
		strcpy(this->title,title);
		this->isbn=new char[strlen(isbn)+1];
		strcpy(this->isbn,isbn);
	}
void Book::ShowBookInfo(){
	cout<<"title: "<<title<<endl;
	cout<<"isbn: "<<isbn<<endl;
	cout<<"price: "<<price<<endl;
}
Book::~Book(){
	delete[] title;
	delete[] isbn;
	cout<<"called Book destructor"<<endl;
}
EBook::EBook(char* title, char* isbn, int price,char* DRMKey)
	:Book(title,isbn,price){
		this->DRMKey=new char[strlen(DRMKey)+1];
		strcpy(this->DRMKey,DRMKey);
	}
void EBook::ShowEBookInfo(){
	ShowBookInfo();
	cout<<"DRMKey: "<<DRMKey<<endl;
}
EBook::~EBook(){
	delete[] DRMKey;
	cout<<"called EBook destructor"<<endl;
}

Employee::Employee(char *name){
	strcpy(this->name,name);
}
void Employee::ShowYourName() const{
	cout<<"Name: "<<name<<endl;
}
PermanentWorker::PermanentWorker(char* name, int baseSalary)
	:Employee(name),baseSalary(baseSalary){}
int PermanentWorker::GetPay() const{
	return baseSalary;
}
void PermanentWorker::ShowSalaryInfo() const{
	ShowYourName();
	cout<<"Salary: "<<GetPay()<<endl;
}
TemporaryWorker::TemporaryWorker(char* name, int payPerHour)
	:Employee(name), workTime(0), payPerHour(payPerHour){}
void TemporaryWorker::AddWorkTime(int time){
	workTime+=time;
}
int TemporaryWorker::GetPay() const{
	return payPerHour*workTime;
}
void TemporaryWorker::ShowSalaryInfo() const{
	ShowYourName();
	cout<<"Salary: "<<GetPay()<<endl;
}
SalesWorker::SalesWorker(char* name, int baseSalary, double bonusRatio)
	:PermanentWorker(name, baseSalary), bonusRatio(bonusRatio){}
void SalesWorker::AddSalesResult(int sales){
	salesResult+=sales;
}
int SalesWorker::GetPay() const{
	return PermanentWorker::GetPay()+salesResult*bonusRatio;
}
void SalesWorker::ShowSalaryInfo() const{
	ShowYourName();
	cout<<"Salary: "<<GetPay()<<endl;
}
ForeignSalesWorker::ForeignSalesWorker(char* name, int baseSalary, double bonusRatio, int riskPayRatio)
	:SalesWorker(name, baseSalary, bonusRatio), riskPayRatio(riskPayRatio){}
int ForeignSalesWorker::GetPay() const{
	//return SalesWorker::GetPay()+SalesWorker::GetPay()*riskPayRatio/100;
	return SalesWorker::GetPay()*(1+riskPayRatio/100.0);
}
void ForeignSalesWorker::ShowSalaryInfo() const{
	ShowYourName();
	cout<<"Salary: "<<SalesWorker::GetPay()<<endl;
	cout<<"Risk Pay: "<<SalesWorker::GetPay()*riskPayRatio/100<<endl;
	cout<<"TotalSalary: "<<GetPay()<<endl;
}
EmployeeHandler::EmployeeHandler()
	:empNum(0){}
void EmployeeHandler::AddEmpList(Employee* emp){
	empList[empNum]=emp;
	empNum++;
}
void EmployeeHandler::ShowAllSalaryInfo() const{
	for(int i=0;i<empNum;i++){
		empList[i]->ShowSalaryInfo();
		cout<<endl;
	}
}
void EmployeeHandler::ShowTotalSalary() const{
	int sum=0;
	for(int i=0;i<empNum;i++){
		sum+=empList[i]->GetPay();
	}
	cout<<"TotalSalary: "<<sum<<endl;
}
EmployeeHandler::~EmployeeHandler(){
	for (int i=0;i<empNum;i++){
		delete empList[i];
	}
}

PointOL::PointOL(int xpos, int ypos)
	:xpos(xpos),ypos(ypos){}
void PointOL::ShowPosition() const{
	cout<<"["<<xpos<<", "<<ypos<<"]"<<endl;
}	
PointOL& PointOL::operator+=(const PointOL& point){
	xpos+=point.xpos;
	ypos+=point.ypos;
	return *this;
}
PointOL& PointOL::operator-=(const PointOL& point){
	xpos-=point.xpos;
	ypos-=point.ypos;
	return *this;
}
PointOL operator+(const PointOL& point1, const PointOL& point2){
	PointOL point3;
	point3.xpos=point1.xpos+point2.xpos;
	point3.ypos=point1.ypos+point2.ypos;
	return point3;
}
PointOL operator-(const PointOL& point1, const PointOL& point2){
	PointOL point3;
	point3.xpos=point1.xpos-point2.xpos;
	point3.ypos=point1.ypos-point2.ypos;
	return point3;
}
bool operator==(const PointOL& point1, const PointOL& point2){
	if((point1.xpos!=point2.xpos)||(point1.ypos!=point2.ypos)){
		return false;
	}else{
		return true;
	}
}
bool operator!=(const PointOL& point1, const PointOL& point2){
	return !operator==(point1,point2);
}
PointOL PointOL::operator-(){
	PointOL point(-xpos,-ypos);
	return point;
}
PointOL operator~(const PointOL& point){
	PointOL pos(point.ypos, point.xpos);
	return pos;
}
ostream& operator<<(ostream& os,const PointOL& pos){
	 cout<<'['<<pos.xpos<<", "<<pos.ypos<<']';
	 return os;
}
istream& operator>>(istream& is,const PointOL& pos){
	// int buffer;
	// cin>>buffer;
	// pos.xpos=buffer;
	// cin>>buffer;
	// pos.ypos=buffer;
	is>>pos.xpos>>pos.ypos;
	return is;
}
int Gun::BulletNum() const{
	return bullet;	
}
Police::Police(Police& police)
	:handcuffs(police.handcuffs){
		if(police.pistol!=NULL){
			// pistol=new Gun(police.pistol->BulletNum());
			pistol=new Gun(*(police.pistol));	// Gun의 디폴트 복사생성자 호출/ 얕은 복사여도 상관 없기 때문에
		}else{
			pistol=NULL;
		}
	
		cout<<"복사생성자"<<endl;
	}
Police& Police::operator=(const Police& police){
	handcuffs=police.handcuffs;
	if(police.pistol!=NULL){
		delete pistol;
		// pistol=new Gun(police.pistol->BulletNum());
		pistol=new Gun(*(police.pistol));	// Gun의 디폴트 복사생성자 호출/ 얕은 복사여도 상관 없기 때문에
	}
	cout<<"operator="<<endl;
	return *this;
}
Book::Book(const Book& book)
	:price(book.price){
	title=new char[strlen(book.title)+1];
	isbn= new char[strlen(book.isbn)+1];
	strcpy(title,book.title);
	strcpy(isbn, book.isbn);
}
Book& Book::operator=(const Book& book){
	delete[] title;
	delete[] isbn;
	title=new char[strlen(book.title)+1];
	isbn= new char[strlen(book.isbn)+1];
	strcpy(title,book.title);
	strcpy(isbn, book.isbn);
	price=book.price;
	return *this;
}
EBook::EBook(const EBook& ebook)
	:Book(ebook){
	DRMKey=new char[strlen(ebook.DRMKey)+1];
	strcpy(DRMKey,ebook.DRMKey);
}
EBook& EBook::operator=(const EBook& ebook){
	delete[] DRMKey;
	DRMKey=new char[strlen(ebook.DRMKey)+1];
	strcpy(DRMKey,ebook.DRMKey);
	Book::operator=(ebook);
	return *this;
}
BoundCheckPointPtrArray::BoundCheckPointPtrArray(int len)
	:arrlen(len){
		arr=new POINT_PTR[len];
	}
POINT_PTR& BoundCheckPointPtrArray::operator[](int idx){
	if(idx<0||idx>=arrlen){
		cout<<"Array index out of bound exception"<<endl;
		exit(1);
	}
	return arr[idx];
}
POINT_PTR BoundCheckPointPtrArray::operator[](int idx) const{
	if(idx<0||idx>=arrlen){
		cout<<"Array index out of bound exception"<<endl;
		exit(1);
	}
	return arr[idx];
}
int BoundCheckPointPtrArray::GetArrLen() const{
	return arrlen;
}
BoundCheckPointPtrArray::~BoundCheckPointPtrArray(){
	for(int i=0;i<arrlen;i++){
		delete arr[i];
	}
	delete[] arr;
}
ostream& operator<<(ostream& os, const PointOL* pos){
	cout<<'['<<pos->xpos<<", "<<pos->ypos<<']'<<endl;
	return os;
}
BoundCheck2DIntArray::BoundCheck2DIntArray(int row, int column)
	:row(row), column(column), tempRow(-1), tempColumn(-1), sequence(0){
		matrix2D= new PointOL*[row];
		for(int i=0;i<row;i++){
			matrix2D[i]=new PointOL[column];
		}
	}
BoundCheck2DIntArray::~BoundCheck2DIntArray(){
	for(int i=0;i<row;i++){
		delete[] matrix2D[i];
	}
	delete[] matrix2D;
}
BoundCheck2DIntArray& BoundCheck2DIntArray::operator[](const int idx){
	if(sequence==1){//idx=column
		tempColumn=idx;
		sequence++;
		return *this;
	}
	// else if(sequence==2){
	// 	cout<<tempColumn<<"행 "<<tempRow<<"열 지정이 취소되었습니다."<<endl;
	// 	cout<<idx<<"행 을 지정하였습니다"<<endl;
	// }
	tempRow=idx;	//idx=row
	sequence=1;
	return *this;
}
void PointOL::SetPointOL(int xpos, int ypos){
	this->xpos=xpos;
	this->ypos=ypos;
}
BoundCheck2DIntArray& BoundCheck2DIntArray::operator=(const int num){
	if(sequence==2){
		sequence=0;
		matrix2D[tempRow][tempColumn].SetPointOL(num,num);
	}
	return *this;
}
BoundCheck2DIntArray& BoundCheck2DIntArray::operator=(const PointOL& pos){
	if(sequence==2){
		sequence=0;
		matrix2D[tempRow][tempColumn]=pos;
	}
	return *this;
}
ostream& operator<<(ostream &os, const BoundCheck2DIntArray& matrix){
	if(matrix.sequence!=2){
		cout<<"행 열 지정이 완료되지 않았습니다"<<endl;
	}
	 cout<<matrix.matrix2D[matrix.tempRow][matrix.tempColumn];	//Pointer -> (주소)(Pointer+tempRow) ->(객체)(Pointer + tempRow)[tempColumn]
	 return os;
}
SString::SString()
	:string(NULL){}
SString::SString(const char* str){
	string=new char[strlen(str)+1];
	strcpy(string,str);
}
SString::SString(const SString& str){
	string=new char[strlen(str.string)+1];
	strcpy(string,str.string);
}
SString& SString::operator=(const SString& str){
	delete[] string;
	string=new char[strlen(str.string)+1];
	strcpy(string,str.string);
	return *this;
}
SString::~SString(){
	delete[] string;
}
SString SString::operator+(const SString& str) const{
	char* tempstr = new char[strlen(string)+strlen(str.string)+1];
	strcpy(tempstr,string);
	strcat(tempstr,str.string);
	SString tempSTR(tempstr);
	delete[] tempstr;
	return tempSTR;
}
SString& SString::operator+=(const SString& str){
	int length = strlen(string)+strlen(str.string)+1;
	char* tempstr = new char[length];
	strcpy(tempstr,string);
	strcat(tempstr,str.string);
	delete[] string;
	// string=new char[length];
	// strcpy(string,tempstr);
	string = tempstr;
	return *this;

	//*this=*this+str;
	//return *this; //간단하게 표현 가능 
}
bool SString::operator==(const SString& str) const{
	// if(strcmp(string,str.string)==0){
	// 	return true;
	// }else{
	// 	return false;
	// }
	return strcmp(string, str.string) ? false : true;
}
ostream& operator<<(ostream& os, const SString& str){
	cout<<str.string;
	//os<<str.string 과 같다 
	return os;
}
istream& operator>>(istream& is, SString& str){
	delete[] str.string;
	char temp[STRLENGTH];
	cin>>temp;
	str.string=new char[strlen(temp)+1];
	strcpy(str.string,temp);
	return is;
}
// class String{
// 	char* string;
// public:
// 	String(const char* str);
// 	String(const String& str);
// 	String& operator=(const String& str);
// 	~String();
// 	String operator+(const String& str) const;
// 	String& operator+=(const String& str);
// 	bool operator==(const String& str) const;
// 	friend String& operator<<(ostream& os,const String& str);
// 	friend String& operator>>(istream& is,const String& str);
// };


//Part1
void Question01_1(void) {
	//문제1
	cout << "문제 1" << endl;
	int num[5] = { 0 };
	int sum = 0;
	for (int i = 0; i < 5; i++) {
		cout << i + 1 << "번째 정수 입력: ";
		cin >> num[i];
		cout << endl;
		sum = sum + num[i];
	}
	cout << "합계: " << sum << endl;

	cout << endl << endl;

	//문제2
	cout << "문제 2" << endl;
	cout << "이름과 전화번호를 입력하시오(20자 이하)" << endl;
	char name[21], number[21];
	//cin >> name >> number; : 공백 입력받기 불가능
	cin.ignore(); // 입력버퍼 초기화, important 참고 
	cin.getline(name, 21,'\n'); // '는 한 문자, "는 문자열, 21개 이상의 문자면 에러
	cin.getline(number, 21);
	cout << endl;
	cout << "이름: " << name << endl;
	cout << "전화번호: " << number << endl;

	cout << endl << endl;

	//문제3
	cout << "문제 3" << endl;
	cout << "숫자를 입력하시면 해당하는 구구단이 출력됩니다: ";
	int num3;
	cin >> num3;
	for (int i = 0; i < 9; i++) {
		cout << num3 << " X " << i + 1 << " = " << num3 * (i + 1) << endl;
	}

	cout << endl << endl;

	//문제4
	cout << "문제 4" << endl;
	int salesPerformance = 0;
	while (1) {
		cout << "판매 실적을 입력하시면 급여를 계산합니다(만원단위, -1 to end): ";
		cin >> salesPerformance;
		if (salesPerformance == -1) {
			cout << "프로그램을 종료합니다.";
			break;
		}
		cout << "이번 달 급여: " << 50 + salesPerformance * 0.12 << endl;
	}
	
}
void Question01_2(void) {

	int num1 = 20, num2 = 30;
	Part1::swap(&num1, &num2);
	cout << num1 << ' ' << num2 << endl;

	char char1 = 'A', char2 = 'Z';
	Part1::swap(&char1, &char2);
	cout << char1 << ' ' << char2 << endl;

	double db11 = 1.111, db55 = 5.555;
	Part1::swap(&db11, &db55);
	cout << db11 << ' ' << db55 << endl;
}
void Question01_3(void) {

	//문제1
	cout << "문제 1" << endl;
	cout << "[3, 3, 3] : " << Part1::BoxVolume(3, 3, 3) << endl;
	cout << "[5, 5, D] : " << Part1::BoxVolume(5, 5) << endl;
	cout << "[7, D, D] : " << Part1::BoxVolume(7) << endl;
	/*
	cout << "[D, D, D] : " << BoxVolume() << endl; 
	*/
	cout << "[D, D, D] : 함수 오버로딩은 변수의 개수와 자료형의 차이로 구분 가능하다. 이때 BoxVolume()는 default가 없기에 에러가 나게 된다." << endl;
	cout << "오버로딩을 사용하면 3개의 함수가 필요하지만, Default를 이용하면 하나로 충분하다" << endl;

	cout << endl << endl;

	//문제2
	cout << "문제2" << endl;
	cout << "SimpleFunc()가 첫번째인지 두번째인지 구별할 수가 없다.";
	cout << "함수를 선언할 때 에러가 발생하지는 않지만, SimpleFunc()라는 함수를 사용하면 빌드에러가 발생한다" << endl;

}
void Question01_4(void) {
	cout << "Solution을 Header파일로 만듦으로서 구현 완료" << endl;
}
void Question02_1(void) {
	//문제1
	cout << "문제 1" << endl;
	int num1 = 10, num2 = 56;
	Part1::RefFunc(num1, num2);

	cout << endl << endl;

	//문제2
	cout << "문제 2" << endl;
	cout << "const int& 형태로 매개변수가 선언된 것이 아니기 때문에 상수를 전달인자로 넣을 수 없다." << endl;

	cout << endl << endl;

	//문제3
	cout << "문제 3" << endl;
	int num3 = 5, num4 = 10;
	int* ptr1 = &num3, * ptr2 = &num4;
	Part1::SwapPointer(ptr1, ptr2);
	cout << "Result			" << "*ptr1: " << *ptr1 << "		*ptr2: " << *ptr2 << endl;
	
	cout << endl << endl;
}
void Question02_2(void) {
	const int num1 = 12;
	const int* ptr1 = &num1;
	const int* &pref1 = ptr1;

	cout << "num1: " << num1 << endl;
	cout << "*ptr1: " << *ptr1 << endl;
	cout << "*pref1: " << *pref1 << endl;
}
void Question02_3(void) {
	Part1::Point* point1 = new Part1::Point;	//Point 객체를 동적할당. 좌측은 (동적할당이므로)포인터형식의 객체명을, 우측에는 객체의 형식(Point)
	Part1::Point* point2 = new Part1::Point;
	cout << "Point1의 x좌표와 y좌표를 순서대로 입력하시오" << endl;
	cin >> point1->xpos;
	cin >> point1->ypos;
	cout << "Point2의 x좌표와 y좌표를 순서대로 입력하시오" << endl;
	cin >> point2->xpos;
	cin >> point2->ypos;

	Part1::Point& result = Part1::PntAdder(*point1, *point2);	
	/*
		PntAdder함수는 매개변수는 참조자 형식이다. 따라서 전달인자는 포인터(주소)가 아닌 가리키는 값(시작점)을 전달해야한다.
			매개변수 형태: const Point& p1 = *point1;
		함수 내부에서 동적할당을 통해 Point struct의 포인터 객체를 선언하며, 이름은 exam이다
			Point *exam = new Point;
		함수값을 참조자 형태로 return(객체 자신의 위치를 return) 하므로, 주소(포인터)가 아닌 가리키는 값(시작점)을 return 해야한다.
			return *exam;
??		exam은 동적할당 되었기 때문에 주소 자체는 남아있지만, exam이라는 객체명은 사라진다?
			아무튼 main에서는 exam객체의 존재를 모르기 때문에, PntAdder의 반환값으로 함수의 결과를 알아내야한다.
			반환값을 참조하는 참조자를 선언해, exam객체의 위치를 알아낸다.
				Point& result = *exam;
	*/
	cout << "두 점의 합은 x좌표: " << result.xpos << " y좌표: " << result.ypos << "입니다." << endl;

	delete point1;	//포인터 형태이기 때문에 그대로 반환이 가능하다
	delete point2;
	delete &result;	//참조자이므로 &을 통해서 주소를 얻어(포인터 형태로) 반환해야 한다.
}
void Question02_4(void) {
	//문제1
	cout << "문제 1" << endl;
	char name[80], hello[100] = "Hello ";
	cout << "이름을 입력하세요: ";
	cin >> name; 
	int len1 = strlen(name);// len1 은 name의 길이, length1 은 str1의 길이, str1은 hello
	char* Nname = new char[len1 + 1];
	//strcpy_s(Nname, len1 + 1, name);
    strcpy(Nname, name);
	//strcat_s(hello, 100, name);
    strcat(hello, name);
	cout << strcmp(name, Nname) << ": 0은 문자열이 같음을 나타냄, 배열의 크기가 달라도 내용이 같다면 같은 문자열" << endl;
	cout << "문자열은 NULL(\\0)문자로 마무리 하기 때문에 이것이 가능하다" << endl;
	cout << "name: " << name << "	Nname: " << Nname << endl;
	cout << "hello: " << hello << endl;
	cout << "len1: " << len1 << "	len2: " << strlen(Nname) << endl;
	cout << endl << endl;

	//문제2
	cout << "문제 2" << endl;
	for (int i = 0; i < 5; i++) {
		cout << rand() % 100 << endl;	
	}
	cout << "srand로 seed를 랜덤화시키지 않으면 항상 같은 순서로 같은 값이 나온다" << endl;
	cout << endl;
	srand(time(NULL));
	cout << "srand(time(NULL))을 통해 seed의 랜덤화" << endl;
	for (int j = 0; j < 5; j++) {
		cout << rand() % 100 << endl;
	}
}
//Part2
void Question03_1(void) {
	Part2::Point pt1 = { 12,4 };
	Part2::Point pt2 = { 20,30 };
	Part2::Point pt3;

	pt1.ShowPosition();
	pt1.MovePos(-7, 10);
	pt1.ShowPosition();

	pt1.AddPoint(pt2);
	pt1.ShowPosition();

	pt3.ShowPosition();
}
void Question03_2(void) {
	//문제 1
	cout << "문제 1" << endl;

	Calculator cal;
	cal.Init();
	cout << "3.2 + 2.4 = " << cal.Add(3.2, 2.4) << endl;
	cout << "3.5 / 1.7 = " << cal.Div(3.5, 1.7) << endl;
	cout << "2.2 - 1.5 = " << cal.Min(2.2, 1.5) << endl;
	cout << "4.9 / 1.2 = " << cal.Div(4.9, 1.2) << endl;
	cal.ShowOpCount();

	cout << endl << endl;
	//문제 2
	cout << "문제 2" << endl;

	Printer pnt;
	pnt.SetString("Hello World!");
	pnt.ShowString();

	pnt.SetString("I love C++");
	pnt.ShowString();
}
void Question04_1(void) {
	FruitSeller seller;
	seller.InitMembers(1000, 20, 0);
	FruitBuyer buyer;
	buyer.InitMembers(5000);
	buyer.BuyApples(seller, 2000);
	buyer.BuyApples(seller, -1000);
	buyer.BuyApples(seller, 2500);
	buyer.BuyApples(seller, 4000);
	cout << "과일 판매자의 현황" << endl;
	seller.ShowSalesResults();
	cout << "과일 구매자의 현황" << endl;
	buyer.ShowBuyResults();
}
void Question04_2(void) {
	Ring ring(1, 1, 4, 2, 2, 9);
	ring.ShowRingInfo();
}
void Question04_3(void) {
	//문제1
	cout << "문제 1은 Question 04-2의 class에서 생성자를 만드는 것" << endl << endl;

	//문제2
	cout << "문제 2" << endl;
	NameCard manClerk("Lee", "ABCEng", "010-1111-2222", Part2::COMP_POS::CLERK);
	NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", Part2::COMP_POS::SENIOR);
	NameCard manAssist("Kim", "SoGoodComp", "010-5555-6666", Part2::COMP_POS::ASSIST);
	NameCard wrongPos("Park", "TestComp", "010-0000-4545", 7);
	manClerk.ShowNameCardnfo();
	manSENIOR.ShowNameCardnfo();
	manAssist.ShowNameCardnfo();
	wrongPos.ShowNameCardnfo();

}
void Question05_1(void) {
	cout << "NameCard Class에 깊은복사를 위한 생성자를 정의했다. " << endl << endl;

	NameCard manClerk("Lee", "ABCEng", "010-1111-2222", Part2::COMP_POS::CLERK);
	NameCard copy1 = manClerk;
	NameCard manSENIOR("Hong", "OrangeEng", "010-3333-4444", Part2::COMP_POS::SENIOR);
	NameCard copy2 = manSENIOR;
	copy1.ShowNameCardnfo();
	copy2.ShowNameCardnfo();
}
//Part3
void Question07_1(void) {
	//문제1
	cout << "문제 1" << endl;
	int g1, g2, g3;
	cout << "연료량을 입력하시오" << endl;
	cin >> g1;
	cin >> g2;
	cin >> g3;
	HybridWaterCar car(g1, g2, g3);
	car.ShowCurrentGauge();
	cout << endl << endl;

	//문제2
	cout << "문제 2" << endl;
	cout << "이름, 주소, 전화번호를 차례로 입력하시오"<<endl;
	char* name = getString();
	int age = 24;
	char* addr = getString();
	char* phone = getString();
	MyFriendDetailInfo friend1(name, age, addr, phone);
	delete[] name;
	delete[] addr;
	delete[] phone;
	friend1.ShowMyFriendDetailInfo();
}
void Question07_2(void) {
	//문제1
	cout<<"문제 1"<<endl<<endl;
	Rectangle rec(4,3);
	rec.ShowAreaInfo();

	Square sqr(7);
	sqr.ShowAreaInfo();
	
	cout<<endl<<endl;
	//문제2
	cout<<"문제 2"<<endl<<endl;
	Book book("좋은 C++", "555-12345-890-0",20000);
	book.ShowBookInfo();
	cout<<endl;
	EBook ebook("좋은 C++ ebook","555-12345-890-1",10000,"qlalfqjsgh486");
	ebook.ShowEBookInfo();
}
void Question08_1(void) {
	EmployeeHandler handler;

	ForeignSalesWorker* fseller1=new ForeignSalesWorker("Hong", 1000, 0.1, RISK_A);
	fseller1->AddSalesResult(7000);
	handler.AddEmpList(fseller1);

	ForeignSalesWorker* fseller2=new ForeignSalesWorker("Yoon", 1000, 0.1, RISK_B);
	fseller2->AddSalesResult(7000);
	handler.AddEmpList(fseller2);

	ForeignSalesWorker* fseller3=new ForeignSalesWorker("Lee", 1000, 0.1, RISK_C);
	fseller3->AddSalesResult(7000);
	handler.AddEmpList(fseller3);

	handler.ShowAllSalaryInfo();
	handler.ShowTotalSalary();
}
void Question10_1(void){
	PointOL point1(3,7), point2(4, -6);
	PointOL point3=point1+point2;
	point3.ShowPosition();
	PointOL point4=point1-point2;
	point4.ShowPosition();
	point4+=point2;
	point4.ShowPosition();
	point3-=point1;
	point3.ShowPosition();
	cout<<(point1==point2)<<endl;
	cout<<(point1!=point2)<<endl;
	cout<<(point1==point4)<<endl;

}
void Question10_2(void){
	PointOL point1(4,7);
	PointOL point2=-point1;
	PointOL point3=~point1;
	point1.ShowPosition();
	point2.ShowPosition();
	point3.ShowPosition();
}
void Question10_3(void){
	PointOL pos1;
	cout<<"x, y 좌표 순으로 입력: "; cin>>pos1;
	cout<<pos1;

	PointOL pos2;
	cout<<"x, y 좌표 순으로 입력: "; cin>>pos2;
	cout<<pos2;

	cout<<"cin>>pos.xpos>>pos.ypos(int형식); 와 같은 상황에서 정수를 입력하고 스페이스바(엔터)를 한번이상 치고 다시 정수를 입력하면 각각 입력이 된다."<<endl;
	cout<<"cin에 오버로딩된 operator>>가 입력을 문자열 형식으로 받은 뒤, 알아서 공백은 거르고 int로 변형시켜서 입력받는 듯 하다."<<endl;
}
void Question11_1(void){
	// //문제1
	Police police1(10,5);
	Police police2(police1);
	Police police3=police1;
	Police police4;
	police4=police1;

	cout<<endl<<endl;

	// //문제2
	Book book1("book1", "a1000",1000);
	Book book2("book2", "b2000",2000);
	Book book3(book1);
	book1.ShowBookInfo();
	book2.ShowBookInfo();
	book3.ShowBookInfo();
	book3=book2;
	cout<<"after book3=book2"<<endl;
	book2.ShowBookInfo();

	cout<<endl<<endl;

	EBook ebook1("ebook1","ea1000",1000,"ea1");
	EBook ebook2("ebook2","eb2000",2000,"eb2");
	EBook ebook3(ebook1);
	ebook1.ShowEBookInfo();
	ebook2.ShowEBookInfo();
	ebook3.ShowEBookInfo();
	ebook3=ebook2;
	cout<<"after ebook3=ebook2"<<endl;
	ebook2.ShowEBookInfo();
}
void Question11_2(void){
	BoundCheckPointPtrArray arr(3);
	arr[0]=new PointOL(3,4);
	arr[1]=new PointOL(5,6);
	arr[2]=new PointOL(7,8);

	for(int i=0;i<arr.GetArrLen();i++){
		cout<<arr[i];
	}
// 	delete arr[0];
// 	delete arr[1];
// 	delete arr[2];
 }
void matrixProblem(void){
	BoundCheck2DIntArray arr2d(3,4);
	PointOL pos;	
	for(int n=0;n<3;n++){
		for(int m=0;m<4;m++){
		//  arr2d[n][m]=n+m;
		pos.SetPointOL(n,m);
		arr2d[n][m] = pos;
	 }
	}

	for(int n=0;n<3;n++){
		for(int m=0;m<4;m++){
			cout<<arr2d[n][m]<<' ';
		}
		cout<<endl;
	}
}
void StringClass(void){
	SString str1="i like ";
	SString str2("string class");
	cout<<str1<<endl<<str2<<endl;
	SString str3=str1+str2;
	cout<<str3<<endl;
	str1+=str2;
	cout<<str1<<endl;
	cout<<(str1==str2)<<endl<<(str1==str3)<<endl;
	cout<<"str에 넣을 문자를 입력하시오, 최대 "<<STRLENGTH<<"글자 입니다.";
	cin>>str1;
	cout<<str1<<endl;
}
void Question13_1(void){
	PointOL point1(4,5);
	PointOL point2(-2,7);
	cout<<point1<<endl<<point2<<endl;
	SwapData<PointOL>(point1, point2);
	cout<<point1<<endl<<point2<<endl;

	double arr[10] = {1.1,2.2,3.3,4.4,5.5,6.6,7.7,8.8,9.9,11.1};
	cout<<SumArray<double>(arr,10)<<endl;
}
void Question13_2(void){
	SmartPtrT<PointOL> sptr1(new PointOL(1,2));
	SmartPtrT<PointOL> sptr2(new PointOL(3,4));
	sptr1->ShowPosition();
	sptr2->ShowPosition();
	sptr1->SetPointOL(10,20);
	sptr2->SetPointOL(30,40);
	cout<<*sptr1<<endl;
	cout<<*sptr2<<endl;
}