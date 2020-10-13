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

void FenceInput(vector<int>& fenceData){
  int fenceNum,tmp;
  cin>>fenceNum;
  fenceData.reserve(fenceNum);
  for(int i=0;i<fenceNum;i++){
    cin>>tmp;
    fenceData.push_back(tmp);
  }
}
int FenceAlgo(vector<int>& fenceData,int left, int right){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  전략1
    기저: left==right일 때, max=leftmax=rightmax=fenceData[left];
    재귀: L(left,mid), R(mid+1,right) 재귀
    반환: max, leftmax, right max
      leftmax= L's leftmax
      rightmax= R's right max
      newMax=if(fenceData[mid]<fenceData[mid+1])
        L's rightmax + R's leftmax*fenceData[mid]/fenceData[mid+1]
        else: vice versa
      max=max(newMax, L's max, R's max);
    time complexity
      O(NlgN): lgN 번 호출, O(n) 비교
    mem complexity
      O(N)
  전략2
    앞에서부터 뒤로 search
      key, prev, now 존재
        key 왼쪽으로는 모두 key보다 크거나 같다
        prev는 now 직전
          now가 prev보다 작다면,
    stack을 이용하는 건데 헷갈려
  전략 3
    quick sort 전략을 이용한다.
      가장 작은 pivot을 구한다
        분할: (left,pivot-1), (pivot+1,right)로 분리
        반환: result= max(pivot*(right-left),func(left,pivot-1),func(pivot+1,right));
        기저: right=left -> return fenceData[left];
      총 lgN번 구한다
      time complexity: NlgN
      mem complexity: N
  */
  //기저
  if(right<left){
    return 0;
  }
  //Algo, 
  int pivot,minValue(12345);
  for(int i=left;i<=right;i++){
    if(fenceData[i]<minValue){
      minValue=fenceData[i];
      pivot=i;
    }
  }
  int leftMax=FenceAlgo(fenceData,left,pivot-1);
  int rightMax=FenceAlgo(fenceData,pivot+1,right);
  return max(minValue*(right-left+1),max(leftMax,rightMax));
}
void Fence(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> fenceData;
    FenceInput(fenceData);
    cout<<FenceAlgo(fenceData,0,fenceData.size()-1)<<"\n";
  }
}
// void FanmeetingInput(longNum& member,longNum& fan){
//   string memberTmp,fanTmp;
//   cin>>memberTmp>>fanTmp;
//   vector<int> memberV,fanV;
//   memberV.reserve(memberTmp.length());
//   for(auto& ele: memberTmp){
//     if(ele=='M'){
//       memberV.push_back(1);
//     }else{
//       memberV.push_back(0);
//     }
//   }
//   fanV.reserve(fanTmp.length());
//   for(auto& ele: fanTmp){
//     if(ele=='M'){
//       fanV.push_back(1);
//     }else{
//       fanV.push_back(0);
//     }
//   }
//   member=move(memberV);
//   fan=move(fanV);
// }
// int FanmeetingAlgo(longNum& member, longNum& fan){
//   /*
//   제한시간 10초
//   제한메모리 2^16kb=64MB
//   전략1
//     모든 멤버와 모든팬은 만난다.
//     한 줄의 모든 멤버들이 포옹하는 경우 -> M & M 이없는 경우 
//       M=1, F=0으로 하고 bit and(&) -> if (0)-> 모든멤버 포옹
//     곱셈을 이용, abc 123 각 숫자가 있다 가정하자.
//       cba*123= a3+(a2+b3)10+(a1+b2+c3)10^2+(b1+c2)10^3+(c1)10^4
//       악수하는 경우 -> c1, b1+c2, a1+b2+c3, a2+b3, a3
//         두 숫자중 한 수를 뒤집고 곱한것의 계수와 같다.
//         이떄 계수가 10을 초과할 수 있으므로 normalize하면 안된다.
//         karatsuba를 수정해서, normalize를 하지 않도록 수정한다.
//         모든 멤버가 포옹해야 한다 -> member수~fan의수
//     time complexity
//       karatsuba Time + ele 세기 = n^lg3 + n = O(n^lg3)
//     mem complexity
//       O(n)
//   */
//   member.reverse();
//   longNum result(fan.karatsuba_notNorm(member));
//   int ans(0),start(member.length()-1),end(fan.length());
//   for(int i=start;i<end;i++){
//     if(result[i]==0){
//       ans++;
//     }
//   }
//   return ans;
// }
// void Fanmeeting(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     longNum member,fan;
//     FanmeetingInput(member,fan);
//     cout<<FanmeetingAlgo(member,fan)<<"\n";
//   }
// }

