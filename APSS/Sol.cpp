#include "Sol.h"

// void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr){
//   for(int i=0;i<25;i++){
//     probTable[i]=rand()%26+'A';
//   }
//   int len=rand()%10+1;
//   for(int i=0;i<len;i++){
//     int numLen=rand()%10+1;
//     string tmp;
//     for(int j=0;j<numLen;j++){
//       tmp.push_back(rand()%26+'A');
//     }
//     wordArr.push_back(tmp);
//   }
// }
// void BoggleInput(vector<char>& probTable, vector<string>& wordArr){
//   for(int i=0;i<5;i++){
//     string tmpS;
//     cin>>tmpS;
//     for(int j=0;j<5;j++){
//       probTable[5*i+j]=tmpS[j];
//     }
//   }
//   int wordNum;
//   cin>>wordNum;
//   for(int i=0;i<wordNum;i++){
//     string tmpS;
//     cin>>tmpS;
//     wordArr.push_back(tmpS);
//   }
// }
// vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr){
//   /*
//     제한시간 10초, 제한 메모리 2^16Kb=64MB
//     brute force
//       8방향을 확인하여 단어를 순서대로 만든다 -> R, E, P, E, A, T
//         bool boggle(string word, int idx, pair<int,int> point);  //word의 idx번째가 point와 값이 같은지 chk;
//       time complexity : 단어의 길이 N 개수 M, M*25*8^(N-1), 지수시간 
//     graph
//       DFS나 BFS는 brute force와 다를것이 없어보인다.
//     DP1
//       단어에서 각 원소가 있는 위치를 저장한다 ex) p r e t t y 에서 행렬을 한번만 순회하며 각 원소가 있는 위치를 저장한다.
//       맨 처음 위치가 존재한다면, 다음 원소가 기존 원소와 인접하는지 확인 -> 상수 연산하면 되므로 1 cost
//         인접하는 경우, 다음 원소 탐색  p->r
//         인접하지 않는경우, 같은 원소의 다른위치로 다시  p1->p2
//     DP2
//       단어의 길이 len -> len 번 순회
//         i번째 순회시 i번째에 해당하는 원소를 찾는다.        25
//           i-1번째 원소와 인접한지 확인후, 인접하다면 input    <=25
//       N번째 원소가 empty가 아니라면, yes 출력 
//       time complexity: 625*len*N
//   */
//   vector<int> result;
//   //인접 8칸을 의미
//   vector<int> near={-6,-5,-4,-1,1,4,5,6};
//   //알고리즘
//   for(auto& ele:wordArr){
//     //DP[i][k]=x, ele의 i번째 원소와 겹치는 위치들 x 
//     int len=ele.length();
//     vector<vector<int>> DP(len);
//     //0번째 원소 초기조건
//     for(int j=0;j<25;j++){
//       if(ele[0]==probTable[j]){
//         DP[0].push_back(j);
//       }
//     }
//     //1~len-1번째 원소
//     for(int i=1;i<len;i++){
//       //probTable 순회
//       for(int j=0;j<25;j++){
//         if(ele[i]==probTable[j]){
// //문제 발생 부분, 최대 9개의 원소가 중복입력될 수 있다 -> 메모리가 지수함수적으로 커져버림 -> set으로 해결 or, 25개짜리 배열을 이용해 해결 
//           for(auto& ele2: DP[i-1]){
//             int gap=ele2-j;
//             for(auto& ele3:near){
//               if(gap==ele3){
//                 DP[i].push_back(j);
//               }
//             }
//           }
//         }
//       }
//     }
//     //결과, 0=no, 1=yes
//     if(DP.back().empty()){
//       result.push_back(0);
//     }else{
//       result.push_back(1);
//     }
//   }
//   return result;
// }
// vector<int> Boggle_Algo2(vector<char>& probTable, vector<string>& wordArr){
//   vector<int> result;
//   //인접 8칸을 의미
//   vector<int> commonNear={-6,-5,-4,-1,1,4,5,6};
//   vector<int> rEdgeNear={-6,-5,-1,4,5};
//   vector<int> lEdgeNear={-5,-4,1,5,6};
//   //알고리즘
//   for(auto& ele:wordArr){
//     //DP[i][k]=x, ele(문장)의 i번째 원소로 k가 사용될 수 있는가(x==1 or 0)
//     int len=ele.length();
//     vector<vector<int>> DP(len,vector<int>(25));
//     //0번째 원소 초기조건
//     for(int j=0;j<25;j++){
//       if(ele[0]==probTable[j]){
//         DP[0][j]=1;
//       }
//     }
//     //1~len-1번째 원소
//     for(int i=1;i<len;i++){
//       //probTable 순회
//       for(int j=0;j<25;j++){
//         if(ele[i]==probTable[j]){
//           vector<int> near;
//           if(j%5==0){
//             near=lEdgeNear;
//           }else if(j%5==4){
//             near=rEdgeNear;
//           }else{
//             near=commonNear;
//           }
//           for(auto& ele: near){
//             if(j+ele>=0&&j+ele<25&&DP[i-1][j+ele]==1){
//               DP[i][j]=1;
//               break;
//             }
//           }
//         }
//       }
//     }
//     //결과, 0=no, 1=yes
//     int tmpResult(0);
//     for(auto& ele2:DP[len-1]){
//       if(ele2==1){
//         tmpResult=1;
//         break;
//       }
//     }
//     result.push_back(tmpResult);
//   }
//   return result;
// }
// void BoggleGame(){
//   /*실험조건
//     10초, 64MB, 테스트케이스=50
//     입력: 5*5 table, #word n: 1~10, each word
//     출력: each word + YES or NO(table에 word가 있는가?)
//   */
//   /*전략1
//     문제점
//       1. Runtime Error -> 메모리 초과???
//     brute force
//       8방향을 확인하여 단어를 순서대로 만든다 -> R, E, P, E, A, T
//         bool boggle(string word, int idx, pair<int,int> point);  //word의 idx번째가 point와 값이 같은지 chk;
//       time complexity : 단어의 길이 N 개수 M, M*25*8^(N-1), 지수시간 
//     graph
//       DFS나 BFS는 brute force와 다를것이 없어보인다.
//     DP1
//       단어에서 각 원소가 있는 위치를 저장한다 ex) p r e t t y 에서 행렬을 한번만 순회하며 각 원소가 있는 위치를 저장한다.
//       맨 처음 위치가 존재한다면, 다음 원소가 기존 원소와 인접하는지 확인 -> 상수 연산하면 되므로 1 cost
//         인접하는 경우, 다음 원소 탐색  p->r
//         인접하지 않는경우, 같은 원소의 다른위치로 다시  p1->p2
//     DP2
//       단어의 길이 len -> len 번 순회
//         i번째 순회시 i번째에 해당하는 원소를 찾는다.        25
//           i-1번째 원소와 인접한지 확인후, 인접하다면 input    <=25
//       N번째 원소가 empty가 아니라면, yes 출력 
//       time complexity: 625*len*N
//   */
//   /*전략2
//     문제점
//       2차원 배열이 아닌 1차원 배열 25칸에 저장한것은, 좌우모서리에서 인접 원소 chk에 문제가 발생한다. -> 코딩으로 해결보자 일단
//     특징 
//       지나간 글자를 다시 지나갈 수 있다, 즉 history가 중요하지 않으므로 Dynamic Programming를 이용할 수 있다.
//     DynamicProgramming
//       2차원 배열 DP(wordLen*25)를 이용한다. table에는 25개의 값이 있다.
//         DP[i][j]=x : j 가 word의 i번째 원소가 될 수 있다면, x==1
//     mem complexity
//       25*10(maxWordLen)
//     time complexity
//       #word*10(wordLen)*25(#ele)*8(near ele chk)
//   */
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<char> probTable(25);
//     vector<string> wordArr;
//     BoggleInput(probTable, wordArr);
//     //int testCase=50;
//     //BoggleRandInput(probTable,wordArr);
//     //vector<int> result=BoggleAlgo(probTable, wordArr); 
//     vector<int> result=Boggle_Algo2(probTable,wordArr);
//     for(int i=0;i<result.size();i++){
//       cout<<wordArr[i]<<" ";
//       if(result[i]){
//         cout<<"YES\n";
//       }else{
//         cout<<"NO\n";
//       }
//     }
//   }
// }

// void PicnicInput(vector<vector<bool>>& friendTable){
//   int studentNum,friendNum;
//   cin>>studentNum>>friendNum;
//   //n*n table로 변경
//   for(int i=0;i<studentNum;i++){
//     friendTable.push_back(vector<bool>(studentNum));
//   }
//   int num1,num2;
//   for(int i=0;i<friendNum;i++){
//     cin>>num1>>num2;
//     friendTable[num1][num2]=true;
//     friendTable[num2][num1]=true;
//   }
// }
// int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush){
//   /*
//   제한시간 1초
//   제한메모리 2^16kb=64MB
//   조합 문제
//     12 34 56 과 21 65 43은 같은 조합.
//     최대 경우의 수:10C2*8C2*6C2*4C2*2C2/(5!)=945
//   brute force
//     재귀
//       Algo(frientTable,input toBePush)
//         stack에는 한번에 두개씩 들어간다, 이때 두번째 원소는 항상 첫번째 원소보다 크다
//         stack의 짝수idx(홀수번째 수)는 오름 차순이다.
//           ex) 09 15 27 34 68
//       첫번째 위치에는 남은 것 중 가장 앞의것을 input, 두번째 위치는 가능한 모든것 input 후 재귀
//         toBePush[idx]=true: idx push 가능
//         friend인 경우에만 input
//       기저: stack의 크기가 10 -> return 1;
//   업데이트
//     기저와 첫번째 학생을 하나의 search로 합칠 수 있다.
//     if 문 통합, loop에 i 대신 직관적 표현 이용 
//   */
//   //첫번째 원소
//   int studentNum(friendTable.size());
//   int result(0),first(-1);
//   for(int i=0;i<studentNum;i++){
//     if(toBePush[i]){
//       first=i;
//       toBePush[first]=false;
//       break;
//     }
//   }
//   //기저, 첫번째 학생이 없다면 모두 정렬 완료된 것이므로.
//   if(first==-1){
//     return 1;
//   }
//   //두번째원소
//   for(int second=first+1;second<studentNum;second++){
//     if(toBePush[second]&&friendTable[first][second]){
//       toBePush[second]=false;
//       result+=PicnicAlgo(friendTable,toBePush);
//       toBePush[second]=true;
//     }
//   }
//   toBePush[first]=true;
//   return result;
// }
// void Picnic(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<vector<bool>> friendTable;
//     PicnicInput(friendTable);
//     vector<bool> toBePush(friendTable.size(),true);
//     int result=PicnicAlgo(friendTable,toBePush);
//     cout<<result<<"\n";
//   }
// }

// void BoardCoverInput(vector<vector<bool>>& boardTable){
//   int height,width;
//   cin>>height>>width;
//   string tmpS;
//   for(int i=0;i<height;i++){
//     boardTable.push_back(vector<bool>(width));
//     cin>>tmpS;
//     for(int j=0;j<width;j++){
//       if(tmpS[j]=='#'){
//         boardTable[i][j]=false;
//       }else{
//         boardTable[i][j]=true;
//       }
//     }
//   }
// }
// bool BoradCoverNoAns(vector<vector<bool>>& boardTable){
//   int cnt(0);
//   for(auto& ele:boardTable){
//     for(auto&& ele2:ele){
//       if(ele2){
//         cnt++;
//       }
//     }
//   }
//   if(cnt%3!=0){
//     return true;
//   }else{
//     return false;
//   }
// }
// int BoardCoverAlgo(vector<vector<bool>>& boardTable){
//   /*
//   제한시간 2초
//   제한메모리 2^16kb=64MB
//   전략1
//     brute force
//       왼쪽 위부터 오른쪽 아래로 가면서 chk 가능, 모양은 4가지 ㄴ, ㄱ, Symmetric ㄴ, Symmetric ㄱ
//         중복은 자연히 걸러짐
//         타일을 올리면 false로 바꾼다.
//         (x,y)기준, (x,y)&(x,y+1)&(x+1,y+1), (x,y)&(x,y+1)&(x-1,y+1), (x,y)&(x+1,y)&(x+1,y+1), (x,y)&(x,y+1)&(x+1,y)
//       first position을 찾는다
//         기저: 찾지 못하면 first==-1, return 1;
//         first 포지션의 4방향을 search
//           4모양 모두 불가능 하면 return 0;
//           가능하다면 재귀
//     time complexity
//       4^(width*height/3)<=10^60 //하얀색이 50칸 이하라는 조건이 존재한다.
//       white<50 -> 4^13=6*10^7
//     mem complexity
//       width*height<=400
//   */
//   //first position
//   int height=boardTable.size();
//   int width=boardTable[0].size();
//   int yPos=-1,xPos=-1;
//   for(int i=0;i<height;i++){
//     for(int j=0;j<width;j++){
//       if(boardTable[i][j]){
//         xPos=j;
//         yPos=i;
//         i=height;
//         break;
//       }
//     }
//   }
//   //기저
//   if(yPos==-1){
//     return 1;
//   }
//   //Algo
//   int result(0);
//   bool xp1(xPos+1<width),xm1(xPos>0),yp1(yPos+1<height);
//   if(xp1&&yp1){
//     if(boardTable[yPos][xPos+1]&&boardTable[yPos+1][xPos+1]){
//       boardTable[yPos][xPos]=boardTable[yPos][xPos+1]=boardTable[yPos+1][xPos+1]=false;
//       result+=BoardCoverAlgo(boardTable);
//       boardTable[yPos][xPos]=boardTable[yPos][xPos+1]=boardTable[yPos+1][xPos+1]=true;
//     }
//     if(boardTable[yPos+1][xPos]&&boardTable[yPos+1][xPos+1]){
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos+1][xPos+1]=false;
//       result+=BoardCoverAlgo(boardTable);
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos+1][xPos+1]=true;
//     }
//     if(boardTable[yPos+1][xPos]&&boardTable[yPos][xPos+1]){
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos][xPos+1]=false;
//       result+=BoardCoverAlgo(boardTable);
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos]=boardTable[yPos][xPos+1]=true;
//     }
//   }
//   if(xm1&&yp1){
//     if(boardTable[yPos+1][xPos-1]&&boardTable[yPos+1][xPos]){
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos-1]=boardTable[yPos+1][xPos]=false;
//       result+=BoardCoverAlgo(boardTable);
//       boardTable[yPos][xPos]=boardTable[yPos+1][xPos-1]=boardTable[yPos+1][xPos]=true;
//     }
//   }
//   return result;
// }
// void BoardCover(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     //true=white, false=black;
//     vector<vector<bool>> boardTable;
//     BoardCoverInput(boardTable);
//     if(BoradCoverNoAns(boardTable)){
//       cout<<"0\n";
//     }else{
//       cout<<BoardCoverAlgo(boardTable)<<"\n";
//     }
//   }
// }

// void ClockSyncInput(vector<int>& clockArr){
//   for(int i=0;i<16;i++){
//     cin>>clockArr[i];
//   }
// }
// int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch){
//   /*
//   제한시간 10초
//   제한메모리 2^16kb=64MB
//   전략1
//     brute force
//       차례대로 가장 적은 스위치와 연결된 시계를 변경하도록 스위치를 조작한다.
//       (스위치)를 조작한 후, (시계)가 0인지 확인
//         확인은 최종단계에서만 해도 충분하다.
//       1. (1,4,9)->(8,9,11,12,13)
//       2. (2,3)->(6,10)
//       3. (7)->(7)
//       4. (8)->(4,5)
//       5. (0,6)->(1,3)
//       6. (5)->(0,2,14,15)
//     time complexity
//       linear
//     mem complexity
//       linear
//     구현이 귀찮다
//   전략2
//     brute force
//       모든 스위치는 3회 이하로 눌린다
//       4회를 눌렀다는 것은 0회를 눌른것과 같다.
//     time complexity
//       4^10
//     유의사항
//       재귀함수 설계시, return하며 답을 만드는 과정을 제대로 만들어야 한다.
//       return시 0 혹은 INF 반환, INF를 반환하면 결과에서 무시되므로 상관없다.
//         0을반환한다면 유효한 경로에 있는 값들만 result 에 더해지게 되는데, 유효하지 않은 경로는 여전히 INF를 갖고 있기 때문이다.
//         프로그램은 순차적으로 실행되기 때문에, 이 경우 참조형식으로 함수를 전달해도 전혀문제가 없다(모든 경우에서 그런진 추가바람)
//       마무리바람
//   */
//   //기저
//   if(nowSwitch==10){
//     bool finish(true);
//     for(auto& ele:clockArr){
//       if(ele%12){
//         finish=false;
//         break;
//       }
//     }
//     return finish? 0: 987654321;
//   }
//   //Algo
//   int result=987654321; //INF
//   for(int i=0;i<4;i++){
//     for(int j=0;j<i;j++){
//       for(auto& ele:switchArr[nowSwitch]) clockArr[ele]+=3;
//     }
//     result=min(result,i+ClockSyncAlgo(clockArr,switchArr,nowSwitch+1));
//     for(int j=0;j<i;j++){
//       for(auto& ele:switchArr[nowSwitch]) clockArr[ele]-=3;
//     }
//   }
//   return result;
// }
// void ClockSync(){
//   int testCase;
//   cin>>testCase;
//   vector<vector<int>> switchArr={
//     {0,1,2},{3,7,9,11},{4,10,14,15},{0,4,5,6,7},
//     {6,7,8,10,12},{0,2,14,15},{3,14,15},
//     {4,5,7,14,15},{1,2,3,4,5},{3,4,5,9,13}
//   };
//   while(testCase--){
//     vector<int> clockArr(16);
//     ClockSyncInput(clockArr);
//     int ans=ClockSyncAlgo(clockArr,switchArr,0);
//     if(ans<987654321){
//       cout<<ans<<"\n";
//     }else{
//       cout<<"-1\n";      
//     }
//   }
// }

