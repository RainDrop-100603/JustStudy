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
  longNum(const vector<int>& v,bool sign=true):num(v),sign(sign){}
  longNum(vector<int>&& v,bool sign=true):num(move(v)),sign(sign){}
  longNum(const string& s,bool sign=true):sign(sign){
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
  int operator[] (int idx) const{return num[idx];}
  friend ostream& operator<<(ostream& os, const longNum& lN);
  //멤버함수
  int length() const{return num.size();}
  longNum sublN(int start, int end) const{
    //[start,end)
    vector<int> tmp(end-start);
    int idx(0);
    start=max(start,0);
    end=min(end,this->length()+1);
    for(int i=start;i<end;i++){
      tmp[idx]=num[i];
      idx++;
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
  longNum add(const longNum& lN)const{
    //부호가 다른경우 sub 계산이부분 바꿔야함
    if(sign^lN.sign){
      return this->sub(lN.changeSign());
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
  longNum sub(const longNum& lN)const{
    //부호가 다를경우 add 계산
    if(sign^lN.sign){
      return this->add(lN.changeSign());
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
  longNum karatsuba(const longNum& lN) const{
    //기저,shortLen(this)<longLen(lN)<50 
    int shortLen(this->length()),longLen(lN.length());
    if(shortLen>longLen){
      return lN.karatsuba(*this);
    }
    if(longLen<50){
      return this->mult(lN);
    }
    //divide&conquer
    int divLen((shortLen+1)/2);
    longNum thisLow(this->sublN(0,divLen)),thisHigh(this->sublN(divLen,shortLen+1));
    longNum lNLow(lN.sublN(0,divLen)),lNHigh(lN.sublN(divLen,longLen+1));
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
  longNum lN3(lN1.mult(lN2));
  longNum lN4(lN1.add(lN2));
  longNum lN5(lN1.sub(lN2));
  longNum lN6(lN2.sub(lN1));
  longNum lN7(lN2.add(lN1));
  cout<<lN1<<endl<<lN2<<endl<<lN3<<endl<<lN4<<endl<<lN5<<endl<<lN6<<endl<<lN7<<endl;

  return 0;
}