#ifndef __GOODFUNCTION_H__
#define __GOODFUNCTION_H__

#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <utility>

#include "tempClass.cpp"

using namespace std;

bool IsPrime(int num);  //소수(Prime Number) 판별
bool* GetPrimeArray(int num); //[0,num] 범위의 소수여부를 저장하는 array(동적할당) 반환
vector<int> GetPrimeVector(int num);  //[0,num] 범위의 소수를 저장하는 vector<int>를 반환
void Merge(int* &array, const int start, const int end);  //Merge를 담당, vector가 배열임을 이용해 변경할 수도 있다.
void MergeSort(int* &array,const int start,const int end);  //MergeSort main 함수 . Merge를 합칠수도 있지만 divide&conquer을 보여주기 위해 남겨둠
void MergeSort(vector<int>& array,const int start,const int end); //vector이용, Merge 통합 버전 
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
#endif