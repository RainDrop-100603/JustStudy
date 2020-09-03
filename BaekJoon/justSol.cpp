#include "justSol.h"

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

//동적 계획법 2
bool cmpPairX(const pair<int,int>& p1,const pair<int,int>& p2){
  return p1.first<p2.first;
}
void BK2293_Memover(){
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<int>> table(K+1,vector<int>(N));  //A(ij)==최댓값이 arr[j]인 i의 경우의 수, 0열에는 1저장
  for(int i=0;i<N;i++){
    table[0][i]=1;
  } 
  int dist,prev;
//calc
  for(int i=1;i<K+1;i++){
    prev=0; //A(ij)=A(i,j-1)+A(i-arr[j],j); ,prev=A(i,j-1);
    for(int j=0;j<N;j++){
      dist=i-arr[j];
      if(dist>=0){
        prev+=table[dist][j];
      }
      table[i][j]=prev;
    }
  }
  printf("%d",table[K][N-1]);
}
void BK2293_Memover2(){  //table에 유효한 값만 저장하자 
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<pair<int,int>>> table(N,vector<pair<int,int>>(1,make_pair(0,1)));  // i행은 arr[i]의 유효한 값: pair<num,count>를 저장
  //for(int i=0;i<N;i++){                                             // i 행의 pair<num,count> : num 에서 최댓값이 i인 경우의 수는 count
  //   table[i].push_back(make_pair(0,1));                             // 기존의 A(i,j)는 lowerbound(table[j].begin(),table[j].end(),i)->second;
  // }                                                                 
  int dist,prev;
//calc
  for(int i=1;i<K+1;i++){
    prev=0; //A(ij)=A(i,j-1)+A(i-arr[j],j); ,prev=A(i,j-1);
    for(int j=0;j<N;j++){
      dist=i-arr[j];
      if(dist>=0){
        prev+=lower_bound(table[j].begin(),table[j].end(),make_pair(dist,0),cmpPairX)->second;
      }
      if(table[j].back().second==prev){
        table[j].back().first++;
      }else{
        table[j].push_back(make_pair(i,prev));
      }
    }
  }
  printf("%d",table[N-1].back().second);
}
void BK2293_3(){
//input
  int N,K;
  scanf("%d %d",&N,&K);
  vector<int> arr(N);
  for(auto& ele: arr){
    scanf("%d",&ele);
  }
//prepare  
  sort(arr.begin(),arr.end());
  vector<vector<int>> table(2,vector<int>(K+1));  //A(ij)==최댓값이 arr[i]인 j의 경우의 수, 0열에는 1저장
  for(int i=0;i<2;i++){
    table[i][0]=1;
  } 
  int from,prev;
  bool first(true); //배열을 절약해 두개만 사용한다. ture면 1행을 이용해 0행에 저장
//calc
  for(int i=0;i<N;i++){
    for(int j=1;j<K+1;j++){ //A(ij)=A(i-1,j)+A(i,j-arr[i]); ,prev=A(i-1,j);
      from=j-arr[i];
      if(first){
        prev=table[1][j];
        if(from>=0){
          prev+=table[0][from];
        }
        table[0][j]=prev;
      }else{
        prev=table[0][j];
        if(from>=0){
          prev+=table[1][from];
        }
        table[1][j]=prev;
      }
    }
    first=!first;
  }
  if(!first){
    printf("%d",table[0][K]);
  }else{
    printf("%d",table[1][K]);
  }
  
}
void BK11066(){
//input
  int N;
  scanf("%d",&N);
  vector<int> arr(N); //input value
  for(int i=0;i<N;i++){
    scanf("%d",&arr[i]);
  }
//prepare
  vector<vector<int>> table(N,vector<int>(N));  //A(ij)==[i,i+j+1) 범위의 value를 만드는데 필요한 cost의 최소값
  int prevMin,newMin,tmpSum;
//calc
  //A(ij)=min(A(ik)+A(i+k+1,j-k-1))+sum(ij),k=0~j-1,sum(ij)=sum(arr[i]~arr[j])
  for(int j=1;j<N;j++){
    for(int i=0;i<N-j;i++){
      prevMin=INT32_MAX;
      tmpSum=0;
      for(int k=i;k<=i+j;k++){
        tmpSum+=arr[k];
      }
      for(int k=0;k<j;k++){
        prevMin=min(prevMin,table[i][k]+table[i+k+1][j-k-1]);
      }
      table[i][j]=prevMin+tmpSum; 
    }
  }
//output
//   printf("\n\n");
//   for(auto& ele:table){
//     for(auto& ele2:ele){
//       printf("%d ",ele2);
//     }
//     printf("\n");
//   }
  printf("%d\n",table[0][N-1]);
}
void BK11049(){
//input
  int N;
  scanf("%d",&N);
  vector<pair<int,int>> arr(N); //input value
  for(int i=0;i<N;i++){
    scanf("%d %d",&arr[i].first,&arr[i].second);
  }
//prepare
  vector<vector<int>> table(N,vector<int>(N));  //A(ij)==[i,i+j+1) 범위의 value를 만드는데 필요한 cost의 최소값
  int prevMin,newMin,mul;
//calc
  //A(ij)=min(A(ik)+A(i+k+1,j-k-1)+mul(ikj))+sum(ij),k=0~j-1,mul(ikj)=a[i].first*a[i+k].second*a[i+j].second;
  for(int j=1;j<N;j++){
    for(int i=0;i<N-j;i++){
      prevMin=INT32_MAX;
      for(int k=0;k<j;k++){
        prevMin=min(prevMin,table[i][k]+table[i+k+1][j-k-1]+arr[i].first*arr[i+k].second*arr[i+j].second);
      }
      table[i][j]=prevMin;
    }
  }
//output
//   printf("\n\n");
//   for(auto& ele:table){
//     for(auto& ele2:ele){
//       printf("%d ",ele2);
//     }
//     printf("\n");
//   }
  printf("%d\n",table[0][N-1]);
}
int DFS(vector<vector<int>>& table, vector<vector<int>>& movTable, int i, int j,int row,int col){
  int now=movTable[i][j];
  if(now>-1){  //0이상이면 이미 탐색을 마친 것
    return now;
  }
  int sum=0;
  int value=table[i][j];
  if(i+1<row){
    if(table[i+1][j]<value){
      sum+=DFS(table,movTable,i+1,j,row,col);
    }
  }
  if(i-1>=0){
    if(table[i-1][j]<value){
      sum+=DFS(table,movTable,i-1,j,row,col);
    }
  }
  if(j+1<col){
    if(table[i][j+1]<value){
      sum+=DFS(table,movTable,i,j+1,row,col);
    }
  }
  if(j-1>=0){
    if(table[i][j-1]<value){
      sum+=DFS(table,movTable,i,j-1,row,col);
    }
  }
  movTable[i][j]=sum;
  return sum;
}
void BK1520_H_DFS(){
//input
  int row,col;
  scanf("%d %d",&row,&col);
  vector<vector<int>> table(row,vector<int>(col)); //input value
  for(int i=0;i<row;i++){
    for(int j=0;j<col;j++){
      scanf("%d",&table[i][j]);
    }
  }
//prepare
  vector<vector<int>> movTable(row,vector<int>(col)); // -1은 미방문, 양수일 경우 방문횟수
  for(auto& ele:movTable){
    for(auto& ele2:ele){
      ele2=-1;
    }
  }
  movTable[row-1][col-1]=1;
//calc
  DFS(table,movTable,0,0,row,col);
//output
  // for(auto& ele:movTable){
  //   for(auto& ele2:ele){
  //     printf("%d ",ele2);
  //   }
  //   printf("\n");
  // }
  printf("%d\n",movTable[0][0]);

}
void BK7579_v2(){
//input
  int N,M;
  scanf("%d %d",&N,&M); //N== # program, M==need size;
  vector<pair<int,int>> arr(N);  //first=rerun cost, second=getMem size
  for(auto& ele:arr){
    scanf("%d",&ele.second);
  }
  for(auto& ele:arr){
    scanf("%d",&ele.first);
  }
//prepare
  sort(arr.begin(),arr.end());
  map<int,int> costMap;  //map[i]= i번째 원소까지 input한 tree
  costMap.insert(make_pair(0,0)); //key=cost, value=memSize
  int ans;
  int cost,memSize;
//calc
  //map 정렬
  for(int i=0;i<N;i++){
    for(auto iter=costMap.rbegin();iter!=costMap.rend();iter++){
      cost=iter->first+arr[i].first;
      memSize=iter->second+arr[i].second;
      auto ret=costMap.insert({cost,memSize});
      if(!ret.second){
        if(ret.first->second<memSize){
          ret.first->second=memSize;
        }
      }
    } 
  }
  // value 검색
  for(auto& ele: costMap){
    if(ele.second>=M){
      ans=ele.first;
      break;
    }
  }
//output
  // for(auto& ele:costMap){
  //   printf("%d %d\n",ele.first,ele.second);
  // }
  printf("%d\n",ans);

}
void BK10942(){
//input
  int N,Q;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d",&N); //N== size of arr
  vector<int> arr(N);  
  for(auto& ele:arr){
    scanf("%d",&ele);
  }
  scanf("%d",&Q); //N== #Question
//prepare
  int from,to,ans;  //(from-1)~(to-1)
  vector<int> pO(N);  //palindrome, p(n) == k: n-k ~ n+K . odd range
  vector<int> pE(N);  //palindrome, p(n) == k: n-k ~ n+k-1 . even range
  list<int> listO;  //odd range을 임시저장하는 list: ex 0 1 2 3 4
  list<int> listE;  //even range를 임시저장하는 list: ex 0 1 2 3 4 5
//calc
  //팬릴드롬 행렬 생성
  if(arr[1]==arr[0]){
    listE.push_back(1);
  }
  for(int i=2;i<N;i++){
    //odd range chk
    auto iter=listO.begin();
    while(iter!=listO.end()){
      int d=*iter;
      int from=i-d*2-2;
      if(from>-1&&arr[from]==arr[i]){
        (*iter)++;
        iter++;
      }else{
        pO[i-d-1]=d;
        iter=listO.erase(iter);
      }
    }
    if(arr[i]==arr[i-2]){
      listO.push_back(1);
    }
    //even range chk
    iter=listE.begin();
    while(iter!=listE.end()){
      int d=*iter;
      int from=i-d*2-1;
      if(from>-1&&arr[from]==arr[i]){
        (*iter)++;
        iter++;
      }else{
        pE[i-d]=d;
        iter=listE.erase(iter);
      }
    }
    if(arr[i]==arr[i-1]){
      listE.push_back(1);
    }
  }
  //list를 비우는 작업 
  for(auto iter=listO.begin();iter!=listO.end();iter++){
    pO[N-*iter-1]=*iter;
  }
  for(auto iter=listE.begin();iter!=listE.end();iter++){
    pE[N-*iter]=*iter;
  }

//output
  // for(auto& ele:pO){
  //   printf("%d ",ele);
  // }printf("\n");
  // for(auto& ele:pE){
  //   printf("%d ",ele);
  // }printf("\n");
  for(int i=0;i<Q;i++){
     scanf("%d %d",&from,&to);
     ans=0;
     from--;to--;
     int d=(to-from)/2;
     if((from+to)%2==0){
       if(pO[(from+to)/2]>=d){
         ans=1;
       }
     }else{
       if(pE[(from+to)/2+1]>=d+1){
         ans=1;
       }
     }
     printf("%d\n",ans);
   }

}
void DFS(vector<vector<int>>& graph, vector<bool>& chk, int from){ 
  chk[from]=true;
  printf("%d ",from);
  for(auto& ele:graph[from]){
    if(!chk[ele]){
        DFS(graph,chk,ele);
    }
  }
}
void BFS(vector<vector<int>>& graph, vector<bool>& chk, int from){
  list<int> deque;
  deque.push_back(from);
  chk[from]=true;
  while(!deque.empty()){
    from=deque.front();
    deque.pop_front();
    printf("%d ",from);
    for(auto& ele:graph[from]){
      if(!chk[ele]){
        chk[ele]=true;
        deque.push_back(ele);
      }
    }
  }
}
void BK1260(){
//input
  int N,M,V,from,to;  //팰린드롬: 앞뒤를 뒤집어도 똑같은 문자열 
  scanf("%d %d %d",&N,&M,&V); //N: #node,M: #edge, V: start node
  vector<vector<int>> graph(N+1);   //graph[i] 의 ele: i node와 연결된 node의 list, 1~N 범위(0은 제외)
  vector<bool> chk(N+1);  //chklist
  for(int i=0;i<M;i++){
    scanf("%d %d",&from,&to);
    graph[from].push_back(to);
    graph[to].push_back(from);
  }
//prepare
  for(auto& ele:graph){
    sort(ele.begin(),ele.end());
  }
  // for(auto& ele:graph){
  //   printf("%d: ",ele.first);
  //   for(auto& ele2:ele.second){
  //     printf("%d ",ele2);
  //   }
  //   printf("\n");
  // }
//calc
  DFS(graph,chk,V);
  printf("\n");
  for(auto iter=chk.begin();iter!=chk.end();iter++){
      *iter=false;
  }
  BFS(graph,chk,V);
//output
}
void BK2606(){
//input
  int N,M,from,to;  
  scanf("%d %d",&N,&M); //N: #node,M: #edge, V: start node
  vector<vector<int>> graph(N+1);   //graph[i] 의 ele: i node와 연결된 node의 list, 1~N 범위(0은 제외)
  vector<bool> chk(N+1);  //chklist
  for(int i=0;i<M;i++){
    scanf("%d %d",&from,&to);
    graph[from].push_back(to);
    graph[to].push_back(from);
  }
//prepare
  for(auto& ele:graph){
    sort(ele.begin(),ele.end());
  }
//calc
  //DFS(graph,chk,V);
  BFS(graph,chk,1);
//output
  int ans(-1);
  for(auto iter=chk.begin();iter!=chk.end();iter++){
      if(*iter){
          ans++;
      }
  }
  printf("%d",ans);
}
int BFS(vector<vector<bool>>& graph, pair<int,int> p){
  int cnt(0);
  int N=graph.size();
  list<pair<int,int>> deque;
  deque.push_back(p);
  graph[p.first][p.second]=false;  //deque에 들어간다 -> 방문 
  while(!deque.empty()){
    p=deque.front();
    deque.pop_front();
    cnt++;
    int i(p.first),j(p.second);
    // idx 체크
    if(i+1<N){
      if(graph[i+1][j]){
        deque.push_back({i+1,j});
        graph[i+1][j]=false;
      }
    }
    if(i>0){
      if(graph[i-1][j]){
        deque.push_back({i-1,j});
        graph[i-1][j]=false;
      }
    }
    if(j+1<N){
      if(graph[i][j+1]){
        deque.push_back({i,j+1});
        graph[i][j+1]=false;
      }
    }
    if(j>0){
      if(graph[i][j-1]){
        deque.push_back({i,j-1});
        graph[i][j-1]=false;
      }
    }
    
  }
  return cnt;
}
void BK2667(){
//input
  int N;
  scanf("%d ",&N); //N: #node,M: #edge, V: start node
  vector<vector<bool>> graph(N,vector<bool>(N));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  //string s 이용
  char buff[101];
    for(int i=0;i<N;i++){
      scanf("%s",buff);
      for(int j=0;j<N;j++){
          graph[i][j]=buff[j]-'0';
      }
  }
//prepare
  // for(int i=0;i<N;i++){
  //   for(int j=0;j<N;j++){
  //     printf("%d",graph[i][j]);
  //   }
  //   printf("\n");
  // }
    vector<int> set;    //단지의 집합을 넣어둔다.
//calc
  //DFS(graph,chk,V);
  for(int i=0;i<N;i++){
      for(int j=0;j<N;j++){
          if(graph[i][j]){
              set.push_back(BFS(graph,make_pair(i,j)));
          }
      }
  }
//output
  printf("%d\n",set.size());
  sort(set.begin(),set.end());
  for(auto& ele:set){
      printf("%d\n",ele);
  }
}
void BK1012(){
//input
  int N,M,K,x,y;
  scanf("%d %d %d",&M,&N,&K); //M: 가로, N: 세로, K: 배추의 개수
  vector<vector<bool>> graph(M,vector<bool>(N));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int i=0;i<K;i++){
    scanf("%d %d",&x,&y);
    graph[x][y]=true;
  }
