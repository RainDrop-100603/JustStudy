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

//순열과 조합
vector<vector<int>> useful_getPermutation(vector<int> set){
  //기저
  if(set.empty()){return vector<vector<int>>();}
  //next_permutation함수는 더 높은(후순위)순열을 찾는 함수
  //set의 모든 순열을 찾으려면, 오름차순 정렬을 해주어야 한다.
  sort(set.begin(),set.end());
  //모든 순열 찾기
  vector<vector<int>> permutations;
  do{
    permutations.push_back(set);
  }while(next_permutation(set.begin(),set.end()));
  return permutations;
}
vector<vector<int>> useful_getCombination(vector<int> set, int select){
  //기저
  int total=set.size();
  if(set.empty()){return vector<vector<int>>();}
  if(total<select){cout<<"select exceed total"<<endl; return vector<vector<int>>();}
  //순서과 상관없는 조합, select개의 1과 (set size-select)개의 0을 만들고, 0과1의 순열을 만든다.
  //set을 정렬할 필요는 없지만, 오름차순으로 조합을 만들기 위해 정렬을 해준다.
  sort(set.begin(),set.end());
  //모든 조합 찾기
  vector<vector<int>> combinations;
  vector<int> key;
  for(int i=0;i<select;i++){key.push_back(1);}
  for(int i=0;i<total-select;i++){key.push_back(0);}
  do{
    vector<int> tmp;
    for(int i=0;i<total;i++){
      if(key[i]==1){tmp.push_back(set[i]);}
    }
    combinations.push_back(tmp);
  }while(prev_permutation(key.begin(),key.end()));
  return combinations;
}

//문자열
vector<int> useful_getFailure(string& str){
  //result[idx]=value: str.substr(idx)[0 .. value-1] = str.substr(idx)[idx-value .. idx-1]
  // 즉, str을 idx길이로 자른 것은, 접두사와 접미사가 value만큼 일치한다.
  vector<int> result(str.length()+1,0);
  int begin(1),match(0);
  while(begin+match<str.length()){
    if(str[begin+match]==str[match]){
      match++;
      result[begin+match]=match;
    }else{
      if(match==0){
        begin++;
      }else{
        begin+=match-result[match];
        match=result[match];
      }
    }
  }
  return result;
}
vector<int> useful_KmpSearch(string& base,string& target){
  vector<int> result;
  //failure function을 구한다.
  vector<int> failure=useful_getFailure(target);
  //탐색을 한다.
  int match=0,begin=0; 
  while(begin+target.length()<=base.length()){
    if(match<target.length()&&base[begin+match]==target[match]){
      match++;
      if(match==target.length()){
        result.push_back(begin);
      }
    }else{
      if(match==0){
        begin++;
      }else{
        begin+=match-failure[match];
        match=failure[match];
      }
    }
  }
  //반환
  return result;
}
