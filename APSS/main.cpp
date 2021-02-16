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
    return 1;
  }
  //Algo 
  result=Dragon_getDragonLen(cache_DragonLen,nthGen-1)*2+2;
  //chk Overflow
  if(result<0){
    result=-2;
  }
  //return
  return result;
}
string Dragon_getDragon(vector<int>& cache_DragonLen, int nthGen, int skip, string nowDragon, int len){
  //remove skip and get dragon
  string result;
  //remove skip
  if(skip!=0){
    //get num of cases of nowDragon[0]
    int numOfCases(1);  // + or - or F
    string lowerGenDragon;
    if(nowDragon[0]=='X' &&nthGen!=0){
      numOfCases=Dragon_getDragonLen(cache_DragonLen, nthGen);
      lowerGenDragon="X+YF";
    }else if(nowDragon[0]=='Y' &&nthGen!=0){
      numOfCases=Dragon_getDragonLen(cache_DragonLen, nthGen);
      lowerGenDragon="FX-Y";
    }
    //remove skip
    if(skip<numOfCases||numOfCases==-2){  //-2 means overflow, means larger than skip
    //this result is not full result, at least result[0]
      result=Dragon_getDragon(cache_DragonLen, nthGen-1,skip,lowerGenDragon,len);
      //front of nowDragon is used in prev section
      if(nowDragon.size()==1){
        return result;
      }
    }else{
      Dragon_getDragon(cache_DragonLen, nthGen,skip-numOfCases,nowDragon.substr(1),len);
    }
  }
  //get Dragon, result.size()!=0 means, result is part of full result
  if(skip==0||result.size()!=0){
    //기저
    if(len==0){
      return string();
    }
    if(result.size()==len){
      return result;
    }
    //Algo
    for(auto& ele:nowDragon){
      if(ele=='X'&&nthGen!=0){
        result+=Dragon_getDragon(cache_DragonLen, nthGen-1,0,"X+YF",len-result.size());
      }else if(ele=='Y'&&nthGen!=0){
        result+=Dragon_getDragon(cache_DragonLen, nthGen-1,0,"FX-Y",len-result.size());
      }else{
        result.push_back(ele);
      }
      if(result.size()==len){
        return result;
      }
    }
  }
  return result;
}

string Dragon_Algo(int nthGen,int skip,int len){
  skip--;
  vector<int> cache_DragonLen(nthGen,-1);
  string result=Dragon_getDragon(cache_DragonLen, nthGen,skip,"FX",len); //string, Gen
  return result;
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
 /*전략
    (실패) skip삭제와 정답을 동시해 구하려니 답이 없어졌다.
    history를 이용해서 답은 따로 구하자 
      history: low Generation으로 이동할 때, 현재 Dragon의 남은 값들을 저장하는 것.
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