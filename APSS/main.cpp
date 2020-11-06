//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <map>

using namespace std;
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
void Ocr_Input(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
  cin>>wordNum>>sentenceNum;
  for(int i=0;i<wordNum;i++){
    string tmp;cin>>tmp;
    wordArrMap.insert({tmp,i});
    wordArr.push_back(tmp);
  }
  firstPoss.resize(wordNum);
  for(auto& ele: firstPoss)
    scanf("%lf",&ele);
  nextPoss=classifiPoss=vector<vector<double>>(wordNum,vector<double>(wordNum));
  for(auto& ele: nextPoss)
    for(auto& ele2: ele)
      scanf("%lf",&ele2);
  for(auto& ele: classifiPoss)
    for(auto& ele2: ele)
      scanf("%lf",&ele2);
  sentenceArr.resize(sentenceNum);
  cin.ignore();
  for(auto& ele: sentenceArr)
    getline(cin,ele);
}
double Ocr_DP1(vector<vector<double>>& DP_Ocr1,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,int prev, int nextGuess){
  double& result=DP_Ocr1[prev][nextGuess];
  if(result>-0.5)
    return result;
  result=0;
  for(int i=0;i<nextPoss[0].size();i++)
    result+=nextPoss[prev][i]*classifiPoss[i][nextGuess];
  return result;
}
double Ocr_DPposs(vector<vector<double>>& DP_Ocr1,vector<double>& firstPoss,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,
                  vector<vector<double>>& DP_Poss,vector<vector<int>>& DP_Path, vector<int>& wordsIdx,int idx,int nowWord){
  //기저, 범위 밖, 이미 값이 있는경우
  if(idx==wordsIdx.size())
    return 1;
  double& result=DP_Poss[idx+1][nowWord];
  if(result>-0.5) 
    return result;
  //함수 진행
  int wordNum=DP_Poss[0].size();
  result=0;
  int& path=DP_Path[idx+1][nowWord];
  //맨처음, idx==-1인 경우
  if(idx==-1){
    double nextGuessPoss=0;
    for(int i=0;i<wordNum;i++)  //실제 다음위치가 i 값인데, 이를 wordsIdx[0] 으로 인식했을 확률
      nextGuessPoss+=firstPoss[i]*classifiPoss[i][wordsIdx[0]];
    for(int i=0;i<wordNum;i++){
      double tmp=firstPoss[i]*classifiPoss[i][wordsIdx[0]]*Ocr_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordsIdx,0,i)/nextGuessPoss;
      if(cmpDouble_AbsRel(tmp,result)==1){
        result=tmp;
        path=i;
      }
    }
  }
  //함수
  for(int i=0;i<wordNum;i++){
    double nextGuessPoss=Ocr_DP1(DP_Ocr1,nextPoss,classifiPoss,nowWord,wordsIdx[idx+1]);
    double tmp=nextPoss[nowWord][i]*classifiPoss[i][wordsIdx[idx+1]]*Ocr_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordsIdx,idx+1,i)/nextGuessPoss;
    if(cmpDouble_AbsRel(tmp,result)==1){
      result=tmp;
      path=i;
    }
  }
  return result;
}
vector<string> Ocr_Algo(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,
                        vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
  /*
  10초, 64MB, 테스트케이스=문장의 수 20개
  입력: 분석이 끝난 과거 자료의 통계치, 분류기가 인식한 문장으로구성, 자세한 내용은 문제에서 확인
  출력: 한 문장마다 한 줄에 주어진 인식 결과에 대해 조건주 출현 확률이 가장 높은 문장을 출력, 같은 확률을 가진 문장이 여러개라면 어떤것을 출력해도 좋다.
  전략1
    Dynamic Programming
      준비: sentenceArr->sentence->word 로 분해
      해석: sentence의 word의 길이 n, 등장 가능한 word의 개수 m
            sentence X에 대해, 각 word는 x0 x2 ... xn-1 이다 (인식된 결과이므로, 실제 문자와 다를 수 있다.)
            이전 문자가 Y일 때, 다음으로 등장한 문자가 Z일 확률 nextPoss[Y][Z]
        DP  이전 문자가 Y일 때, 다음으로 인식된 문자가 R일 확률 p(Y,R)=nextPoss[Y][0]*classifiPoss[0][R]+ ... +nextPoss[Y][m-1]*classifiPoss[m-1][R]
            이전 문자가 Y이고, 인식된 문자가 R일 때, 실제 등장한 문자가 Z일 가능성 rp(Y,R,Z)=nextPoss[Y][Z]*classifiPoss[Z][R]/p(Y,R)
              맨 처음 문자는 이전문자를 -1이라고 가정하고 처리하자
      Ocr_DP1(이전문자 Y,인식된문자 R)=가능성
        DP: 500*500
      func(sentence 에서 idx 번째 word,실제 word:X)=idx번째 word가 X일 때, idx+1부터 시작하는 sentence의 조건부 확률 최대치
          idx부터 시작하는 sentence의 조건부 확률 최대치 = DP[0][0] 
        DP: 101*500, idx번째 정보는 idx+1 위치에 저장 
        substructure: func(idx,nowWord)=for(nextWord=word range), max, nextPoss[Y][Z]*classifiPoss[Z][R]/Ocr_DP1(Y,R)*func(idx+1,nextWord)
        기저: idx==sentenceLen: return 1, idx==-1: nextPoss 대신 firstPoss 사용 
        정답: Ocr_DP2 func_DP를 이용하여 최적 경로를 따라간다.
    의문점
      Ocr_DP2 있는것이 속도 측면에서 유리한가? 경로를 추적해야 하므로 Ocr_DP2 필요한긴 하지만 속도적인 측면에서 어떤지.
        -> 함수 실행시간이 1이므로 속도측면에서 유리하지 않다. 경로추적은 전용 DP를 추가하여 해결하자
    time complexity
      #func(n*m)*func(m)+#Ocr_DP2(n*m^2)*Ocr_DP2(1)+#Ocr_DP1(n*m)*Ocr_DP1(m)=O(n*m^2)
    mem complexity
      DP(m*m*m)=O(m^3)
  */
  //DP 생성
  vector<vector<double>> DP_Ocr1(wordNum,vector<double>(wordNum,-1));
  //정답 생성
  vector<string> result;
  for(int cnt=0;cnt<sentenceNum;cnt++){
    //sentence의 각 word 분리, idx로 치환하여저장
    vector<int> wordsIdx;
    string sentence=sentenceArr[cnt].substr(2); //앞에 두개는 sentence의 word 갯수, 공백(스페이스바)
    string tmpWord;
    for(auto iter=sentence.begin();iter!=sentence.end();iter++){
      if(*iter==' '){
        wordsIdx.push_back(wordArrMap.find(tmpWord)->second);
        tmpWord.clear();
      }else{
        tmpWord.push_back(*iter);
      }
    }
    wordsIdx.push_back(wordArrMap.find(tmpWord)->second);
    //조건부 출현확률 최대치 도출
    vector<vector<double>> DP_Poss(wordsIdx.size()+1,vector<double>(wordNum,-1));
    vector<vector<int>> DP_Path(wordsIdx.size()+1,vector<int>(wordNum,-1));
    double maxPoss=Ocr_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordsIdx,-1,0);
    //경로 도출
    vector<int> path;
    int frag=DP_Path[0][0];
    for(int i=0;i<wordsIdx.size();i++){
      path.push_back(frag);
      frag=DP_Path[i+1][frag];
    }
    string tmpResult;
    for(auto& ele: path){
      tmpResult+=wordArr[ele]+' ';
    }
    tmpResult.pop_back(); //마지막 공백 제거 
    //result에 정답 입력
    result.push_back(move(tmpResult));
  }
  return result;
}
void Ocr(){
  int wordNum,sentenceNum;
  vector<string> wordArr,sentenceArr;   //i, am, a, boy, buy 각 단어 저장, i am a boy 각 문장 저장
  map<string,int> wordArrMap;
  vector<double> firstPoss;    //맨 처음에 각 word가 나올 확률
  vector<vector<double>> nextPoss,classifiPoss; //A(ij)=i단어 다음 j단어가 나올 확률, B(ij)=i단어를 j단어로 분류할 확률
  Ocr_Input(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
  vector<string> result=Ocr_Algo(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
  for(auto& ele:result){
    cout<<ele<<'\n';
  }
}

int main(void){
  Ocr();
  return 0;
}