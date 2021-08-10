#include "useful.h"

//"에라스토테네스의 채"와 bitmask를 이용한 prime 구하기 
bool useful_isPrime(vector<unsigned char>& eratosthenes, int num){return eratosthenes[num>>3] & ( 1 << (num&7)); }
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num){return eratosthenes[num>>3] &= (~( 1 << (num&7))); }
vector<unsigned char> useful_eratosthenes(int num){
  //한칸에 8비트씩 저장, num의 위치는 arr[num/8] & (1<<(num&7)), (num+7)/8 은 num을 8로 나눈것의 올림 
  vector<unsigned char> eratosthenes((num+7)/8,255); 
  //0,1,2, 짝수 처리
  useful_setComposite(eratosthenes,0);
  useful_setComposite(eratosthenes,1);
  for(int i=4;i<=num;i+=2){
    useful_setComposite(eratosthenes,i);
  }
  //에라스토테네스의 채, 짝수는 다 제외시킨다.
  int sqrtNum=sqrt(num);
  for(int i=3;i<=sqrtNum;i+=2){
    if(useful_isPrime(eratosthenes,i)){
      for(int j=i*i;j<=num;j+=i){
        useful_setComposite(eratosthenes,j);
      }
    }
  }
  //return
  return eratosthenes;
}