//prepare
  vector<int> set;    //단지의 집합을 넣어둔다.
//calc
  //DFS(graph,chk,V);
  for(int i=0;i<M;i++){
      for(int j=0;j<N;j++){
          if(graph[i][j]){
              set.push_back(BFS(graph,make_pair(i,j)));
          }
      }
  }
//output
  printf("%d\n",set.size());
}
int BFS2(vector<vector<bool>>& graph, pair<int,int> p){
  int cnt(0);
  int N=graph.size();
  int M=graph[0].size();
  list<pair<int,int>> deque;
  deque.push_back(p);
  graph[p.first][p.second]=false;  //deque에 들어간다 -> 방문 
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      p=deque.front();
      deque.pop_front();
      int i(p.first),j(p.second);
      if(i==N-1&&j==M-1){
        deque.clear();
        break;
      }
      // idx 체크
      if(i+1<N){
        if(graph[i+1][j]){
          deque.push_back({i+1,j});
          graph[i+1][j]=false;
        }
      }
      if(i>0){
        if(graph[i-1][j]){
          deque.push_back({i-1,j});
          graph[i-1][j]=false;
        }
      }
      if(j+1<M){
        if(graph[i][j+1]){
          deque.push_back({i,j+1});
          graph[i][j+1]=false;
        }
      }
      if(j>0){
        if(graph[i][j-1]){
          deque.push_back({i,j-1});
          graph[i][j-1]=false;
        }
      }
    }
    cnt++;
  }
  return cnt;
}
void BK2178(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로, 
  cin.ignore();
  vector<vector<bool>> graph(N,vector<bool>(M));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int i=0;i<N;i++){
    string s;
    getline(cin,s);
    for(int j=0;j<M;j++){
      graph[i][j]=s[j]-'0';
    }
  }