void WildcardInput(string& wildcard,vector<string>& fileArr){
  int fileNum;
  string tmp;
  cin>>wildcard>>fileNum;
  fileArr.reserve(fileNum);
  for(int i=0;i<fileNum;i++){
    cin>>tmp;
    fileArr.push_back(move(tmp));
  }
}
bool Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
  //wildcard의 w_idx, file의 f_idx부터 비교한다.
  char& result=DP[w_idx][f_idx];
  //답이 이미 있을경우
  if(result!=-1){
    return result;
  }
  //w_idx==w_len까지, wildcard를 모두 비교하는것이 목표
  int w_len(wildcard.length()),f_len(file.length());;
  while(w_idx<w_len&&f_idx<f_len){
    char w_char=wildcard[w_idx];
    if(w_char==file[f_idx]||w_char=='?'){
      w_idx++;f_idx++;
      continue;
    }
    if(w_char=='*'){
      //*에 하나이상 대응
      if(Wildcard_match(wildcard,file,w_idx,f_idx+1,DP)){
        return result;
      }
      //*에 0개 대응
      w_idx++;
      continue;
    }
    //*도 아니고, 두 문자도 다른경우 false;
    result=0;
    return result;
  }
  //f_len은 반드시 모두 매칭되어야 하며, w_len은 마지막 부분이 모두 *라면 모두 매칭되지 않아도 괜찮다.
  if(f_len==f_idx){
    if(w_len>w_idx){
      for(int i=w_idx;i<w_len;i++){
        if(wildcard[i]!='*'){
          result=0;
          return result;
        }
      }
    }
    result=1;
  }else{
    result=0;
  }
  return result;
}
bool Wildcard_match2(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
  //답이 이미 있을경우
  char& result=DP[w_idx][f_idx];
  if(result!=-1){
    return result;
  }
  //1:1 대응시 다음 idx로 넘어간다.
  int w_len(wildcard.length()),f_len(file.length());
  if(w_idx<w_len&&f_idx<f_len&&(wildcard[w_idx]==file[f_idx]||wildcard[w_idx]=='?')){
    return result=Wildcard_match2(wildcard,file,w_idx+1,f_idx+1,DP);
  }
  //wildcard search가 끝났을 경우, file search도 끝났어야 match가 된 것이다.
  if(w_idx==w_len){
    return result=(f_idx==f_len);
  }
  // *이 있을 경우, *와 대응되는것의 길이가 0인 경우(w_idx+1)와 1이상인 경우(f_idx+1)로 구분, 이때 match함수에는 f_idx==file_len에 대한 조건이 없으므로, 제한조건에 추가한다.
  if(wildcard[w_idx]=='*'){
    if(Wildcard_match2(wildcard,file,w_idx+1,f_idx,DP)||(f_idx<f_len&&Wildcard_match2(wildcard,file,w_idx,f_idx+1,DP))){
      return result=1;
    }
  }
  //나머지 경우에는 문자열과 wildcard가 대응되지 않는다.
  return result=0;
}
vector<string> WildcardAlgo(string& wildcard,vector<string>& fileArr){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  문자열의 길이는 1~100, 알파벳 대소문자, ?, *로 구성, 공백 없음 
  ?는 문자 하나를 대응, *는 길이 0이상의 문자열 대응
  파일명의 수 1~50개
  전략1
    brtue force
      1:1 비교 원칙: 같으면 continue, 다르면 return false
      ?의 경우: 항상 continue
      *의 경우: 
        *의 다음 문자가 있을경우: 해당 문자를 찾을 때까지 continue -------Problem-------
            다음 문자가 없을경우: return true
    Problem 
      *의 다음문자가 l이라 하자, l이 여러개 있을경우 그만큼 분기를 생성해줘야 한다.
        분기-> 재귀, 재귀: 중복 생성 가능, 중복: DP로 해결
    time complexity
      wildCardLen(N)*#fileArr(50)*fileNameLen(M)^numOf*(L)=50N*M^L
    mem complexity
      100+50*100
  전략 2
    Dynamic Programming
      Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx)
        wildcard의 w_idx와 file의 f_idx 비교
      재귀를 통한 완전 탐색을 기준으로 한다.
        1:1 비교 원칙: 같으면 continue, 다르면 return false
        ?의 경우: 항상 continue
        *의 경우: f_idx+1로 재귀 or w_idx+1로 loop 이어서
      반환 경우의 수
        w_idx와 f_idx가 마무리 -> return true;
        w_idx만 마무리-> return false;
        f_idx만 마무리-> w_idx에 남은것이 *뿐이라면 true, 다른것도 있다면 false; 
      DP
        반환하기 전에 DP[w_idx][f_idx]에 1(true) 0(false)저장, -1(not initialized)
        DP여부 맨 처음에 확인 
    time complexity
      wildCardLen(100)*fileLen(100)*loopInMatch(100) = O(n^3);
    mem complexity
      wildcard(100)+DP(100*100)+fileArr(100*50) = O(n);
  전략 3
    Dynamic Programming
      전략2에서 함수 내 재귀를 없앤다. -> O(n^2)
    time complexity
      wildCardLen*fileLen=O(n^2);
    mem complexity
      same as 전략 2
  */
  vector<string> result;
  for(int i=0;i<fileArr.size();i++){
    string& file=fileArr[i];
    vector<vector<char>> DP(wildcard.length()+1,vector<char>(file.length()+1,-1));
    if(Wildcard_match(wildcard,file,0,0,DP)){
      result.push_back(file);
    }
  }
  return result;
}
void Wildcard(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string wildcard;
    vector<string> fileArr;
    WildcardInput(wildcard,fileArr);
    vector<string> result(WildcardAlgo(wildcard,fileArr));
    sort(result.begin(),result.end());
    for(auto& ele:result){
        cout<<ele<<"\n";
    }
  }
}

