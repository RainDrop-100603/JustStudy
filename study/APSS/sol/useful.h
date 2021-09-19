#ifndef ___USEFUL_H___
#define ___USEFUL_H___

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;


//유용한 함수
vector<int> getPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
int getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
// LCM=A*B/GCD(A*B);
pair<long long,long long> euclidAlgo(long long A,long long B);  //유클리드 알고리즘"Ax+By=gcd(A,B)"의 해(x,y), 
int fastSum(int n); //1~n까지의 합을 구한다. 분할정복방식

//행렬 곱
template <class T>
vector<vector<T>> matrix2_mult(const vector<vector<T>>& m1,const vector<vector<T>>& m2){
  //간단한 에러체크, 모든 경우를 체크하진 않는다.
  if(m1.size()==0||m2.size()==0||m1[0].size()==0||m2[0].size()==0||m1[0].size()!=m2.size()){
    cout<<"matrix2_mult Error!"<<endl;
    return vector<vector<T>>();
  }
  //계산
  long long row(m1.size()), mid(m2.size()), col(m2[0].size());
  vector<vector<T>> result(row,vector<T>(col,0));
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      for(int z=0;z<mid;z++){
        result[i][j]+=m1[i][z]*m2[z][j];
      }
    }
  }
  return result;
}
template <class T>
vector<vector<T>> matrix2_pow(const vector<vector<T>>& m1, long long pow){
  if(pow==1){
    return m1;
  }
  vector<vector<T>> result=matrix2_pow<T>(m1,pow/2);
  result=matrix2_mult(result,result);
  if(pow%2==1){
    result=matrix2_mult<T>(result,m1);
  }
  return result;
}

//유용한 테스트
void moveTest_vec();  //move가 제대로 이루어 졌는지 확인하는 방법에 대한 참고 