//prepare
//calc
  int result=BFS2(graph,{0,0});
//output
  cout<<result;
}
int BFS3(vector<vector<int>>& graph){
  int cnt(-1);
  int N=graph.size();
  int M=graph[0].size();
  list<pair<int,int>> deque;\
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(graph[i][j]==1){
        deque.push_back({i,j});
      }
    }
  }
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      int i(p.first),j(p.second);
      // idx 체크
      if(i+1<N){
        if(!graph[i+1][j]){
          deque.push_back({i+1,j});
          graph[i+1][j]=1;
        }
      }
      if(i>0){
        if(!graph[i-1][j]){
          deque.push_back({i-1,j});
          graph[i-1][j]=1;
        }
      }
      if(j+1<M){
        if(!graph[i][j+1]){
          deque.push_back({i,j+1});
          graph[i][j+1]=1;
        }
      }
      if(j>0){
        if(!graph[i][j-1]){
          deque.push_back({i,j-1});
          graph[i][j-1]=1;
        }
      }
    }
    cnt++;
  }
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      if(!graph[i][j]){
        cnt=-1;
        i=N;
        break;
      }
    }
  }
  return cnt;
}
void BK7576(){
//input
  int N,M;
  cin>>M>>N; //M: 가로, N: 세로, 
  cin.ignore();
  vector<vector<int>> graph(N,vector<int>(M));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int i=0;i<N;i++){
    for(int j=0;j<M;j++){
      cin>>graph[i][j];
    }
  }