void JoinedLISInput(vector<int>& arrA,vector<int>& arrB){
  int lenA,lenB;
  scanf("%d",&lenA);scanf("%d",&lenB);
  arrA=vector<int>(lenA);
  for(int i=0;i<lenA;i++){
    scanf("%d",&arrA[i]);
  }
  arrB=vector<int>(lenB);
  for(int i=0;i<lenB;i++){
    scanf("%d",&arrB[i]);
  }
}
bool joinedLIS_Afirst(vector<int>& arrA,vector<int>& arrB,int idxA,int idxB){
  //out of idx 처리
  if(idxA==arrA.size()){
    return false;
  }else if(idxB==arrB.size()){
    return true;
  }
  //비교
  if(arrA[idxA]!=arrB[idxB]){
    return arrA[idxA]<arrB[idxB];
  }else{
    return arrA[idxA+1]<arrB[idxB+1];
  }
}
int JoinedLISAlgo_1(vector<int>& arrA,vector<int>& arrB){
  vector<long long> result;
  int idxA(0),idxB(0);
  //result의 맨 처음 값 설정
  if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
    result.push_back(arrA[idxA]);
    idxA++;
  }else{
    result.push_back(arrB[idxB]);
    idxB++;
  }
  //남은 값에 대해
  int input; 
  while(idxA<arrA.size()||idxB<arrB.size()){
    if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
      input=arrA[idxA];
      idxA++;
    }else{
      input=arrB[idxB];
      idxB++;
    }
    if(result.back()<input){
      result.push_back(input);
    }else{
      *lower_bound(result.begin(),result.end(),input)=input;
    }
  }
  return result.size();
}
int JoinedLISAlgo_3(vector<int>& arrA,vector<int>& arrB){
  vector<int> result1;
  vector<int> result2;
  result1.push_back(arrA.front());
  result2.push_back(arrB.front());
  //전략 1, 각 arr에 대해 LIS를 만든다
  for(auto& ele:arrA){
    if(result1.back()<ele){
      result1.push_back(ele);
    }else{
      *lower_bound(result1.begin(),result1.end(),ele)=ele;
    }
  }
  for(auto& ele:arrA){
    if(result2.back()<ele){
      result2.push_back(ele);
    }else{
      *lower_bound(result2.begin(),result2.end(),ele)=ele;
    }
  }
  //전략 2, 각 결과에 대해 앞에서부터 greedy
  vector<int> result;

  return result.size();
}
int JoinedLISAlgo_2(vector<int>& arrA,vector<int>& arrB,int idxA, int idxB,vector<vector<int>>& DP){
  /*
  제한시간 2초
  제한메모리 2^16kb=64MB
  각 arr의 원소의 개수는 1~100, 자료형 int
  전략1
    Dynamic Programming
      substructure
        idxA, idxB
      기존 LIS 전략을 쓰되, 입력을 양쪽 arr의 head중 더 작은값을 넣는다.
      LIS 전략
        input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
      input
        각 arr의 head 중 작은 값을 input, 값이 같다면 바로 다음 값을 비교하여 더 작은 값을 input, 둘이 같다면 그냥 첫번째 input
    Problem
      (10 20 30 1 2), (10 20 30)의 길이는 5 이지만, 이 Algo를 이용하면 3이 나온다.
    time complexity
      #arr(n)*lower_bound(lgn)=O(nlgn)
    mem complexity
      #arr(n)=O(n)
  전략2
    Dynamic Programming
      substructure
        idxA, idxB를 입력으로 받는 부분함수
        substructure(idxA,idxB)는 idxA와 idxB가 각 Arr에서 (이전까지)마지막 수 이며, 두 중 큰 수가 JLIS에서 마지막일 것이다.
        DP=n^2
      LIS 전략
        마지막 값 max(arrA[idxA],arrB[idxB])보다 큰 값을 찾아 재귀, 이때 arrA에대해 한번, arrB에 대해서도 한번 한다.
    time complexity
      재귀 n^2* 반복문 n: O(n^3)
    mem complexity
      DP(n^2)+ arrA and B(n): O(n^2)
  전략3
    Stack
      각 arr에 전략 1 적용후(vector 형식으로 생성), 적용한 것들을 가지고 greedy(전략 2)
      LIS 전략:1
        input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
      전략 2
        결과값은 정렬되어 있다 -> 앞에서부터 작은 값을 input
    Problem
      10 20 40 100 400 에서 10 20 30 100 400 으로 변한 결과1
      15 25 30 200 300 인 결과 2가 있다고 하자
      결과 1의 3번째가 40일때가 30일때보다 1 긴데, 30이 최종 값이다. 즉 실제 결과보다 길이가 짧다.
    time complexity
      (arrA(n)+arrB(n))*lower_bound(lgn)=O(nlgn)
    mem complexity
      arrA(n)+arrB(n)+result(2n)=O(n)
  */
  //-1부터 시작해서 각 idx에 1을 더했다.
  int& result=DP[idxA+1][idxB+1];
  if(result!=-1){
    return result;
  }
  //마지막 value를 찾는다.
  long long valueA=(idxA==-1? -9876543210:arrA[idxA]);
  long long valueB=(idxB==-1? -9876543210:arrB[idxB]);
  long long lastEle(max(valueA,valueB));
  //A와 B에 대해 substructure
  result=0;
  for(int i=idxA+1;i<arrA.size();i++){
    if(arrA[i]>lastEle){
      result=max(result,JoinedLISAlgo_2(arrA,arrB,i,idxB,DP));
    }
  }
  for(int i=idxB+1;i<arrB.size();i++){
    if(arrB[i]>lastEle){
      result=max(result,JoinedLISAlgo_2(arrA,arrB,idxA,i,DP));
    }
  }
  result++;
  return result;
}
void JoinedLIS(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> arrA,arrB;
    JoinedLISInput(arrA,arrB);
    //vector<vector<int>> DP(arrA.size()+1,vector<int>(arrB.size()+1,-1));
    printf("%d\n",JoinedLISAlgo_3(arrA,arrB));
  }
}