// void QuadTreeInput(string& treeData){
//   cin>>treeData;
// }
// string QuadTreeAlgo(string::iterator& iter){
//   /*
//   제한시간 1초
//   제한메모리 2^16kb=64MB
//   전략1
//     기저: b or w를 만났을 때, 그대로 반환
//     재귀: x를 만났을 때, 이때 상하반전 이므로 순서를 바꿔야 한다. 이때 반환되어 오는 값을 result에 더한다 
//       1234 순서가 3412 순서로
//     반환: string 값을 합쳐서 반환
//     time complexity
//       O(N): N 번 호출, 총 길이 N 만큼 문자열 합
//     mem complexity
//       O(N)
//     업데이트
//       iterator를 이용하여 전달인자 간소화
//   */
//   //기저, b and w
//   char head=*iter;
//   iter++;
//   if(head=='b'||head=='w'){
//     return string(1,head);
//   }
//   //Algo, x인 경우
//   string tmp[4];
//   for(int i=0;i<4;i++){
//     tmp[i]=QuadTreeAlgo(iter);
//   }
//   return string("x")+tmp[2]+tmp[3]+tmp[0]+tmp[1];
// }
// void QuadTree(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     string treeData;
//     QuadTreeInput(treeData);
//     string::iterator iter=treeData.begin();
//     cout<<QuadTreeAlgo(iter)<<"\n";
//   }
// }

// void FenceInput(vector<int>& fenceData){
//   int fenceNum,tmp;
//   cin>>fenceNum;
//   fenceData.reserve(fenceNum);
//   for(int i=0;i<fenceNum;i++){
//     cin>>tmp;
//     fenceData.push_back(tmp);
//   }
// }
// int FenceAlgo(vector<int>& fenceData,int left, int right){
//   /*
//   제한시간 1초
//   제한메모리 2^16kb=64MB
//   전략1
//     기저: left==right일 때, max=leftmax=rightmax=fenceData[left];
//     재귀: L(left,mid), R(mid+1,right) 재귀
//     반환: max, leftmax, right max
//       leftmax= L's leftmax
//       rightmax= R's right max
//       newMax=if(fenceData[mid]<fenceData[mid+1])
//         L's rightmax + R's leftmax*fenceData[mid]/fenceData[mid+1]
//         else: vice versa
//       max=max(newMax, L's max, R's max);
//     time complexity
//       O(NlgN): lgN 번 호출, O(n) 비교
//     mem complexity
//       O(N)
//   전략2
//     앞에서부터 뒤로 search
//       key, prev, now 존재
//         key 왼쪽으로는 모두 key보다 크거나 같다
//         prev는 now 직전
//           now가 prev보다 작다면,
//     stack을 이용하는 건데 헷갈려
//   전략 3
//     quick sort 전략을 이용한다.
//       가장 작은 pivot을 구한다
//         분할: (left,pivot-1), (pivot+1,right)로 분리
//         반환: result= max(pivot*(right-left),func(left,pivot-1),func(pivot+1,right));
//         기저: right=left -> return fenceData[left];
//       총 lgN번 구한다
//       time complexity: NlgN
//       mem complexity: N
//   */
//   //기저
//   if(right<left){
//     return 0;
//   }
//   //Algo, 
//   int pivot,minValue(12345);
//   for(int i=left;i<=right;i++){
//     if(fenceData[i]<minValue){
//       minValue=fenceData[i];
//       pivot=i;
//     }
//   }
//   int leftMax=FenceAlgo(fenceData,left,pivot-1);
//   int rightMax=FenceAlgo(fenceData,pivot+1,right);
//   return max(minValue*(right-left+1),max(leftMax,rightMax));
// }
// void Fence(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<int> fenceData;
//     FenceInput(fenceData);
//     cout<<FenceAlgo(fenceData,0,fenceData.size()-1)<<"\n";
//   }
// }
// // void FanmeetingInput(longNum& member,longNum& fan){
// //   string memberTmp,fanTmp;
// //   cin>>memberTmp>>fanTmp;
// //   vector<int> memberV,fanV;
// //   memberV.reserve(memberTmp.length());
// //   for(auto& ele: memberTmp){
// //     if(ele=='M'){
// //       memberV.push_back(1);
// //     }else{
// //       memberV.push_back(0);
// //     }
// //   }
// //   fanV.reserve(fanTmp.length());
// //   for(auto& ele: fanTmp){
// //     if(ele=='M'){
// //       fanV.push_back(1);
// //     }else{
// //       fanV.push_back(0);
// //     }
// //   }
// //   member=move(memberV);
// //   fan=move(fanV);
// // }
// // int FanmeetingAlgo(longNum& member, longNum& fan){
// //   /*
// //   제한시간 10초
// //   제한메모리 2^16kb=64MB
// //   전략1
// //     모든 멤버와 모든팬은 만난다.
// //     한 줄의 모든 멤버들이 포옹하는 경우 -> M & M 이없는 경우 
// //       M=1, F=0으로 하고 bit and(&) -> if (0)-> 모든멤버 포옹
// //     곱셈을 이용, abc 123 각 숫자가 있다 가정하자.
// //       cba*123= a3+(a2+b3)10+(a1+b2+c3)10^2+(b1+c2)10^3+(c1)10^4
// //       악수하는 경우 -> c1, b1+c2, a1+b2+c3, a2+b3, a3
// //         두 숫자중 한 수를 뒤집고 곱한것의 계수와 같다.
// //         이떄 계수가 10을 초과할 수 있으므로 normalize하면 안된다.
// //         karatsuba를 수정해서, normalize를 하지 않도록 수정한다.
// //         모든 멤버가 포옹해야 한다 -> member수~fan의수
// //     time complexity
// //       karatsuba Time + ele 세기 = n^lg3 + n = O(n^lg3)
// //     mem complexity
// //       O(n)
// //   */
// //   member.reverse();
// //   longNum result(fan.karatsuba_notNorm(member));
// //   int ans(0),start(member.length()-1),end(fan.length());
// //   for(int i=start;i<end;i++){
// //     if(result[i]==0){
// //       ans++;
// //     }
// //   }
// //   return ans;
// // }
// // void Fanmeeting(){
// //   int testCase;
// //   cin>>testCase;
// //   while(testCase--){
// //     longNum member,fan;
// //     FanmeetingInput(member,fan);
// //     cout<<FanmeetingAlgo(member,fan)<<"\n";
// //   }
// // }

// void WildcardInput(string& wildcard,vector<string>& fileArr){
//   int fileNum;
//   string tmp;
//   cin>>wildcard>>fileNum;
//   fileArr.reserve(fileNum);
//   for(int i=0;i<fileNum;i++){
//     cin>>tmp;
//     fileArr.push_back(move(tmp));
//   }
// }
// bool Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
//   //wildcard의 w_idx, file의 f_idx부터 비교한다.
//   char& result=DP[w_idx][f_idx];
//   //답이 이미 있을경우
//   if(result!=-1){
//     return result;
//   }
//   //w_idx==w_len까지, wildcard를 모두 비교하는것이 목표
//   int w_len(wildcard.length()),f_len(file.length());;
//   while(w_idx<w_len&&f_idx<f_len){
//     char w_char=wildcard[w_idx];
//     if(w_char==file[f_idx]||w_char=='?'){
//       w_idx++;f_idx++;
//       continue;
//     }
//     if(w_char=='*'){
//       //*에 하나이상 대응
//       if(Wildcard_match(wildcard,file,w_idx,f_idx+1,DP)){
//         return result;
//       }
//       //*에 0개 대응
//       w_idx++;
//       continue;
//     }
//     //*도 아니고, 두 문자도 다른경우 false;
//     result=0;
//     return result;
//   }
//   //f_len은 반드시 모두 매칭되어야 하며, w_len은 마지막 부분이 모두 *라면 모두 매칭되지 않아도 괜찮다.
//   if(f_len==f_idx){
//     if(w_len>w_idx){
//       for(int i=w_idx;i<w_len;i++){
//         if(wildcard[i]!='*'){
//           result=0;
//           return result;
//         }
//       }
//     }
//     result=1;
//   }else{
//     result=0;
//   }
//   return result;
// }
// bool Wildcard_match2(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP){
//   //답이 이미 있을경우
//   char& result=DP[w_idx][f_idx];
//   if(result!=-1){
//     return result;
//   }
//   //1:1 대응시 다음 idx로 넘어간다.
//   int w_len(wildcard.length()),f_len(file.length());
//   if(w_idx<w_len&&f_idx<f_len&&(wildcard[w_idx]==file[f_idx]||wildcard[w_idx]=='?')){
//     return result=Wildcard_match2(wildcard,file,w_idx+1,f_idx+1,DP);
//   }
//   //wildcard search가 끝났을 경우, file search도 끝났어야 match가 된 것이다.
//   if(w_idx==w_len){
//     return result=(f_idx==f_len);
//   }
//   // *이 있을 경우, *와 대응되는것의 길이가 0인 경우(w_idx+1)와 1이상인 경우(f_idx+1)로 구분, 이때 match함수에는 f_idx==file_len에 대한 조건이 없으므로, 제한조건에 추가한다.
//   if(wildcard[w_idx]=='*'){
//     if(Wildcard_match2(wildcard,file,w_idx+1,f_idx,DP)||(f_idx<f_len&&Wildcard_match2(wildcard,file,w_idx,f_idx+1,DP))){
//       return result=1;
//     }
//   }
//   //나머지 경우에는 문자열과 wildcard가 대응되지 않는다.
//   return result=0;
// }
// vector<string> WildcardAlgo(string& wildcard,vector<string>& fileArr){
//   /*
//   제한시간 2초
//   제한메모리 2^16kb=64MB
//   문자열의 길이는 1~100, 알파벳 대소문자, ?, *로 구성, 공백 없음 
//   ?는 문자 하나를 대응, *는 길이 0이상의 문자열 대응
//   파일명의 수 1~50개
//   전략1
//     brtue force
//       1:1 비교 원칙: 같으면 continue, 다르면 return false
//       ?의 경우: 항상 continue
//       *의 경우: 
//         *의 다음 문자가 있을경우: 해당 문자를 찾을 때까지 continue -------Problem-------
//             다음 문자가 없을경우: return true
//     Problem 
//       *의 다음문자가 l이라 하자, l이 여러개 있을경우 그만큼 분기를 생성해줘야 한다.
//         분기-> 재귀, 재귀: 중복 생성 가능, 중복: DP로 해결
//     time complexity
//       wildCardLen(N)*#fileArr(50)*fileNameLen(M)^numOf*(L)=50N*M^L
//     mem complexity
//       100+50*100
//   전략 2
//     Dynamic Programming
//       Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx)
//         wildcard의 w_idx와 file의 f_idx 비교
//       재귀를 통한 완전 탐색을 기준으로 한다.
//         1:1 비교 원칙: 같으면 continue, 다르면 return false
//         ?의 경우: 항상 continue
//         *의 경우: f_idx+1로 재귀 or w_idx+1로 loop 이어서
//       반환 경우의 수
//         w_idx와 f_idx가 마무리 -> return true;
//         w_idx만 마무리-> return false;
//         f_idx만 마무리-> w_idx에 남은것이 *뿐이라면 true, 다른것도 있다면 false; 
//       DP
//         반환하기 전에 DP[w_idx][f_idx]에 1(true) 0(false)저장, -1(not initialized)
//         DP여부 맨 처음에 확인 
//     time complexity
//       wildCardLen(100)*fileLen(100)*loopInMatch(100) = O(n^3);
//     mem complexity
//       wildcard(100)+DP(100*100)+fileArr(100*50) = O(n);
//   전략 3
//     Dynamic Programming
//       전략2에서 함수 내 재귀를 없앤다. -> O(n^2)
//     time complexity
//       wildCardLen*fileLen=O(n^2);
//     mem complexity
//       same as 전략 2
//   */
//   vector<string> result;
//   for(int i=0;i<fileArr.size();i++){
//     string& file=fileArr[i];
//     vector<vector<char>> DP(wildcard.length()+1,vector<char>(file.length()+1,-1));
//     if(Wildcard_match(wildcard,file,0,0,DP)){
//       result.push_back(file);
//     }
//   }
//   return result;
// }
// void Wildcard(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     string wildcard;
//     vector<string> fileArr;
//     WildcardInput(wildcard,fileArr);
//     vector<string> result(WildcardAlgo(wildcard,fileArr));
//     sort(result.begin(),result.end());
//     for(auto& ele:result){
//         cout<<ele<<"\n";
//     }
//   }
// }

// void JoinedLISInput(vector<int>& arrA,vector<int>& arrB){
//   int lenA,lenB;
//   scanf("%d",&lenA);scanf("%d",&lenB);
//   arrA=vector<int>(lenA);
//   for(int i=0;i<lenA;i++){
//     scanf("%d",&arrA[i]);
//   }
//   arrB=vector<int>(lenB);
//   for(int i=0;i<lenB;i++){
//     scanf("%d",&arrB[i]);
//   }
// }
// bool joinedLIS_Afirst(vector<int>& arrA,vector<int>& arrB,int idxA,int idxB){
//   //out of idx 처리
//   if(idxA==arrA.size()){
//     return false;
//   }else if(idxB==arrB.size()){
//     return true;
//   }
//   //비교
//   if(arrA[idxA]!=arrB[idxB]){
//     return arrA[idxA]<arrB[idxB];
//   }else{
//     return arrA[idxA+1]<arrB[idxB+1];
//   }
// }
// int JoinedLISAlgo_1(vector<int>& arrA,vector<int>& arrB){
//   vector<long long> result;
//   int idxA(0),idxB(0);
//   //result의 맨 처음 값 설정
//   if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
//     result.push_back(arrA[idxA]);
//     idxA++;
//   }else{
//     result.push_back(arrB[idxB]);
//     idxB++;
//   }
//   //남은 값에 대해
//   int input; 
//   while(idxA<arrA.size()||idxB<arrB.size()){
//     if(joinedLIS_Afirst(arrA,arrB,idxA,idxB)){
//       input=arrA[idxA];
//       idxA++;
//     }else{
//       input=arrB[idxB];
//       idxB++;
//     }
//     if(result.back()<input){
//       result.push_back(input);
//     }else{
//       *lower_bound(result.begin(),result.end(),input)=input;
//     }
//   }
//   return result.size();
// }
// int JoinedLISAlgo_3(vector<int>& arrA,vector<int>& arrB){
//   vector<int> result1;
//   vector<int> result2;
//   result1.push_back(arrA.front());
//   result2.push_back(arrB.front());
//   //전략 1, 각 arr에 대해 LIS를 만든다
//   for(auto& ele:arrA){
//     if(result1.back()<ele){
//       result1.push_back(ele);
//     }else{
//       *lower_bound(result1.begin(),result1.end(),ele)=ele;
//     }
//   }
//   for(auto& ele:arrA){
//     if(result2.back()<ele){
//       result2.push_back(ele);
//     }else{
//       *lower_bound(result2.begin(),result2.end(),ele)=ele;
//     }
//   }
//   //전략 2, 각 결과에 대해 앞에서부터 greedy
//   vector<int> result;
//   return result.size();
// }
// int JoinedLISAlgo_2(vector<int>& arrA,vector<int>& arrB,int idxA, int idxB,vector<vector<int>>& DP){
//   /*
//   제한시간 2초
//   제한메모리 2^16kb=64MB
//   각 arr의 원소의 개수는 1~100, 자료형 int
//   전략1
//     Dynamic Programming
//       substructure
//         idxA, idxB
//       기존 LIS 전략을 쓰되, 입력을 양쪽 arr의 head중 더 작은값을 넣는다.
//       LIS 전략
//         input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
//       input
//         각 arr의 head 중 작은 값을 input, 값이 같다면 바로 다음 값을 비교하여 더 작은 값을 input, 둘이 같다면 그냥 첫번째 input
//     Problem
//       (10 20 30 1 2), (10 20 30)의 길이는 5 이지만, 이 Algo를 이용하면 3이 나온다.
//     time complexity
//       #arr(n)*lower_bound(lgn)=O(nlgn)
//     mem complexity
//       #arr(n)=O(n)
//   전략2
//     Dynamic Programming
//       substructure
//         idxA, idxB를 입력으로 받는 부분함수
//         substructure(idxA,idxB)는 idxA와 idxB가 각 Arr에서 (이전까지)마지막 수 이며, 두 중 큰 수가 JLIS에서 마지막일 것이다.
//         DP=n^2
//       LIS 전략
//         마지막 값 max(arrA[idxA],arrB[idxB])보다 큰 값을 찾아 재귀, 이때 arrA에대해 한번, arrB에 대해서도 한번 한다.
//     time complexity
//       재귀 n^2* 반복문 n: O(n^3)
//     mem complexity
//       DP(n^2)+ arrA and B(n): O(n^2)
//   전략3
//     Stack
//       각 arr에 전략 1 적용후(vector 형식으로 생성), 적용한 것들을 가지고 greedy(전략 2)
//       LIS 전략:1
//         input이 tail보다 크면 push_back, tail보다 작으면 lower_bound를 찾아서 해당 값을 input으로 변경
//       전략 2
//         결과값은 정렬되어 있다 -> 앞에서부터 작은 값을 input
//     Problem
//       10 20 40 100 400 에서 10 20 30 100 400 으로 변한 결과1
//       15 25 30 200 300 인 결과 2가 있다고 하자
//       결과 1의 3번째가 40일때가 30일때보다 1 긴데, 30이 최종 값이다. 즉 실제 결과보다 길이가 짧다.
//     time complexity
//       (arrA(n)+arrB(n))*lower_bound(lgn)=O(nlgn)
//     mem complexity
//       arrA(n)+arrB(n)+result(2n)=O(n)
//   */
//   //-1부터 시작해서 각 idx에 1을 더했다.
//   int& result=DP[idxA+1][idxB+1];
//   if(result!=-1){
//     return result;
//   }
//   //마지막 value를 찾는다.
//   long long valueA=(idxA==-1? -9876543210:arrA[idxA]);
//   long long valueB=(idxB==-1? -9876543210:arrB[idxB]);
//   long long lastEle(max(valueA,valueB));
//   //A와 B에 대해 substructure
//   result=0;
//   for(int i=idxA+1;i<arrA.size();i++){
//     if(arrA[i]>lastEle){
//       result=max(result,JoinedLISAlgo_2(arrA,arrB,i,idxB,DP));
//     }
//   }
//   for(int i=idxB+1;i<arrB.size();i++){
//     if(arrB[i]>lastEle){
//       result=max(result,JoinedLISAlgo_2(arrA,arrB,idxA,i,DP));
//     }
//   }
//   result++;
//   return result;
// }
// void JoinedLIS(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<int> arrA,arrB;
//     JoinedLISInput(arrA,arrB);
//     //vector<vector<int>> DP(arrA.size()+1,vector<int>(arrB.size()+1,-1));
//     printf("%d\n",JoinedLISAlgo_3(arrA,arrB));
//   }
// }