//prepare
//calc
  int result=BFS3(graph);
//output
  cout<<result;
}
int BFS4(vector<vector<vector<int>>>& graph){
  int cnt(-1);
  int N=graph.size();
  int M=graph[0].size();
  int H=graph[0][0].size();
  list<pair<int,pair<int,int>>> deque;
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(graph[i][j][k]==1){
          deque.push_back({i,{j,k}});
        }
      }
    }
  }
  
  while(!deque.empty()){
    int sz=deque.size();
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      int x(p.first),y(p.second.first),z(p.second.second);
      // idx 체크
      if(x+1<N){
        if(!graph[x+1][y][z]){
          deque.push_back({x+1,{y,z}});
          graph[x+1][y][z]=1;
        }
      }
      if(x>0){
        if(!graph[x-1][y][z]){
          deque.push_back({x-1,{y,z}});
          graph[x-1][y][z]=1;
        }
      }
      if(y+1<M){
        if(!graph[x][y+1][z]){
          deque.push_back({x,{y+1,z}});
          graph[x][y+1][z]=1;
        }
      }
      if(y>0){
        if(!graph[x][y-1][z]){
          deque.push_back({x,{y-1,z}});
          graph[x][y-1][z]=1;
        }
      }
      if(z>0){
        if(!graph[x][y][z-1]){
          deque.push_back({x,{y,z-1}});
          graph[x][y][z-1]=1;
        }
      }
      if(z+1<H){
        if(!graph[x][y][z+1]){
          deque.push_back({x,{y,z+1}});
          graph[x][y][z+1]=1;
        }
      }
    }
    cnt++;
  }
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        if(!graph[i][j][k]){
          cnt=-1;
          i=N;
          k=H;
          break;
        }
      }
    }
  }
  return cnt;
}
void BK7569(){
//input
  int N,M,H;
  cin>>M>>N>>H; //M: 가로, N: 세로, H: 높이
  cin.ignore();
  vector<vector<vector<int>>> graph(N,vector<vector<int>>(M,vector<int>(H)));  //graph와 chklist 겸임. true는 갈 수 있음, false는 이미 방문 혹은 갈 수 없음 
  for(int k=0;k<H;k++){
    for(int i=0;i<N;i++){
      for(int j=0;j<M;j++){
        cin>>graph[i][j][k];
      }
    }
  }
//prepare
//calc
  int result=BFS4(graph);
//output
  cout<<result;
}
int BFS5(int from, int to){
  bool chk[200001]; //시작 범위가 0~100000지만, 그 범위 밖으로 나가면 안된다고 하지는 않았다.
  int cnt(0);
  list<int> deque;
  deque.push_back(from);
  chk[from]=true;
  while(!deque.empty()){
    int sz=deque.size();
    if(chk[to]){
      break;
    }
    for(int k=0;k<sz;k++){
      auto p=deque.front();
      deque.pop_front();
      if(p<100000){
        if(!chk[p*2]){
          deque.push_back(p*2);
          chk[p*2]=true;
        }
      }
      if(p<100000){
        if(!chk[p+1]){
          deque.push_back(p+1);
          chk[p+1]=true;
        }
      }
      if(p>0){
        if(!chk[p-1]){
          deque.push_back(p-1);
          chk[p-1]=true;
        }
      }
    }
    cnt++;
  }
  return cnt;
}
void BK1697(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로
//prepare
//calc
  int result=BFS5(N,M);
//output
  cout<<result;
}
void visit(vector<vector<int>>& graph, deque<pair<bool,pair<int,int>>>& dq,int X,int Y,bool brk){
  switch(graph[X][Y]){
    case 1:
      if(brk){
        dq.push_back({false,{X,Y}});
        graph[X][Y]=-3;
      }
      break;
    case 0:
      dq.push_back({brk,{X,Y}});
      if(brk){
        graph[X][Y]=-2;
      }else{
        graph[X][Y]=-1;
      }
      break;
    case -1:
      if(brk){
        dq.push_back({true,{X,Y}});
        graph[X][Y]=-2;
      }
      break;
    default:
      break;
  }
}
int BFS6(vector<vector<int>>& graph){
  int N=graph.size(); 
  int M=graph[0].size();
  int cnt(1);
  deque<pair<bool,pair<int,int>>> dq; //벽뚫 가능 여부, x, y
  dq.push_back({true,{0,0}});
  graph[0][0]=-2;     // -3 벽에 방문, 1 벽, 0 미방문, -1 벽뚫고방문, -2 방문불가==그냥 방문 (그냥 방문이 벽뚫고 방문이랑 같거나 빠르다면 그냥이 우선된다.)
  while(!dq.empty()){
    int sz=dq.size();
    if(graph[N-1][M-1]<0){
      break;
    }
    for(int k=0;k<sz;k++){
      auto p=dq.front();
      dq.pop_front();
      int x(p.second.first),y(p.second.second);
      bool brk(p.first);
      if(x>0){visit(graph,dq,x-1,y,brk);}
      if(x<N-1){visit(graph,dq,x+1,y,brk);}
      if(y>0){visit(graph,dq,x,y-1,brk);}
      if(y<M-1){visit(graph,dq,x,y+1,brk);}
    }
    cnt++;
  }
  if(graph[N-1][M-1]>=0){
    cnt=-1;
  }
  return cnt;
}
void BK2206(){
//input
  int N,M;
  cin>>N>>M; //M: 가로, N: 세로
  vector<vector<int>> graph(N,vector<int>(M));
  cin.ignore();
  for(int i=0;i<N;i++){
    string s;
    getline(cin,s);
    for(int j=0;j<M;j++){
      graph[i][j]=s[j]-'0';
    }
  }
//prepare
//calc
  int result=BFS6(graph);
//output
  cout<<result;
}
void BK1753(){
//input
  int V,E,K,u,v,w;
  cin>>V>>E>>K; // V: #vortex, E: #edge, K: start V
  vector<map<int,int>> graph(V+1,map<int,int>()); // V[i]'s element =pair : i에서 p.first 로가는 가중치 p.second의 edge, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    auto ans=graph[u].insert({v,w});
    if(!ans.second){
      if(ans.first->second>w){
        ans.first->second=w;
      }
    }
  }
