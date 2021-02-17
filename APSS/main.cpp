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
int Dragon_getCases(int nthGen){
  if(nthGen==0){
    return 1;
  }
  //2^nthGen== x+y의 개수, -2: 앞부분 F하나 빼기, 뒷부분 +(-) 하나 빼기 
  //3배수: 구조가  F  X(or Y) +(or -)
  double result=pow(2,nthGen)*3-2; 
  //chk overflow
  if(result>INT32_MAX){
    result=-2;
  }
  //return
  return result;
}
void Dragon_del_skip_make_history(int nthGen, int skip,vector<pair<string,int>>& history){
  //기저 
  if(skip==0){
    return;
  }
  //get #cases and next_string(in case of X or Y)
  string& last_string=history.back().first;
  int cases(1);  // + or - or F, cases == 1
  string next_string;
   //nthGen > 0 아직 string이 분리되어야함 
  if(nthGen>0){
    if(last_string.front()=='X'){
      cases=Dragon_getCases(nthGen);
      next_string="X+YF";
    }else if(last_string.front()=='Y'){
      cases=Dragon_getCases(nthGen);
      next_string="FX-Y";
    }
  }
  //history update
  if(last_string.size()==1){
    history.pop_back();
  }else{
    last_string=last_string.substr(1);
  }
  //compare with skip
  if(cases>skip||cases==-2){
    history.push_back({next_string,nthGen-1});  //#cases > skip 이라면, 반드시 낮은 Gen이 있을 수밖에 없다.
    Dragon_del_skip_make_history(nthGen-1,skip,history);
  }else if(cases<skip){
    Dragon_del_skip_make_history(nthGen,skip-cases,history);
  }else{
    return; //cases-skip==0
  }
}
string Dragon_getDragon(vector<pair<string,int>>& history, int len){
  //기저
  if(len==0){
    return string();
  }
  //prepare
  string& last_string=history.back().first;
  int nthGen=history.back().second;
  string result;
  //nthGen == 0 string이 최종 분리된 상태 
  if(nthGen==0){
    int inputSize=min(len,static_cast<int>(last_string.size()));
    for(int i=0;i<inputSize;i++){
      result.push_back(last_string[i]);
    }
    //inputSize==len 인 경우 result 완성, inputSize==last_string_len 인 경우 last_string을 모두 result에 포함시켰으므로 pop_back()
    history.pop_back();
    return result;
  }
  //nthGen > 0 아직 string이 분리되어야함 
  if(nthGen>0){
    char ele=last_string.front();
    //history update
    if(last_string.size()>1){
      last_string=last_string.substr(1);
    }else{
      history.pop_back();
    }
    //push element to result
    if(ele=='X'){
      history.push_back({"X+YF", nthGen-1});
      result+=Dragon_getDragon(history, len-result.size());
    }else if(ele=='Y'){
      history.push_back({"FX-Y", nthGen-1});
      result+=Dragon_getDragon(history, len-result.size());
    }else{
      result.push_back(ele);
    }
  }
  //result 길이에 따라 차이 
  if(result.size()==len){
    return result;
  }else{
    return result+Dragon_getDragon(history, len-result.size());
  }
} 
string Dragon_Algo(int nthGen,int skip,int len){
  skip--;
  //remove skip and get history
  vector<pair<string,int>> history(1,{"FX",nthGen});
  Dragon_del_skip_make_history(nthGen,skip,history); //string, Gen
  //make result from history
  return Dragon_getDragon(history,len);
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