// void PImem_Input(string& s){
//   cin>>s;
// }
// int PImem_hard(string& numbers,int start,int len){
//   //기저
//   if(start+len>numbers.size()) return 12345;
//   int begin(start+1),end(start+len);
//   //난이도 1
//   bool result(true);
//   for(int i=begin;i<end;i++){
//     if(numbers[i]!=numbers[i-1]) result=false;
//   }
//   if(result) return 1;
//   //난이도 2
//   result=true;
//   int gap=numbers[start+1]-numbers[start];
//   if(gap!=1&&gap!=-1) result=false;
//   for(int i=begin;i<end;i++){
//     if(numbers[i]-numbers[i-1]!=gap) result=false;
//   }
//   if(result) return 2;
//   //난이도 4
//   result=true;
//   for(int i=start+2;i<end;i++){
//     if(numbers[i]!=numbers[i-2]) result=false;
//   }
//   if(result) return 4;
//   //난이도 5
//   result=true;
//   gap=numbers[start+1]-numbers[start];
//   for(int i=begin;i<end;i++){
//     if(numbers[i]-numbers[i-1]!=gap) result=false;
//   }
//   if(result) return 5;
//   //나머지
//   return 10;
// }
// int PImem_Algo(string& numbers, vector<int>& DP, int start){
//   /*
//   제한시간 1초
//   제한메모리 2^16kb=64MB
//   테스트 케이스 50개
//   각 숫자들의 길이는 8~10000, 0~9
//   전략1
//     Dynamic Programming
//       substructure
//         Algo(DP,start)=min(hard(s,start,3)+Algo(DP,start+3),hard(s,start,4)+Algo(DP,start+4),hard(s,start,5)+Algo(DP,start+5));
//           Algo(DP,start)=start에서 마지막까지 외울때의 값,DP이용
//           hard(s,start,len)=string s에서 start부터 길이 len인 조각의 난이도
//         제한조건
//           최대값은 10000/3*10이므로, search완료는 0 반환, out of idx와 같은 것은 12,345 반환
//     time complexity
//       #Algo(n)*Algo(1)*hard(1)
//     mem complexity
//       #arr(n)=O(n)
//   */
//   //기저, search 완료, out of idx
//   if(start==numbers.size()) return 0;
//   if(start>numbers.size()) return 12345;
//   //메모제이션
//   int& result=DP[start];
//   if(result!=0) return result;
//   //substructure
//   int sub3=PImem_hard(numbers,start,3)+PImem_Algo(numbers,DP,start+3);
//   int sub4=PImem_hard(numbers,start,4)+PImem_Algo(numbers,DP,start+4);
//   int sub5=PImem_hard(numbers,start,5)+PImem_Algo(numbers,DP,start+5);
//   return result=min(sub3,min(sub4,sub5));
// }
// void PImem(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     string numbers;
//     PImem_Input(numbers);
//     vector<int> DP(numbers.size());
//     printf("%d\n",PImem_Algo(numbers,DP,0));
//   }
// }

// void Quantization_Input(vector<int>& number,int& quantRange){
//   int numSize;
//   cin>>numSize>>quantRange;
//   number.resize(numSize);
//   for(auto& ele:number){
//     scanf("%d",&ele);
//   }
// }
// void Quantization_DP_A(vector<int>& number, vector<vector<int>>& DP_A){
//   for(int i=0;i<number.size();i++){
//     for(int j=i;j<number.size();j++){
//       int sum(0),avg(0),len(j-i+1),result(0);
//       for(int k=i;k<=j;k++){
//         sum+=number[k];
//       }
//       //반올림
//       avg=int(0.5+static_cast<double>(sum)/len);
//       //제곱합
//       for(int k=i;k<=j;k++){
//         result+=(number[k]-avg)*(number[k]-avg);
//       }
//       DP_A[i][j]=result;
//     }
//   }
// }
// void Quantization_DP_A_2(vector<int>& number, vector<vector<int>>& DP_A){
//   //부분합을 이용해 계산시간을 줄인다. 합, 제곱합을 n에서 1로 최적화
//   int numLen=number.size();
//   vector<int> DP_pSum(numLen); //A(i)=for(x=0~i)sum(number[x])
//   vector<int> DP_pSqSum(numLen);//A(i)=for(x=0~i)sum(number[x]^2)
//   DP_pSum[0]=number[0];DP_pSqSum[0]=number[0]*number[0];
//   for(int i=1;i<numLen;i++){
//     DP_pSum[i]=DP_pSum[i-1]+number[i];
//     DP_pSqSum[i]=DP_pSqSum[i-1]+number[i]*number[i];
//   }
//   //DP_A 계산
//   for(int i=0;i<numLen;i++){
//     for(int j=i;j<numLen;j++){
//       int sum=DP_pSum[j]-(i==0? 0 : DP_pSum[i-1]);
//       int sqSum=DP_pSqSum[j]-(i==0? 0 : DP_pSqSum[i-1]);
//       //반올림
//       int avg=int(0.5+static_cast<double>(sum)/(j-i+1));
//       //제곱합최소값
//       DP_A[i][j]=sqSum-2*avg*sum+avg*avg*(j-i+1);
//     }
//   }
// }
// int Quantization_DP_B(vector<int>& number, vector<vector<int>>& DP_A,vector<vector<int>>& DP_B,int start,int depth){
//   //기저, 모든 숫자를 양자화, 숫자는 남았는데 더 양자화 할 수 없을때
//   if(start==number.size()) return 0;
//   if(depth==0) return 123456789;
//   //메모제이션
//   int& result=DP_B[start][depth];
//   if(result!=-1) return result;
//   //substructure
//   result=123456789;
//   for(int i=0;start+i<number.size();i++){
//     result=min(result,DP_A[start][start+i]+Quantization_DP_B(number,DP_A,DP_B,start+i+1,depth-1));
//   }
//   return result;
// }
// int Quantization_Algo(vector<int>& number,int quantRange){
//   /*
//   제한시간 2초
//   제한메모리 64MB
//   테스트 케이스 50개
//   수열의 길이 1~100, 사용할 숫자의 수 1~10
//   전략1
//     Dynamic Programming
//       두개의 DP 배열
//         첫번째 DP_A
//           수열 오름차순 정렬
//           수열의 길이 * 수열의 길이
//           A(ij)=i~j를 한 숫자로 양자화 했을때의 제곱합 최소치 
//         두번째 DP_A
//           수열의 길이 * 양자화에 사용할 숫자의 수
//           B(i,j)=i번째 숫자부터 j번째 양자화 수를 사용할 때, i번째 숫자부터 제곱합최소치
//       A(i,j)
//         arr[i]~arr[j]범위의 양자화 값 하나를 이용할 때, 제곱합 최소치를 구한다.
//           양자화 값은 arr[i]~arr[j]의 평균
//             증명: 평균보다 a만큼 차이가 나면, (gap1-a)^2+(gap2+a)^2+... > gap1^2+gap2^2+...
//             미분을 이용해서도 증명 가능
//         A(ij)=sum((x-avg)^2), x=i~j
//       substructure  
//         B(i,j)= for(k=i~ last) 
//           B(i,j)=C(i~k-1)+B(k,j+1)
//           오름차순 정렬이기 때문에, optimal substructure가 성립한다.
//         제한조건
//           최대값=1000^2*100=100,000,000, INF=123456789
//           j가 10이면 return 0
//           i가 last를 벗어나면 return INF
//     time complexity
//       sorting(nlgn)+#A(1)*A(n^3)+#B(n^2)*B(n) = O(n^3)
//         optimize: #A2(1)*A2(n^2)
//     mem complexity
//       #arr(n)=O(n)
//   */
//   //정렬
//   sort(number.begin(),number.end());
//   //DP_A, i~j를 한 숫자로 양자화 했을때의 제곱합 최소치
//   vector<vector<int>> DP_A(number.size(),vector<int>(number.size(),-1));
//   Quantization_DP_A_2(number,DP_A);
//   //DP_B
//   vector<vector<int>> DP_B(number.size(),vector<int>(quantRange+1,-1));
//   return Quantization_DP_B(number,DP_A,DP_B,0,quantRange);
// }
// void Quantization(){
//   int testCase;
//   cin>>testCase;
//   vector<int> result;
//   while(testCase--){
//     vector<int> number;
//     int quantRange;
//     Quantization_Input(number,quantRange);
//     cout<<Quantization_Algo(number,quantRange)<<'\n';
//   }
// }

// void AsymTiling_Input(int& tileLen){
//   cin>>tileLen;
// }
// int AsymTiling_DP(vector<int>& DP,int tileLen){
//   int& result=DP[tileLen];
//   if(result!=0) return result;
//   return result=(AsymTiling_DP(DP,tileLen-1)+AsymTiling_DP(DP,tileLen-2))%1000000007;
// }
// int AsymTiling_Algo(int tileLen){
//   /*
//   1초, 64MB, 테스트케이스 50개
//   사각형의 너비 1~100, mod 1,000,000,007
//   전략1
//     Dynamic Programming
//       모든 사각형의 수 - 대칭인 사각형의 수
//       뺄셈에서 mod는 항등이다(음수일경우 mod를 더해준다.)
//       모든 사각형
//         substructure: func(len)=func(len-1)+func(len-2)
//         기저: if len<=1, return 1; -> DP[0], DP[1]을 1로 미리 정하면 됨
//       대칭 사각형
//         if(len%2==1) func2(len)=func(len/2)
//         if(len%2==0) func2(len)=func(len/2)+func(len/2-1)
//     time complexity
//       #func(n)*func(1)+#func2(1)*func2(1)=O(n)
//     mem complexity
//       #DP_A(n)=O(n)
//   */
//   //모든 사각형의 경우의 수
//   vector<int> DP(tileLen+1);DP[0]=1;DP[1]=1;
//   int result=AsymTiling_DP(DP,tileLen);
//   //정답
//   int modValue=1000000007;
//   if(tileLen%2==0)
//     result=(result-(DP[tileLen/2]+DP[tileLen/2-1])%modValue+modValue)%modValue;
//   else
//     result=(result-DP[tileLen/2]+modValue)%modValue;
//   return result;
// }
// void AsymTiling(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int tileLen;
//     AsymTiling_Input(tileLen);
//     cout<<AsymTiling_Algo(tileLen)<<'\n';
//   }
// }

// void Poly_Input(int& block){
//   cin>>block;
// }
// int Poly_DP(vector<vector<int>>& DP,int blockNum,int topNum){
//   int& result=DP[blockNum][topNum];
//   if(result!=-1) return result;
//   //substructrue, preTop=꼭대기 직전 블록의 갯수
//   result=0;
//   for(int preTop=1;preTop<=blockNum-topNum;preTop++){
//     result=(result+(topNum+preTop-1)*Poly_DP(DP,blockNum-topNum,preTop))%10000000;
//   }
//   return result;
// }
// int Poly_Algo(int block){
//   /*
//   1초, 64MB, 테스트케이스 50개
//   사각형의 개수 1~100, mod 10,000,000
//   전략1
//     Dynamic Programming
//       func(사용한 정사각형의 개수, 높이), x는 가장 위에 쌓을 개수
//         substructure: for(height=1~n) func(n,height)= for(x=1~n-height+1) sum(x*func(n-x,height-1))
//         기저: func(i.i)=1;func(i,1)=1;
//         정답: for(i=1~n) sum(func(n,i))
//     Problem
//       top*func(...)가 아니고, (top+직전 높이의 가로 개수-1)*func(...)이다.
//     time complexity
//       #func(n^2)*func(n)+=O(n^3)
//     mem complexity
//       #DP_A(n^2)=O(n^2)
//   전략2
//     Dynamic Programming
//       func(사용한 정사각형의 개수, 가장 높은 위치(top)의 블록갯수)
//         substructure: for(topNum=1~n) func(n,topNum)=for(x=1~n-topNum) sum((topNum+x-1)*func(n-topNum,x))
//         기저: func(i,i)=1;
//         정답: for(i=1~n) sum(func(n,i))
//     time complexity
//       #func(n^2)*func(n)+=O(n^3)
//     mem complexity
//       #DP_A(n^2)=O(n^2)
//   */
//   //DP 생성 및 계산
//   vector<vector<int>> DP(block+1,vector<int>(block+1,-1));
//   //기저
//   for(int i=1;i<=block;i++){
//     DP[i][i]=1;
//   } 
//   int result=0;
//   for(int i=1;i<=block;i++)
//     result+=Poly_DP(DP,block,i);
//   return result%10000000;
// }
// void Poly(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int block;
//     Poly_Input(block);
//     cout<<Poly_Algo(block)<<'\n';
//   }
// }