//prepare
  vector<int> chk(V+1,-1);  // priority Queue에는 같은 vertex를 중복해서 넣을 수 있다. 이때 chk를 확인하여 이미 경로탐색을 했다면, 다시 경로탐색을 하지 않고 넘어간다.
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq; //first=cost, second=key
//calc
  pq.push({0,K});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second);
    if(chk[key]!=-1){
      continue; //이미 했다면 넘어간다.
    }
    chk[key]=cost;
    for(auto& ele: graph[key]){
      pq.push({cost+ele.second,ele.first});    
    }
  }
//output
  for(int i=1;i<=V;i++){
    if(chk[i]==-1){
      cout<<"INF\n";
    }else{
      cout<<chk[i]<<"\n";
    }
  }
}
void BK1504(){  //Dijkstra, 1과 N이 거쳐야 하는 경로 두 경로중 하나일 때를 고려 
  /*
    시작 정점(1)에서 마지막 정점(V)으로 이동, 양방향 경로, 목표지점 두곳 반드시 통과
    각 vertex의 원소는 4개, 목표지점을 00개, 01개, 10개, 11개를 통과한 것을 원소로 하자 : level 이라 명명
    Dijkstra Algo 이용시, 각 3개에 대해 모두 적용 
  */
//input
  int V,E,u,v,w,obj1,obj2;
  cin>>V>>E; // V: #vortex, E: #edge
  vector<map<int,int>> graph(V+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 양방향 경로, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<E;i++){
    cin>>u>>v>>w;
    auto ans=graph[u].insert({v,w});
    auto ans2=graph[v].insert({u,w}); //양방향
    if(!ans.second){
      if(ans.first->second>w){
        ans.first->second=w;
        ans2.first->second=w;
      }
    }
  }
  cin>>obj1>>obj2;  //목표지점
//prepare
  vector<vector<int>> chk(V+1,vector<int>(4,-1));  // priority Queue에는 같은 vertex를 중복해서 넣을 수 있다. 이때 chk를 확인하여 이미 경로탐색을 했다면, 다시 경로탐색을 하지 않고 넘어간다.
  priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq; //first=cost, second.first=key, second.second= key's level(00 01 10 11)
//calc
  pq.push({0,{1,0}});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second.first),level(tmp.second.second);
    if(chk[key][level]!=-1){
      continue; //이미 했다면 넘어간다.
    }
    if(key==obj1&&(level==0||level==2)){
      level+=1;
    }else if(key==obj2&&(level==0||level==1)){
      level+=2;
    }
    chk[key][level]=cost;
    if(chk[V][3]!=-1){break;}
    for(auto& ele: graph[key]){
      pq.push({cost+ele.second,{ele.first,level}});
    }
  }
  
