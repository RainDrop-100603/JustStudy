#ifndef __JUSTSOL_H__
#define __JUSTSOL_H__


#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>
#include <algorithm>
#include <set>
#include <map>

using namespace std;

#include "GoodFunction.h"

//just Sol
vector<vector<int>> Remainder_nCr(int n, int M){ //nCn까지 구할 수 있는 파스칼 삼각형, 각 원소에 mod_M(%M)을 취했다. nCr이 엄청나게 커질경우, mod는 파스칼 삼각형으로 구해야 한다. 나눗셈이 있을경우 mod에 대한 결합법칙은 성립하지 않기때문.
  vector<vector<int>> pascalTriangle(n+1,vector<int>(n+1));
  for(int i=0;i<=n;i++){    //n
    pascalTriangle[i][0]=1; //nC0
    pascalTriangle[i][i]=1; //nCn
    for(int j=1;j<i;j++){  //r
      pascalTriangle[i][j]=(pascalTriangle[i-1][j-1]+pascalTriangle[i-1][j])%M;
    }
  }
  return pascalTriangle;
}
bool ChkDuplicate(int x, int depth, int* num){ //num의 depth-1번째 까지 수에서, x와 겹치는 것이 있는지 확인
  for(int i=0;i<depth;i++){
    if(num[i]==x){
      return true;
    }
  }
  return false;
}
void PrintAllCombi(int n, int r, int depth, int* num){ //nCr 조합, depth번째 수, 수를 저장하는 num, digit=0: 가장 앞에 수(167:digit 0 -> 1);
  if(depth==r){   //출력
    int count=0;
    while(count<r){
      cout<<num[count]<<' ';
      count++;
    }
    cout<<"\n";
    return;
  }

  for(int i=1;i<=n;i++){
    if(!ChkDuplicate(i,depth,num)){
      num[depth]=i;
      PrintAllCombi(n,r,depth+1,num);
    }
  }
}
void PrintAllCombi2(int n, int r, int depth, int* num, int start){ //N과 M(2) 문제 
  if(depth==r){   //출력
    int count=0;
    while(count<r){
      cout<<num[count]<<' ';
      count++;
    }
    cout<<"\n";
    return;
  }
  if(start>n){
    return;
  }
  for(int i=start;i<=n;i++){
    num[depth]=i;
    PrintAllCombi2(n,r,depth+1,num,i+1);
  }
}
void PrintAllCombi3(int n, int r, int depth, int* num){ //N과 M(3) 문제 
  if(depth==r){   //출력
    int count=0;
    while(count<r){
      cout<<num[count]<<' ';
      count++;
    }
    cout<<"\n";
    return;
  }

  for(int i=1;i<=n;i++){
    num[depth]=i;
    PrintAllCombi3(n,r,depth+1,num);
  }
}
void PrintAllCombi4(int n, int r, int depth, int* num, int start){ //N과 M(4) 문제
  if(depth==r){   //출력
    int count=0;
    while(count<r){
      cout<<num[count]<<' ';
      count++;
    }
    cout<<"\n";
    return;
  }
  if(start>n){
    return;
  }
  for(int i=start;i<=n;i++){
    num[depth]=i;
    PrintAllCombi4(n,r,depth+1,num,i);
  }
}
int N_Queen(int N,vector<bool>& colQueen,vector<bool>& lineRDQueen,vector<bool>& lineLDQueen, int row){ //N_Queen문제, count는 N번째 Queen을 말함 
  int sum=0;
  if(row==N){
    return 1; //N개가 모두 놓아야 하나의 case 이므로 
  }

  for(int j=0;j<N;j++){
    if(!(colQueen[j]||lineRDQueen[N-row+j]||lineLDQueen[row+j])){
      colQueen[j]=true;
      lineRDQueen[N-row+j]=true;
      lineLDQueen[row+j]=true;
      sum+=N_Queen(N,colQueen,lineRDQueen,lineLDQueen,row+1);
      colQueen[j]=false;
      lineRDQueen[N-row+j]=false;
      lineLDQueen[row+j]=false;        
    }
  }

  return sum;
}
bool Sdoku(int sdoku[9][9],vector<pair<int,int>>& empty,int filledNum,int emptySize){ //filledNum은 채워진 개수, emptySize까지 가면 true, 아니면 false 반환 
  // 모두 채우기를 완료하면 true 반환 
  if(filledNum==emptySize){
    return true;
  }

  //table 채우기
  bool chkInputOk[10];  //각각의 row, column, box에서 삽입 가능한 숫자,1~9만 사용하며 true일때 삽입 가능하단 뜻 
  fill_n(chkInputOk,10,true);
  int x,y,box;//array[x][y], (0,1,2) "\n" (3,4,5) "\n" (6,7,8) Box
  x=empty[filledNum].first;
  y=empty[filledNum].second;
  box=x/3*3+y/3;
  for(int j=0;j<9;j++){       //중복 체크
    chkInputOk[sdoku[x][j]]=false;  //row check
    chkInputOk[sdoku[j][y]]=false;  //column check
    chkInputOk[sdoku[box/3*3+j/3][box%3*3+j%3]]=false;  //Box  check
  }
  
  //대입과 loop
  for(int k=1;k<=9;k++){
    if(chkInputOk[k]){
      sdoku[x][y]=k;
      if(Sdoku(sdoku,empty,filledNum+1,emptySize)){
        return true;
      }
      sdoku[x][y]=0;
    }
  }

  return false;
  
}
void GetMaxMin(vector<int>& arrayV,int* AddSubMulDiv,int& max,int& min,int idx,int sum){ //idx번째까지의 결과(sum)와 idx+1번째 수를 계산. idx=arrayV.len()이면 max min 체크
  if(idx+1==arrayV.size()){ //모든 계산 완료
    if(sum>max){
      max=sum;
    }
    if(sum<min){
      min=sum;
    }
    return;
  }

  for(int i=0;i<4;i++){ //ADD, SUB, MUL, DIV
    if(AddSubMulDiv[i]==0){
      continue;
    }
    switch(i){
      case 0:
        sum+=arrayV[idx+1];
        break;
      case 1:
        sum-=arrayV[idx+1];
        break;
      case 2:
        sum*=arrayV[idx+1];
        break;
      case 3:
        sum/=arrayV[idx+1];
        break;
    }
    AddSubMulDiv[i]--;
    GetMaxMin(arrayV, AddSubMulDiv, max, min, idx+1, sum);
    AddSubMulDiv[i]++;
    switch(i){
      case 0:
        sum-=arrayV[idx+1];
        break;
      case 1:
        sum+=arrayV[idx+1];
        break;
      case 2:
        sum/=arrayV[idx+1];
        break;
      case 3:
        sum*=arrayV[idx+1];
        break;
    }
  }
}
void GetLowGap(int& gap,vector<vector<int>>& table,vector<int>& startTeam,vector<int>& linkTeam,int idx){ //idx번째 선수를 각 팀에 배분. 배분이 끝나면 gap 을 계산하고 기존 gap보다 낮을시 갱신 
  int len=table.size(); //N: 전체 인원수, len/2: 각 팀의 인원수
  //인원 배분이 완료 된 후, 각 팀의 능력치 계산 
  if(idx==len){
    int sum1=0;
    int sum2=0;
    for(int i=1;i<=len/2;i++){
      for(int j=i+1;j<=len/2;j++){
        sum1+=table[startTeam[i]][startTeam[j]]+table[startTeam[j]][startTeam[i]];
        sum2+=table[linkTeam[i]][linkTeam[j]]+table[linkTeam[j]][linkTeam[i]];
      }
    }
    int tempGap=abs(sum1-sum2);
    if(tempGap<gap){
      gap=tempGap;
    }
    return;
  }
  //인원 배분
  for(int i=0;i<2;i++){
    if(i==0&&startTeam[0]!=len/2){
      startTeam[startTeam[0]+1]=idx;
      startTeam[0]++;
      GetLowGap(gap,table,startTeam,linkTeam,idx+1);
      startTeam[0]--;
    }else if(i==1&&linkTeam[0]!=len/2){
      linkTeam[linkTeam[0]+1]=idx;
      linkTeam[0]++;
      GetLowGap(gap,table,startTeam,linkTeam,idx+1);
      linkTeam[0]--;
    }
  }

}