void PImem_Input(string& s){
  cin>>s;
}
int PImem_hard(string& numbers,int start,int len){
  //기저
  if(start+len>numbers.size()) return 12345;
  int begin(start+1),end(start+len);
  //난이도 1
  bool result(true);
  for(int i=begin;i<end;i++){
    if(numbers[i]!=numbers[i-1]) result=false;
  }
  if(result) return 1;
  //난이도 2
  result=true;
  int gap=numbers[start+1]-numbers[start];
  if(gap!=1&&gap!=-1) result=false;
  for(int i=begin;i<end;i++){
    if(numbers[i]-numbers[i-1]!=gap) result=false;
  }
  if(result) return 2;
  //난이도 4
  result=true;
  for(int i=start+2;i<end;i++){
    if(numbers[i]!=numbers[i-2]) result=false;
  }
  if(result) return 4;
  //난이도 5
  result=true;
  gap=numbers[start+1]-numbers[start];
  for(int i=begin;i<end;i++){
    if(numbers[i]-numbers[i-1]!=gap) result=false;
  }
  if(result) return 5;
  //나머지
  return 10;
}
int PImem_Algo(string& numbers, vector<int>& DP, int start){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  테스트 케이스 50개
  각 숫자들의 길이는 8~10000, 0~9
  전략1
    Dynamic Programming
      substructure
        Algo(DP,start)=min(hard(s,start,3)+Algo(DP,start+3),hard(s,start,4)+Algo(DP,start+4),hard(s,start,5)+Algo(DP,start+5));
          Algo(DP,start)=start에서 마지막까지 외울때의 값,DP이용
          hard(s,start,len)=string s에서 start부터 길이 len인 조각의 난이도
        제한조건
          최대값은 10000/3*10이므로, search완료는 0 반환, out of idx와 같은 것은 12,345 반환
    time complexity
      #Algo(n)*Algo(1)*hard(1)
    mem complexity
      #arr(n)=O(n)
  */
  //기저, search 완료, out of idx
  if(start==numbers.size()) return 0;
  if(start>numbers.size()) return 12345;
  //메모제이션
  int& result=DP[start];
  if(result!=0) return result;
  //substructure
  int sub3=PImem_hard(numbers,start,3)+PImem_Algo(numbers,DP,start+3);
  int sub4=PImem_hard(numbers,start,4)+PImem_Algo(numbers,DP,start+4);
  int sub5=PImem_hard(numbers,start,5)+PImem_Algo(numbers,DP,start+5);
  return result=min(sub3,min(sub4,sub5));
}
void PImem(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string numbers;
    PImem_Input(numbers);
    vector<int> DP(numbers.size());
    printf("%d\n",PImem_Algo(numbers,DP,0));
  }
}

