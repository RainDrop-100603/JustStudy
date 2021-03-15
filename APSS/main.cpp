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
int RESTORE_isInValid(const string& shortStr,const string& longStr){
  if(shortStr.size()>longStr.size()){
    return -1*RESTORE_isInValid(longStr,shortStr);
  }
  for(int i=0;i<=longStr.size()-shortStr.size();i++){
    bool invalid(true);
    for(int j=0;j<shortStr.size();j++){
      if(shortStr[j]!=longStr[i+j]){
        invalid=false;
        break;
      }
    }
    if(invalid){
      return 1;
    }
  }
  return 0;
}
vector<string> RESTORE_strOptimize(const vector<string>& strArr){
  vector<string> strArr_opti;
  vector<int> valid_arr(strArr.size(),1);
  for(int i=0;i<strArr.size();i++){
    //최적화, A가 B를 invalid하게 만들었다면, B가 invalid하게 만드는 모든것은 A가 invalid하게 만든다(포함관계 생각하자)
    if(valid_arr[i]==0){
      continue;
    }
    //Algo
    const string& ele(strArr[i]);
    for(int j=i+1;j<strArr.size();j++){
      //기저
      if(valid_arr[j]==0){
        continue;
      }
      //Algo
      const string& ele2(strArr[j]);
      int inValid=RESTORE_isInValid(ele,ele2);  //both valid:0, ele invalid: 1, ele2 invalid: -1
      if(inValid==-1){
        valid_arr[j]=0;
      }
      if(inValid==1){
        valid_arr[i]=0;
        break;  //invalid되면 더이상 비교할 필요가 없다.
      }
    }
  }
  for(int i=0;i<valid_arr.size();i++){
    if(valid_arr[i]){
      strArr_opti.push_back(strArr[i]);
    }
  }
  return strArr_opti;
}
void RESTORE_DP_prepare(vector<vector<int>>& DP_strSaved,vector<string>& strArr_opti){
  int strNum(strArr_opti.size());
  //DP(0,front) 
  for(int front=0;front<strNum;front++){
    DP_strSaved[0][front]=0;
  }
  //DP(front,back)
  for(int front=0;front<strNum;front++){
    for(int back=0;back<strNum;back++){
      if(front==back){
        continue;
      }
      //겹치는 정도 확인
      int len=min(strArr_opti[front].size(),strArr_opti[back].size());
      int savedLen=0;
      const string& frontStr=strArr_opti[front];
      const string& backStr=strArr_opti[back];
      for(int i=1;i<len;i++){
        bool isSaved(true);
        //하나하나비교 
        for(int j=0;j<i;j++){
          if(frontStr[frontStr.size()-i+j]!=backStr[j]){
            isSaved=false;
            break;
          }
        }
        //전부 겹치면 saved
        if(isSaved==true){
          savedLen=i;
        }
      }
      DP_strSaved[1<<front][back]=savedLen;
    }
  }
}
int RESTORE_DP(vector<vector<int>>& dp_bitmask,int now_bitmask,int add_str){
  int strNum=dp_bitmask[0].size();
  int& result=dp_bitmask[now_bitmask][add_str];
  if(result!=-1){
    return result;
  }
  result=0;
  //정답 chk
  if(now_bitmask==(1<<strNum)-1){
    for(int i=0;i<strNum;i++){
      result=max(result,RESTORE_DP(dp_bitmask,now_bitmask-(1<<i),i));
    }
    return result;
  }
  //general
  for(int front=0;front<strNum;front++){
    if((now_bitmask&1<<front)!=0){
      result=max(result,RESTORE_DP(dp_bitmask,now_bitmask-(1<<front),front)+dp_bitmask[1<<front][add_str]);
    }
  }
  return result;
}
string RESTORE_result(vector<vector<int>>& DP_strSaved,const vector<string>& strArr_opti){
  string result;
  int strNum=strArr_opti.size();
  int used_bitmask=(1<<strNum)-1;
  int back;
  for(back=0;back<strNum;back++){
    if(DP_strSaved[used_bitmask][0]==DP_strSaved[used_bitmask-(1<<back)][back]){
      used_bitmask-=(1<<back);
      result=strArr_opti[back];
      break;
    }
  }
  while(used_bitmask!=0){
    for(int front=0;front<strNum;front++){
      if((used_bitmask&1<<front)!=0){
        if(DP_strSaved[used_bitmask][back]==DP_strSaved[used_bitmask-(1<<front)][front]+DP_strSaved[1<<front][back]){
          used_bitmask-=(1<<front);
          const string& str_front=strArr_opti[front];
          result=str_front.substr(0,str_front.size()-DP_strSaved[1<<front][back])+result;
          back=front;
          break;
        }
      }
    }
  }
  return result;
}
string RESTORE_Algo(int strNum,vector<string> strArr){
  //한 문자열이 다른문자열에 온전히 포함되는 경우가 있다면, 제거
  vector<string> strArr_opti=RESTORE_strOptimize(strArr);
  //DP_준비
  int strNum_opti(strArr_opti.size()); 
  vector<vector<int>> DP_strSaved(1<<strNum_opti,vector<int>(strNum_opti,-1));  //DP(used_bitmask,add_str)=saved str len
  RESTORE_DP_prepare(DP_strSaved,strArr_opti);  //DP(1<<front,back), DP(0,front) 을 미리 저장한다.
  //result
  RESTORE_DP(DP_strSaved,(1<<strNum_opti)-1,0); //DP is such a history
  return RESTORE_result(DP_strSaved,strArr_opti);
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
      f(used_bitamsk,add_str) = used_bitamsk+ add_str을 할 때, saved_value(절약한 정도)
        f(used_bitmask,add_str) = for(x=ele of used_bitmask) min(f(used_bitmask without add_str,x)+f2(x,add_str))
      f2(front,back)=saved_value: front-back로 이어질 때, 절약되는 정도
        f2(front,back) = f(1<<front,back)
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