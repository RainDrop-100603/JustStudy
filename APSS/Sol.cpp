#include "Sol.h"

void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr){
  for(int i=0;i<25;i++){
    probTable[i]=rand()%26+'A';
  }
  int len=rand()%10+1;
  for(int i=0;i<len;i++){
    int numLen=rand()%10+1;
    string tmp;
    for(int j=0;j<numLen;j++){
      tmp.push_back(rand()%26+'A');
    }
    wordArr.push_back(tmp);
  }
}
void BoggleInput(vector<char>& probTable, vector<string>& wordArr){
  for(int i=0;i<5;i++){
    string tmpS;
    cin>>tmpS;
    for(int j=0;j<5;j++){
      probTable[5*i+j]=tmpS[j];
    }
  }
  int wordNum;
  cin>>wordNum;
  string tmpS;
  for(int i=0;i<wordNum;i++){
    cin>>tmpS;
    wordArr.push_back(tmpS);
  }
}
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr){
  /*
    제한시간 10초, 제한 메모리 2^16Kb=64MB
    brute force
      8방향을 확인하여 단어를 순서대로 만든다 -> R, E, P, E, A, T
        bool boggle(string word, int idx, pair<int,int> point);  //word의 idx번째가 point와 값이 같은지 chk;
      time complexity : 단어의 길이 N 개수 M, M*25*8^(N-1), 지수시간 
    graph
      DFS나 BFS는 brute force와 다를것이 없어보인다.
    DP1
      단어에서 각 원소가 있는 위치를 저장한다 ex) p r e t t y 에서 행렬을 한번만 순회하며 각 원소가 있는 위치를 저장한다.
      맨 처음 위치가 존재한다면, 다음 원소가 기존 원소와 인접하는지 확인 -> 상수 연산하면 되므로 1 cost
        인접하는 경우, 다음 원소 탐색  p->r
        인접하지 않는경우, 같은 원소의 다른위치로 다시  p1->p2
    DP2
      단어의 길이 len -> len 번 순회
        i번째 순회시 i번째에 해당하는 원소를 찾는다.        25
          i-1번째 원소와 인접한지 확인후, 인접하다면 input    <=25
      N번째 원소가 empty가 아니라면, yes 출력 
      time complexity: 625*len*N
  */
  vector<int> result;
  //인접 8칸을 의미
  vector<int> near={-6,-5,-4,-1,1,4,5,6};
  //알고리즘
  for(auto& ele:wordArr){
    //DP[i][k]=x, ele의 i번째 원소와 겹치는 위치들 x 
    int len=ele.length();
    vector<vector<int>> DP(len);
    //0번째 원소 초기조건
    for(int j=0;j<25;j++){
      if(ele[0]==probTable[j]){
        DP[0].push_back(j);
      }
    }
    //1~len-1번째 원소
    for(int i=1;i<len;i++){
      //probTable 순회
      for(int j=0;j<25;j++){
        if(ele[i]==probTable[j]){
          for(auto& ele2: DP[i-1]){
            int gap=ele2-j;
            for(auto& ele3:near){
              if(gap==ele3){
                DP[i].push_back(j);
              }
            }
          }
        }
      }
    }
    //결과, 0=no, 1=yes
    if(DP.back().empty()){
      result.push_back(0);
    }else{
      result.push_back(1);
    }
  }
  return result;
}
void BoggleGame(){
  // int testCase;
  // cin>>testCase;
  int testCase=50;
  while(testCase--){
    vector<char> probTable(25);
    vector<string> wordArr;
    //BoggleInput(probTable, wordArr);
    BoggleRandInput(probTable,wordArr);
    vector<int> result=BoggleAlgo(probTable, wordArr); 
    int len=result.size();
    for(int i=0;i<len;i++){
      cout<<wordArr[i]<<" ";
      if(result[i]){
        cout<<"YES\n";
      }else{
        cout<<"NO\n";
      }
    }
  }
}

