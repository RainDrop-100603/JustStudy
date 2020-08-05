#include "GoodFunction.h"

bool IsPrime(int num){
  if(num%2==0){
    if(num==2){
      return true;
    }
    return false;
  }
  if(num==1){
    return false;
  }
  int tstNum=num-2;
  while(tstNum>1){
    if(num%tstNum==0){
      return false;
    }
    tstNum-=2;
  }
  return true;
}
bool* GetPrimeArray(int num){
  num++;
  bool* array=new bool[num+1];
  fill_n(array,num+1,true);
  array[0]=false;
  array[1]=false;
  for(int i=2;i<sqrt(num);i++){
    if(array[i]){
      for(int j=i*2;j<num+1;j+=i){
        if(array[j]){
          array[j]=false;
        }
      }
    }
  }
  return array;
}
vector<int> GetPrimeVector(int num){
  vector<int> prime;
  bool* array= GetPrimeArray(num);
  for(int i=0;i<num+1;i++){
    if(array[i]){
      prime.push_back(i);
    }
  }
  delete[] array;
  return prime;
}
void Merge(int* &array, const int start, const int end){  //[start,end) sorting 
  int middle=(end+start)/2; //두 vector 사이의 경계 idx
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  int tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  int temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    if(temp<array[rotateBack]||rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
      temp=tempArray[rotateFront-start];
    }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
    }
  }
  return;
}
void MergeSort(int* &array,const int start,const int end){
  //divide
  int middle=(end+start)/2;
  if(end-start==1){
    return;
  }else{
    MergeSort(array,start,middle);
    MergeSort(array,middle,end);
  }
  //conquer
  Merge(array,start,end); //Merge를 합치고 싶다면, 여기다가 그냥 함수 내용을 붙여넣으면 된다.
}
void MergeSort(vector<int>& array,const int start,const int end){
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    MergeSort(array,start,middle);
    MergeSort(array,middle,end);
  }
  //conquer : Merge
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  int tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  int temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    temp=tempArray[rotateFront-start];
    if(rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
    }else{
      if(temp<array[rotateBack]){
        array[mainRotate]=temp;
        rotateFront++;
        mainRotate++;
      }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
      }
    }
  }
}
int Combi_nCr(int n, int r){
  int sum=1;
  for(int i=n;i>n-r;i--){
    sum*=i;
  }
  for(int i=1;i<=r;i++){
    sum/=i;
  }
  return sum;
}

int getGCD(int A, int B){     //유클리드 호제법을 이용한 A와 B의 GCD
  return A%B ? getGCD(B,A%B) : B; //A=qB+r, r=A%B, GCD(A,B)=GCD(B,r)=GCD(B,A%B), r==0이면 B가 최대공약수 
}
pair<long long,long long> EuclidAlgo(long long A,long long B){      //조건: A>B  ____  Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
  if(B!=0){ //B=r==0이면 A가 최대공약수
    pair<long long,long long> temp=EuclidAlgo(B,A%B);
    return make_pair(temp.second,temp.first-(A/B)*temp.second);
  }else{
    return make_pair(1,0);  // GCD(d,0) = dx+0y=d: 
  }
} 
vector<vector<long long>> FibonacciMatrix(long long m){ //Fibonacci identity: 도가뉴 항등식, d'Ocagne's identity, f_m matrix 반환, important 참고 
  vector<vector<long long>> matrix_m(2,vector<long long>(2));
  //m==1일 경우, f0, f1, f1, f2 반환, 즉 f_1 matrix 반환 
  if(m==1){
    matrix_m[0][0]=0;
    matrix_m[0][1]=1;
    matrix_m[1][0]=1;
    matrix_m[1][1]=1;
    return matrix_m;
  }
  //m>0일 경우 f_m matrix 반환 : f_m matrix == f_(m-1), f_m, f_m, f_(m+1)
  vector<vector<long long>> matrix_m2=FibonacciMatrix(m/2);
  long long a=matrix_m2[0][0];
  long long b=matrix_m2[0][1];
  long long c=matrix_m2[1][0];
  long long d=matrix_m2[1][1];
  
  if(m%2==0){
    matrix_m[0][0]=a*a+b*c;
    matrix_m[0][1]=b*(a+d);
    matrix_m[1][0]=c*(a+d);
    matrix_m[1][1]=d*d+b*c;
  }else{
    matrix_m[0][0]=b*(a+d);
    matrix_m[0][1]=d*d+b*c;
    matrix_m[1][0]=d*d+b*c;
    matrix_m[1][1]=d*d+b*c+b*(a+d);
  }
  
  matrix_m[0][0]%=1000000;
  matrix_m[0][1]%=1000000;
  matrix_m[1][0]%=1000000;
  matrix_m[1][1]%=1000000;
  
  return matrix_m;
} 