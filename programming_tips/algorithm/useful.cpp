#include "useful.h"

//"에라스토테네스의 채"를 이용한 prime 구하기
아래 두개 더 살펴보기 
bool useful_isPrime(vector<unsigned char>& eratosthenes, int num){return eratosthenes[num>>3] & ( 1 << (num&7)); }
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num){return eratosthenes[num>>3] &= ~( 1 << (num&7)); }
vector<unsigned char> useful_eratosthenes(int num){
  //한칸에 8비트씩 저장, num의 위치는 arr[num/8] & (1<<(num&7)), (num+7)/8 은 num을 8로 나눈것의 올림 
  vector<unsigned char> eratosthenes((num+7)/8); 
}