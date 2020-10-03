//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;

class longNum{
  //ele=num[idx]*10^idx, only 양수(추후 음수 추가)
  vector<int> num;
public:
  //생성자
  longNum(){} 
  longNum(vector<int>& v):num(v){}
  longNum(const string& s){
    num.reserve(s.length());
    for(auto& ele:s){
      num.push_back(ele-'0');
    }
  }
  longNum(long long n){
    // 더 낮은 비트수의 자료형, int도 포함된다.
    while(n>0){
      num.push_back(n%10);
      n/=10;
    }
  }
  longNum(longNum&& lN):num(move(lN.num)){}
  ~longNum(){}
  //복사 생성자, 이동 생성자
  longNum(const longNum& lN):num(lN.num){}
  //대입 연산자 오버로딩
  longNum& operator=(const longNum& lN){num=lN.num;return *this;}
  longNum& operator=(longNum&& lN){num=move(lN.num);return *this;}
  //멤버함수
  int length() const{return num.size();}
  int at(int idx) const{return num[idx];}
  void change(int idx, int n){num[idx]=n;}
  longNum mult(const longNum& a) const{
    int lenThis(this->length()),lenA(a.length());
    vector<int> result(lenThis+lenA);
    for(int i=0;i<lenThis;i++){
      for(int j=0;j<lenA;j++){
        result[i+j]+=this->at(i)*a.at(j);
      }
    }
    return longNum(result);
  }
  longNum karatsuba(const longNum& a) const{

  }
  longNum& normalize(){
    int len=num.size();
    int prev,now(num.at(0)),borrow;
    for(int i=1;i<len;i++){
      prev=now;
      now=num.at(i);
      borrow=prev/10;
      if(prev<0){
        borrow--;
      }
      prev-=borrow*10;
      now+=borrow;
      this->change(i-1,prev);
    }
    this->change(len-1,now);
    return *this;
  }
  void print_withSpace(){
    int len(num.size());
    if(num[len-1]!=0){
      cout<<num[len-1]<<' ';
    }
    for(int i=len-2;i>=0;i--){
      cout<<num[i]<<' ';
    }
  }
  void print(){//주석
    //must be normalized
    int len(num.size());
    if(num[len-1]!=0){
      cout<<num[len-1];
    }
    for(int i=len-2;i>=0;i--){
      cout<<num[i];
    }
  }
};
//https://jungwoong.tistory.com/53
//std move, std forward, 이동생성자 공부
//rValue로 전달된 a는 num을 초기화 할때도 rvalue 상태인가?
//longNum(vector<int>&& a):num(a){} 가 맞는가, longNum(vector<int>&& a):num(move(a)){} 가 맞는가 

void longNumTest(){
  //자료형 생성
  longNum void1;
  longNum int1(123);
  longNum ll1(1234567891011121314);
  string tmpStr1("12345678910111213141516171819202122232425262728293031323334353637383940");
  vector<int> tmpVec1={1,2,3,4,5,6,7,8,9,10};
  longNum lN1(tmpStr1);
  longNum lN2(tmpVec1);
  //각 자료형의 주소
  // cout<<"----------address----------"<<endl;
  // int1.printAddress();cout<<endl;
  // ll1.printAddress();cout<<endl;
  // cout<<&tmpStr1<<endl;
  // lN1.printAddress();cout<<endl;
  // cout<<&tmpVec1<<endl;
  // lN2.printAddress();cout<<endl;
  // //이동생성자 테스트
  // cout<<"----------move Test----------"<<endl;
  // cout<<"lN1: ";lN1.printAddress();cout<<endl;
  // longNum void2(move(lN1));
  // cout<<"void2: ";void2.printAddress();cout<<endl;
}

void moveTest_vec(){
  vector<int> vec1(3,1);
  cout<<"vec1: "<<&vec1<<endl;
  vector<int> vec2(move(vec1));
  cout<<"vec2: "<<&vec2<<endl;
  //권장되지 않는 선언
  vector<int> vec3(vec1);
  cout<<"vec3: "<<&vec3<<endl;
  for(auto& ele:vec1){
    cout<<ele;
  }cout<<endl;
  for(auto& ele:vec2){
    cout<<ele;
  }cout<<endl;
  for(auto& ele:vec3){
    cout<<ele;
  }cout<<endl;
  //std::move가 일어나도 vector의 주소는 바뀐다는ㅗ 것을 확인할 수 있다. 
}

void FanmeetingInput(vector<int>& member,vector<int>& fan){
  string memberTmp,fanTmp;
  cin>>memberTmp>>fanTmp;
  member.reserve(memberTmp.length());
  for(auto& ele: memberTmp){
    if(ele=='M'){
      member.push_back(1);
    }else{
      member.push_back(0);
    }
  }
  fan.reserve(fanTmp.length());
  for(auto& ele: fanTmp){
    if(ele=='M'){
      fan.push_back(1);
    }else{
      fan.push_back(0);
    }
  }
}
int FanmeetingAlgo(vector<int>& member, vector<int>& fan){
  /*
  제한시간 10초
  제한메모리 2^16kb=64MB
  전략1
    모든 멤버와 모든팬은 만난다.
    한 줄의 모든 멤버들이 포옹하는 경우 -> M & M 이없는 경우 
      M=1, F=0으로 하고 bit and(&) -> if (0)-> 모든멤버 포옹
    time complexity
    mem complexity
  전략2
  전략 3
  */
  //기저
  //Algo, 
  
}
void Fanmeeting(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> member,fan;
    FanmeetingInput(member,fan);
    cout<<FanmeetingAlgo(member,fan)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  //Fanmeeting();
  //longNumTest();
  //moveTest_vec();
  longNum lN1(123),lN2(456);
  longNum lN3=(lN1.mult(lN2));
  cout<<"Before Normalize: ";
  lN3.print_withSpace();cout<<endl;
  cout<<"After Normalize: ";
  lN3.normalize();
  lN3.print_withSpace();cout<<endl;
  lN3.print();

  return 0;
}