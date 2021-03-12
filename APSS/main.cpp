//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @*@* 조건을 이용하여 연산을 줄인다. 특정 순열보다 작은 순열에 대한 계산. history의 필요유무에 따라 다른 DP
void RESTORE_Input(int& strNum,vector<string>& strArr){
  cin>>strNum;
  strArr.resize(strNum);
  for(auto& ele: strArr){
    cin>>ele;
  }
}
string RESTORE_strMerge(const string strShort,const string strLong){
  if(strShort.size()>strLong.size()){
    return RESTORE_strMerge(strLong,strShort);
  }
  int skipped_count=0;
  //strShort가 왼쪽에 있을 때
  for(int i=1;i<strShort.size();i++){
    bool canMerge(true);
    for(int j=0;j<i;j++){
      if(strShort[strShort.size()-i+j]!=strLong[j]){
        canMerge=false;
        break;
      }
    }
    if(canMerge){
      skipped_count=i;
    }
  }
  string tmp_result;
  for(int i=0;i<strShort.size()-skipped_count;i++){
    tmp_result+=strShort[i];
  }
  tmp_result+=strLong;
  //strShort와 strLong이 겹칠 때
  for(int i=0;i<strLong.size()-strShort.size();i++){
    bool canMerge(true);
    for(int j=0;j<strShort.size();i++){
      if(strShort[j]!=strLong[i+j]){
        canMerge=false;
        break;
      }
    }
    if(canMerge){
      return strLong;
    }
  }
  //strShort가 오른쪽에 있을 때
  int skipped_count2(0);
  for(int i=skipped_count+1;i<strShort.size();i++){
    bool canMerge(true);
    for(int j=0;j<i;j++){
      if(strLong[strLong.size()-i+j]!=strShort[j]){
        canMerge=false;
        break;
      }
    }
    if(canMerge){
      skipped_count2=i;
    }
  }
  if(skipped_count2!=0){
    tmp_result=strLong;
    for(int i=skipped_count2;i<strShort.size();i++){
      tmp_result+=strShort[i];
    }
  }
  return tmp_result;
}
string RESTORE_DP(vector<string>& dp_bitmask,int now_bitmask){
  //기저
  string& result=dp_bitmask[now_bitmask];
  if(result.size()!=0){
    return result;
  } 
  //func
  int strNum=stoi(dp_bitmask[0]);
  int tmp_len=1000; //max=600
  for(int i=0;i<strNum;i++){
    if((1<<i&now_bitmask)!=0){
      string tmp_str=RESTORE_DP(dp_bitmask,now_bitmask-(1<<i));
      if(tmp_str.size()>tmp_len){
        continue;
      }
      string tmp_result=RESTORE_strMerge(dp_bitmask[1<<i],tmp_str);
      if(tmp_result.size()<tmp_len){
        result=tmp_result;
        tmp_len=result.size();
      }
    }
  }
  return result;
}
string RESTORE_Algo(int strNum,vector<string> strArr){
  //DP생성
  vector<string> dp_bitmask(1<<strNum);
  for(int i=0;i<strNum;i++){
    dp_bitmask[1<<i]=strArr[i];
  }
  dp_bitmask[0]=to_string(strNum);  //0은 어차피 사용하지 않으므로, strNum을 넣어준다.
  //결과 return
  return RESTORE_DP(dp_bitmask,(1<<strNum)-1);
}
void RESTORE(){
  //RESTORE
  /*설명 및 입력
  설명
    여러개의 문자열이 주어진다. 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력하라
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C(C≤50)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 부분 문자열의 수 k(1≤k≤15)가 주어지고, 다음 k줄에 알파벳 소문자로만 구성된 문자열 조각이 주어집니다. 
    각 문자열 조각의 길이는 1 이상 40 이하입니다.
  출력
    각 테스트 케이스마다 한 줄로, 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력합니다.
  제한조건
    2초, 64MB
  */
  /*전략
  전략1
    앞, 뒤를 연결하며 많은 조합을 시도해본다
      DP[bitmask_used]=string: 사용된 원소들 중에 가장 짧은 str을 저장한다
        ex) DP[1101] = minLen(getStr(DP[1100],DP[0001]),getStr(DP[1001],DP[0100]),getStr(...))
    시간:
      getStr: O(strlen^2)
      #DP_func: for(1~n), sum(x(n-x))=n^3
      Time:O(n^3*strlen^2), n<16, strLen<601
    문제
      중간 위치에서, str의 길이가 같다면 두개 모두 고려해야 하지 않을까?
        ex) DP[11000101]= AABBCC or ABCABC
      위 문제를 해결하지 못함
  전략2
    정답에서 하나씩 빼는 방법으로 생각하자
      f(used_bitamsk,last) = saved_value(절약한 정도)
        f(used_bitmask,last) = for(x=ele of used_bitmask) min(f(used_bitmask without last,x)+f2(x,last))
      f2(front,back)=saved_value: front-back로 이어질 때, 절약되는 정도
    시간
      f: size(2^16*15)*time(15)
      f2: size(15*15)*time(40)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int strNum;
    vector<string> strArr;
    RESTORE_Input(strNum, strArr);
    string result=RESTORE_Algo(strNum, strArr);
    cout<<result<<'\n';
  }
}

int main(void){
  RESTORE();
  return 0;
}