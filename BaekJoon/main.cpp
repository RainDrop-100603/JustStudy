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

class Queue2{
  int num;              //Queue의 크기
  LinkedList2* first;    //Queue의 가장 앞부분
  LinkedList2* last;   //Queue의 마지막 부분
  const int NULLVALUE=-1; //배열이 비어있을 경우의 pop
public:
  Queue2():num(0),first(nullptr){}   //Queue의 컨트롤러, 시작과 동시에 원소를 넣지는 못하게 하였다.
  LinkedList2* Back() const{
    return last;
  }
  LinkedList2* Front() const{
    return first;
  }
  Queue2& Push(int key){
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





int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);

  //Math3
  

  //입력
  string oper;
  int temp,num;
  cin>>num;
  
  //변수
  Queue2 q;

  //계산
  while(num--){
    cin>>oper;
    if(oper=="push"){
      cin>>temp;
      q.Push(temp);
    }else if(oper=="pop"){
      cout<<q.Pop()<<"\n";
    }else if(oper=="size"){
      cout<<q.Size()<<"\n";
    }else if(oper=="empty"){
      if(q.Empty()){
        cout<<1<<"\n";
      }else{
        cout<<0<<"\n";
      }
    }else if(oper=="front"){
      if(q.Front()==nullptr){
        cout<<-1<<"\n";
      }else{
        cout<<q.Front()->Get_Key()<<"\n";
      }
    }else if(oper=="back"){
      if(q.Back()==nullptr){
        cout<<-1<<"\n";
      }else{
        cout<<q.Back()->Get_Key()<<"\n";
      }
    }
  }
  
  //출력
  
 
  return 0;
}