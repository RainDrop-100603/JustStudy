//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @*@*@* 지나친 수학적 접근이 문제, 프로그래밍적으로 접근필요
void Dragon_example(){
  vector<char> dragon={'F','X'};
  int cnt=10; //you can change
  while(cnt!=0){
    //print
    for(auto& ele: dragon){
      cout<<ele;
    }
    cout<<"\n";
    //next gen
    vector<char> tmpDragon;
    for(auto& ele:dragon){
      if(ele=='X'){
        tmpDragon.insert(tmpDragon.end(),{'X','+','Y','F'});
      }else if(ele=='Y'){
        tmpDragon.insert(tmpDragon.end(),{'F','X','-','Y'});
      }else{
        tmpDragon.push_back(ele);
      }
    }
    dragon=move(tmpDragon);
    cnt--;
  }
}
void Dragon_Input(int& nthGen,int& skip,int& len){
  cin>>nthGen>>skip>>len;
}
int Dragon_getDragonLen(vector<int>& cache_DragonLen,int nthGen){
  int& result=cache_DragonLen[nthGen];
  if(result!=-1){
    return result;
  }
  if(nthGen==0){
    return 4;
  }
  //Algo 
  result=Dragon_getDragonLen(cache_DragonLen,nthGen-1)*2+2;
  //chk Overflow
  if(result<0){
    return -2;
  }
  //return
  return result;
}
pair<string,int> Dragon_removeSkip(vector<int>& cache_DragonLen, int nthGen, int skip, string nowDragon){
  //기저
  if(skip==0){
    return {nowDragon,nthGen};
  }
  //get numOfCases
  int numOfCases(1);
  string lowerGenDragon;
  if(nowDragon[0]=='X'){
    numOfCases=Dragon_getDragonLen(cache_DragonLen,nthGen);
    lowerGenDragon="X+YF";
  }else if(nowDragon[0]=='Y'){
    numOfCases=Dragon_getDragonLen(cache_DragonLen,nthGen);
    lowerGenDragon="FX-Y";
  }
  //recursive Algo
  if(skip<numOfCases||numOfCases==-2){
    return Dragon_removeSkip(cache_DragonLen,nthGen-1,skip,lowerGenDragon);
  }else{
    return Dragon_removeSkip(cache_DragonLen,nthGen,skip-numOfCases,nowDragon.substr(1));
  }
}
string Dragon_getDragon(string tmpDragon, int gen, int lenCap){
  if(lenCap==0){
    return tmpDragon;
  }
  string result;
  for(auto& ele:tmpDragon){
    if(ele=='X'){
      result+=Dragon_getDragon("X+YF",gen-1,lenCap-result.size());
    }else if(ele=='Y'){
      result+=Dragon_getDragon("FX-Y",gen-1,lenCap-result.size());
    }else{
      result.push_back(ele);
    }
    if(result.size()==lenCap){
      return result;
    }
  }
  return result;
}
string Dragon_Algo(int nthGen,int skip,int len){
  string nowDragon="FX";
  //remove skip
  vector<int> cache_DragonLen(nthGen+1,-1); //0 for 'X', 1 for 'Y'
  auto dragonInfo=Dragon_removeSkip(cache_DragonLen,nthGen,skip,nowDragon); //string, Gen
  //get Dragon [skip,skip+len)
  return Dragon_getDragon(dragonInfo.first,dragonInfo.second,len);
}
void Dragon(){
  //Dragon Curve
  /*설명 및 입력
  설명
    n세대 드래곤 커브 문자열을 구하고 싶습니다. 이 때 문자열 전체를 구하면 너무 기니, 문자열 중 p번째 글자부터 l글자만을 계산하는 프로그램을 작성하세요.
    Dragon curve: FX로 시작 -> FX+YF -> FX+YF+FX-YF
      X->X+YF, Y-> FX-Y (+,- 는 문자 취급)
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <=50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 세 개의 정수로 드래곤 커브의 세대 n (0 <= n <= 50)
      그리고 p 와 l (1 <= p <= 1,000,000,000 , 1 <= l <= 50) 이 주어집니다. n세대의 드래곤 커브 문자열의 길이는 항상 p+l 이상이라고 가정해도 좋습니다.
    int 범위로 조건부 해결 가능
      p는 int 범위이지만, 최대 경우의 수는 2^50이라 표현 불가능, 1,000,000,000 이상은 -2로 처리하여 해결하자.
  제한조건
    2초, 64MB
  */
  /*전략
    (실패)반복되는 수열이 존재한다 -> DP를 통해 길이와 값을 예상 가능
      -> 반복되는 것에 집중하여 문제를 어렵게 풀게됨. 수학적 접근도 중요하지만, 프로그래밍적 접근도 충분히 생각하자.
    Dynamic Programming
      skip 후 len만큼 길이를 구하는 것이다.
        skip을 구할때는 경우의 수만 DP를 이용하여 구한다.
        len을 구할때는, 규칙을 이용해 순서대로 출력한다.
  */
  //example for 
  //Dragon_example();
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int nthGen, skip, len;
    Dragon_Input(nthGen, skip, len);
    string result=Dragon_Algo(nthGen, skip, len);
    cout<<result<<'\n';
  }
}

int main(void){
  Dragon();
  
  return 0;
}