//미완성 
class longNum{
  //ver0.1, 2020_10_4
  //fanMeeting algospot 문제 실패, 추후 수정 
  //ele=num[idx]*10^idx, sign: true means positive
  vector<int> num;
  bool sign;
public:
  //생성자
  longNum():num(vector<int>()),sign(true){} 
  longNum(const vector<int>& v,bool sign=true):num(v),sign(sign){}
  longNum(vector<int>&& v,bool sign=true):num(move(v)),sign(sign){}
  longNum(const string& s){
    num.reserve(s.length());
    for(auto iter=s.rbegin();iter!=s.rend();iter++){
      num.push_back(*iter-'0');
    }
    //부호결정
    if(num.back()=='-'-'0'){
      num.pop_back();
      sign=false;
    }else{
      sign=true;
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
  longNum operator+(const longNum& lN)const{
    //부호가 다른경우 sub
    if(sign^lN.sign){
      if(sign){
        return *this-lN.changeSign();
      }else{
        return lN-(this->changeSign());
      }
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
  longNum operator-(const longNum& lN)const{
    //부호가 다를경우 add 
    if(sign^lN.sign){
      return *this+lN.changeSign();
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
  longNum operator*(const longNum& lN)const{
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
  //연산자 오버로딩
  int& operator[] (int idx){return num[idx];}
  int operator[] (int idx) const{return num[idx];}
  friend ostream& operator<<(ostream& os, const longNum& lN);
  //멤버함수
  int length() const{return num.size();}
  longNum& reverse(){
    vector<int> tmp;
    tmp.reserve(num.size());
    for(auto iter=num.rbegin();iter!=num.rend();iter++){
      tmp.push_back(*iter);
    }
    num=move(tmp);
    return *this;
  }
  longNum sublN(int start, int end) const{
    //[start,end)
    if(start>=end){
      return longNum();
    }
    vector<int> tmp;
    tmp.reserve(end-start);
    start=max(start,0);
    end=min(end,this->length()+1);
    for(int i=start;i<end;i++){
      tmp.push_back(num[i]);
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
  longNum karatsuba(const longNum& lN) const{
    //기저,shortLen(this)<longLen(lN)<50, 
    int longLen(this->length()),shortLen(lN.length());
    if(shortLen>longLen){
      return lN.karatsuba(*this);
    }
    if(shortLen==0||longLen==0){
      return longNum();
    }
    if(longLen<50){
      return this->operator*(lN);
    }
    //divide&conquer
    int divLen((shortLen+1)/2);
    longNum thisLow(this->sublN(0,divLen)),thisHigh(this->sublN(divLen,longLen));
    longNum lNLow(lN.sublN(0,divLen)),lNHigh(lN.sublN(divLen,shortLen));
    //a0 x^2 + a1 x + a2 : x=10^divLen, a0=thisHigh*lNHigh, a1=(this low+high)*(lN low+high)-a0-a2, a2=thisLow*lNLow
    longNum a0(thisHigh.karatsuba(lNHigh));
    longNum a2(thisLow.karatsuba(lNLow));
    longNum a1((thisLow+thisHigh).karatsuba(lNLow+lNHigh)-a0-a2);
    return longNum(a0.pow10(divLen*2)+a1.pow10(divLen)+a2);
  }
  void print_withSpace(){
    if(!sign){
      cout<<"- ";
    }
    for(auto iter=num.rbegin();iter!=num.rend();iter++){
      cout<<*iter<<' ';
    }
  }
  //문제풀이용
  longNum mult_notNorm(const longNum& lN)const{
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    int lenThis(num.size()),lenA(lN.length());
    vector<int> tmp(vector<int>(lenThis+lenA-1));
    for(int i=0;i<lenThis;i++){
      for(int j=0;j<lenA;j++){
        tmp[i+j]+=num[i]*lN[j];
      }
    }
    return longNum(move(tmp),true);
  }
  longNum& sub_notNorm(const longNum& lN){
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    for(int i=0;i<lN.length();i++){
      num[i]-=lN[i];
    }
    return *this;
  }
  longNum& add_notNorm(const longNum& lN){
    //양수 계산만 한다, this가 lN보다 크다. 기존 방식은 시간이 너무 오래 걸려서 빠른 방식
    for(int i=0;i<lN.length();i++){
      num[i]+=lN[i];
    }
    return *this;
  }
  longNum karatsuba_notNorm(const longNum& lN)const{
    //기저,shortLen(lN)<longLen(this)<50, normalize하지 않는다.
    int shortLen(lN.length()),longLen(this->length());
    if(shortLen>longLen){
      return lN.karatsuba_notNorm(*this);
    }
    if(shortLen==0||longLen==0){
      return longNum();
    }
    if(longLen<50){
      return this->mult_notNorm(lN);
    }
    //divide&conquer
    int divLen((shortLen+1)/2);
    longNum thisLow(this->sublN(0,divLen)),thisHigh(this->sublN(divLen,longLen));
    longNum lNLow(lN.sublN(0,divLen)),lNHigh(lN.sublN(divLen,shortLen));
    //a0 x^2 + a1 x + a2 : x=10^divLen, a0=thisHigh*lNHigh, a1=(this low+high)*(lN low+high)-a0-a2, a2=thisLow*lNLow
    longNum a0(thisHigh.karatsuba_notNorm(lNHigh));
    longNum a2(thisLow.karatsuba_notNorm(lNLow));
    longNum a1((thisLow.add_notNorm(thisHigh)).karatsuba_notNorm(lNLow.add_notNorm(lNHigh)).sub_notNorm(a0).sub_notNorm(a2));
    return longNum(a0.pow10(divLen*2).add_notNorm(a1.pow10(divLen)).add_notNorm(a2));
  }
  //range based loop(for), operator++부터 추가바람
  //이 경우 operator를 오버로딩할 필요가 없을듯 하다? int*형식이기 때문
  int* begin(){return &num[0];}
  int* end(){return &num[num.size()];}
};
ostream& operator<<(ostream& os, const longNum& lN);
//https://jungwoong.tistory.com/53
//std move, std forward, 이동생성자 공부
//rValue로 전달된 a는 num을 초기화 할때도 rvalue 상태인가? -> lvalue 취급되서 move를 써주어여 한다.
//longNum(vector<int>&& a):num(a){} 가 맞는가, longNum(vector<int>&& a):num(move(a)){} 가 맞는가-> 후자가 맞다.

#endif