// void Numb3rs_Input(int& dayPast,int& prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
//   int townNum;
//   cin>>townNum>>dayPast>>prison;
//   townGraph=vector<vector<int>>(townNum,vector<int>(townNum));
//   for(auto& ele:townGraph)
//     for(auto& ele2:ele)
//       scanf("%d",&ele2);
//   int chkTownNum;
//   cin>>chkTownNum;
//   chkTown=vector<int>(chkTownNum);
//   for(auto& ele:chkTown)
//     scanf("%d",&ele);
// }
// double Numb3rs_DP(vector<vector<int>>& townGraph,vector<int>& degree,vector<vector<double>>& DP, int dayPast, int town){
//   double& result=DP[dayPast][town];
//   if(result>-0.5) return result;
//   //substructrue, preTop=꼭대기 직전 블록의 갯수
//   result=0;
//   for(int preTown=0;preTown<townGraph.size();preTown++){
//     if(townGraph[preTown][town])
//       result+=Numb3rs_DP(townGraph,degree,DP,dayPast-1,preTown)/degree[preTown];
//   }
//   return result;
// }
// vector<double> Numb3rs_Algo(int dayPast,int prison,vector<vector<int>>& townGraph,vector<int>& chkTown){
//   /*
//   2초, 64MB, 테스트케이스 50개
//   마을의 수(n)2~50, 지난 일수(d) 1~100, 교도소 위치(마을 중 하나), 마을 이름=0~n-1,확률을 계산할 마을의 수(1~n)
//   전략1
//     Dynamic Programming
//       func(지난 날짜, 마을)= 마을을 방문한 경우의 수
//         substructure: for(town=0~n-1) func(dayPast,town)=for(preTown=인접마을 of town, from townGraph) sum(func(dayPast-1,preTown))
//         기저: prison이 정해져 있으므로, prison인접 마을은 1, prison마을 및 비인접마을은 0으로 초기화,
//         정답: 마지막 날짜, 마을의 경우의 수/전체 경우의 수
//     Problem 
//       경우의 수로 구하는것이 불가능하다.
//     time complexity
//       #func(nd)*func(n)+=O(d*n^2)
//     mem complexity
//       #DP_A(nd)=O(nd)
//   전략2
//     전략1과 같은데 경우의 수가 아닌 확률 계산
//   */
//   //DP 생성, degree[town]=town에서 갈 수 있는 마을의 경우의 수
//   int townNum=townGraph.size();
//   vector<vector<double>> DP(dayPast+1,vector<double>(townNum,-1));
//   vector<int> degree(townNum);
//   for(int i=0;i<townNum;i++){
//     for(auto& ele:townGraph[i]){
//       degree[i]+=ele;
//     }
//   }
//   //기저 생성
//   for(int i=0;i<townNum;i++){
//     if(townGraph[prison][i]) DP[1][i]=(double)1/degree[prison];
//     else DP[1][i]=0;
//   }
//   //정답 생성
//   vector<double> result;
//   for(auto& ele:chkTown)
//     result.push_back(Numb3rs_DP(townGraph,degree,DP,dayPast,ele));
//   return result;
// }
// void Numb3rs(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int dayPast,prison;
//     vector<vector<int>> townGraph;
//     vector<int> chkTown;
//     Numb3rs_Input(dayPast,prison,townGraph,chkTown);
//     for(auto& ele:Numb3rs_Algo(dayPast,prison,townGraph,chkTown))
//       printf("%.8f ",ele);
//     cout<<"\n";
//   }
// }
// void Packing_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp){
//   int itemNum;
//   cin>>itemNum>>weight;
//   itemName=vector<string>(itemNum);
//   itemWeight=itemDesp=vector<int>(itemNum);
//   for(int i=0;i<itemNum;i++)
//     cin>>itemName[i]>>itemWeight[i]>>itemDesp[i];
// }
// int Packing_DP(vector<vector<int>>& DP_desp,vector<int>& itemWeight,vector<int>& itemDesp,int nowChoice,int weightRemain){
//   //기저, nowChoice==N
//   if(nowChoice==itemDesp.size()) return 0;
//   int& result=DP_desp[nowChoice][weightRemain];
//   if(result!=-1) return result;
//   //substructrue, 선택하지 않았을경우, 선택했을경우
//   result=Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain);
//   if(weightRemain>=itemWeight[nowChoice])
//     result=max(result,itemDesp[nowChoice]+Packing_DP(DP_desp,itemWeight,itemDesp,nowChoice+1,weightRemain-itemWeight[nowChoice]));
//   return result;
// }
// vector<int> Packing_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp){
//   /*
//   2초, 64MB, 테스트케이스 50개
//   입력:물건의 수(N)1~100, 캐리어의 용량(W)1~1000, N개의 물건을 이름,부피,절박도 순서로 각 줄에 주어짐, 이름:공백없는 알파벳 대소문자 1~20, 부피와절박도는 1~1000
//   출력:첫 줄에는 최대 절박도 합과 가져갈 물건들의 개수 출력, 이후 한 줄마다 각 물건들의 이름을 출력, 조합이 여러개일 경우 하나만 출력한다.
//   제한: 절박도 최대=100*1000=100000
//   전략1
//     Dynamic Programming
//       func(직전에 선택한 물건, 남은 캐리어 용량)= 절박도의 합
//         DP: size 100*1000, 물건은 순서대로만 선택 가능
//         substructure: func(nowChoice,weightRemain)=for(i=nowChoice+1~N), max, func(i,weightRemain-i_weight)
//         기저: weightRemain<0
//         정답: 경로를 저장한 DP를 이용하여 출력
//     개선1
//       func내부의 loop를 제거하여 수행시간을 줄인다.
//       다음 물건을 선택하느냐/선택하지 않느냐로 구분
//         func(이번에 선택할 물건, 남은 캐리어 용량)= 절박도의 합
//         기저:이번에 선택할 물건==N
//       선택지가 두개뿐이다 -> 이전 기록과 비교하여 선택이 됐는지 비교 가능, 기록 DP 삭제
//     time complexity
//       #func(NW)*func(1)+=O(NW)
//     mem complexity
//       #DP(NW)=O(NW)
//   */
//   //DP 생성
//   vector<vector<int>> DP_desp(itemWeight.size(),vector<int>(weight+1,-1));
//   //DP 채우기
//   int tmp=Packing_DP(DP_desp,itemWeight,itemDesp,0,weight);
//   //정답 생성
//   vector<int> result;
//   result.push_back(tmp);
//   int nowPick(0),weightRemain(weight);
//   while(nowPick<itemWeight.size()-1){
//     //선택했다면, 절박도가 다를것이다.
//     if(DP_desp[nowPick][weightRemain]!=DP_desp[nowPick+1][weightRemain]){
//       result.push_back(nowPick);
//       weightRemain-=itemWeight[nowPick];
//     }
//     nowPick++;
//   }
//   if(DP_desp[nowPick][weightRemain]>0)
//     result.push_back(nowPick);
//   return result;
// }
// void Packing(){
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int weight;
//     vector<string> itemName;
//     vector<int> itemWeight,itemDesp;
//     Packing_Input(weight,itemName,itemWeight,itemDesp);
//     vector<int> result=Packing_Algo(weight,itemWeight,itemDesp);
//     cout<<result.front()<<' '<<result.size()-1<<'\n';
//     for(auto iter=++result.begin();iter!=result.end();iter++){
//       cout<<itemName[*iter]<<'\n';
//     }
//   }
// }

// void Ocr_Input(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
//                 vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
//   cin>>wordNum>>sentenceNum;  //wordNum:1~500, sentenceNum:1~20
//   for(int i=0;i<wordNum;i++){
//     string tmp;cin>>tmp;
//     wordArrMap.insert({tmp,i});
//     wordArr.push_back(tmp);
//   }
//   firstPoss.resize(wordNum);
//   for(auto& ele: firstPoss)
//     scanf("%lf",&ele);
//   classifiPoss=nextPoss=vector<vector<double>>(wordNum,vector<double>(wordNum));
//   for(auto& ele: nextPoss)
//     for(auto& ele2: ele)
//       scanf("%lf",&ele2);
//   for(auto& ele: classifiPoss)
//     for(auto& ele2: ele)
//       scanf("%lf",&ele2);
//   sentenceArr.resize(sentenceNum);
//   cin.ignore();
//   for(auto& ele: sentenceArr)
//     getline(cin,ele);
// }
// void Ocr_Input_test(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
//                 vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
//   cout<<"wordNum: "<<wordNum<<"\n";
//   cout<<"sentenceNum: "<<sentenceNum<<"\n";
//   cout<<"wordArr----------\n";
//   for(auto& ele: wordArr)
//     cout<<ele<<" ";
//   cout<<"\n";
//   cout<<"wordArrMap----------\n";
//   for(auto& ele:wordArrMap)
//     cout<<"("<<ele.first<<", "<<ele.second<<") ";
//   cout<<"\n";
//   cout<<"firstPoss----------\n";
//   for(auto& ele: firstPoss)
//     cout<<ele<<" ";
//   cout<<"\n";
//   cout<<"nextPoss----------\n";
//   for(auto& ele:nextPoss){
//     for(auto& ele2:ele)
//       cout<<ele2<<" ";
//     cout<<"\n";
//   }
//   cout<<"classifiPoss----------\n";
//   for(auto& ele:classifiPoss){
//     for(auto& ele2:ele)
//       cout<<ele2<<" ";
//     cout<<"\n";
//   }
//   cout<<"sentenceArr----------\n";
//   for(auto& ele:sentenceArr)
//     cout<<ele<<"END\n";
// }
// void Ocr_randInput(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
//                 vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
//   wordNum=rand()%500+1; //1~500
//   sentenceNum=rand()%20+1;  //1~20
//   wordArr.resize(wordNum);
//   //wordArr, wordArrMap
//   int idx=0;
//   for(auto& ele:wordArr){ //each word=1~10, only lowercase
//     while(true){
//       int len=rand()%10+1;
//       string tmpStr;
//       for(int i=0;i<len;i++){
//         tmpStr.push_back(rand()%26+97);  //a~z: #26, 97~122
//       }
//       if(wordArrMap.insert({tmpStr,idx}).second){
//         wordArr[idx]=tmpStr;
//         break;
//       }
//     }
//     idx++;
//   }
//   //firstPoss
//   firstPoss.resize(wordNum);
//   int tmpsum(0);
//   for(auto& ele:firstPoss){
//     ele=rand()%100;
//     tmpsum+=ele;
//   }
//   for(auto& ele:firstPoss){
//     ele/=tmpsum;
//   }
//   //classifiPoss, nextPoss
//   classifiPoss=nextPoss=vector<vector<double>>(wordNum,vector<double>(wordNum));
//   for(auto& ele: classifiPoss){
//     tmpsum=0;
//     for(auto& ele2:ele){
//       ele2=rand()%100;
//       tmpsum+=ele2;
//     }
//     for(auto& ele2:ele){
//       ele2/=tmpsum;
//     }
//   }
//   for(auto& ele: nextPoss){
//     tmpsum=0;
//     for(auto& ele2:ele){
//       ele2=rand()%100;
//       tmpsum+=ele2;
//     }
//     for(auto& ele2:ele){
//       ele2/=tmpsum;
//     }
//   }
//   //sentence
//   sentenceArr.resize(sentenceNum);
//   for(auto& sentence:sentenceArr){
//     int sentenceLen=rand()%100+1; //1~100
//     sentence+=to_string(sentenceLen)+' ';
//     for(int i=0;i<sentenceLen;i++){
//       int tmp=rand()%wordNum;
//       sentence+=wordArr[tmp]+' ';
//     }
//     sentence.pop_back();
//   }   
// }
// void Ocr_input_simpleT(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
//                 vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
//   cout<<"wordNum: "<<wordNum<<"___"<<wordArr.size()<<"___"<<wordArrMap.size()<<"___"<<firstPoss.size()<<"___"<<nextPoss.size()<<"___"<<classifiPoss.size()<<endl;
//   cout<<"sentenceNum: "<<sentenceNum<<"___"<<sentenceArr.size()<<endl;
//   //wordArr
//   for(auto& ele:wordArr)
//     cout<<ele<<' ';
//   cout<<endl;
//   //firstPoss
//   double tmpSum(0);
//   for(auto& ele:firstPoss)
//     tmpSum+=ele;
//   cout<<"firstPoss Sum: "<<tmpSum<<endl;
//   //nextPoss,classifiPoss
//   cout<<"nextPoss Sum: ";
//   for(auto& ele: nextPoss){
//     tmpSum=0;
//     for(auto& ele2: ele){
//       tmpSum+=ele2;
//     }
//     cout<<tmpSum;
//   }
//   cout<<endl;
//   cout<<"classifiPoss Sum: ";
//   for(auto& ele: classifiPoss){
//     tmpSum=0;
//     for(auto& ele2: ele){
//       tmpSum+=ele2;
//     }
//     cout<<tmpSum;
//   }
//   cout<<endl;
//   //sentence
//   cout<<"----sentence----\n";
//   for(auto& ele:sentenceArr)
//     cout<<ele<<'\n';
// }
// double Ocr1_DP1(vector<vector<double>>& DP_Ocr1,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,int now, int nextGuess){
//   double& result=DP_Ocr1[now][nextGuess];
//   if(result>-0.5)
//     return result;
//   result=0.0;
//   for(int i=0;i<nextPoss[0].size();i++)
//     result+=nextPoss[now][i]*classifiPoss[i][nextGuess];
//   return result;
// }
// double Ocr1_DPposs(vector<vector<double>>& DP_Ocr1,vector<double>& firstPoss,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,
//                   vector<vector<double>>& DP_Poss,vector<vector<int>>& DP_Path, vector<int>& wordOfSentence,int idx,int nowWord){
//   //기저, 범위 밖, 이미 값이 있는경우
//   if(idx==wordOfSentence.size()-1)
//     return 1.0;
//   double& result=DP_Poss[idx+1][nowWord];
//   if(result>-0.5) 
//     return result;
//   //함수 진행
//   int wordNum=firstPoss.size();
//   result=0.0;
//   int& path=DP_Path[idx+1][nowWord];
//   //맨처음, idx==-1인 경우
//   if(idx==-1){
//     double nextGuessPoss=0.0;
//     for(int i=0;i<wordNum;i++)  //실제 다음위치가 i 값인데, 이를 wordOfSentence[0] 으로 인식했을 확률
//       nextGuessPoss+=firstPoss[i]*classifiPoss[i][wordOfSentence[idx+1]];
//     for(int i=0;i<wordNum;i++){
//       double tmp=firstPoss[i]*classifiPoss[i][wordOfSentence[idx+1]]*Ocr1_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordOfSentence,idx+1,i)/nextGuessPoss;
//       if(cmpDouble_AbsRel(tmp,result)==1){
//         result=tmp;
//         path=i;
//       }
//     }
//     return result;
//   }
//   //함수
//   double nextGuessPoss=Ocr1_DP1(DP_Ocr1,nextPoss,classifiPoss,nowWord,wordOfSentence[idx+1]);
//   if(cmpDouble_AbsRel(0.0,nextGuessPoss)==0){
//     return 0.0;
//   }
//   for(int i=0;i<wordNum;i++){
//     double tmp=nextPoss[nowWord][i]*classifiPoss[i][wordOfSentence[idx+1]]*Ocr1_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordOfSentence,idx+1,i)/nextGuessPoss;
//     if(cmpDouble_AbsRel(tmp,result)==1){
//       result=tmp;
//       path=i;
//     }
//   }
//   return result;
// }
// vector<string> Ocr1_Algo(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,
//                         vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,vector<string>& sentenceArr){
//   //DP 생성
//   vector<vector<double>> DP_Ocr1(wordNum,vector<double>(wordNum,-1.0));
//   //정답 생성
//   vector<string> result;
//   for(auto& ele: sentenceArr){
//     //sentence의 각 word 분리, idx로 치환하여저장
//     vector<int> wordOfSentence;
//     string sentence=ele.substr(2); //앞에 두개는 sentence의 word 갯수, 공백(스페이스바)
//     string tmpWord;
//     for(auto iter=sentence.begin();iter!=sentence.end();iter++){
//       if(*iter==' '){
//         wordOfSentence.push_back(wordArrMap.find(tmpWord)->second);
//         tmpWord.clear();
//       }else{
//         tmpWord.push_back(*iter);
//       }
//     }
//     wordOfSentence.push_back(wordArrMap.find(tmpWord)->second);
//     //조건부 출현확률 최대치 도출
//     vector<vector<double>> DP_Poss(wordOfSentence.size()+1,vector<double>(wordNum,-1.0));
//     vector<vector<int>> DP_Path(wordOfSentence.size()+1,vector<int>(wordNum,-1));
//     Ocr1_DPposs(DP_Ocr1,firstPoss,nextPoss,classifiPoss,DP_Poss,DP_Path,wordOfSentence,-1,0);
//     //경로 도출
//     vector<int> path;
//     int frag=DP_Path[0][0];
//     for(int i=0;i<wordOfSentence.size();i++){
//       path.push_back(frag);
//       frag=DP_Path[i+1][frag];
//     }
//     string tmpResult;
//     for(auto& ele: path){
//       tmpResult+=wordArr[ele]+' ';
//     }
//     tmpResult.pop_back(); //마지막 공백 제거 
//     //result에 정답 입력
//     result.push_back(move(tmpResult));
//   }
//   return result;
// }
// double Ocr2_possQ(const vector<vector<double>>& DP, int prev, int now){
//   return DP[prev+1][now];
// }
// double Ocr2_DPposs(const vector<vector<double>>& DP_possQ,const vector<vector<double>>& DP_RgivenQ,vector<vector<double>>& DP_Poss,
//                     vector<vector<int>>& DP_Path,const vector<int>& wordOfSentence,int nextIdx,int nowWord){
//   //기저, 
//   if(nextIdx==wordOfSentence.size()){
//     return 0.0;
//   }
//   double& result=DP_Poss[nextIdx][nowWord];
//   if(result<0.5){
//     return result;
//   }
//   //Algo
//   int& path=DP_Path[nextIdx][nowWord];
//   if(nextIdx==0){
//     nowWord=-1;
//   }
//   result=-1e200;
//   for(int nextWord=0;nextWord<DP_RgivenQ.size();nextWord++){
//     double tmp=Ocr2_DPposs(DP_possQ,DP_RgivenQ,DP_Poss,DP_Path,wordOfSentence,nextIdx+1,nextWord);
//     tmp+=DP_RgivenQ[nextWord][wordOfSentence[nextIdx]]+Ocr2_possQ(DP_possQ,nowWord,nextWord);
//     //double tmp=Ocr2_possQ(DP_possQ,nowWord,nextWord)+DP_RgivenQ[nextWord][wordOfSentence[nextIdx]]+Ocr2_DPposs(DP_possQ,DP_RgivenQ,DP_Poss,DP_Path,wordOfSentence,nextIdx+1,nextWord);
//     if(cmpDouble_AbsRel(tmp,result)==1){
//       result=tmp;
//       path=nextWord;
//     }
//   }
//   return result;
// }
// vector<string> Ocr2_Algo(int wordNum,int sentenceNum,const vector<string>& wordArr,const map<string,int>& wordArrMap,const vector<double>& firstPoss,
//                         const vector<vector<double>>& nextPoss,const vector<vector<double>>& classifiPoss,const vector<string>& sentenceArr){
//   // log값으로 변횐하고, firstPoss와 nextPoss를 통합한 P(R|Q)를 만든다. 
//   // Ocr2_possQ를 이용하여 값을 받자.
//   // DP[prev][now] 값, first라서 prev가 없는경우 -1로 적어준다.
//   vector<vector<double>> DP_possQ(wordNum+1);
//   for(auto& ele:firstPoss){
//     DP_possQ[0].push_back(log(ele));
//   }
//   for(int i=1;i<=wordNum;i++){
//     for(auto& ele:nextPoss[i-1]){
//       DP_possQ[i].push_back(log(ele));
//     }
//   }
//   //classifiPoss를 log형식으로 변환한 함수 생성
//   vector<vector<double>> DP_RgivenQ=classifiPoss;
//   for(auto& ele:DP_RgivenQ){
//     for(auto& ele2:ele){
//       ele2=log(ele2);
//     }
//   }
//   //정답 생성
//   vector<string> result;
//   for(auto& ele: sentenceArr){
//     //sentence의 각 word 분리, idx로 치환하여저장
//     vector<int> wordOfSentence;
//     string::size_type sz;
//     int sentenceLen=stoi(ele,&sz);  //각 sentence의 단어의 길이는 1~100이다.
//     //int sentenceLen=ele.front() - '0'; // sentence의 단어의 길이가 1~9일때만 성립한다.
//     string sentence=ele.substr(sz+1); // sentence의 길이와, 첫 단어 사이에는 공백이 있기 때문에 제거 
//     int from(0), len(0);
//     for(auto iter=sentence.begin();iter!=sentence.end();iter++){
//       if(*iter==' '){
//         wordOfSentence.push_back(wordArrMap.find(sentence.substr(from,len))->second);
//         from+=len+1;
//         len=0;
//       }else{
//         len++;
//       }
//     }
//     wordOfSentence.push_back(wordArrMap.find(sentence.substr(from,len))->second);
//     //조건부 출현확률 최대치 도출
//     vector<vector<double>> DP_Poss(sentenceLen,vector<double>(wordNum,1.0));  //확률은 1이하이기 때문에 항상 음수값, 따라서 기저는 1.0
//     vector<vector<int>> DP_Path(sentenceLen,vector<int>(wordNum,-1));
//     int cnt(0);
//     for(auto& ele:DP_Poss){
//       for(auto& ele2:ele){
//         cnt++;
//       }
//     }
//     Ocr2_DPposs(DP_possQ,DP_RgivenQ,DP_Poss,DP_Path,wordOfSentence,0,0);
//     //경로 도출
//     vector<int> path;
//     int frag=0;
//     for(int i=0;i<sentenceLen;i++){
//       frag=DP_Path[i][frag];
//       path.push_back(frag);
//     }
//     string tmpResult;
//     for(auto& ele: path){
//       tmpResult+=wordArr[ele]+' ';
//     }
//     tmpResult.pop_back(); //마지막 공백 제거 
//     //result에 정답 입력
//     result.push_back(move(tmpResult));
//   }
//   return result;
// }
// void Ocr(){
//   /*
//   10초, 64MB, 테스트케이스=문장의 수 20개
//   입력: 분석이 끝난 과거 자료의 통계치, 분류기가 인식한 문장으로구성, 자세한 내용은 문제에서 확인
//   출력: 한 문장마다 한 줄에 주어진 인식 결과에 대해 조건주 출현 확률이 가장 높은 문장을 출력, 같은 확률을 가진 문장이 여러개라면 어떤것을 출력해도 좋다.
//   전략1
//     Dynamic Programming
//       준비: sentenceArr->sentence->word 로 분해
//       해석: sentence의 word의 길이 n, 등장 가능한 word의 개수 m
//             sentence X에 대해, 각 word는 x0 x2 ... xn-1 이다 (인식된 결과이므로, 실제 문자와 다를 수 있다.)
//             이전 문자가 Y일 때, 다음으로 등장한 문자가 Z일 확률 nextPoss[Y][Z]
//         DP  이전 문자가 Y일 때, 다음으로 인식된 문자가 R일 확률 p(Y,R)=nextPoss[Y][0]*classifiPoss[0][R]+ ... +nextPoss[Y][m-1]*classifiPoss[m-1][R]
//             이전 문자가 Y이고, 인식된 문자가 R일 때, 실제 등장한 문자가 Z일 가능성 rp(Y,R,Z)=nextPoss[Y][Z]*classifiPoss[Z][R]/p(Y,R)
//               맨 처음 문자는 이전문자를 -1이라고 가정하고 처리하자
//       Ocr1_DP1(이전문자 Y,인식된문자 R)=가능성
//         DP: 500*500
//       func(sentence 에서 idx 번째 word,실제 word:X)=idx번째 word가 X일 때, idx+1부터 시작하는 sentence의 조건부 확률 최대치
//           idx부터 시작하는 sentence의 조건부 확률 최대치 = DP[0][0] 
//         DP: 101*500, idx번째 정보는 idx+1 위치에 저장 
//         substructure: func(idx,nowWord)=for(nextWord=word range), max, nextPoss[Y][Z]*classifiPoss[Z][R]/Ocr1_DP1(Y,R)*func(idx+1,nextWord)
//         기저: idx==sentenceLen: return 1, idx==-1: nextPoss 대신 firstPoss 사용 
//         정답: DP_path를 이용한다
//     의문점
//       Ocr_DP2 있는것이 속도 측면에서 유리한가? 경로를 추적해야 하므로 Ocr_DP2 필요한긴 하지만 속도적인 측면에서 어떤지.
//         -> 함수 실행시간이 1이므로 속도측면에서 유리하지 않다. 경로추적은 전용 DP를 추가하여 해결하자
//     개선점
//       확률 자체보다 확륭리 최대치인 경로를 구하는 것인데, P(R)==DP1의 경우 공통되는 항이므로 없애버리자
//       확률을 그대로 사용하면 반드시 상대비교만을 사용해야한다(절대비교를 사용할시 오차 발생)
//       0이하의 확률을 곱하다보면 의미없는 수치로 낮아질 수 있다. log로 변환하여 이용하자
//     time complexity
//       #func(n*m)*func(m)+#Ocr_DP2(n*m^2)*Ocr_DP2(1)+#Ocr1_DP1(n*m)*Ocr1_DP1(m)=O(n*m^2)
//     mem complexity
//       DP(m*m*m)=O(m^3)
//   전략1_개선
//     준비: 확률을 log값으로 변경, firstPoss를 nextPoss에 통합
//     해석: P(Q|R)=P(QnR)/P(R), P(R)은 모두 동일하므로 삭제
//             P(QnR)=P(R|Q)*P(Q), P(R|Q)=classifiPoss와 P(Q)=nextPoss 모두 문제에서 주어짐
//             lg(P_QnR)=lg(P_R|Q)+lg(P_Q), 덧셈으로 변환 가능
//             double 비교는 상대-절대 혼합비교 이용해도 될듯
//     func(idx, nowWord): idx번째 word가 nowWord일 때, idx+1번째 부터 시작하는 sentence의 조건부 확률 최대치 에 비례하는 값
//     DP: sentenceLen*wordNum , idx의 정보는 idx+1 위치에 저장, idx==sentenceLen-1일 경우는 기저로 처리하여 log1(==0)반환
//     substructure: func(idx,nowWord)=for(nextWord=wordNum range), max, nextPoss[Y][Z]*classifiPoss[Z][R]*func(idx+1,Z)
//     기저: idx==sentenceLen-1: return 1
//     time complexity
//       #func(n*m)*func(m)=O(n*m^2)
//     mem complexity
//       DP(n*m)=O(nm)
//   책의 해답과 나의 해답의 차이: 전략1_개선에서 해결
//     원문 Q, 인식된 sentence R, Q 후보 Q1, Q2 ... 이라 하면
//       나는 각 후보 Qn에 대해 P(Qn|R)를 직접 구하여 Q를 구한 것이고
//         P(Q|R)=P(QnR)/P(R) 에서 P(QnR)을 구했다.
//       해답은 P(Qn|R)==P(R|Qn)*P(Qn)/P(R)로 수정하여 구했다.
//         P(R)은 모든 Qn에 대해 동일하다
//         P(Qn)과 P(R|Qn)은 문제에서 주어진 값을 이용해 쉽게 구할 수 있다.
//   */
//   int wordNum,sentenceNum;
//   vector<string> wordArr,sentenceArr;   //i, am, a, boy, buy 각 단어 저장, i am a boy 각 문장 저장
//   map<string,int> wordArrMap;
//   vector<double> firstPoss;    //맨 처음에 각 word가 나올 확률
//   vector<vector<double>> nextPoss,classifiPoss; //A(ij)=i단어 다음 j단어가 나올 확률, B(ij)=i단어를 j단어로 분류할 확률
//   Ocr_Input(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
//   //Ocr_randInput(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
//   //Ocr_Input_test(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
//   //Ocr_input_simpleT(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
//   vector<string> result=Ocr2_Algo(wordNum,sentenceNum,wordArr,wordArrMap,firstPoss,nextPoss,classifiPoss,sentenceArr);
//   for(auto& ele:result){
//     cout<<ele<<'\n';
//   }
// }

