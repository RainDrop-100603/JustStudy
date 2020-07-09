#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <algorithm>
#include <utility>

// #include "GoodFunction.h"

using namespace std;

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

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  int testCase,num; 
  string oper,element;
  cin>>testCase;
  
  //변수
  DequeLL2 deque;
  int operlen;
  bool error;
  int dequelen;
  // string::size_type sz;
  int toBePop=0;
  
  //계산
  while(testCase--){
    cin>>oper>>num>>element;
    
    //입력부
    deque.clear();
    // sz=0;
    // for(int i=0;i<num;i++){
    //   element=element.substr(sz+1);
    //   deque.Push_back(stoi(element,&sz));
    // }
    if(element.size()>2){
      for(int i=1;i<element.size();i++){
        if(element[i]>='0'&&element[i]<='9'){
          toBePop*=10;
          toBePop+=element[i]-'0';
        }else{
          deque.Push_back(toBePop);
          toBePop=0;
        }
      }
    }
    
    //연산부
    error=false;
    operlen=oper.size();
    for(int i=0;i<operlen;i++){
      if(oper[i]=='R'){
        deque.changeSignal();
      }else{
        if(deque.Pop_front()==-1){
          error=true;
          break;
        }
      }
    }

    //츌력부
    if(error){
      cout<<"error"<<"\n";
      continue;
    }else{
      dequelen=deque.Size();
      cout<<'[';
      if(dequelen>0){
        cout<<deque.Pop_front();
        for(int i=0;i<dequelen-1;i++){
          cout<<','<<deque.Pop_front();
        }
      }
      cout<<']'<<"\n";
    }
  }

  
  //출력
  
 
  return 0;
}