void Quantization_Input(vector<int>& number,int& quantRange){
  int numSize;
  cin>>numSize>>quantRange;
  number.resize(numSize);
  for(auto& ele:number){
    scanf("%d",&ele);
  }
}
void Quantization_DP_A(vector<int>& number, vector<vector<int>>& DP_A){
  for(int i=0;i<number.size();i++){
    for(int j=i;j<number.size();j++){
      int sum(0),avg(0),len(j-i+1),result(0);
      for(int k=i;k<=j;k++){
        sum+=number[k];
      }
      //반올림
      avg=int(0.5+static_cast<double>(sum)/len);
      //제곱합
      for(int k=i;k<=j;k++){
        result+=(number[k]-avg)*(number[k]-avg);
      }
      DP_A[i][j]=result;
    }
  }
}
void Quantization_DP_A_2(vector<int>& number, vector<vector<int>>& DP_A){
  //부분합을 이용해 계산시간을 줄인다. 합, 제곱합을 n에서 1로 최적화
  int numLen=number.size();
  vector<int> DP_pSum(numLen); //A(i)=for(x=0~i)sum(number[x])
  vector<int> DP_pSqSum(numLen);//A(i)=for(x=0~i)sum(number[x]^2)
  DP_pSum[0]=number[0];DP_pSqSum[0]=number[0]*number[0];
  for(int i=1;i<numLen;i++){
    DP_pSum[i]=DP_pSum[i-1]+number[i];
    DP_pSqSum[i]=DP_pSqSum[i-1]+number[i]*number[i];
  }
  //DP_A 계산
  for(int i=0;i<numLen;i++){
    for(int j=i;j<numLen;j++){
      int sum=DP_pSum[j]-(i==0? 0 : DP_pSum[i-1]);
      int sqSum=DP_pSqSum[j]-(i==0? 0 : DP_pSqSum[i-1]);
      //반올림
      int avg=int(0.5+static_cast<double>(sum)/(j-i+1));
      //제곱합최소값
      DP_A[i][j]=sqSum-2*avg*sum+avg*avg*(j-i+1);
    }
  }
}
int Quantization_DP_B(vector<int>& number, vector<vector<int>>& DP_A,vector<vector<int>>& DP_B,int start,int depth){
  //기저, 모든 숫자를 양자화, 숫자는 남았는데 더 양자화 할 수 없을때
  if(start==number.size()) return 0;
  if(depth==0) return 123456789;
  //메모제이션
  int& result=DP_B[start][depth];
  if(result!=-1) return result;
  //substructure
  result=123456789;
  for(int i=0;start+i<number.size();i++){
    result=min(result,DP_A[start][start+i]+Quantization_DP_B(number,DP_A,DP_B,start+i+1,depth-1));
  }
  return result;
}
int Quantization_Algo(vector<int>& number,int quantRange){
  /*
  제한시간 2초
  제한메모리 64MB
  테스트 케이스 50개
  수열의 길이 1~100, 사용할 숫자의 수 1~10
  전략1
    Dynamic Programming
      두개의 DP 배열
        첫번째 DP_A
          수열 오름차순 정렬
          수열의 길이 * 수열의 길이
          A(ij)=i~j를 한 숫자로 양자화 했을때의 제곱합 최소치 
        두번째 DP_A
          수열의 길이 * 양자화에 사용할 숫자의 수
          B(i,j)=i번째 숫자부터 j번째 양자화 수를 사용할 때, i번째 숫자부터 제곱합최소치
      A(i,j)
        arr[i]~arr[j]범위의 양자화 값 하나를 이용할 때, 제곱합 최소치를 구한다.
          양자화 값은 arr[i]~arr[j]의 평균
            증명: 평균보다 a만큼 차이가 나면, (gap1-a)^2+(gap2+a)^2+... > gap1^2+gap2^2+...
            미분을 이용해서도 증명 가능
        A(ij)=sum((x-avg)^2), x=i~j
      substructure  
        B(i,j)= for(k=i~ last) 
          B(i,j)=C(i~k-1)+B(k,j+1)
          오름차순 정렬이기 때문에, optimal substructure가 성립한다.
        제한조건
          최대값=1000^2*100=100,000,000, INF=123456789
          j가 10이면 return 0
          i가 last를 벗어나면 return INF
    time complexity
      sorting(nlgn)+#A(1)*A(n^3)+#B(n^2)*B(n) = O(n^3)
        optimize: #A2(1)*A2(n^2)
    mem complexity
      #arr(n)=O(n)
  */
  //정렬
  sort(number.begin(),number.end());
  //DP_A, i~j를 한 숫자로 양자화 했을때의 제곱합 최소치
  vector<vector<int>> DP_A(number.size(),vector<int>(number.size(),-1));
  Quantization_DP_A_2(number,DP_A);
  //DP_B
  vector<vector<int>> DP_B(number.size(),vector<int>(quantRange+1,-1));
  return Quantization_DP_B(number,DP_A,DP_B,0,quantRange);
}
void Quantization(){
  int testCase;
  cin>>testCase;
  vector<int> result;
  while(testCase--){
    vector<int> number;
    int quantRange;
    Quantization_Input(number,quantRange);
    cout<<Quantization_Algo(number,quantRange)<<'\n';
  }
}