// KLIS
//1. overflow -> -2로 처리 
//2. 연상하는 것을 간단하게 처리, 함수는 되도록 독립적으로 처리(kthLIS 부분)
//3. error가 발생할경우 return이 항상 발생하는지 확인
// void KLIS_Input(int& arrLen,int& orderK,vector<int>& array){
//   cin>>arrLen>>orderK;
//   array=vector<int>(arrLen);
//   for(auto& ele:array)
//     cin>>ele;
// }
// void KLIS_getHistory(vector<int>& array, vector<vector<pair<int,int>>>& history, vector<int>& tmpLIS, int idx=0){
//   //모든 ele에 대해 검토가 완료됐을때
//   if(idx==array.size()){
//     return;
//   }
//   //Algo, last==임시LIS의 가장 뒤의 원소
//   int now(array[idx]),last(idx==0 ? -1 : tmpLIS.back());
//   if(now>last){
//     tmpLIS.push_back(now);
//     history.push_back(vector<pair<int,int>>(1,make_pair(idx,now)));
//   }else{
//     int pointIdx=distance(tmpLIS.begin(),lower_bound(tmpLIS.begin(),tmpLIS.end(),now));
//     tmpLIS[pointIdx]=now;
//     history[pointIdx].push_back(make_pair(idx,now));
//   }
//   KLIS_getHistory(array, history, tmpLIS, idx+1);
// } 
// int KLIS_DP(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases, int LISidx, int reverse_Seq){
//   //LISidx번째 숫자가 reverse_Seq번째로 작은 숫자일 때, LISidx~END 범위에서의 경우의 수
//   //기저
//   if(LISidx==history.size()-1){ //마지막 순서인 경우: 경우의 수가 항상 1
//     return 1;
//   }
//   auto nowIter=history[LISidx].rbegin()+reverse_Seq;
//   int& result=cache_numOfCases[nowIter->first];
//   if(result!=-1){
//     return result;
//   }
//   //Algo
//   result=0;
//   auto nextIter=lower_bound(history[LISidx+1].begin(),history[LISidx+1].end(),make_pair(nowIter->first,0));
//   for(;nextIter!=history[LISidx+1].end();nextIter++){
//     //value chk, value is strictly decreasing
//     if(nowIter->second>nextIter->second){
//       break;
//     }
//     int next_RVS_seq=history[LISidx+1].size()-distance(history[LISidx+1].begin(),nextIter)-1;
//     int tmp=KLIS_DP(history,cache_numOfCases,LISidx+1,next_RVS_seq);
//     result+=tmp;
//     //overflow chk
//     if(result<0||tmp==-2){
//       result=-2;
//       return result;
//     }
//   }
//   return result;
// }
// vector<int> KLIS_kthLIS(vector<vector<pair<int,int>>>& history, vector<int>& cache_numOfCases,int LISidx, int orderK, pair<int,int> prevPair){
//   //기저
//   if(LISidx==history.size()){
//     return vector<int>();
//   }
//   //Algo, pair: {idx, value}, 
//   for(int reverse_Seq=0;reverse_Seq<history[LISidx].size();reverse_Seq++){
//     auto nowPair=*(history[LISidx].rbegin()+reverse_Seq);
//     //value chk, reverse_Seq가 커질수록 value는 커진다.
//     if(prevPair.second>nowPair.second){
//       continue;
//     }
//     //idx chk는 생략, LIS의 개수>=K이기 때문에, 유효한 idx를 벗어나지 않는다.
//     //Algo
//     int cases=KLIS_DP(history,cache_numOfCases,LISidx,reverse_Seq);
//     if(cases>=orderK||cases==-2){ //-2 means INT32 overflow, always bigger than orderK
//       auto tmp=KLIS_kthLIS(history,cache_numOfCases,LISidx+1,orderK,nowPair);
//       tmp.push_back(nowPair.second);
//       return tmp;
//     }else{
//       orderK-=cases;
//     }
//   }
// }
// void KLIS_funcTest(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases){
//   cout<<"=============Test==============\n";
//   cout<<"----------history--------------\n";
//   for(auto& ele:history){
//     for(auto& ele2:ele){
//       cout<<ele2.second<<"("<<ele2.first<<") ";
//     }
//     cout<<"\n";
//   }
//   cout<<"----------cache_numOfCases--------------\n";
//   for(auto& ele:cache_numOfCases){
//     cout<< ele<<" ";
//   }cout<<"\n";
//   cout<<"==========TestEnd==============\n";
// }
// vector<int> KLIS_Algo(int arrLen,int orderK,vector<int>& array){
//   //History 생성, History는 유효하지 않은 값(LIS에 포함되지 않는 값)도 포함되어 있다. 이 경우는 경우의수가 0으로 표기
//   vector<vector<pair<int,int>>> history; //history[LISidx][reverse_Seq] = {ArrIdx, value}, reverse_Seq는 뒤에서 부터의 순서, 값이 작은 순서
//   vector<int> tmpLIS;
//   KLIS_getHistory(array,history,tmpLIS);
//   //정답 생성
//   vector<int> cache_numOfCases(arrLen,-1);
//   vector<int> result= KLIS_kthLIS(history,cache_numOfCases,0,orderK,{0,0}); //pair: {prev idx, prev value}
//   reverse(result.begin(),result.end());
//   //KLIS_funcTest(history,cache_numOfCases);
//   return result; 
// }
// void KLIS(){
//   /*실험 조건
//   2초, 64MB, 테스트케이스=50
//   입력: #eleOfAr n: 1~500, k(th LIS): 1~INT32MAX, #LIS >= k
//   출력: 두 줄에 나눠서 K번쨰 LIS 의 길이, 값 출력
//   */
//   /*전략1_fail
//     문제점: 
//       1. overflow -> -2로 처리 
//       2. history의 잡 값이 runtimeError 유발 
//       3. 연상하는것이 너무 어렵다. 수학적으로 증명을 해야하거나, 비 직관적이다.
//     바탕이 되는 최적화 문제를 푼다. : 이때 최적해를 세야한다는 것을 감안하고 문제를 풀자.
//     최적화 문제의 최적해를 세는 문제를 푼다.
//     답의 수를 기반으로 답안을 재구성한다.
//     Dynamic Programming
//       해결법
//         LIS생성 정보를 담는 History를 만든다. H(ij)=arr idx : nlgn
//           arr idx는 arr에서의 idx를 말한다. 즉 ele의 value가 아니라, arr에서의 위치를 History에 저장하는 것이다.
//         arr idx 번째 원소가 사용될 경우, 해당원소이후의 경우의 수를 저장하는 DP배열을 만든다.: 각 lgn, 최대 nlgn
//           어떤 원소가 LIS에서 등장한다면, 해당 원소는 항상 LIS에서 같은 idx번째에 등장한다. 이를 이용한 DP
//           미리 생성하지 않고 이용할 때 호출하도록 만든다.
//           A라는 ele가 등장 했다면, LIS에서 특정위치(A_idx)의 값이 A로 고정되었다는 뜻이다. 이때 A_idx+1의 값은 아직 고정이 아니므로, 경우의 수가 생기게 되는 것이다.
//           DP생성시, arr idx가 더 큰 최초 위치부터 (lower bound를 이용하여 위치찾기) 탐색하여, 값이 arr idx보다 처음으로 더 작아지는 위치에서 끝낸다.
//         History와 DP를 이용하여 KLIS를 탐색한다. 최대 n
//           History의 i행에서, 열이 클 수록 작은 수 이므로, 큰 열 부터 이용하여 탐색한다.
//             currentK=k에서 시작, 열이 큰것부터 탐색해야 하므로 reverse iterator을 이용하여 탐색한다(jIter == R iter).
//             if(DP(H(ij))<currentK) -> H(ij)번째 수는 포함되지 않는다.다음 열을 탐색한다. currentK-=DP(H(ij));, jIter++;
//             else -> H(ij)번째 수는 포함된다.해당 값을 result에 push한 후, History에서 행을 넘어간다. i++; , result.push_back(arr(H(ij)));
//         오버플로우 해결
//           K는 항상 int_MAX이하의 크기이다.
//           오버플로우를 -2로 처리하면, -2인 경우 항상 해당 원소가 포함되어야한다는 것을 알 수 있다.
//       KLIS_GetLIS(arr, History)
//         History[LIS idx][order]=idx of Arr
//           LIS의 길이를 구하는 식을 사용할 때 생성
//           order가 낮으면 사전순으로 더 앞이 되도록 설정하자
//       KLIS_DP(LIS idx, order,History)= #cases
//         DP: LIS len * arr len
//         DP개선: History[LIS idx][order]를 통해 길이를 arrlen(O(n))으로 줄일 수 있다.
//       vector<int> func(LIS idx, order, k) = LIS idx ~ LIS END 범위에 대해, k번째 LIS return
//         substructure: func(LIS idx, order, k), #cases=KLIS_DP(LIS idx, order)
//                   if k==0  -> return arr[History[LIS idx].back()]+func(LIS idx+1,0,0);
//                   if cases>k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,k);
//                   if cases=k -> return arr[History[LIS idx][order]]+func(LIS idx+1,0,0); 
//                   if cases<k -> return func(LIS idx, order+1, k-cases);
//         기저: if LIS idx== idx len -> return vector<int>();  
//     time complexity
//       GetLIS(#n*lgn)+DP(#n*lgn)+func(#n*4)
//     mem complexity
//       GetLIS(#n)+DP(#n)
//   */
//   /*전략2
//     특징 
//       LIS를 형성할 때, 각 원소가 가질 수 있는 위치는 하나뿐이다. (stack을 이용한 LIS를 잘 생각하면 이해 가능)
//       LIS를 구성하는 원소가, 원본 arr에서 뒤에 있는 원소일수록, 사전순으로는 앞에 위치하는 LIS다.
//         LIS에서 각 원소가 가질 수 있는 위치는 하나뿐인데, 같은 위치에서 arrIdx가 큰 원소라는 것은, value가 더 작은 원소임을 의미한다. (value가 더 크다면 같은 위치를 가질수가 없다.)
//           증명: 임의의 LIS를 잘라서 LIS A , a , b , LIS B 로 만들었다고 하자.
//                 LIS A, alpha, a, LIS B로 대체하였다고 가정하면, alpha < a < b 이므로, LIS A, alpha, a, b, LIS B 라는 새로운 LIS가 생겨난다.
//                 따라서 임의의 alpha는 추가될수 없으므로, a 또한 위치를 변경할 수 없으며, 원소의 위치는 고정된다.
//     DynamicProgramming
//       stack을 이용해 LIS의 길이를 구하는 알고리즘을 이용하여, History를 구한다. -> n*lgn
//         History: stack을 이용하여 LIS를 구할때, 각 stack에서의 값이 변하는 것을 history에 기록한다. 
//           의의: LIS를 형성할때, 각 원소가 가질 수 있는 위치는 하나뿐이다. History를 통해 모든 원소를 검사하지 않고도 numOfCases를 구할 수 있다.
//       History를 이용하여, k번째 LIS를 구한다.
//         LIS의 idx번째 원소의 값이 value일 때의, idx부터 시작하는 LIS의 경우의 수 numOfCases에 대해 -> O(1)
//           k>= numOfCases: k번째 LIS의 idx번째 원소의 값은 value이다.  ->  idx+1에 대해 같은 작업 수행
//           k< numOfCases: idx번째 원소가 value인 LIS는 k번째 LIS보다 사전순으로 앞에서 나온다. ->  History에서 value보다 사전순으로 뒤에 있는 값을 가져오도록 한다.
//         nunOfCases: idx-1위치의 {arridx,value}를 가져와서, arridx가 뒤에있고 value가 더 큰 모든 것의 numOfCases를 더한다. -> LIS_len*(n/LIS_len) ~= n 
//   */
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int arrLen,orderK;
//     vector<int> array;
//     KLIS_Input(arrLen,orderK,array);
//     vector<int> result=KLIS_Algo(arrLen,orderK,array);
//     cout<<result.size()<<'\n';
//     for(auto& ele:result)
//       cout<<ele<<' ';
//     cout<<'\n';
//   }
// }

