#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>

using namespace std;
//useful
bool IsPrime(int num);  //소수(Prime Number) 판별
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
template <class T>
void MergeSortT(vector<T>& array,const int idx,const int start,const int end){   //T라는 자료형의 idx번째 수에대한 merge sort
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    MergeSortT(array,idx,start,middle);
    MergeSortT(array,idx,middle,end);
  }
  //conquer : Merge
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  T tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  T temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    temp=tempArray[rotateFront-start];
    if(rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
    }else{
      if(temp[idx]<=array[rotateBack][idx]){
        array[mainRotate]=temp;
        rotateFront++;
        mainRotate++;
      }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
      }
    }
  }
}
int Combi_nCr(int n, int r);  
int getGCD(int A, int B); //유클리드 호제법을 이용한 A와 B의 GCD
pair<long long,long long> EuclidAlgo(long long A,long long B);  //A>B, Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
vector<vector<long long>> FibonacciMatrix(long long m); //Fibonacci identity: 도가뉴 항등식, d'Ocagne's identity, f_m matrix의 두배에 해당하는 f_2m matrix 반환, important 참고 

//useful에서 쓰는 함수 
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array(동적할당) 반환
void Merge(int* &array, const int start, const int end);  //Merge를 담당, vector가 배열임을 이용해 변경할 수도 있다.
void MergeSort(int* &array,const int start,const int end);  //MergeSort main 함수 . Merge를 합칠수도 있지만 divide&conquer을 보여주기 위해 남겨둠
void MergeSort(vector<int>& array,const int start,const int end); //vector이용, Merge 통합 버전 

//just Sol
vector<vector<int>> Remainder_nCr(int n, int M); //nCn까지 구할 수 있는 파스칼 삼각형, 각 원소에 mod_M(%M)을 취했다. nCr이 엄청나게 커질경우, mod는 파스칼 삼각형으로 구해야 한다. 나눗셈이 있을경우 mod에 대한 결합법칙은 성립하지 않기때문.
bool ChkDuplicate(int x, int depth, int* num);  //num의 depth-1번째 까지 수에서, x와 겹치는 것이 있는지 확인
void PrintAllCombi(int n, int r, int depth, int* num);//nCr 조합, depth번째 수, 수를 저장하는 num, digit=0: 가장 앞에 수(167:digit 0 -> 1);
void PrintAllCombi2(int n, int r, int depth, int* num, int start);//N과 M(2) 문제 
void PrintAllCombi3(int n, int r, int depth, int* num);//N과 M(3) 문제 
void PrintAllCombi4(int n, int r, int depth, int* num, int start);//N과 M(4) 문제
int N_Queen(int N,vector<bool>& colQueen,vector<bool>& lineRDQueen,vector<bool>& lineLDQueen, int row);  //N_Queen문제, count는 N번째 Queen을 말함 
bool Sdoku(int sdoku[9][9],vector<pair<int,int>>& empty,int filledNum,int emptySize); //filledNum은 채워진 개수, emptySize까지 가면 true, 아니면 false 반환 
void GetMaxMin(vector<int>& arrayV,int* AddSubMulDiv,int& max,int& min,int idx,int sum); //idx번째까지의 결과(sum)와 idx+1번째 수를 계산. idx=arrayV.len()이면 max min 체크
void GetLowGap(int& gap,vector<vector<int>>& table,vector<int>& startTeam,vector<int>& linkTeam,int idx);  //idx번째 선수를 각 팀에 배분. 배분이 끝나면 gap 을 계산하고 기존 gap보다 낮을시 갱신 
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



#endif