//output
  cout<<chk[V][3];
}
void BK9370(){  //Dijkstra, 여러개의 우선순위가 필요할 때, pq를 변형하여 해결
  /*
    1. s에서 출발해 모든 vertex까지의 최단경로를 찾는다.
    2. 이때 g->h 혹은 h->g로 갈 때, pass를 true로
    #priority Queue에서 cost는 같은데 경로가 다른 경우가 있다. 이때 g~h을 pass한 경로를 우선한다.
  */
//input
  int n,m,t,s,g,h,a,b,d,x;
  cin>>n>>m>>t>>s>>g>>h; // #교차로(vertex), #도로(edge), #목적지 후보, 출발지, g~h 사이의 도로 경유
  vector<map<int,int>> graph(n+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 양방향 경로, 중복 간선은 최저치 빼고 삭제
  set<int> dest; //목적지 후보를 저장한 vector
  for(int i=0;i<m;i++){
    cin>>a>>b>>d;
    graph[a].insert({b,d});
    graph[b].insert({a,d}); //양방향
  }
  for(int i=0;i<t;i++){
    cin>>x;
    dest.insert(x);
  }
//prepare
  vector<pair<int,bool>> chk(n+1,{-1,false});  // first== cost, second== 도로 경유 여부
  priority_queue<pair<int,pair<int,int>>,vector<pair<int,pair<int,int>>>,greater<pair<int,pair<int,int>>>> pq; //first=cost, second.first=경유, second.second=key
//calc
  pq.push({0,{0,s}}); //second.first: 0은 미통과, -1은 통과
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),key(tmp.second.second),pass(tmp.second.first);
    if(chk[key].first!=-1){
      continue; //이미 했다면 넘어간다.
    }
    chk[key].first=cost;chk[key].second=pass;
    if(key==g){
      for(auto& ele: graph[key]){
        if(ele.first==h){
          pq.push({cost+ele.second,{-1,ele.first}});
        }else{
          pq.push({cost+ele.second,{pass,ele.first}});
        }
      }
    }else if(key==h){
      for(auto& ele: graph[key]){
        if(ele.first==g){
          pq.push({cost+ele.second,{-1,ele.first}});
        }else{
          pq.push({cost+ele.second,{pass,ele.first}});
        }
      }
    }else{
      for(auto& ele: graph[key]){
        pq.push({cost+ele.second,{pass,ele.first}});
      }
    }
  }
