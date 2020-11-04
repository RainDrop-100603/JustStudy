//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

void Ocr_Input(int& wordNum,int& sentenceNum,vector<string>& wordArr,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
  cin>>wordNum>>sentenceNum;
  wordArr.resize(wordNum);
  for(auto& ele:wordArr)
    cin>>ele;
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
vector<string> Ocr_Algo(int& wordNum,int& sentenceNum,vector<string>& wordArr,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
  /*
  10초, 64MB, 테스트케이스=문장의 수 20개
  입력: 분석이 끝난 과거 자료의 통계치, 분류기가 인식한 문장으로구성, 자세한 내용은 문제에서 확인
  출력: 한 뭉장마다 한 줄에 주어진 인식 결과에 대해 조건주 출현 확률이 가장 높은 문장을 출력, 같은 확률을 가진 문장이 여러개라면 어떤것을 출력해도 좋다.
  제한: 절박도 최대=100*1000=100000
  전략1
    Dynamic Programming
      준비: sentenceArr->sentence->word 로 분해
      해석: sentence의 word의 길이 n, 등장 가능한 word의 개수 m
            sentence X에 대해, 각 word는 x0 x2 ... xn-1 이다 (인식된 결과이므로, 실제 문자와 다를 수 있다.)
            이전 문자가 Y일 때, 다음으로 등장한 문자가 Z일 확률 nextPoss[Y][Z]
        DP  이전 문자가 Y일 때, 다음으로 인식된 문자가 R일 확률 p(Y,R)=nextPoss[Y][0]*classifiPoss[0][R]+ ... +nextPoss[Y][m-1]*classifiPoss[m-1][R]
        DP  이전 문자가 Y이고, 인식된 문자가 R일 때, 실제 등장한 문자가 Z일 가능성 rp(Y,R,Z)=nextPoss[Y][Z]*classifiPoss[Z][R]/p(Y,R)
      Ocr_DP1(이전문자 Y,인식된문자 R)=가능성
        DP: 500*500
      Ocr_DP2(이전문자 Y,인식된문자 R, 실제문자 Z)=가능성
        DP: 501*500*500
        맨 첫번째 문자는 이전문자가 없다. 따라서 이전문자를 -1로 해주고, DP에는 Y+1위치에 저장하도록 하자
        기저: Y==0인 모든 경우를 우선 설정해준다.
      func(sentence 에서 idx 번째 word,idx-1에서 선택한 word)=idx번째 word부터 시작할때 최대 possibility
        DP: 100*500
        substructure: func(idx,prevWord)=for(nowWord=word range), max, Ocr_DP2(prevWord,sentence[idx],nowWord)*func(idx+1,nowWord)
        기저: idx>sentenceLen: return 1, 맨 처음에 선택한 word는 -1
        정답: Ocr_DP2 func_DP를 이용하여 최적 경로를 따라간다.
    의문점
      Ocr_DP2 있는것이 속도 측면에서 유리한가? 경로를 추적해야 하므로 Ocr_DP2 필요한긴 하지만 속도적인 측면에서 어떤지.
    time complexity
      #func(n*m)*func(m)+#Ocr_DP2(n*m^2)*Ocr_DP2(1)+#Ocr_DP1(n*m)*Ocr_DP1(m)=O(n*m^2)
    mem complexity
      DP(m*m*m)=O(m^3)
  */
  //DP 생성
  vector<vector<double>> DP_Ocr1(wordNum,vector<double>(wordNum,-1));
  vector<vector<vector<double>>> DP_Ocr2(wordNum+1,vector<vector<double>>(wordNum,vector<double>(wordNum,-1)));
  //DP 기저
  for(int guess=0;guess<wordNum;guess++){
    for(int real=0;real<wordNum;real++){
      double guessPoss(0);
      for(int k=0;k<wordNum;k++)
        guessPoss+=firstPoss[k]*classifiPoss[k][guess];
      DP_Ocr2[0][guess][real]=firstPoss[real]*classifiPoss[real][guess]/guessPoss;
    }
  }
  //정답 생성
  vector<string> result;
  for(int cnt=0;cnt<sentenceNum;cnt++){
    //sentence의 각 word 분리
    vector<int> wordsIdx;
    string sentence=sentenceArr[cnt].substr(2); //앞에 두개는 sentence의 word 갯수, 공백(스페이스바)
    string tmpWord;
    for(auto iter=sentence.begin();iter!=sentence.end();iter++){
      if(*iter==' '){
        wordsIdx.push_back(tmpWord);
        tmpWord.clear();
      }else{
        tmpWord.push_back(*iter);
      }
    }
    wordsIdx.push_back(move(tmpWord));
    //조건부 출현확률 최대치 도출
    double maxPoss=Ocr_DPposs(DP_Ocr1,DP_Ocr2,wordsIdx,wordsIdx.front(),-1);
  }
}
void Ocr(){
  int wordNum,sentenceNum;
  vector<string> wordArr,sentenceArr;   //i, am, a, boy, buy 각 단어 저장, i am a boy 각 문장 저장
  vector<double> firstPoss;    //맨 처음에 각 word가 나올 확률
  vector<vector<double>> nextPoss,classifiPoss; //A(ij)=i단어 다음 j단어가 나올 확률, B(ij)=i단어를 j단어로 분류할 확률
  Ocr_Input(wordNum,sentenceNum,wordArr,firstPoss,nextPoss,classifiPoss,sentenceArr);
  vector<string> result=Ocr_Algo(wordNum,sentenceNum,wordArr,firstPoss,nextPoss,classifiPoss,sentenceArr);
  for(auto& ele:result){
    cout<<ele<<'\n';
  }
}

int main(void){
  Ocr();
  return 0;
}