// void Dragon_example(){
//   vector<char> dragon={'F','X'};
//   int cnt=10; //you can change
//   while(cnt!=0){
//     //print
//     for(auto& ele: dragon){
//       cout<<ele;
//     }
//     cout<<"\n";
//     //next gen
//     vector<char> tmpDragon;
//     for(auto& ele:dragon){
//       if(ele=='X'){
//         tmpDragon.insert(tmpDragon.end(),{'X','+','Y','F'});
//       }else if(ele=='Y'){
//         tmpDragon.insert(tmpDragon.end(),{'F','X','-','Y'});
//       }else{
//         tmpDragon.push_back(ele);
//       }
//     }
//     dragon=move(tmpDragon);
//     cnt--;
//   }
// }
// void Dragon_Input(int& nthGen,int& skip,int& len){
//   cin>>nthGen>>skip>>len;
// }
// int Dragon_getCases(int nthGen){
//   if(nthGen==0){
//     return 1;
//   }
//   //2^nthGen== x+y의 개수, -2: 앞부분 F하나 빼기, 뒷부분 +(-) 하나 빼기 
//   //3배수: 구조가  F  X(or Y) +(or -)
//   long long result=pow(2,nthGen)*3-2; 
//   //chk overflow
//   if(result>1023456789){
//     result=1023456789;
//   }
//   //return
//   return result;
// }
// void Dragon_del_skip_make_history(int nthGen, int skip,vector<pair<string,int>>& history){
//   //기저 
//   if(skip==0){
//     return;
//   }
//   //get #cases and next_string(in case of X or Y)
//   string& last_string=history.back().first;
//   int cases(1);  // + or - or F, cases == 1
//   string next_string;
//    //nthGen > 0 아직 string이 분리되어야함 
//   if(nthGen>0){
//     if(last_string.front()=='X'){
//       cases=Dragon_getCases(nthGen);
//       next_string="X+YF";
//     }else if(last_string.front()=='Y'){
//       cases=Dragon_getCases(nthGen);
//       next_string="FX-Y";
//     }
//   }
//   //history update
//   if(last_string.size()==1){
//     history.pop_back();
//   }else{
//     last_string=last_string.substr(1);
//   }
//   //compare with skip
//   if(cases>skip){
//     history.push_back({next_string,nthGen-1});  //#cases > skip 이라면, 반드시 낮은 Gen이 있을 수밖에 없다.
//     Dragon_del_skip_make_history(nthGen-1,skip,history);
//   }else if(cases<skip){
//     Dragon_del_skip_make_history(nthGen,skip-cases,history);
//   }else{
//     return; //cases-skip==0
//   }
// }
// string Dragon_getDragon(vector<pair<string,int>>& history, int len){
//   //기저
//   if(len==0){
//     return string();
//   }
//   //prepare
//   string& last_string=history.back().first;
//   int nthGen=history.back().second;
//   char ele=last_string.front();
//   //history update
//   if(last_string.size()>1){
//     last_string=last_string.substr(1);
//   }else{  //nthGen>0 : string이 분리가 더 필요한 상태
//     history.pop_back();
//   }
//   //push element to result or history update
//   string result;
//   if(nthGen==0){
//     result.push_back(ele);
//   }else if(ele=='X'){
//     history.push_back({"X+YF", nthGen-1});
//   }else if(ele=='Y'){
//     history.push_back({"FX-Y", nthGen-1});
//   }else{
//     result.push_back(ele);
//   }
//   //result 길이가 부족하면 추가작업 
//   if(result.size()<len){
//     result+=Dragon_getDragon(history, len-result.size());
//   }
//   return result;
// } 
// string Dragon_Algo(int nthGen,int skip,int len){
//   skip--;
//   //remove skip and get history
//   vector<pair<string,int>> history(1,{"FX",nthGen});
//   Dragon_del_skip_make_history(nthGen,skip,history); //string, Gen
//   //make result from history
//   return Dragon_getDragon(history,len);
// }
// void Dragon(){
//   //Dragon Curve
//   /*설명 및 입력
//   설명
//     n세대 드래곤 커브 문자열을 구하고 싶습니다. 이 때 문자열 전체를 구하면 너무 기니, 문자열 중 p번째 글자부터 l글자만을 계산하는 프로그램을 작성하세요.
//     Dragon curve: FX로 시작 -> FX+YF -> FX+YF+FX-YF
//       X->X+YF, Y-> FX-Y (+,- 는 문자 취급)
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 c (c <=50) 가 주어집니다. 각 테스트 케이스의 첫 줄에는 세 개의 정수로 드래곤 커브의 세대 n (0 <= n <= 50)
//       그리고 p 와 l (1 <= p <= 1,000,000,000 , 1 <= l <= 50) 이 주어집니다. n세대의 드래곤 커브 문자열의 길이는 항상 p+l 이상이라고 가정해도 좋습니다.
//     int 범위로 조건부 해결 가능
//       p는 int 범위이지만, 최대 경우의 수는 2^50이라 표현 불가능, 1,000,000,000 이상은 -2로 처리하여 해결하자.
//   제한조건
//     2초, 64MB
//   */
//   /*전략
//     (실패)반복되는 수열이 존재한다 -> DP를 통해 길이와 값을 예상 가능
//       -> 반복되는 것에 집중하여 문제를 어렵게 풀게됨. 수학적 접근도 중요하지만, 프로그래밍적 접근도 충분히 생각하자.
//     Dynamic Programming
//       skip 후 len만큼 길이를 구하는 것이다.
//         skip을 구할때는 경우의 수만 DP를 이용하여 구한다.
//         len을 구할때는, 규칙을 이용해 순서대로 출력한다.
//   */
//  /*전략
//     (실패) skip삭제와 정답을 동시해 구하려니 답이 없어졌다.
//     history를 이용해서 답은 따로 구하자 
//       history: low Generation으로 이동할 때, 현재 Dragon의 남은 값들을 저장하는 것.
//  */
//   //example for 
//   //Dragon_example();
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int nthGen, skip, len;
//     Dragon_Input(nthGen, skip, len);
//     string result=Dragon_Algo(nthGen, skip, len);
//     cout<<result<<'\n';
//   }
// }

// void ZIMBABWE_Input(long long& nowPrice,long long&  mFactor){
//   cin>>nowPrice>>mFactor;
// }
// int ZIMBABWE_bitmaskCount(long long bitmask){
//   //count 1 from bitmask
//   int count(0);
//   while(bitmask!=0){
//     count+=bitmask&1;
//     bitmask>>=1;
//   }
//   return count;
// }
// int ZIMBABWE_DP(vector<vector<int>>& DP_ZIMBABWE,vector<int>& arr_price, long long used_bitmask,int mfactor_remain){
//   //주어진 원소들을 무작위로 정렬하여 만든수를, mod했을때의 분류 
//   //기저
//   int& result=DP_ZIMBABWE[used_bitmask][mfactor_remain];
//   if(result!=-1){
//     return result;
//   }
//   if(used_bitmask==(1<<arr_price.size())-1){
//     if(mfactor_remain==0){
//       return 1;
//     }else{
//       return 0;
//     }
//   }
//   //Algo
//   long long tmp_result(0);  //long long 형식으로 계산하려고 이렇게 함
//   vector<int> arr_duplicateChk(10,0); //0~9가 두번 이상 사용되면 안됨
//   int digit(arr_price.size()-1-ZIMBABWE_bitmaskCount(used_bitmask)), modValue(DP_ZIMBABWE[0].size());
//   for(int idx=0;idx<arr_price.size();idx++){
//     int ele=arr_price[idx];
//     if((used_bitmask&(1<<idx))==0&&arr_duplicateChk[ele]==0){
//       arr_duplicateChk[ele]=1;
//       int mod_tmp_remain=(-ele*static_cast<long long>(pow(10,digit))%modValue+mfactor_remain+modValue)%modValue;
//       tmp_result+=ZIMBABWE_DP(DP_ZIMBABWE,arr_price,used_bitmask|(1<<idx),mod_tmp_remain);
//     }
//   }
//   result=tmp_result%1000000007;
//   return result;
// }
// int ZIMBABWE_func1(vector<vector<int>>& DP_ZIMBABWE,vector<int>& arr_price, int digit, int mfactor_remain){
//   //기저, digit=현재 처리할 위치 
//   long long result(0),value(arr_price[digit]),modValue(DP_ZIMBABWE[0].size());
//   if(digit==0){
//     return 0; //now_price> prev_price이므로, 항상 0을 ret 
//   }
//   //get bitmask, digit자리를 처리해야 하는 것이고, digit+1~ 제일 높은 자릿수 까지는 모두 처리되어 있다.
//   long long bitmask(0);
//   for(int i=digit+1;i<arr_price.size();i++){
//     bitmask|=(1<<i);
//   }
//   //ele<value
//   vector<int> arr_duplicateChk(10,0); //0~9가 두번 이상 사용되면 안됨
//   for(int idx=0;idx<digit;idx++){
//     int ele=arr_price[idx];
//     if(ele<value&&arr_duplicateChk[ele]==0){
//       arr_duplicateChk[ele]=1;
//       int mod_remain=(-ele*static_cast<long long>(pow(10,digit))%modValue+mfactor_remain+modValue)%modValue;
//       result+=ZIMBABWE_DP(DP_ZIMBABWE,arr_price,bitmask|(1<<idx),mod_remain);
//     }
//   }
//   //ele==value
//   int mod_remain=(-value*static_cast<long long>(pow(10,digit))%modValue+mfactor_remain+modValue)%modValue;
//   result+=ZIMBABWE_func1(DP_ZIMBABWE,arr_price,digit-1,mod_remain);
//   return result%1000000007;
// }
// int ZIMBABWE_Algo(long long nowPrice,long long mFactor){
//   //arr_price(nowPrice를 배열로 변경)
//   vector<int> arr_price;  //idx==차수, 낮은 idx가 낮은 차수다
//   while(nowPrice!=0){ //맨 앞자리는 0이 아니므로 문제 없다
//     arr_price.push_back(nowPrice%10);
//     nowPrice/=10;
//   }
//   //DP생성
//   vector<vector<int>> DP_ZIMBABWE(1<<arr_price.size(),vector<int>(mFactor,-1));
//   //결과 return
//   return ZIMBABWE_func1(DP_ZIMBABWE,arr_price,arr_price.size()-1,0);
// }
// void ZIMBABWE(){
//   //ZIMBABWE
//   /*설명 및 입력
//   설명
//     계란을 사간 손님이 환불을 요청한다. 단, 가격은 모른다.
//       가격표는 플라스틱 판으로 표현한다. 3500 은 3 5 0 0 4개로 표시하는 것이다.
//       가격표의 플라스틱판 구성은 바뀌지 않았다. 계란가격이 오름에 따라 순서만 바뀌었다.
//       손님의 계란은 m의 배수다.
//     현재 계란가격 e와 m이 주어질 때, 손님의 구매했을때의 가격의 경우의 수를 구하라 
//       이전 계란 가격은 e보다 항상 작다.
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 그 후 c줄에 각각 2개의 자연수 e와 m (1 <= e <= 10^14, 2 <= m <= 20)이 주어집니다. 
//     현재 계란 가격은 0으로 시작하지 않지만, 이전 계란 가격은 0으로 시작할 수 있습니다.
//       long long 범위로 해결 (10^14가 있으므로)
//   출력
//     경우의 수를 1,000,000,007 로 나눈 나머지를 출력하라 
//   제한조건
//     2초, 64MB
//   */
//   /*전략
//   전략1
//     결국 모든 경우에 대해 구해야 한다. 최대한 빠르게 모든 경우를 구하는 방법이 필요 
//         정말 모든 경우에 대해 구해야 할까? 
//       case 1: e에서 시작하여, 다음으로 가장 큰 수를 구하는 함수를 이용한다.
//         가장 마지막 수를 pivot, 해당 위치를 end, 처음으로 pivot보다 큰 수의 위치를 start라 하자
//           a[start]와 a[end] 바꾼다.
//           a[ent+1] ~ a[start-1]은 가장 큰 숫자가 앞으로 오도록 sorting
//       case 2: 가장 작은 수에서 시작하여, e와 같아질 때 멈춘다. 
//       case 3: mod는 덧셈이 가능함을 이용해 DP계산을 한다.
//         DP가 성립하나? 그냥 mod를 쓰면 되는데?
//       case 4: stack을 이용하면, 특정 숫자보다 작은 모든 숫자를 구할 수 있지 않을까?
//       case 5: std: prev_permutation 이용
//   전략2 
//     mod는 덧셈이 가능하다. 같은 mod를 가진 것들끼리 하나로 묶고, 한번에 연산하면 연산을 줄일 수 있다.
//       길이가 x인 문자열의, 나머지가 y인 DP를 만들 수 있다.
//         DP[x][y] = (DP[x-1][a] + static_cast<long long>(pow(10,x-1)*a))%mod , a=0~ mod -1. mod=modValue, DP[0][a]=0;
//       근데 처음 가격보다 낮은 건 어떻게 계산하지?
//         1.분리방법: 맨 앞자리가 처음과 같으면 수동으로 계산하고, 처음과 다르면(작으면) 첫 값을 고정하고 모든 경우 계산
//           -> 99999876543210과 같은 경우, 최대 13!/4! ~= 2.6억회 
//   정답(전략 2와 유사)
//     모든 경우를 계산할 필요는 없음에 유의하자. mod라는 조건이 있으므로, 해당 조건을 이용하여 연산을 줄인다
//       높은 digit부터 낮은 digit까지, digit의 mod가 정해지면 0~digit-1의 mod도 정해진다는 것을 이용한다. -- DP
//     특정 순열보다 작은 모든 순열이라는 조건
//       높은차수(digit)에서 낮은 digit으로 가면서 계산한다
//         original[digit]=a, another[digit]=b<a 인 another은 항상 original보다 작다.
//         즉, 0~digit-1은 제한조건이 사라지므로 단순한 계산이 가능하다.
//     history가 필요한지 파악하자
//       케이스의 갯수만 구하면 되는 경우는 history가 필요 없으므로, 계산 횟수를 많이 줄일 수 있다. 
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     long long nowPrice, mFactor;
//     ZIMBABWE_Input(nowPrice, mFactor);
//     int result=ZIMBABWE_Algo(nowPrice, mFactor);
//     cout<<result<<'\n';
//   }
// }

