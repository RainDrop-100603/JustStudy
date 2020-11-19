#include "useful.h"

//유용한 함수

vector<int> getPrimeVector(int num){
  //0~num 범위의 bool arr, prime 이라면 true
  vector<bool> arr(num+1,true);
  arr[0]=false;arr[1]=false;
  for(int i=2;i<=sqrt(num);i++){  
    if(arr[i]){
      for(int j=i*2;j<=num;j+=i){
        arr[j]=false;
      }
    }
  }
  //prime number만을 원소로 가진 arr 
  vector<int> result;
  for(int i=2;i<=num;i++){
    if(arr[i]){
      result.push_back(i);
    }
  }
  return result;
}
int getGCD(int A, int B){     //유클리드 호제법을 이용한 A와 B의 GCD
  return A%B ? getGCD(B,A%B) : B; //A=qB+r, r=A%B, GCD(A,B)=GCD(B,r)=GCD(B,A%B), r==0이면 B가 최대공약수 
}
pair<long long,long long> euclidAlgo(long long A,long long B){      //Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
  if(B<A){
    return euclidAlgo(B,A);
  }
  if(B!=0){ //B=r==0이면 A가 최대공약수
    pair<long long,long long> temp=euclidAlgo(B,A%B);
    return make_pair(temp.second,temp.first-(A/B)*temp.second);
  }else{
    return make_pair(1,0);  // GCD(d,0) = dx+0y=d: 
  }
} 
int fastSum(int n){
  //기저
  if(n==1) return 1;
  //홀수
  if(n%2) return fastSum(n-1)+n;
  //짝수
  return 2*fastSum(n/2)+(n/2)*(n/2);
}

//실수 비교
int cmpDouble_Abs(double a, double b, double absTolerance=(1.0e-8)){  // 1:(a>b), 0:(a==b), -1:(a<b)
  //큰 수는 비교하기 어렵다.
  double diff=a-b;
  if(fabs(diff)<=absTolerance) 
    return 0;
  return diff>0 ? 1: -1;
}
int cmpDouble_Rel(double a, double b, double relTolerance=__DBL_EPSILON__){  // 1:(a>b), 0:(a==b), -1:(a<b)
  //0에 아주 가까운 작은 값은 비교하기 어렵다
  double diff=a-b;
  if(fabs(diff)<=relTolerance*max(fabs(a),fabs(b))) 
    return 0;
  return diff>0 ? 1: -1;
}
int cmpDouble_AbsRel(double a, double b, double absTolerance=(1.0e-8), double relTolerance=__DBL_EPSILON__){  // 1:(a>b), 0:(a==b), -1:(a<b)
  double diff=a-b;
  if(fabs(diff)<=absTolerance) // absolute compare
    return 0;  
  if(fabs(diff)<=relTolerance*max(fabs(a),fabs(b))) // relative compare
    return 0; 
  return diff>0 ? 1: -1;
}
int cmpDouble_Ulps(double a, double b, int ulpsTolerance=4){  // 1:(a>b), 0:(a==b), -1:(a<b)
  //bit를 double이 아닌 long long(64bit)으로 해석하여, 두 값을 정수형태로 비교, 상대오차 비교와 유사
  //주의할 것은 double->long long으로 형을 변환한것이 아닌, 비트 자체는 그대로 두고 long long으로 해석한 것
  double diff=a-b;
  long long na=*((long long*)&a); //bit를 long long형식으로 해석했을경우
  long long nb=*((long long*)&b);
  //부호비트를 비교, 부호가 다를경우 처리
  if((na&0x8000000000000000)!=(nb&0x8000000000000000)){
    if(a==b) //0은 double에서 +0과 -0으로 처리되므로, 부호비트가 다를수도 있다.
      return 0;  
    return diff>0 ? 1: -1;  //부호가 다르면 비교가 easy
  }
  long long ulpsDiff=abs(na-nb); //ulps 비교
  if(ulpsDiff<=ulpsTolerance) 
    return 0;
  return (diff>0) ? 1: -1; 
}
int cmpDouble_UlpsAbs(double a, double b, int absTolerance=(1.0e-8), int ulpsTolerance=4){  // 1:(a>b), 0:(a==b), -1:(a<b)
  double diff=a-b;
  if(fabs(diff)<=absTolerance) 
    return 0;
  long long na=*((long long*)&a); 
  long long nb=*((long long*)&b);
  if((na&0x8000000000000000)!=(nb&0x8000000000000000)) 
    return diff>0 ? 1: -1;  
  long long ulpsDiff=abs(na-nb); 
  if(ulpsDiff<=ulpsTolerance) 
    return 0;
  return (diff>0) ? 1: -1;
}


//유용한 테스트
void moveTest_vec(){
  vector<int> vec1(3,1);
  cout<<"&vec1: "<<&vec1<<endl;
  cout<<"&vec1[0]: "<<&vec1[0]<<endl;
  vector<int> vec2(move(vec1));
  cout<<"&vec2: "<<&vec2<<endl;
  cout<<"&vec2[0]: "<<&vec2[0]<<endl;
  //권장되지 않는 선언
  vector<int> vec3(vec1);
  cout<<"&vec3: "<<&vec3<<endl;
  for(auto& ele:vec1){
    cout<<ele;
  }cout<<endl;
  for(auto& ele:vec2){
    cout<<ele;
  }cout<<endl;
  for(auto& ele:vec3){
    cout<<ele;
  }cout<<endl;
  //vector v1에서 v1은 "배열의 시작위치"가 아닌, "배열의 시작위치를 가리키는 포인터"이다. 배열의 시작위치는 "&v[0]"이다.
  //따라서 move연산이 제대로 이루어졌는지 확인하려면, &v1이 아닌 &v1[0]을 통해 확인해야한다.
}

//미완성