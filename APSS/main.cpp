//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

// @* algo와 algo2의 속도차이에 유의하자(하드웨어적 원인). 속도가 느린 장치에 자주 접근할수록, 속도는 느려진다.
void GENIUS_Input(int& songNum,int& targetTime,int& favSongNum,vector<int>& songPlaytime,vector<int>& favSongList,vector<vector<double>>& possibility){
  cin>>songNum>>targetTime>>favSongNum;
  songPlaytime.resize(songNum);
  for(auto& ele:songPlaytime){
    cin>>ele;
  }
  possibility.resize(songNum);//열 resize
  for(auto& ele: possibility){
    ele.resize(songNum);//행 resize
    for(auto& ele2: ele){
      cin>>ele2;
    }
  }
  favSongList.resize(favSongNum);
  for(auto& ele:favSongList){
    cin>>ele;
  }
}
vector<double> GENIUS_Algo(int& songNum,int& targetTime,int& favSongNum,vector<int>& songPlaytime,vector<int>& favSongList,vector<vector<double>>& possibility){
  //DP생성, 0분 초기화
  vector<vector<double>> DP_cache(songNum,vector<double>(9,0));
  DP_cache[0][0]=1;
  //Algo 1~3분 초기화 (if문 없애주기 위함)
  for(int time=1;time<=min(3,targetTime);time++){
    for(int now_song=0;now_song<songNum;now_song++){
      double tmp=0;
      for(int prev_song=0;prev_song<songNum;prev_song++){
        int prev_song_time=songPlaytime[prev_song];
        if(prev_song_time<=time){
          tmp+=DP_cache[prev_song][time-prev_song_time]*possibility[prev_song][now_song];
        }
      }
      DP_cache[now_song][time]=tmp;
    }  
  }
  //Algo, 4 ~ targetTime
  for(int time=max(4,targetTime);time<=targetTime;time++){
    for(int now_song=0;now_song<songNum;now_song++){
      double tmp=0;
      for(int prev_song=0;prev_song<songNum;prev_song++){
        tmp+=DP_cache[prev_song][(time-songPlaytime[prev_song])%9]*possibility[prev_song][now_song];
      }
      DP_cache[now_song][(time)%9]=tmp;
    }  
  }
  //test
  cout<<"cache===================\n";
  for(auto& ele: DP_cache){
    for(auto& ele2: ele){
      cout<<ele2<<" ";
    }
    cout<<"\n";
  }
  cout<<"--------------------------------------\n";
  //result
  vector<double> result;
  for(auto& songIdx:favSongList){
    double tmp_result=0;
    for(int i=0;i<songPlaytime[songIdx];i++){
      tmp_result+=DP_cache[songIdx][(targetTime-i)%9];
    }
    result.push_back(tmp_result);
  }
  return result;
}
void GENIUS(){
  //GENIUS
  /*설명 및 입력
  설명
    지니어스를 사용하면 한 곡 다음에 다음 곡이 재생될 확률은 두 곡의 유사도에 따라 결정됩니다.
    음악들 간의 유사도를 조사해, i 번 곡 다음에 j 번 곡이 재생될 확률을 나타내는 확률 행렬 T 를 만들었습니다.
    K 분 30초가 지난 후 태윤이가 좋아하는 곡이 재생되고 있을 확률은 얼마일까요? 
    MP3 플레이어에 들어 있는 곡들의 길이는 모두 1분, 2분, 3분 혹은 4분입니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 MP3 플레이어에 들어 있는 곡의 수 N (1 <= N <= 50 ) 과 K (1 <= K <= 1,000,000) , 
      그리고 태윤이가 좋아하는 곡의 수 M (1 <= M <= 10) 이 주어집니다. 
    그 다음 줄에는 N 개의 정수로 각 곡의 길이 Li 가 분 단위로 주어지고, 그 후 N 줄에는 한 곡이 재생된 후 다음 곡이 재생될 확률을 나타내는 행렬 T 가 주어집니다. 
    T 의 i 번 줄의 j 번 숫자 (0 <= i,j < N) T[i,j] 는 i 번 곡이 끝난 뒤 j 번 곡을 재생할 확률을 나타냅니다. T 의 각 행의 합은 1 입니다. 
    각 테스트 케이스의 마지막 줄에는 M 개의 정수로 태윤이가 좋아하는 곡의 번호 Qi 가 주어집니다.
  출력
    각 테스트 케이스마다 한 줄로 태윤이가 좋아하는 M 개의 곡에 대해 각 곡이 재생되고 있을 확률을 출력합니다. 
    10^-7 이하의 절대/상대 오차가 있는 답은 정답으로 인정됩니다.
  제한조건
    20초, 64MB
  */
  /*힌트
    K분 30초가 지난 후의 곡의 확률은 아래 것들의 합이다.
      K분에 바뀐 {1분,2분,3분,4분} 노래 : K-1 ~ K-4분전에 시작해 K분에 끝나는 노래 * 현재 내가 좋아하는 노래{1,2,3,4}가 등장할 확률
      K-1분에 {2분,3분,4분} 바뀐 노래: K-2~K-5, same as others
      K-2분에 {3분,4분} 바뀐 노래: K-3~K-6, same as others
      K-3분에 {4분} 바뀐 노래: K-4 ~ K-7 분에 시작해 K-3분에 끝나는 노래 * 현재 내가 좋아하는 노래{4}가 등장할 확률
    DP: sliding window기법을 사용할 수 있다.
      cache에는 현재시간 -7분 ~ 현재시간 까지 저장해야 한다. 길이는 8+1(여유분)
      cache에는 모든 노래에 대한 확률이 있어야 한다. 높이는 N
      cache[song][time%9]=time에 시작한 song을 의미한다. 
        cache[song][now%9]=for(x=each song) sum(cache[now_song][(now_time-x_time)%9]*possibility[x_song][now_song])
      초기값은 0번곡으로 시작, cache[0][0]에 저장한다
    위 두개를 합치면 정답은
      for(auto& ele: fav song)
        for(int i=0;i<ele.time;i++)
          result+=cache[ele.idx][(now-i)%9];
  */
  /*전략
  전략1
    Dynamic Programing
      sliding window 기법을 사용한다.
      작은단위 -> 큰단위 DP (time 0~K)
      금액과 예산은 모두 100으로 먼저 나눈뒤 사용한다.
      cache[song][now%9]=for(x=each song) sum(cache[now_song][(now_time-x_time)%9]*possibility[x_song][now_song])
        cache 크기: 8+1
        연산시간: N:50 각 노래
        연산횟수: N:50 * K:1,000,000(지난 시간)
      정답
        for(auto& ele: fav song)
          for(int i=0;i<ele.time;i++)
            result+=cache[ele.idx][(now-i)%9];
    시간:
      O(N^2 * K), 50^2 * 1,000,000=2,500,000,000
    크기:
      O(N), 50*9=450
    sol 유의사항
      
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int songNum,targetTime,favSongNum;
    vector<int> songPlaytime,favSongList;
    vector<vector<double>> possibility;
    GENIUS_Input(songNum,targetTime,favSongNum,songPlaytime,favSongList,possibility);
    vector<double> result=GENIUS_Algo(songNum,targetTime,favSongNum,songPlaytime,favSongList,possibility);
    cout<<"result: ";
    for(auto& ele:result){
      cout<<ele<<" ";
    }
    cout<<'\n';
  }
}

int main(void){
  GENIUS();
  return 0;
}