class Queue{
  vector<int> q;
  int idx=0;
public:
  Queue& push(int num){
    q.push_back(num);
    return *this;
  }
  int pop(){
    if(this->empty()){
      return -1;
    }else{
      return q[idx++];
    }
  }
  int size(){
    return q.size()-idx;
  }
  bool empty(){
    if(this->size()<1){
      return true;
    }else{
      return false;
    }
  }
  int front(){
    if(this->empty()){
      return -1;
    }else{
      return q[idx];
    }
  }
  int back(){
    if(this->empty()){
      return -1;
    }else{
      return q.back();
    }
  }
};
class PriorityQueue{
  vector<pair<int,int>> q;    //first= value, second=priority
  int from=0;                  //queue는 from부터 시작한다.
  vector<int> priority; //prioirty 개수 저장, 0~priority
public:
  PriorityQueue(int maxpriority){
    priority=vector<int>(maxpriority+1);
  }
  PriorityQueue& push(pair<int,int> p){
    q.push_back(p);
    priority[p.second]++;
    return *this;
  }
  int size(){
    return q.size()-from;
  }
  bool empty(){
    if(this->size()<1){
      return true;
    }else{
      return false;
    }
  }
  pair<int,int> pop(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      priority[q[from].second]--;
      return q[from++];
    }
  }
  int maxPriority(){
    int len=priority.size()-1;
    for(int i=len;i>=0;i--){
      if(priority[i]){
        return i;
      }
    }
    return 0;
  }
  pair<int,int> prioirtyPop(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      int maxP=maxPriority();
      while(this->front().second!=maxP){
        this->push(this->pop());
      }
      return this->pop();
    }
  }
  pair<int,int> front(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      return q[from];
    }
  }
  pair<int,int> back(){
    if(this->empty()){
      return make_pair(-1,-1);
    }else{
      return q.back();
    }
  }
  void clear(){
    q.clear();
    for(auto& ele:priority){
      ele=0;
    }
    from=0;
  }
  
};
class LinkedList{ //Linked List Controlloer, Controller-list1-list2... -lastlist와 같은 형식으로 이루어져 있다.
  int key;
  LinkedList* next;
  LinkedList(int key,LinkedList* next):key(key),next(next){}  //list, list추가는 직접할 수 없고 멤버함수를 통해야만한다.
  LinkedList* GetList(int num){ //num번째 link의 포인터 반환, 0은 controller 
    LinkedList* returnValue=this;;
    while(num--){
      returnValue=returnValue->next;
    }
    return returnValue;
  }
  bool idxError(int idx){
    int listLen=GetLength();
    if(listLen<idx||idx<1){
      return true;
    }
    return false;
  }
public:
  LinkedList():key(0),next(nullptr){} //controller, key 초기화 불가능
  LinkedList* Push_list(int idx, int key, LinkedList* next=nullptr){ //linked list의 마지막에 list를 추가한다.
    if(idxError(idx)){
      cout<<"Pop_list: idx error"<<"\n";
      return this;
    }
    LinkedList* idxM1=GetList(idx-1);
    LinkedList* idxP1=GetList(idx);
    idxM1->next=new LinkedList(key,idxP1);
    return this;
  }
  int Pop_list(int idx){  //idx번째 list를 pop한다
    if(idxError(idx)){
      cout<<"Pop_list: idx error"<<"\n";
      return -1;
    }
    LinkedList* toBePop=GetList(idx);
    LinkedList* toBePopM1=GetList(idx-1);
    toBePopM1->next=toBePop->next;
    int returnValue=toBePop->key;
    delete toBePop;
    return returnValue;

  }
  int Get_Key(int idx){
    if(idxError(idx)){
      cout<<"Get_Key: idx error"<<"\n";
      return -1;
    }
    return GetList(idx)->key;
  }
  int GetLength() const{
    int len=0;
    const LinkedList* tmpNext=this; //constant pointer, 가리키는 위치의 값을 바꾸지 않는다.
    while(tmpNext->next!=nullptr){
      tmpNext=tmpNext->next;
      len++;
    }
    return len;
  }
  ~LinkedList(){
    cout<<"called Destructor"<<"\n";
  }
};
class LinkedList2{ //Linked List2, list0-list1-list2-list3... controller를 별개의 class로 구현 
  int key;
  LinkedList2* next;
public:
  LinkedList2(int key,LinkedList2* next=nullptr):key(key),next(next){} 
  LinkedList2* AddLink(LinkedList2* list){
    next=list;
    return this;
  }
  LinkedList2* DeleteLink(){
    next=nullptr;
    return this;
  }
  int Get_Key() const{
    return key;
  }
  LinkedList2* Get_Next() const{
    return next;
  }
};
class D_LinkedList{ //Linked List2, list0-list1-list2-list3... controller를 별개의 class로 구현 
  int key;
  D_LinkedList* next;
  D_LinkedList* previous;
public:
  D_LinkedList(int key,D_LinkedList* next=nullptr,D_LinkedList* previous=nullptr):key(key),next(next),previous(previous){} 
  D_LinkedList* AddLink(D_LinkedList* list){
    next=list;
    list->previous=this;
    return this;
  }
  D_LinkedList* DeleteLink(){
    if(next!=nullptr){
      next->previous=nullptr;
    }
    next=nullptr;
    return this;
  }
  int Get_Key() const{
    return key;
  }
  D_LinkedList* Get_Next() const{
    return next;
  }
  D_LinkedList* Get_Previous() const{
    return previous;
  }
};
class QueueLinkedList{
  int num;              //Queue의 크기
  LinkedList2* first;    //Queue의 가장 앞부분
  LinkedList2* last;   //Queue의 마지막 부분
  const int NULLVALUE=-1; //배열이 비어있을 경우의 pop
public:
  QueueLinkedList():num(0),first(nullptr),last(nullptr){}   //Queue의 컨트롤러, 시작과 동시에 원소를 넣지는 못하게 하였다.
  LinkedList2* Back() const{
    return last;
  }
  LinkedList2* Front() const{
    return first;
  }
  QueueLinkedList& Push(int key){
    LinkedList2* temp=new LinkedList2(key);
    if(num==0){
      first=temp;
      last=temp;
    }else{
      last->AddLink(temp);
      last=temp;
    }
    num++;
    return *this;
  }
  int Pop(){
    LinkedList2* temp=first;  //delete 하기 위해
    if(first==nullptr){
      return NULLVALUE;
    }
    num--;
    if(num==0){
      last=nullptr;
    }
    int popKey=temp->Get_Key();
    first=temp->Get_Next();
    delete temp;                
    return popKey;
  }
  int Size() const{
    return num;
  }
  bool Empty() const{
    if(num==0){
      return true;
    }else{
      return false;
    }
  }
};
class DequeLinkedList{
  int num;              //Queue의 크기
  D_LinkedList* first;    //Queue의 가장 앞부분
  D_LinkedList* last;   //Queue의 마지막 부분
  const int NULLVALUE=-1; //배열이 비어있을 경우의 pop
public:
  DequeLinkedList():num(0),first(nullptr),last(nullptr){}   //Queue의 컨트롤러, 시작과 동시에 원소를 넣지는 못하게 하였다.
  D_LinkedList* Back() const{
    return last;
  }
  D_LinkedList* Front() const{
    return first;
  }
  DequeLinkedList& Push_front(int key){
    D_LinkedList* temp=new D_LinkedList(key);
    if(num==0){
      first=temp;
      last=temp;
    }else{
      temp->AddLink(first);
      first=temp;
    }
    num++;
    return *this;
  }
  DequeLinkedList& Push_back(int key){
    D_LinkedList* temp=new D_LinkedList(key);
    if(num==0){
      first=temp;
      last=temp;
    }else{
      last->AddLink(temp);
      last=temp;
    }
    num++;
    return *this;
  }
  int Pop_front(){
    D_LinkedList* temp=first;  //delete 하기 위해
    if(first==nullptr){
      return NULLVALUE;
    }
    num--;
    if(num==0){
      last=nullptr;
    }
    int popKey=temp->Get_Key();
    first=temp->Get_Next();
    temp->DeleteLink();
    delete temp;                
    return popKey;
  }
  int Pop_back(){
    D_LinkedList* temp=last;  //delete 하기 위해
    if(first==nullptr){
      return NULLVALUE;
    }
    num--;
    if(num==0){
      first=nullptr;
    }
    int popKey=temp->Get_Key();
    last=temp->Get_Previous();
    if(last!=nullptr){
      last->DeleteLink();
    }
    delete temp;                
    return popKey;
  }
  int Size() const{
    return num;
  }
  bool Empty() const{
    if(num==0){
      return true;
    }else{
      return false;
    }
  }
};
class DequeLL2{
  int num;              //Deque의 크기
  D_LinkedList* first;    //Deque의 가장 앞부분
  D_LinkedList* last;   //Deque의 마지막 부분
  const int NULLVALUE=-1; //배열이 비어있을 경우의 pop
  bool signal; // true면 정방향(fisrt-lats), false면 역방향(last-first)
  bool chk;    // true면 signal 작동, false면 작동 안함. 무한루프 방지 
public:
  DequeLL2():num(0),first(nullptr),last(nullptr),signal(true),chk(true){}   //Queue의 컨트롤러, 시작과 동시에 원소를 넣지는 못하게 하였다.
  D_LinkedList* Back() const{
    if(signal){
      return last;
    }else{
      return first;
    }
  }
  D_LinkedList* Front() const{
    if(signal){
      return first;
    }else{
      return last;
    }
  }
  DequeLL2& Push_front(int key){
    //역방향 체크
    if(!signal&&chk){
      chk=false;
      return Push_back(key);
    }
    chk=true;

    D_LinkedList* temp=new D_LinkedList(key);
    if(num==0){
      first=temp;
      last=temp;
    }else{
      temp->AddLink(first);
      first=temp;
    }
    num++;
    return *this;
  }
  DequeLL2& Push_back(int key){
    //역방향 체크
    if(!signal&&chk){
      chk=false;
      return Push_front(key);
    }
    chk=true;

    D_LinkedList* temp=new D_LinkedList(key);
    if(num==0){
      first=temp;
      last=temp;
    }else{
      last->AddLink(temp);
      last=temp;
    }
    num++;
    return *this;
  }
  int Pop_front(){
    if(!signal&&chk){
      chk=false;
      return Pop_back();
    }
    chk=true;

    D_LinkedList* temp=first;  //delete 하기 위해
    if(first==nullptr){
      return NULLVALUE;
    }
    num--;
    if(num==0){
      last=nullptr;
    }
    int popKey=temp->Get_Key();
    first=temp->Get_Next();
    temp->DeleteLink();
    delete temp;                
    return popKey;
  }
  int Pop_back(){
    //역방향 체크
    if(!signal&&chk){
      chk=false;
      return Pop_front();
    }
    chk=true;

    D_LinkedList* temp=last;  //delete 하기 위해
    if(first==nullptr){
      return NULLVALUE;
    }
    num--;
    if(num==0){
      first=nullptr;
    }
    int popKey=temp->Get_Key();
    last=temp->Get_Previous();
    if(last!=nullptr){
      last->DeleteLink();
    }
    delete temp;                
    return popKey;
  }
  int Size() const{
    return num;
  }
  bool Empty() const{
    if(num==0){
      return true;
    }else{
      return false;
    }
  }
  DequeLL2& changeSignal(){
    if(signal){
      signal=false;
    }else{
      signal=true;
    }
    return *this;
  }
  void clear(){
    signal=true;
    int len=num;
    for(int i=0;i<len;i++){
      Pop_back();
    }
  }
  ~DequeLL2(){
    clear();
  }
};
class RoundQueue_LL{
  int num;  //원소의 개수
  D_LinkedList* start;  //round queue의 시작지점
  D_LinkedList* last;   //round queue의 마지막 지점, 시작과 마지막을 연결해야 하기 때문에 필요하다
  const int NULLVALUE=-1; //배열이 비어있을 경우의 pop
public:
  RoundQueue_LL():num(0),start(nullptr),last(nullptr){}
  RoundQueue_LL& Push(int key){
    D_LinkedList* temp=new D_LinkedList(key);
    num++;
    if(num==1){
      start=temp;
      last=temp;
      return *this;
    }
    last->AddLink(temp);
    temp->AddLink(start);
    last=temp;
    return *this;
  }
  int Pop(){    //start를 pop
    D_LinkedList* temp=start;
    if(num==0){
      return NULLVALUE;
    }else if(num==1){
      start=nullptr;
      last=nullptr;
    }else{
      start=start->Get_Next();
      last->AddLink(start);
    }
    int popKey=temp->Get_Key();
    num--;
    delete temp;
    return popKey;
  }
  int Find_Key_idx(int key){
    D_LinkedList* temp=start;
    int count;
    for(count=0;count<num;count++){
      if(key==temp->Get_Key()){
        break;
      }else{
        temp=temp->Get_Next();
      }
    }
    if(count==num){
      return -1;
    }else{
      return count;
    }
  }
  RoundQueue_LL& TurnR(int idx){
    D_LinkedList* temp=start;
    while(idx--){
      temp=temp->Get_Next();
    }
    start=temp;
    last=temp->Get_Previous();
    return *this;
  }
  RoundQueue_LL& TurnL(int idx){
    D_LinkedList* temp=start;
    while(idx--){
      temp=temp->Get_Previous();
    }
    start=temp;
    last=temp->Get_Previous();
    return *this;
  }
  int Size(){
    return num;
  }

};
//정답오류, 원인?
void BK6549(vector<vector<long long>>& v, int start, int end){  //[start,end)
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    BK6549(v,start,middle);
    BK6549(v,middle,end);
  }
  //conquer : Merge
  long long left_H=v[0][middle-1];
  long long left_M=v[2][middle-1];
  long long right_H=v[0][middle];
  long long right_M=v[2][middle];
  long long currentMax=max(v[1][start],v[1][middle]);
  long long newMax;
  int cnt;
  bool flagL=false;
  bool flagR=false;
  if(left_H>right_H){ //오른쪽에서 왼족으로 밀고감
    if(v[3][middle]==3){
      flagR=true;
    }
    cnt=middle-1;
    newMax=right_M;
    while(v[0][cnt]>=right_H){
      newMax+=right_H;
      if(cnt==start){
        flagL=true;
        break;
      }
      cnt--;
    }
  }else{
    if(v[3][start]==3){
      flagL=true;
    }
    cnt=middle;
    newMax=left_M;
    while(v[0][cnt]>=left_H){
      newMax+=left_H;
      if(cnt==end-1){
        flagR=true;
        break;
      }
      cnt++;
    }
  }
  if(flagR&&flagL){
    v[3][start]=3;
    v[2][end-1]=max(v[1][end-1],newMax);
    v[2][start]=max(v[1][start],newMax);
  }else if(flagR){
    v[3][start]=2;
    v[2][end-1]=max(v[1][end-1],newMax);
  }else if(flagL){
    v[3][start]=1;
    v[2][start]=max(v[1][start],newMax);
  }else{
    v[3][start]=0;
  }
  
  v[1][start]=max(currentMax,newMax);
}
//정답은 맞다, 원본 데이터를 건드리면서 길이도 매번 측정했기 때문에 시간이 오래 걸린다.
long long popFunc(vector<int>& v){ //key보다 큰 값을 key로 다듬으며, tmpMax 반환 
  int key;
  long long realMax(0),count(1);
  vector<int>::iterator iter=v.end()-2;
  if(*iter>v.back()){
    key=v.back();
  }else{
    key=-1;
    iter++;
  }
  while(*iter>key&&iter>=v.begin()){
    realMax=max(realMax,(*iter)*count);
    *iter=key;
    iter--;
    count++;
  }
  return realMax;
}
void BK6549_Stack(int times){
  vector<int> v;
  int input,prev(-1);
  long long realMax(0);
  while(times--){
    cin>>input;
    v.push_back(input);
    if(input<prev){
      realMax=max(realMax,popFunc(v));
    }
    prev=input;
  }
  realMax=max(realMax,popFunc(v));
  cout<<realMax<<"\n";
}
//정답. Stack, 원본데이터는 그대로 두고, 추가된 stack에 간략하게 정보를 저장한다.
long long PopFunc2(vector<int>& v,vector<int>& stack, int idx){
  long long realMax(0),tmpKey,tmpKeyM1; // Max, stack의 마지막 key, stack의 마지막 -1 key
  int value(v[idx]);                    // tmpKeyM1과 tmpKey 사이에는 "빈 공간"이 존재할 수 있다. 
  while(!stack.empty()){                // 이 빈 공간은, tmpKey번째 Value가 입력되면서, 해당 value보다 큰 값을 가진 value의 key를 pop 해서 생긴 공간이다.
    tmpKey=stack.back();                // 간단히 말해서, 이 "빈 공간" 은 v[tmpKey]보다 큰 value들이 있었던 공간이다. 
    vector<int>::iterator iter=stack.end()-2;   // 따라서, Max를 계산한 때는 이 빈 공간의 크기도 포함해서 해야 정확한 계산이 가능하다.
    if(iter<stack.begin()){
      tmpKeyM1=-1;
    }else{
      tmpKeyM1=*iter;
    }
    if(v[tmpKey]<=value){
      break;
    }
    realMax=max(realMax,v[tmpKey]*(idx-tmpKeyM1-1));
    stack.pop_back();
  }
  return realMax;
}
void BK6549_Stack2(long long times){
  vector<int> v,stack;
  int input;
  long long realMax(0);
  int prev(-1);

  for(int i=0;i<times;i++){
  //입력
    cin>>input;
    v.push_back(input);
  //계산
    if(input<prev){
      realMax=max(realMax,PopFunc2(v,stack,i));
    }
    stack.push_back(i);
    prev=input;
  }

  long long tmpKey,tmpKeyM1;
  while(!stack.empty()){
    tmpKey=stack.back();
    vector<int>::iterator iter=stack.end()-2;
    if(iter<stack.begin()){
      tmpKeyM1=-1;
    }else{
      tmpKeyM1=*iter;
    }
    realMax=max(realMax,v[tmpKey]*(times-tmpKeyM1-1));
    stack.pop_back();
  }
  
  cout<<realMax<<"\n";
}
//정답. SegmentTree, 각 node는 범위 내의 min 값을 저장 
int BK6549_ST_init(vector<int>& a, vector<int>& tree, int node, int start, int end){ //[start,end] 범위 ST,node는 min값의 key 
  if(start==end){
    return tree[node] = start;
  }else{
    int keyL=BK6549_ST_init(a,tree,node*2,start,(start+end)/2);
    int keyR=BK6549_ST_init(a,tree,node*2+1,(start+end)/2+1,end);
    if(a[keyL]<=a[keyR]){
      return tree[node] = keyL;
    }else{
      return tree[node] = keyR;
    }
  }
}
vector<int> BK6549_SegmentTree(vector<int>& a){ //arr a를 segment Tree로 
  long long len=a.size();
  long long N(1);
  while(N<len){
    N*=2;
  }
  vector<int> tree(N*2,-1);  //원래는 N*2-1 이다. 그러나 node는 0이 아닌 1부터 시작하기 때문에 크기를 1 키웠다. 0이상의 정수만을 사용하는 segment tree
  BK6549_ST_init(a,tree,1,0,len-1);
  return tree;
}
int BK6549_ST_min(vector<int> &a, vector<int> &tree, int node, int start, int end, int left, int right){  //[left,right]의 min 의 key
  if(right<start||end<left){
    return -1;
  }else if(left<=start&&end<=right){
    return tree[node];
  }else{
    int keyL=BK6549_ST_min(a,tree,node*2,start,(start+end)/2,left,right);
    int keyR=BK6549_ST_min(a,tree,node*2+1,(start+end)/2+1,end,left,right);
    if(keyL==-1||keyR==-1){
      if(keyL==-1&&keyR==-1){
        return -1;
      }else if(keyL==-1){
        return keyR;
      }else{
        return keyL;
      }
    }else{
      if(a[keyL]<=a[keyR]){
        return keyL;
      }else{
        return keyR;
      }
    }
  }
}
long long BK6549_ST_MaxSum(vector<int> &a, vector<int> &tree, int start, int end, int left, int right){ //[left,right]의 max value
  if(left==right){
    return a[left];
  }else if(right<left){
    return 0;
  }
  long long key=BK6549_ST_min(a,tree,1,start,end,left,right);
  long long midMax=static_cast<long>(a[key])*(right-left+1);
  long long leftMax=BK6549_ST_MaxSum(a,tree,start,end,left,key-1);
  long long rightMax=BK6549_ST_MaxSum(a,tree,start,end,key+1,right);
  return max(midMax,max(leftMax,rightMax));
}
void printTree(vector<int> &tree){// Tree 인쇄, 디버그용  
  int len=tree.size();
  int cnt=2;
  int flag=2;
  for(int i=1;i<len;i++){
    cout<<tree[i]<<"  ";
    if(cnt==flag){
      cout<<"\n";
      flag*=2;
    }
    cnt++;
  }
}
void BK6549_ST(long long times){
  vector<int> a(times);
  for(int i=0;i<times;i++){
    cin>>a[i];
  }
  vector<int> tree=BK6549_SegmentTree(a);
  cout<<BK6549_ST_MaxSum(a,tree,0,times-1,0,times-1)<<"\n";
}
  //Line Sweep
