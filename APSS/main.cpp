//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;

class longNum{
  //ele=num[idx]*10^idx, sign: true means positive
  vector<int> num;
  bool sign;
public:
  //생성자
  longNum(){} 
  longNum(vector<int>& v,bool sign=true):num(v),sign(sign){}
  longNum(vector<int>&& v,bool sign=true):num(move(v)),sign(sign){}
  longNum(const string& s, bool sign=true):sign(sign){
    num.reserve(s.length());
    for(auto& ele:s){
      num.push_back(ele-'0');
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
  //연산자 오버로딩
  int& operator[] (int idx){return num[idx];}
  const int& operator[] (int idx) const{return num[idx];}
  friend ostream& operator<<(ostream& os, const longNum& lN);
  //멤버함수
  int length() const{return num.size();}
  longNum mult(const longNum& lN) const{
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
  longNum karatsuba(const longNum& a) const{
    //기저
    if((this->length()<50)&&a.length()<50){
      return this->mult(a);
    }
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
    while(num.back()>9||num.back()<-9){
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
  void print_withSpace(){
    if(!sign){
      cout<<"- ";
    }
    for(auto iter=num.rbegin();iter!=num.rend();iter++){
      cout<<*iter<<' ';
    }
  }
};
ostream& operator<<(ostream& os, const longNum& lN){
  if(!lN.sign){
    os<<'-';
  }
  for(auto iter=lN.num.rbegin();iter!=lN.num.rend();iter++){
    os<<*iter;
  }
  return os;
}
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
  longNum lN1(-123),lN2(456);
  longNum lN3=(lN1.mult(lN2));
  cout<<"Before Normalize: ";
  lN3.print_withSpace();cout<<endl;
  cout<<"After Normalize: ";
  lN3.normalize();
  lN3.print_withSpace();cout<<endl;
  cout<<lN3<<endl;

  return 0;
}