void AsymTiling_Input(int& tileLen){
  cin>>tileLen;
}
int AsymTiling_DP(vector<int>& DP,int tileLen){
  int& result=DP[tileLen];
  if(result!=0) return result;
  return result=(AsymTiling_DP(DP,tileLen-1)+AsymTiling_DP(DP,tileLen-2))%1000000007;
}
int AsymTiling_Algo(int tileLen){
  /*
  1초, 64MB, 테스트케이스 50개
  사각형의 너비 1~100, mod 1,000,000,007
  전략1
    Dynamic Programming
      모든 사각형의 수 - 대칭인 사각형의 수
      뺄셈에서 mod는 항등이다(음수일경우 mod를 더해준다.)
      모든 사각형
        substructure: func(len)=func(len-1)+func(len-2)
        기저: if len<=1, return 1; -> DP[0], DP[1]을 1로 미리 정하면 됨
      대칭 사각형
        if(len%2==1) func2(len)=func(len/2)
        if(len%2==0) func2(len)=func(len/2)+func(len/2-1)
    time complexity
      #func(n)*func(1)+#func2(1)*func2(1)=O(n)
    mem complexity
      #DP_A(n)=O(n)
  */
  //모든 사각형의 경우의 수
  vector<int> DP(tileLen+1);DP[0]=1;DP[1]=1;
  int result=AsymTiling_DP(DP,tileLen);
  //정답
  int modValue=1000000007;
  if(tileLen%2==0)
    result=(result-(DP[tileLen/2]+DP[tileLen/2-1])%modValue+modValue)%modValue;
  else
    result=(result-DP[tileLen/2]+modValue)%modValue;
  return result;
}
void AsymTiling(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int tileLen;
    AsymTiling_Input(tileLen);
    cout<<AsymTiling_Algo(tileLen)<<'\n';
  }
}