struct Point{
  int x,y;
  Point(){}
  Point(int x, int y):x(x),y(y){}
  bool operator< (const Point& p) const{
    if(y==p.y){
      return x<p.x;
    }else{
      return y<p.y;
    }
  }
};
bool cmpX(const Point& p1, const Point& p2){
  return p1.x<p2.x;
}
int dist2(const Point& p1, const Point& p2){
  return (p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y);
}
void BK2261_3_H_LineSweeping(){ //scanf를 사용하므로 유의 
//input and sort
  int n;  // #input 
  scanf("%d",&n);
  Point p;  //point
  vector<Point> a;  //point arr
  for(int i=0;i<n;i++){
    scanf("%d %d",&p.x,&p.y);
    a.push_back(p);
  }
  sort(a.begin(),a.end(),cmpX);

//line sweeping
  set<Point> tree = {a[0],a[1]};
  int ans=dist2(a[0],a[1]);
  int start=0;
  for(int i=2;i<n;i++){
    Point now=a[i];
  //x값 비교
    while(start<i){     
      Point p=a[start];
      if(ans<(p.x-now.x)*(p.x-now.x)){
        tree.erase(p);
        start++;
      }else{
        break;
      }
    }
  //y값 비교
    int d=sqrt(ans)+1;
    Point lowerP(-100000,now.y-d);
    Point upperP(100000,now.y+d); 
    set<Point>::iterator LBiter=tree.lower_bound(lowerP);
    set<Point>::iterator UBiter=tree.upper_bound(upperP);
    for(LBiter;LBiter!=UBiter;LBiter++){
      p=*LBiter;
      if(dist2(p,now)<ans){
        ans=dist2(p,now);
      }
    }
  //입력
    tree.insert(now);
  }
  cout<<ans;
}
//이분탐색
void BK1920(){
//input
  set<int> tree;
  int n,m,num;
  cin>>n;
  for(int i=0;i<n;i++){
    cin>>num;
    tree.insert(num);
  }
//calc
  cin>>m;
  set<int>::iterator end(tree.end());
  for(int i=0;i<m;i++){
    cin>>num;
    if(tree.find(num)==end){
      cout<<0<<'\n';
    }else{
      cout<<1<<'\n';
    }
  }
}
void BK10816_1(){
  int t=10000000;
    vector<int> v(2*t+1);
    
    int n,m,num;
    scanf("%d",&n);
    for(int i=0;i<n;i++){
        scanf("%d",&num);
        v[num+t]++;
    }
    scanf("%d",&m);
    for(int i=0;i<m;i++){
        scanf("%d",&num);
        printf("%d ",v[num+t]);
    }
}
void BK10816_2(){
  int n,num,m,d;
  scanf("%d",&n);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
  sort(v.begin(),v.end());
  scanf("%d",&m);
  for(int i=0;i<m;i++){
    scanf("%d",&num);
    d=upper_bound(v.begin(),v.end(),num)-lower_bound(v.begin(),v.end(),num);
    printf("%d ",d);
  }
}
void BK1654(){  //unsigned int가 왜 사용되었는지 chk
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//calc  
  sort(v.begin(),v.end());
  unsigned int left(1),right,mid,sum;     ///중요. 범위가 1~2^31-1 까지, 즉 int 범위이지만, mid+1을 할 때 overflow가 발생할 수 있다. 이를 방지하기 위해 unsigned int를 사용했다.
  right=v[n-1];
  while(true){
    sum=0;
    mid=(left+right)/2;
    for(const auto& ele: v){
        sum+=ele/mid;
    }
    if(sum<m){
        right=mid-1;
    }else{
        left=mid+1;
    }
    if(left>right){
        break;
    }
  }

  printf("%d",left-1);
}
void BK2805(){ 
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//calc  
  sort(v.begin(),v.end());
  long long left(1),right,mid,sum;    //m의 범위가 int_max의 근접해서, sum이 int 범위를 초과할 수 있기 때문에 long long 사용 
  right=v[n-1];
  while(true){
    sum=0;
    mid=(left+right)/2;
    for(const auto& ele: v){
      if(ele>mid){
        sum+=ele-mid;
      } 
    }
    if(sum<m){
        right=mid-1;
    }else{
        left=mid+1;
    }
    if(left>right){
        break;
    }
  }

  printf("%d",left-1);
}
void BK2110(){ 
//input
  int n,m;
  scanf("%d %d",&n,&m);
  vector<int> v(n);
  for(int i=0;i<n;i++){
    scanf("%d",&v[i]);
  }
//prepare  
  sort(v.begin(),v.end());
//calc
  int left,right,mid;  
  left=1;right=v[n-1];
  vector<int>::iterator iterFirst=v.begin();
  vector<int>::iterator iterEnd=v.end();
  vector<int>::iterator iterNow;
  while(true){
    mid=(left+right)/2;
    iterNow=iterFirst;
    for(int i=0;i<m-1;i++){   //first = 1, add m-1
      if(iterNow==iterEnd){
        break;
      }
      iterNow=lower_bound(v.begin(),v.end(),*iterNow+mid);
    }
    if(iterNow==iterEnd){ //End여서는 안된다/
      right=mid-1;
    }else{
      left=mid+1;
    }
    if(left>right){
      break;
    }
  }
  
  printf("%d",left-1);
}
void BK1300_H(){ //기저에 깔린 법칙
/*
  K번째 수는 K보다 작거나 같다.
    배열의 어떤 원소 A(i,j)를 생각하자.
      배열에는 최소 i*j-1개의 A(i,j)보다 작은 수와, 1개의 A(i,j)가 있다.
      또한 행이 i+1이상인, 열이 j+1이상인 위치에서 A(i,j)보다 작은 수가 존재할 수 있다.
        즉 아래와 같은 식이 도출된다
          A(i,j)<=A(i,j)보다 작거나 같은 수의 개수
        다시 말하면
          A(i,j)번째 수 <= A(i,j) , (등호는 i==j==N일 경우에만 성립하는건 아니다. 1번째 1 2번째2, 더 있을수도?)
          K번째 수는 K보다 작거나 같다.
  min(K/i,N)은, i행에서 K보다 작은 수의 개수이다.
    어떤 수 K를 행 i로 나눈다고 생각하자.
      행 i에서, 숫자의 최대값은 i*N 이다.
      행 i에서, i*j보다 작거나 같은 수의 개수는 j개 이다.
        즉 min(K/i,N)은 ,i행에서 K보다 작은 수의 개수이다.
  K는 행렬에서 sum+1번째 수보다 크거나 같고, sum+2번째 수보다 작다
    sum=0,for(i=1~N){sum+=min(K/i),N}은 행렬에서 K보다 작은 수의 개수이다.  
    K는 행렬의 있는 숫자가 아니라 임의의 숫자다. 즉 sum+1 번재 숫자보다 클 수 있다.
      그러나 sum+2번째 숫자보다 크거나 같다면 K의 순서는 sum+2가 되므로,K는 sum+2보다 작다.
  K-a에 대하여, 이분탐색을 통하여 a=0일때 sum+1을 만족하는 K를 찾는다.
    K-3이 여전히 sum+1번째 숫자보다 크거나 같다면, K-3은 K보다 sum+1에 더 가까워진 것이다.
    K는 조건을 만족하는데 K-1을 만족하지 못한다면, 그때의 K가 sum+1번째 수라고 할 수 있다. 
  sum+1=K가 되도록 해서 구하자
*/
//input
  int N,K;
  scanf("%d %d",&N,&K);
//prepare  
//calc
  int left(1),right(K),mid,sum;  
  while(left<=right){
    mid=(left+right)/2;
    sum=0;
    for(int i=1;i<=N;i++){
      sum+=min(mid/i,N);
    }
    if(sum<K){ 
      left=mid+1;
    }else{
      right=mid-1;
    }
  }
  
  printf("%d",right+1);
}
void BK12015_H(){ //기저에 깔린 법칙
/*
Longest Increasing Subsequence: LIS
무엇을 key로 정할 것인가. key :left, right로 비교할 것
  LIS의 길이를 key로 한다 가정하자
    이분 탐색에는 lgn*operTime이 소요된다.
    operTime은 nlgn이하여야 한다.
      nlgn시간으로 배열에서 key길이의 IS가 있는지 탐색할 수 있는가?
      key길이의 IS가 있는지 알고싶다면 어떻게 해야 하는가
        key가 LIS의 길이보다 작다면, 모든 경우를 비교하지 않아도 된다.
        key가 LIS의 길이보다 크거나 같다면, 배열의 LIS를 구해야만 key보다 크거나 같은 IS의 존재유무를 판별할 수 있다.
          그러나 배열에서 LIS를 구한다면 그 자체로 답이 된다.
          즉, key를 LIS의 길이로 하는것은 유용하지 않다.
            만약, 배열에서 key길이의 IS를 구하는 것이 n Time에 가능하다면 유용할지도(LIS인지는 판별 불가하지만 key길이의 IS를 구할 수 있는 Algo가 있을까?)
이분탐색 자체가 아니라 이분탐색을 이용한다면?
  Lower bound 와 같이 이분탐색을 이용한 함수를 이용해서 푸는 것일수도 있다.
Lower bound와 vector를 이용한 방법 
  v가 비어있으면 tmp push
  v.back()<tmp 라면 push
  v.back()>=tmp 라면, lower_bound(v.begin(),v.end(),tmp)위치에 tmp push
    LIS를 구하는 것이 아니라 LIS의 길이는 구하는 것이기 때문에 유효한 방법
    LIS의 길이를 구할때, 가장 큰 문제는 분기점을 어떻게 처리하냐는 것이다. 
      분기점은 tmp의 크기가 LIS의 중간정도의 위치에 들어가는 경우를 말한다. 10 20 40에서 7이 들어오면 분기점 생성
    v의 lower bound에 덮어 씌우는 방식을 사용
      분기점이 LIS로 가는 것이 아니라면, 덮어 씌운것은 v.back()을 넘어서지 못한다. 즉 LIS의 길이에는 영향을 주지 못한다.
      분기점이 LIS로 가는 것이라면, 어느 시점에서 덮어 씌운것이 v.back()까지 도달하게 된다. 기존의 LIS후보가 새로운 LIS후보로 교체되는 것이다.
        ex)10 20 40 25 20 30 7 8
          10 -> 10 20 -> 10 20 25 -> 10 20(덮어씌워짐) 25->10 20 25 30 -> 10 20 25 30 -> 7 10 25 30 -> 7 8 25 30
            7 8 은 덮어씌워 졌지만 back()까지 가지 못했다.
        ex)10 20 40 25 20 30 7 8 9 10 11
          ... ->7 8 9 30-> 7 8 9 10 -> 7 8 9 10 11
            10에서 v.back()까지 도달한 후 새로운 LIS로 후보로 변경
        ex)10 20 40 25 20 30 7 8 9 10 70
          ...->7 8 9 10->7 8 9 10 70
            이 경우 10 20 25 30 70, 7 8 9 10 70모두 LIS. 어차피 길이를 구하는 것이므로 상관없다.
*/  
//input
  int N;
  scanf("%d",&N);
//prepare  
//calc
  vector<int> v;
  int tmp;
  v.push_back(0); //원소는 자연수 이므로 항상 0보다 크다
  for(int i=0;i<N;i++){
    scanf("%d",&tmp);
    if(v.back()<tmp){
      v.push_back(tmp);
    }else{
      vector<int>::iterator iter=lower_bound(v.begin(),v.end(),tmp);
      *iter=tmp;
    }
  }
  
  cout<<v.size()-1;
}
//우선순위 큐
void BK11279(){
//input
  int N;
  scanf("%d",&N);
//prepare  
//calc
  map<int,int> tree;
  int tmp;
  for(int i=0;i<N;i++){
    scanf("%d",&tmp);
    if(tmp==0){
      if(tree.size()==0){
        printf("%d\n",0);
      }else{
        int first=tree.rbegin()->first;
        int second=tree.rbegin()->second;
        printf("%d\n",first);
        tree.erase(first);
        if(second>1){
          tree.insert(make_pair(first,second-1));
        }
      }
    }else{
      map<int,int>::iterator iter=tree.find(tmp);
      if(iter==tree.end()){
        tree.insert(make_pair(tmp,1));
      }else{
        int first=iter->first;
        int second=iter->second+1;
        tree.erase(first);
        tree.insert(make_pair(first,second));
      }
    }
  }
  
}
void PrintIter(map<int,int>::iterator& iter,map<int,int>& tree){
  cout<<iter->first<<'\n';
  if(iter->second==1){
    tree.erase(iter);
  }else{
    iter->second-=1;
  }
}
void BK11286(){
//input
  int N;
  scanf("%d",&N);
//prepare  
//calc
  map<int,int> tree;
  int tmp;
  for(int i=0;i<N;i++){
    scanf("%d",&tmp);
    if(tmp==0){
      if(tree.size()==0){
        printf("%d\n",0);
      }else{
        map<int,int>::iterator iterP=tree.lower_bound(0); //양수에서 가장 작은 수
        if(iterP==tree.begin()){  //양수만 있는 경우
          PrintIter(iterP,tree);
        }else if(iterP==tree.end()){  //음수만 있는 경우 
          PrintIter(--tree.end(),tree);
        }else{
          map<int,int>::iterator iterM=--tree.lower_bound(0);             //음수에서 가장 0에 가까운 수 
          if(iterP->first+iterM->first<0){
            PrintIter(iterP,tree);
          }else{
            PrintIter(iterM,tree);
          }
        }
      }
    //tmp!=0 
    }else{
      map<int,int>::iterator iter=tree.find(tmp);
      if(iter==tree.end()){
        tree.insert(make_pair(tmp,1));
      }else{
        iter->second+=1;
      }
    }
  }
  
}
void BK1655(){
//input
  int N;
  scanf("%d",&N);
//prepare  
  int mid,tmp,gap;
  multiset<int> leftQ;
  multiset<int> rightQ;
//calc
  //n==1
  scanf("%d",&mid);
  printf("%d\n",mid);
  map<int,int> tree;
  //n>1
  for(int i=0;i<N-1;i++){
    scanf("%d",&tmp);
    if(tmp>mid){
      rightQ.insert(tmp);
      gap=rightQ.size()-leftQ.size();
      while(gap>1){
        leftQ.insert(mid);
        mid=*rightQ.begin();
        rightQ.erase(rightQ.begin());
        gap--;
      }
    }else{
      leftQ.insert(tmp);
      gap=leftQ.size()-rightQ.size();
      while(gap>0){
        rightQ.insert(mid);
        mid=*leftQ.rbegin();
        leftQ.erase(--leftQ.end());
        gap--;
      }
    }
    printf("%d\n",mid);
  }
}


#endif