// void RESTORE_Input(int& strNum,vector<string>& strArr){
//   cin>>strNum;
//   strArr.resize(strNum);
//   for(auto& ele: strArr){
//     cin>>ele;
//   }
// }
// int RESTORE_isInValid(const string& shortStr,const string& longStr){
//   if(shortStr.size()>longStr.size()){
//     return -1*RESTORE_isInValid(longStr,shortStr);
//   }
//   for(int i=0;i<=longStr.size()-shortStr.size();i++){
//     bool invalid(true);
//     for(int j=0;j<shortStr.size();j++){
//       if(shortStr[j]!=longStr[i+j]){
//         invalid=false;
//         break;
//       }
//     }
//     if(invalid){
//       return 1;
//     }
//   }
//   return 0;
// }
// vector<string> RESTORE_strOptimize(const vector<string>& strArr){
//   vector<string> strArr_opti;
//   vector<int> valid_arr(strArr.size(),1);
//   for(int i=0;i<strArr.size();i++){
//     //최적화, A가 B를 invalid하게 만들었다면, B가 invalid하게 만드는 모든것은 A가 invalid하게 만든다(포함관계 생각하자)
//     if(valid_arr[i]==0){
//       continue;
//     }
//     //Algo
//     const string& ele(strArr[i]);
//     for(int j=i+1;j<strArr.size();j++){
//       //기저
//       if(valid_arr[j]==0){
//         continue;
//       }
//       //Algo
//       const string& ele2(strArr[j]);
//       int inValid=RESTORE_isInValid(ele,ele2);  //both valid:0, ele invalid: 1, ele2 invalid: -1
//       if(inValid==-1){
//         valid_arr[j]=0;
//       }
//       if(inValid==1){
//         valid_arr[i]=0;
//         break;  //invalid되면 더이상 비교할 필요가 없다.
//       }
//     }
//   }
//   for(int i=0;i<valid_arr.size();i++){
//     if(valid_arr[i]){
//       strArr_opti.push_back(strArr[i]);
//     }
//   }
//   return strArr_opti;
// }
// void RESTORE_DP_prepare(vector<vector<int>>& DP_strSaved,vector<string>& strArr_opti){
//   int strNum(strArr_opti.size());
//   //DP(0,front) 
//   for(int front=0;front<strNum;front++){
//     DP_strSaved[0][front]=0;
//   }
//   //DP(front,back)
//   for(int front=0;front<strNum;front++){
//     for(int back=0;back<strNum;back++){
//       if(front==back){
//         continue;
//       }
//       //겹치는 정도 확인
//       int len=min(strArr_opti[front].size(),strArr_opti[back].size());
//       int savedLen=0;
//       const string& frontStr=strArr_opti[front];
//       const string& backStr=strArr_opti[back];
//       for(int i=1;i<len;i++){
//         bool isSaved(true);
//         //하나하나비교 
//         for(int j=0;j<i;j++){
//           if(frontStr[frontStr.size()-i+j]!=backStr[j]){
//             isSaved=false;
//             break;
//           }
//         }
//         //전부 겹치면 saved
//         if(isSaved==true){
//           savedLen=i;
//         }
//       }
//       DP_strSaved[1<<front][back]=savedLen;
//     }
//   }
// }
// int RESTORE_DP(vector<vector<int>>& dp_bitmask,int now_bitmask,int add_str){
//   int strNum=dp_bitmask[0].size();
//   int& result=dp_bitmask[now_bitmask][add_str];
//   if(result!=-1){
//     return result;
//   }
//   result=0;
//   //정답 chk
//   if(now_bitmask==(1<<strNum)-1){
//     for(int i=0;i<strNum;i++){
//       result=max(result,RESTORE_DP(dp_bitmask,now_bitmask-(1<<i),i));
//     }
//     return result;
//   }
//   //general
//   for(int front=0;front<strNum;front++){
//     if((now_bitmask&1<<front)!=0){
//       result=max(result,RESTORE_DP(dp_bitmask,now_bitmask-(1<<front),front)+dp_bitmask[1<<front][add_str]);
//     }
//   }
//   return result;
// }
// string RESTORE_result(vector<vector<int>>& DP_strSaved,const vector<string>& strArr_opti){
//   string result;
//   int strNum=strArr_opti.size();
//   int used_bitmask=(1<<strNum)-1;
//   int back;
//   for(back=0;back<strNum;back++){
//     if(DP_strSaved[used_bitmask][0]==DP_strSaved[used_bitmask-(1<<back)][back]){
//       used_bitmask-=(1<<back);
//       result=strArr_opti[back];
//       break;
//     }
//   }
//   while(used_bitmask!=0){
//     for(int front=0;front<strNum;front++){
//       if((used_bitmask&1<<front)!=0){
//         if(DP_strSaved[used_bitmask][back]==DP_strSaved[used_bitmask-(1<<front)][front]+DP_strSaved[1<<front][back]){
//           used_bitmask-=(1<<front);
//           const string& str_front=strArr_opti[front];
//           result=str_front.substr(0,str_front.size()-DP_strSaved[1<<front][back])+result;
//           back=front;
//           break;
//         }
//       }
//     }
//   }
//   return result;
// }
// string RESTORE_Algo(int strNum,vector<string> strArr){
//   //한 문자열이 다른문자열에 온전히 포함되는 경우가 있다면, 제거
//   vector<string> strArr_opti=RESTORE_strOptimize(strArr);
//   //DP_준비
//   int strNum_opti(strArr_opti.size()); 
//   vector<vector<int>> DP_strSaved(1<<strNum_opti,vector<int>(strNum_opti,-1));  //DP(used_bitmask,add_str)=saved str len
//   RESTORE_DP_prepare(DP_strSaved,strArr_opti);  //DP(1<<front,back), DP(0,front) 을 미리 저장한다.
//   //result
//   RESTORE_DP(DP_strSaved,(1<<strNum_opti)-1,0); //DP is such a history
//   return RESTORE_result(DP_strSaved,strArr_opti);
// }
// void RESTORE(){
//   //RESTORE
//   /*설명 및 입력
//   설명
//     여러개의 문자열이 주어진다. 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력하라
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 C(C≤50)가 주어집니다. 
//     각 테스트 케이스의 첫 줄에는 부분 문자열의 수 k(1≤k≤15)가 주어지고, 다음 k줄에 알파벳 소문자로만 구성된 문자열 조각이 주어집니다. 
//     각 문자열 조각의 길이는 1 이상 40 이하입니다.
//   출력
//     각 테스트 케이스마다 한 줄로, 해당 문자열을 모두 포함하는 가장 짧은 문자열 중 하나를 출력합니다.
//   제한조건
//     2초, 64MB
//   */
//   /*전략
//   전략1
//     앞, 뒤를 연결하며 많은 조합을 시도해본다
//       DP[bitmask_used]=string: 사용된 원소들 중에 가장 짧은 str을 저장한다
//         ex) DP[1101] = minLen(getStr(DP[1100],DP[0001]),getStr(DP[1001],DP[0100]),getStr(...))
//     시간:
//       getStr: O(strlen^2)
//       #DP_func: for(1~n), sum(x(n-x))=n^3
//       Time:O(n^3*strlen^2), n<16, strLen<601
//     문제
//       중간 위치에서, str의 길이가 같다면 두개 모두 고려해야 하지 않을까?
//         ex) DP[11000101]= AABBCC or ABCABC
//       위 문제를 해결하지 못함
//   전략2
//     정답에서 하나씩 빼는 방법으로 생각하자
//       f(used_bitamsk,add_str) = used_bitamsk+ add_str을 할 때, saved_value(절약한 정도)
//         f(used_bitmask,add_str) = for(x=ele of used_bitmask) min(f(used_bitmask without add_str,x)+f2(x,add_str))
//       f2(front,back)=saved_value: front-back로 이어질 때, 절약되는 정도
//         f2(front,back) = f(1<<front,back)
//     시간
//       f: size(2^16*15)*time(15)
//       f2: size(15*15)*time(40)
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int strNum;
//     vector<string> strArr;
//     RESTORE_Input(strNum, strArr);
//     string result=RESTORE_Algo(strNum, strArr);
//     cout<<result<<'\n';
//   }
// }

// void TICTACTOE_Input(vector<vector<string>>& board){
//   for(int i=0;i<board.size();i++){
//     string tmp;
//     cin>>tmp;
//     for(int j=0;j<board[0].size();j++){
//       board[i][j]=tmp[j];
//     }
//   }
// }
// int TICTACTOE_bijection(vector<vector<string>>& board){
//   int result(0);
//   for(int i=0;i<9;i++){
//     result*=3;
//     string tmp=board[i/3][i%3];
//     if(tmp=="o"){
//       result+=1;
//     }else if(tmp=="x"){
//       result+=2;
//     }
//   }
//   return result;
// }
// bool TICTACTOE_isFinished(vector<vector<string>>& board, string turn){
//   //직접계산
//   if(board[0][0]==turn){
//     if(board[0][1]==turn&&board[0][2]==turn) return true;
//     if(board[1][0]==turn&&board[2][0]==turn) return true;
//   }
//   if(board[2][2]==turn){
//     if(board[2][1]==turn&&board[2][0]==turn) return true;
//     if(board[1][2]==turn&&board[0][2]==turn) return true;
//   }
//   if(board[1][1]==turn){
//     if(board[0][0]==turn&&board[2][2]==turn) return true;
//     if(board[2][0]==turn&&board[0][2]==turn) return true;
//     if(board[0][1]==turn&&board[2][1]==turn) return true;
//     if(board[1][0]==turn&&board[1][2]==turn) return true;
//   }
//   return false;
// }
// int TICTACTOE_result(vector<vector<string>>& board, vector<int>& cache_result,string turn_last){
//   //기저
//   int& result=cache_result[TICTACTOE_bijection(board)];
//   if(result!=2){
//     return result;
//   }
//   //기저 2, 직전에 상대방이 둔 수로 게임이 끝났는가?
//   if(TICTACTOE_isFinished(board,turn_last)){
//     result=1;
//     return result;
//   }
//   //Algo
//   string turn_now;
//   if(turn_last=="o"){
//     turn_now="x";
//   }else{
//     turn_now="o";
//   }
//   for(int i=0;i<3;i++){
//     for(int j=0;j<3;j++){
//       if(board[i][j]=="."){
//         board[i][j]=turn_now;
//         result=min(result,-1*TICTACTOE_result(board,cache_result,turn_now));
//         board[i][j]=".";
//       }
//     }
//   }
//   //return, -2 는 더 둘 자리가 없고, 승부도 나지 않았음을 의미한다.
//   if(result==2){
//     result=0;
//     return result;
//   }else{
//     return result;
//   }
// }
// string TICTACTOE_Algo(vector<vector<string>>& board){
//   //누구의 turn인지 구하기
//   int used_O(0), used_X(0);
//   string turn_now, turn_last;
//   for(auto& ele:board){
//     for(auto& ele2: ele){
//       if(ele2=="o"){
//         used_O++;
//       }else if(ele2=="x"){
//         used_X++;
//       }
//     }
//   }
//   if(used_X > used_O){
//     turn_now="o";
//     turn_last="x";
//   }else{
//     turn_now="x";
//     turn_last="o";
//   }
//   //result
//   vector<int> cache_result(static_cast<int>(pow(3,9)),2);
//   int result_int=TICTACTOE_result(board,cache_result,turn_last);
//   if(result_int==1){
//     return turn_last;
//   }else if(result_int==-1){
//     return turn_now;
//   }else if(result_int==0){
//     return string("TIE");
//   }
//   return string("error in TICTACTOE_Algo");
// }
// void TICTACTOE(){
//   //TICTACTOE
//   /*설명 및 입력
//   설명
//     틱택토 게임. 현재 게임판의 상태가 주어질 때, 게임이 진행되었을 때 승자(패자) 혹은 무승부 여부를 구하여라
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 C(<= 50)가 주어집니다.
//     각 테스트 케이스는 세 줄에 각 세 글자로 게임판의 각 위치에 쓰인 글자가 주어집니다.
//     글자가 없는 칸은 마침표(.)로 표현합니다.
//   출력
//     각 테스트 케이스마다 한 줄을 출력합니다.
//     두 사람이 모두 최선을 다할 경우 비긴다면 TIE를, 아닌 경우 이기는 사람의 글자를 출력합니다.
//   제한조건
//     1초, 64MB
//   */
//   /*힌트
//     점대칭, 선대칭(좌우상하대각) 되어도 항상 같은 결과가 나온다 -> 최적화 가능 요소
//     3진법으로 치환하면 승자여부 쉽계 계산 가능하다.  
//   */
//   /*전략
//   전략1
//       int isFinished(board, turn_last): 직전에 둔 사람(turn_last)로 인해 게임이 끝나면 1, 아니면 0 반호나
//       int bijection(board): "."=0, "o"=1, "x"=2로 치환하여 반환 
//       int bitmask(board, turn_last): 
//         기저: cache chk
//         기저2: isFinished로 확인
//         재귀: 남은 부분에 O또는 X 넣고 재귀
//     시간:
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<vector<string>> board(3,vector<string>(3));
//     TICTACTOE_Input(board);
//     string result=TICTACTOE_Algo(board);
//     cout<<result<<'\n';
//   }
// }