void PicnicInput(vector<vector<bool>>& friendTable){
  int studentNum,friendNum;
  cin>>studentNum>>friendNum;
  //n*n table로 변경
  for(int i=0;i<studentNum;i++){
    friendTable.push_back(vector<bool>(studentNum));
  }
  int num1,num2;
  for(int i=0;i<friendNum;i++){
    cin>>num1>>num2;
    friendTable[num1][num2]=true;
    friendTable[num2][num1]=true;
  }
}
int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  조합 문제
    12 34 56 과 21 65 43은 같은 조합.
    최대 경우의 수:10C2*8C2*6C2*4C2*2C2/(5!)=945
  brute force
    재귀
      Algo(frientTable,input toBePush)
        stack에는 한번에 두개씩 들어간다, 이때 두번째 원소는 항상 첫번째 원소보다 크다
        stack의 짝수idx(홀수번째 수)는 오름 차순이다.
          ex) 09 15 27 34 68
      첫번째 위치에는 남은 것 중 가장 앞의것을 input, 두번째 위치는 가능한 모든것 input 후 재귀
        toBePush[idx]=true: idx push 가능
        friend인 경우에만 input
      기저: stack의 크기가 10 -> return 1;
  업데이트
    기저와 첫번째 학생을 하나의 search로 합칠 수 있다.
    if 문 통합, loop에 i 대신 직관적 표현 이용 
  */
  //첫번째 원소
  int studentNum(friendTable.size());
  int result(0),first(-1);
  for(int i=0;i<studentNum;i++){
    if(toBePush[i]){
      first=i;
      toBePush[first]=false;
      break;
    }
  }
  //기저, 첫번째 학생이 없다면 모두 정렬 완료된 것이므로.
  if(first==-1){
    return 1;
  }
  //두번째원소
  for(int second=first+1;second<studentNum;second++){
    if(toBePush[second]&&friendTable[first][second]){
      toBePush[second]=false;
      result+=PicnicAlgo(friendTable,toBePush);
      toBePush[second]=true;
    }
  }
  toBePush[first]=true;
  return result;
}
void Picnic(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<vector<bool>> friendTable;
    PicnicInput(friendTable);
    vector<bool> toBePush(friendTable.size(),true);
    int result=PicnicAlgo(friendTable,toBePush);
    cout<<result<<"\n";
  }
}

void BoardCoverInput(vector<vector<bool>>& boardTable){
  int height,width;
  cin>>height>>width;
  string tmpS;
  for(int i=0;i<height;i++){
    boardTable.push_back(vector<bool>(width));
    cin>>tmpS;
    for(int j=0;j<width;j++){
      if(tmpS[j]=='#'){
        boardTable[i][j]=false;
      }else{
        boardTable[i][j]=true;
      }
    }
  }
}
bool BoradCoverNoAns(vector<vector<bool>>& boardTable){
  int cnt(0);
  for(auto& ele:boardTable){
    for(auto&& ele2:ele){
      if(ele2){
        cnt++;
      }
    }
  }
  if(cnt%3!=0){
    return true;
  }else{
    return false;
  }
}
int BoardCoverAlgo(vector<vector<bool>>& boardTable){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  전략1
    brute force
      왼쪽 위부터 오른쪽 아래로 가면서 chk 가능, 모양은 4가지 ㄴ, ㄱ, Symmetric ㄴ, Symmetric ㄱ
        중복은 자연히 걸러짐
        타일을 올리면 false로 바꾼다.
        (x,y)기준, (x,y)&(x,y+1)&(x+1,y+1), (x,y)&(x,y+1)&(x-1,y+1), (x,y)&(x+1,y)&(x+1,y+1), (x,y)&(x,y+1)&(x+1,y)
      first position을 찾는다
        기저: 찾지 못하면 first==-1, return 1;
        first 포지션의 4방향을 search
          4모양 모두 불가능 하면 return 0;
          가능하다면 재귀
    time complexity
      4^(width*height/3)<=10^60 //하얀색이 50칸 이하라는 조건이 존재한다.
      white<50 -> 4^13=6*10^7
    mem complexity
      width*height<=400
   
  */
  //first position
  int height=boardTable.size();
  int width=boardTable[0].size();
  int yPos=-1,xPos=-1;
  for(int i=0;i<height;i++){
    for(int j=0;j<width;j++){
      if(boardTable[i][j]){
        xPos=j;
        yPos=i;
        i=height;
        break;
      }
    }
  }
  //기저
  if(yPos==-1){
    return 1;
  }
  //Algo
  int result(0);
  bool xp1(xPos+1<width),xm1(xPos>0),yp1(yPos+1<height);
  if(xp1&&yp1){
    if(boardTable[yPos][xPos+1]&&boardTable[yPos+1][xPos+1]){
      boardTable[yPos][xPos]=boardTable[yPos][xPos+1]=boardTable[yPos+1][xPos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[yPos][xPos]=boardTable[yPos][xPos+1]=boardTable[yPos+1][xPos+1]=true;
    }
    if(boardTable[yPos+1][xPos]&&boardTable[yPos+1][xPos+1]){
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos+1][xPos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos+1][xPos+1]=true;
    }
    if(boardTable[yPos+1][xPos]&&boardTable[yPos][xPos+1]){
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos][xPos+1]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos][xPos+1]=true;
    }
  }
  if(xm1&&yp1){
    if(boardTable[yPos+1][xPos-1]&&boardTable[yPos+1][xPos]){
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos-1]=boardTable[yPos+1][xPos]=false;
      result+=BoardCoverAlgo(boardTable);
      boardTable[yPos][xPos]=boardTable[yPos+1][xPos-1]=boardTable[yPos+1][xPos]=true;
    }
  }
  return result;
}
void BoardCover(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    //true=white, false=black;
    vector<vector<bool>> boardTable;
    BoardCoverInput(boardTable);
    if(BoradCoverNoAns(boardTable)){
      cout<<"0\n";
    }else{
      cout<<BoardCoverAlgo(boardTable)<<"\n";
    }
  }
}

