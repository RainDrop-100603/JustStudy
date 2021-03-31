//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

using namespace std;

//https://www.youtube.com/watch?v=x7STjpcKZP8 
//사회복무요원 교육 


// @*@*, c(i)=W^(i) * c(0), W는 단순히 확률 관련 부분이고, 실제로 고민할 것은 열벡터 c 부분이다.
// p(x)=w1p(x-1)+...+wnp(x-n)과 같이 여러 시간대의 항목이 필요할경우, 모두 열벡터에 넣어주면 된다.
template <class T>
vector<vector<T>> matrix2_mult(const vector<vector<T>>& m1,const vector<vector<T>>& m2){
  //간단한 에러체크, 모든 경우를 체크하진 않는다.
  if(m1.size()==0||m2.size()==0||m1[0].size()==0||m2[0].size()==0||m1[0].size()!=m2.size()){
    cout<<"matrix2_mult Error!"<<endl;
    return vector<vector<T>>();
  }
  //계산
  long long row(m1.size()), mid(m2.size()), col(m2[0].size());
  vector<vector<T>> result(row,vector<T>(col,0));
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      for(int z=0;z<mid;z++){
        result[i][j]+=m1[i][z]*m2[z][j];
      }
    }
  }
  return result;
}
template <class T>
vector<vector<T>> matrix2_pow(const vector<vector<T>>& m1, long long pow){
  if(pow==1){
    return m1;
  }
  vector<vector<T>> result=matrix2_pow<T>(m1,pow/2);
  result=matrix2_mult(result,result);
  if(pow%2==1){
    result=matrix2_mult<T>(result,m1);
  }
  return result;
}
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
  //열벡터 생성, 초기화
  vector<vector<double>> colVector(4*songNum,vector<double>(1,0));
  colVector[0][0]=1;
  //W: 곱셈 벡터 생성
  vector<vector<double>> wMatrix(4*songNum,vector<double>(4*songNum,0));
  for(int row=0;row<4*songNum;row++){
    //i-1 ~ i-3 처리
    if(row%4!=0){
      wMatrix[row][row-1]=1;
      continue;
    }
    //i 처리
    int nextSongIdx=row/4;
    for(int col=0;col<4*songNum;col++){
      int songIdx=col/4;
      int songLen=songPlaytime[songIdx];
      int timeAgo=col%4+1;  //지나간 시간 
      if(timeAgo==songLen){
        wMatrix[row][col]=possibility[songIdx][nextSongIdx];
      }
    }
  }
  //계산
  vector<vector<double>> wResult=matrix2_pow<double>(wMatrix,targetTime);
  colVector=matrix2_mult<double>(wResult,colVector);
  //result
  vector<double> result;
  for(auto& songIdx:favSongList){
    double tmp_result=0;
    for(int i=0;i<songPlaytime[songIdx];i++){
      tmp_result+=colVector[songIdx*4+i][0];
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
      time Over
  전략2
    Dynamic Programming
      행렬곱을 이용한다. C(i)=W^(i)C(0), i<0 인부분은 0으로 처리하면 된다(확률이기 때문에)
      열행렬 C(i): for(x=0~n-1) p(x,i),p(x,i-1),p(x,i-2),p(x,i-3)
      행렬 W: 4n*4n
        p(x,i+1)=for(x=1~n) p(x,i)*w(x,i)+..+p(x,i-3)*w(x,i-3) 
        p(x,i)~p(xi-2): 기존것 그대로 
      행렬 거듭제곱 
        시간: M^3 lgN , M=행렬크기, N=거듭제곱할 수
      정답
        c(i)를 이용해서 구한다.
    시간:
      O((4N)^3 * lgK)=8,000,000*lg(1,000,000) = 110,000,000
    공간:
      O(4N + (4N)^2)
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
    cout.precision(10);
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