// void NUMBERGAME_Input(vector<int>& board){
//   int tmp;
//   cin>>tmp;
//   board.resize(tmp);
//   for(auto& ele: board){
//     cin>>ele;
//   }
// }
// int NUMBERGAME_cache(const vector<int>& board, vector<vector<int>>& DP_cache, int left, int len){
//   //기저
//   if(len==0){
//     return 0;
//   }
//   //기저 2
//   int& result=DP_cache[left][len];
//   if(result!=-50001){
//     return result;
//   }
//   //Algo
//   if(len>=2){
//     result=max(result,-1*NUMBERGAME_cache(board,DP_cache,left+2,len-2)); //왼쪽 두개 삭제
//     result=max(result,-1*NUMBERGAME_cache(board,DP_cache,left,len-2)); //오른쪽 두개 삭제
//   }
//   result=max(result,board[left]-NUMBERGAME_cache(board,DP_cache,left+1,len-1));  //왼쪽 하나 챙기기
//   result=max(result,board[left+len-1]-NUMBERGAME_cache(board,DP_cache,left,len-1));  //오른쪽 하나 챙기기
//   return result;
// }
// int NUMBERGAME_Algo(const vector<int>& board){
//   //DP생성
//   int boardLen=board.size();
//   vector<vector<int>> DP_cache(boardLen,vector<int>(boardLen+1,-50001));
//   //Algo, 
//   return NUMBERGAME_cache(board,DP_cache,0,boardLen);
// }
// void NUMBERGAME(){
//   //NUMBERGAME
//   /*설명 및 입력
//   설명
//     n개의 정수를 일렬로 늘어놓은 게임판을 가지고 현우와 서하가 게임을 합니다. 게임은 현우부터 시작해서 번갈아가며 진행하며, 각 참가자는 자기 차례마다 두 가지 일 중 하나를 할 수 있습니다.
//       게임판의 왼쪽 끝에 있는 숫자나 오른쪽 끝에 있는 숫자 중 하나를 택해 가져갑니다. 가져간 숫자는 게임판에서 지워집니다.
//       게임판에 두 개 이상의 숫자가 있을 경우, 왼쪽 끝에서 2개, 혹은 오른쪽 끝에서 2개를 지웁니다.
//     게임은 모든 숫자가 다 없어졌을 때 끝나며, 각 사람의 점수는 자신이 가져간 숫자들의 합입니다. 
//     두 사람 모두 최선을 다할 때, 두 사람의 최종 점수 차이는 얼마일까요?
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 C (C <= 50) 이 주어집니다. 
//     각 테스트 케이스의 첫 줄에는 게임판의 길이 n (1 <= n <= 50) 이 주어지며, 그 다음 줄에 n 개의 정수로 게임판의 숫자들이 순서대로 주어집니다. 
//     각 숫자는 -1,000 에서 1,000 사이의 정수입니다.
//   출력
//     각 테스트 케이스마다 한 줄로, 두 사람이 최선을 다했을 때 현우가 서하보다 몇 점 더 얻을 수 있는지를 출력합니다.
//   제한조건
//     1초, 64MB
//   */
//   /*힌트
//     대칭게임이므로, 두 사용자가 DP_cache를 공유한다.
//     f=for(모든행동){행동으로 얻은 점수 - f(남은 게임판에서의 상대의 최적 행동)}
//     DP_default: -1000*50-1=-50001
//   */
//   /*전략
//   전략1
//     Dynamic Programing
//       정답(큰단위)->작은단위 DP
//       f=for(모든행동){행동으로 얻은 점수 - f(남은 게임판에서의 상대의 최적 행동)}  이용
//         행동: 2*2종류
//         총 연산수(DP_cache크기): sum(1개가 있을 위치 ~ 연속된 n개가 있을 위치) == sum(n~1)= n^2
//       DP_cache 표현방법
//         DP_cache[left][len]=left번째 부터 len길이만큼 이어져 있는 board
//         크기=n^2
//         default: -50001
//     시간:
//       O(n^2)
//     크기:
//       O(n^2)
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<int> board;
//     NUMBERGAME_Input(board);
//     int result=NUMBERGAME_Algo(board);
//     cout<<result<<'\n';
//   }
// }

// void BLOCKGAME_Input(vector<vector<string>>& board){
//   string tmp;
//   for(int i=0;i<5;i++){
//     cin>>tmp;
//     for(int j=0;j<5;j++){
//       board[i][j]=tmp[j];
//     }
//   }
// }
// char BLOCKGAME_cache(vector<char>& DP_cache, int can_use_bitmask){
//   //기저
//   if(can_use_bitmask==0){
//     return -1;
//   }
//   //기저 2
//   char& result=DP_cache[can_use_bitmask];
//   if(result!=-2){
//     return result;
//   }
//   //Algo
//   for(int idx=0;idx<25;idx++){
//     if((1<<idx)&can_use_bitmask){
//       can_use_bitmask-=(1<<idx);
//       //오른쪽 끝이 아닐경우, 오른쪽으로 확장 가능
//       if((idx%5!=4)&&(1<<(idx+1)&can_use_bitmask)){
//         can_use_bitmask-=(1<<(idx+1));
//         if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//           result=1;
//           return result;
//         }
//         //오른쪽 윗부분 체크
//         if((idx+1-5>0)&&((1<<(idx+1-5))&can_use_bitmask)){
//           can_use_bitmask-=(1<<(idx+1-5));
//           if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//             result=1;
//             return result;
//           }
//           can_use_bitmask+=(1<<(idx+1-5));
//         }
//         //오른쪽 아랫부분 체크
//         if((idx+1+5<25)&&((1<<(idx+1+5))&can_use_bitmask)){
//           can_use_bitmask-=(1<<(idx+1+5));
//           if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//             result=1;
//             return result;
//           }
//           can_use_bitmask+=(1<<(idx+1+5));
//         }
//         //왼쪽 아랫부분 체크
//         if((idx+5<25)&&((1<<(idx+5))&can_use_bitmask)){
//           can_use_bitmask-=(1<<(idx+5));
//           if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//             result=1;
//             return result;
//           }
//           can_use_bitmask+=(1<<(idx+5));
//         }
//         //왼쪽 윗부분 체크
//         if((idx-5>=0)&&((1<<(idx-5))&can_use_bitmask)){
//           can_use_bitmask-=(1<<(idx-5));
//           if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//             result=1;
//             return result;
//           }
//           can_use_bitmask+=(1<<(idx-5));
//         }
//         can_use_bitmask+=(1<<(idx+1));
//       }
//       //맨아래가 아닐경우, 아래로 확장 가능 
//       if((idx+5<25)&&((1<<(idx+5))&can_use_bitmask)){
//         can_use_bitmask-=(1<<(idx+5));
//         if(BLOCKGAME_cache(DP_cache,can_use_bitmask)==-1){
//           result=1;
//           return result;
//         }
//         can_use_bitmask+=(1<<(idx+5));
//       }
//       can_use_bitmask+=(1<<idx);
//     }
//   }
//   //결과값 return, 승리한것을 반환하지 못하면 ,패배 했다느 뜻
//   result=-1;
//   return result;
// }
// string BLOCKGAME_Algo(vector<vector<string>>& board){
//   //DP생성, 비트마스크 생성
//   vector<char> DP_cache(1<<25,-2);
//   int can_use_bitmask=0;
//   for(int i=0;i<5;i++){
//     for(int j=0;j<5;j++){
//       if(board[i][j]=="."){
//         can_use_bitmask+=1<<(5*i+j);
//       }
//     }
//   }
//   //Algo
//   int result=BLOCKGAME_cache(DP_cache,can_use_bitmask);
//   if(result==1){
//     return string("WINNING");
//   }else if(result==-1){
//     return string("LOSING");
//   }
//   return string("ERROR");
// }
// void BLOCKGAME(){
//   //BLOCKGAME
//   /*설명 및 입력
//   설명
//     5×5 크기의 게임판에서 시작해, 둘이 번갈아 가며 블럭을 하나씩 게임판에 내려놓습니다. 
//     블럭은 L 모양으로 구성된 3칸짜리 블럭과 2칸짜리 블럭이 있으며, 항상 게임판에 있는 줄에 맞춰 내려놓아야 합니다. 
//     블럭들은 서로 겹칠 수 없습니다. 
//     각 블록은 자유롭게 뒤집거나 회전해서 올려놓을 수 있습니다. 
//     두 사람이 번갈아가며 블록을 올려놓다가 더 올려놓을 수 없게 되면 마지막에 올려놓은 사람이 승리합니다.
//     진행 중인 게임판이 주어질 때 이번 차례인 사람이 승리할 수 있는 방법이 있는지를 판단하는 프로그램을 작성하세요.
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 C (C≤50)가 주어집니다. 
//     각 테스트 케이스는 다섯 줄에 각 다섯 개의 문자로 구성되며, #는 이미 블록이 놓인 칸, 마침표(.)는 블록이 없는 칸을 의미합니다.
//   출력
//     각 테스트 케이스마다 한 줄을 출력합니다. 
//     이번 차례인 사람이 항상 이길 수 있는 방법이 있다면 WINNING을, 항상 질 수밖에 없다면 LOSING을 출력합니다.
//   제한조건
//     2초, 64MB
//   */
//   /*힌트
//     대칭게임이므로, 두 사용자가 DP_cache를 공유한다.
//     f=max(for(모든 나의행동){나의 행동 & f(남은 게임판에서 상대의 승리여부)}) , 나의승리=1, 상대의 승리=-1
//     DP_default: -1
//     board를 사용하거나, board를 bitmask로 바꾸어 사용하거나, 둘 중 하나만 하면 된다.
//       25칸이므로 bitmask를 사용할 수 있다.
//       board를 bijection하는 함수가 필요하다.
//     왼쪽위(0,0)부터 오른쪽아래(4,4)로 진행하며, 확장 위치는 각 블록별로 다르게
//       2블록은 우측과 아래측
//       4블록은 우측 확장후, 위, 아래, 우측위, 우측아래 4방향으로 확장
//   */
//   /*전략
//   전략1
//     Dynamic Programing
//       정답(큰단위)->작은단위 DP
//       f=max(for(모든 나의행동){나의 행동 & f(남은 게임판에서 상대의 승리여부)}) , 나의승리=1, 상대의 승리=-1
//         행동: 25번 반복, 블록 확인은 2개(2블록)+4개(3블록) = 6n
//         총 연산수(DP_cache크기): bitamsk=2^25 = 2^n
//     시간:
//       O(2^n * n)
//     크기:
//       O(2^n)
//     sol유의사항
//       int로 DP를 만들면 memover가 떠서, char로 바꾸어주었다.
//         vector<bitset<1>> 2줄을 이용할 수도 있다.(vector<bool>은 사용하지 않는다) 
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     vector<vector<string>> board(5,vector<string>(5));
//     BLOCKGAME_Input(board);
//     string result=BLOCKGAME_Algo(board);
//     cout<<result<<'\n';
//   }
// }

// void SUSHI_Input(vector<pair<int,int>>& menu, int& budget){
//   int menuLen;
//   cin>>menuLen>>budget;
//   menu.resize(menuLen);
//   for(auto& ele: menu){
//     cin>>ele.first>>ele.second;
//   }
// }
// int SUSHI_Algo2(vector<pair<int,int>> menu,int budget){
//   //budget과 menu 100 나누기, menu sort
//   for(auto& ele:menu){
//     ele.first/=100;
//   }
//   budget/=100;
//   sort(menu.begin(),menu.end());
//   //DP생성, 초기화
//   vector<int> tmp_cache(201,0);
//   for(auto& ele:menu){
//     if(ele.first<=budget){
//       tmp_cache[ele.first]=ele.second;
//     }
//   }
//   //Algo
//   for(int cost=0;cost<=budget;cost++){
//     int cand=0;
//     for(auto& ele: menu){
//       if(cost>=ele.first){
//         cand=max(cand,tmp_cache[(cost-ele.first)%201]+ele.second);
//       }
//     }
//     tmp_cache[cost%201]=cand;
//   }
//   //result
//   int result=0;
//   for(auto& ele:tmp_cache){
//     result=max(result,ele);
//   }
//   return result;
// }
// int SUSHI_Algo(vector<pair<int,int>> menu,int budget){
//   //budget과 menu 100 나누기, menu sort
//   for(auto& ele:menu){
//     ele.first/=100;
//   }
//   budget/=100;
//   sort(menu.begin(),menu.end());
//   //DP생성, 초기화
//   vector<int> tmp_cache(201,0);
//   for(auto& ele:menu){
//     if(ele.first<=budget){
//       tmp_cache[ele.first]=ele.second;
//     }
//   }
//   //Algo
//   for(int cost=0;cost<=budget;cost++){
//     if(tmp_cache[cost%201]!=0){
//       for(auto& ele:menu){
//         if(cost+ele.first<=budget){
//           int& value=tmp_cache[(cost+ele.first)%201];
//           value=max(value,tmp_cache[cost%201]+ele.second);
//         }
//       }
//     }
//   }
//   //result
//   int result=0;
//   for(auto& ele:tmp_cache){
//     result=max(result,ele);
//   }
//   return result;
// }
// void SUSHI(){
//   //SUSHI
//   /*설명 및 입력
//   설명
//     회전초밥집에는 n종류의 메뉴가 있는데, 운영진들은 각 메뉴에 대해 선호도를 매겼습니다.
//     운영진들은 주어진 예산 안에서 선호도의 합을 최대한으로 하도록 초밥을 먹고 싶습니다. 
//     각 종류의 초밥은 무한정으로 공급된다고 가정합시다. 이 때 얻을 수 있는 최대한의 선호도는 얼마일까요?
//   입력
//     입력의 첫 줄에는 테스트 케이스의 수 c(1 <= c <= 50)가 주어집니다. 
//     각 테스트 케이스의 첫 줄에는 초밥의 종류 n(1 <= n <= 20)과 운영진들의 예산 m (1 <= m <= 2,147,483,647)이 주어집니다. 
//     그 후 n 줄에 각 초밥의 가격과 선호도가 순서대로 주어집니다. 가격은 20,000 이하의 자연수로, 항상 100 의 배수입니다. 선호도는 20 이하의 자연수입니다.
//   출력
//     각 테스트 케이스별로 한 줄에 가능한 선호도의 최대 합을 출력합니다.
//   제한조건
//     8초, 64MB
//   */
//   /*힌트
//     예산이 1~int_max이지만, 금액은 항상 100의 배수다. 즉 DP이용시 cache의 크기를 100배 줄일 수 있다.
//     가격은 항상 20000원 이하이다. 현재금액에서 20000원보다 낮은 금액은 이용하지 않으므로, sliding window기법으로 mem 절약이 가능하다.
//       cost 오름차순으로 정렬해야 한다.
//       위 두개를 이용하면, 0~200까지, 총 201만큼의 cache만으로 연산이 가능하다.
//         0~199까지 할 경우, 200이 0에 저장되어 순서가 꼬이는 문제가 발생한다.
//       작은단위에서 큰 단위로 계산해야한다. 0~budget
//       마지막 정해진 금액을 초과할 경우, cache내부에서 가장 큰 값이 정답이다.
//       if(DP[x] != 0) -> for(모든 음식 1~n) DP[x+cost] = max(DP[x+cost],DP[x] + value) 
//   */
//   /*전략
//   전략1
//     Dynamic Programing
//       sliding window 기법을 사용한다.
//       작은단위 -> 큰단위 DP
//       금액과 예산은 모두 100으로 먼저 나눈뒤 사용한다.
//       if(DP[x] != 0) -> for(모든 음식 1~n) DP[x+cost] = max(DP[x+cost],DP[x] + value) 
//         cache 크기: 201
//         연산시간: 20(메뉴의 갯수)
//         연산횟수: 0~21474836 (int_max/100)
//     시간:
//       4억회
//     크기:
//       201 byte
//     sol 유의사항
//       algo2가 왜 algo보다 빠를까?
//         우선 tmp_cache[]!=0 부분, 배열이 비어있는지 확인하는 부분은 매우 제한적으로 유효하다.(항상 비어있는 부분이 있을때만 유효)
//           이 부분을 제거하여도 보편적인 속도에는 큰 차이가 없음을 확인할 수 있다.
//         그렇다면 두 algorithm의 구조적차이에서 속도의 차이가 발생함을 알 수 있다.
//           algo: tmp_cache[now]에서 tmp_cache[now+cost]부분을 수정한다.
//           algo2: tmp_cache[now]부분을 수정하며, tmp_cache[now-cost]에서 값을 불러온다.  
//           두 알고리즘 모두 캐시 호출 횟수에서는 차이가 없음을 알 수 있다.
//           두 알고리즘 모두 불러오는 캐시의 위치의 분포가 같다(+cost냐 -cost냐 차이이므로 당연히 같다)
//           algo의 경우 반복문 호출마다 참조형태로 값을 불러오는데 이는 속도에 큰 영향을 끼치지는 않는다(algo2를 유사한 형식으로 바꿔도 속도차이 x)
//           남은 차이는, max함수를 여러 부분에 적용하는지, 한 부분에 적용하는지의 차이다.
//             algo2는 tmp_cache[now]에만 max를 적용하면 된다.
//             algo는 tmp_cache[now+each cost], 각각의 cost에 대해 max를 적용해야 한다.
//             algo는 한번의 6개의 위치를 수정하고, algo2는 한번의 1개의 위치를 수정한다.
//               하드웨어적인 특성에서 기인했다고 본다.
//           하드웨어적인 특성 
//             cpu는 cache에서 계산하여 비교적 속도가 느린 mem 혹은 hdd에 저장한다.
//             algo와 algo2는 cache에서 계산하는 횟수는 동일하다
//             그러나 algo2는 속도가 느린 저장장치에 1번 접근하는 반면
//               algo는 속도가 느린 저장장치에 n번(음식의 갯수)만큼 접근하여 저장해야한다.
//             속도의 느린 저장장치에 접근하는 횟수가 많아져, 시간에 더 오래걸린 것이다. 
//   */
//   //Sol
//   int testCase;
//   cin>>testCase;
//   while(testCase--){
//     int budget;
//     vector<pair<int,int>> menu; 
//     SUSHI_Input(menu,budget);
//     int result=SUSHI_Algo(menu,budget);
//     cout<<result<<'\n';
//   }
// }