void ClockSyncInput(vector<int>& clockArr){
  for(int i=0;i<16;i++){
    cin>>clockArr[i];
  }
}
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch){
  /*
  제한시간 10초
  제한메모리 2^16kb=64MB
  전략1
    brute force
      차례대로 가장 적은 스위치와 연결된 시계를 변경하도록 스위치를 조작한다.
      (스위치)를 조작한 후, (시계)가 0인지 확인
        확인은 최종단계에서만 해도 충분하다.
      1. (1,4,9)->(8,9,11,12,13)
      2. (2,3)->(6,10)
      3. (7)->(7)
      4. (8)->(4,5)
      5. (0,6)->(1,3)
      6. (5)->(0,2,14,15)
    time complexity
      linear
    mem complexity
      linear
    구현이 귀찮다
  전략2
    brute force
      모든 스위치는 3회 이하로 눌린다
      4회를 눌렀다는 것은 0회를 눌른것과 같다.
    time complexity
      4^10
    유의사항
      재귀함수 설계시, return하며 답을 만드는 과정을 제대로 만들어야 한다.
      return시 0 혹은 INF 반환, INF를 반환하면 결과에서 무시되므로 상관없다.
        0을반환한다면 유효한 경로에 있는 값들만 result 에 더해지게 되는데, 유효하지 않은 경로는 여전히 INF를 갖고 있기 때문이다.
        프로그램은 순차적으로 실행되기 때문에, 이 경우 참조형식으로 함수를 전달해도 전혀문제가 없다(모든 경우에서 그런진 추가바람)
      마무리바람
  */
  //기저
  if(nowSwitch==10){
    bool finish(true);
    for(auto& ele:clockArr){
      if(ele%12){
        finish=false;
        break;
      }
    }
    return finish? 0: 987654321;
  }
  
  //Algo
  int result=987654321; //INF
  for(int i=0;i<4;i++){
    for(int j=0;j<i;j++){
      for(auto& ele:switchArr[nowSwitch]) clockArr[ele]+=3;
    }
    result=min(result,i+ClockSyncAlgo(clockArr,switchArr,nowSwitch+1));
    for(int j=0;j<i;j++){
      for(auto& ele:switchArr[nowSwitch]) clockArr[ele]-=3;
    }
  }
  return result;
}
void ClockSync(){
  int testCase;
  cin>>testCase;
  vector<vector<int>> switchArr={
    {0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},
    {6,7,8,10,12},{0,2,14,15},{3,14,15},
    {4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}
  };
  while(testCase--){
    vector<int> clockArr(16);
    ClockSyncInput(clockArr);
    int ans=ClockSyncAlgo(clockArr,switchArr,0);
    if(ans<987654321){
      cout<<ans<<"\n";
    }else{
      cout<<"-1\n";      
    }
  }
}

void QuadTreeInput(string& treeData){
  cin>>treeData;
}
string QuadTreeAlgo(string::iterator& iter){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  전략1
    기저: b or w를 만났을 때, 그대로 반환
    재귀: x를 만났을 때, 이때 상하반전 이므로 순서를 바꿔야 한다. 이때 반환되어 오는 값을 result에 더한다 
      1234 순서가 3412 순서로
    반환: string 값을 합쳐서 반환
    time complexity
      O(N): N 번 호출, 총 길이 N 만큼 문자열 합
    mem complexity
      O(N)
    업데이트
      iterator를 이용하여 전달인자 간소화
  */
  //기저, b and w
  char head=*iter;
  iter++;
  if(head=='b'||head=='w'){
    return string(1,head);
  }
  //Algo, x인 경우
  string tmp[4];
  for(int i=0;i<4;i++){
    tmp[i]=QuadTreeAlgo(iter);
  }
  return string("x")+tmp[2]+tmp[3]+tmp[0]+tmp[1];
}
void QuadTree(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string treeData;
    QuadTreeInput(treeData);
    string::iterator iter=treeData.begin();
    cout<<QuadTreeAlgo(iter)<<"\n";
  }
}