void Poly_Input(int& block){
  cin>>block;
}
int Poly_DP(vector<vector<int>>& DP,int blockNum,int topNum){
  int& result=DP[blockNum][topNum];
  if(result!=-1) return result;
  //substructrue, preTop=꼭대기 직전 블록의 갯수
  result=0;
  for(int preTop=1;preTop<=blockNum-topNum;preTop++){
    result=(result+(topNum+preTop-1)*Poly_DP(DP,blockNum-topNum,preTop))%10000000;
  }
  return result;
}
int Poly_Algo(int block){
  /*
  1초, 64MB, 테스트케이스 50개
  사각형의 개수 1~100, mod 10,000,000
  전략1
    Dynamic Programming
      func(사용한 정사각형의 개수, 높이), x는 가장 위에 쌓을 개수
        substructure: for(height=1~n) func(n,height)= for(x=1~n-height+1) sum(x*func(n-x,height-1))
        기저: func(i.i)=1;func(i,1)=1;
        정답: for(i=1~n) sum(func(n,i))
    Problem
      top*func(...)가 아니고, (top+직전 높이의 가로 개수-1)*func(...)이다.
    time complexity
      #func(n^2)*func(n)+=O(n^3)
    mem complexity
      #DP_A(n^2)=O(n^2)
  전략2
    Dynamic Programming
      func(사용한 정사각형의 개수, 가장 높은 위치(top)의 블록갯수)
        substructure: for(topNum=1~n) func(n,topNum)=for(x=1~n-topNum) sum((topNum+x-1)*func(n-topNum,x))
        기저: func(i,i)=1;
        정답: for(i=1~n) sum(func(n,i))
    time complexity
      #func(n^2)*func(n)+=O(n^3)
    mem complexity
      #DP_A(n^2)=O(n^2)
  */
  //DP 생성 및 계산
  vector<vector<int>> DP(block+1,vector<int>(block+1,-1));
  //기저
  for(int i=1;i<=block;i++){
    DP[i][i]=1;
  } 
  int result=0;
  for(int i=1;i<=block;i++)
    result+=Poly_DP(DP,block,i);
  return result%10000000;
}
void Poly(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    int block;
    Poly_Input(block);
    cout<<Poly_Algo(block)<<'\n';
  }
}