//output
  for(auto& ele: dest){
    if(chk[ele].second){
      cout<<ele<<" ";
    }
  }
  cout<<endl;
}
void BK11657(){  // Bellman-Ford Algorithm, 음수 가중치도 허용한다, Edge 중심, vertex의 cost가 매우 작아질 수 있으므로 overflow 주의 
  /*
  Bellman-Ford Algorithm

  문제에서는 음의 cycle이 발생할 경우 -1을 출력하므로 문제되지 않는다.
  V-1번 bellman-Ford실행후, V번째 실행을 한번 더 하여 변화가 있으면 -1, 없으면 출력
  출력시 INF는 -1로 출력

  지나온 경로를 다시 지나갈 수 있는가?
    무한으로 시간을 돌리는 경로라 함은 지나온 경로를 다시 지나갈 수 있음을 의미한다.
      중복 제거를 해도 된다.

  Dijkstra를 이용한 해법. 그러나 구현하지 않았다.
    graph문제 이지만, cost가 음수, 0이 가능하다.
    순환하는 고리
      합이 양수: 순환하지 않는다.
      합이 0 : 순환을 최대 한번 할 수 있다.
      합이 음수: 무한히 순환한다. 
        -> pq에 방문한 vertex를 표시하고, 재방문이 확인된다면 합이 음수인 순환하는 고리, 그 중에서도 -INF로 가는 수임을 알 수 있다.
            재방문 cost가 기존 cost보다 크면 방문하지 않기 때문에 INF로 가지는 않는다.
        -INF는 고리 밖에 있는 vertex로 갈 때, 해당 vertex도 -INF로 만든다
        -INF는 고리 내부에 있는 vertex를 재방문 해서는 안된다.
          -> 고리의 vertex를 확인하는 function을 이용해 재방문을 막자
    pq.의 구성
      cost, key, 방문한 vertex를 저장한 set,방문 불가능한 vertex를 저장한 set
  */
//input
  int N,M,A,B,C;
  cin>>N>>M; // #교차로(vertex), #도로(edge)
  vector<map<int,int>> graph(N+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 경로, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<M;i++){
    cin>>A>>B>>C;
    auto ans= graph[A].insert({B,C});
    if(!ans.second){
      if(ans.first->second>C){
        ans.first->second=C;
      }
    }
  }
//prepare
  int INF=6000*10000+1;   // cost의 최댓값 +1
  vector<long long> cost_V(N+1);  // cost
//calc
  int ans=BellmanFord(graph,cost_V,1,INF);
//output
  if(ans){
    cout<<-1<<"\n";
  }else{
    for(int i=2;i<=N;i++){
      if(cost_V[i]==INF){
        cout<<-1<<"\n";
      }else{
        cout<<cost_V[i]<<"\n";
      }
    }
  }
}
void BK11404(){  // Floyd-Warshall Algorithm, 음수 가중치도 허용한다, DP 이용
  /*
  Floyd-Warshall Algorithm
    DP table 두개를 이용하는 Algorithm
      1. Vertex간 최단거리를 저장하는 table
      2. 최단거리일 때, 각 Vertex의 직전 Vertex를 저장하는 table
      # table의 갱신: 경유하는 vertex가 0개 ~ #vertex-1 개 일때까지 차례로 DP
  */
//input
  int N,M,A,B,C;
  cin>>N>>M; // #교차로(vertex), #도로(edge)
  vector<map<int,int>> graph(N+1); // V[i]'s element =pair : i 와 p.first사이의 가중치 p.second의 경로, 중복 간선은 최저치 빼고 삭제
  for(int i=0;i<M;i++){
    cin>>A>>B>>C;
    auto ans= graph[A].insert({B,C});
    if(!ans.second){
      if(ans.first->second>C){
        ans.first->second=C;
      }
    }
  }
//prepare
  int INF=INT32_MAX;
  vector<vector<int>> cost_V(N+1,vector<int>(N+1));  // cost
  vector<vector<int>> prev_V(N+1,vector<int>(N+1));  // prev, prev[i][j]=k means the path is (i, ..., k, j) 
//calc
  FloydWarshall(graph,cost_V,prev_V);
//output
  for(int i=1;i<=N;i++){
    for(int j=1;j<=N;j++){
      if(cost_V[i][j]==INF){
        cout<<0<<' ';
      }else{
        cout<<cost_V[i][j]<<' ';
      }
    }
    cout<<endl;
  }
}