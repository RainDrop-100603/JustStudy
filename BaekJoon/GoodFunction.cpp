#include "GoodFunction.h"

bool IsPrime(int num){
  if(num%2==0){
    if(num==2){
      return true;
    }
    return false;
  }
  if(num==1){
    return false;
  }
  int tstNum=num-2;
  while(tstNum>1){
    if(num%tstNum==0){
      return false;
    }
    tstNum-=2;
  }
  return true;
}
bool* GetPrimeArray(int num){
  num++;
  bool* array=new bool[num+1];
  fill_n(array,num+1,true);
  array[0]=false;
  array[1]=false;
  for(int i=2;i<sqrt(num);i++){
    if(array[i]){
      for(int j=i*2;j<num+1;j+=i){
        if(array[j]){
          array[j]=false;
        }
      }
    }
  }
  return array;
}
vector<int> GetPrimeVector(int num){
  vector<int> prime;
  bool* array= GetPrimeArray(num);
  for(int i=0;i<num+1;i++){
    if(array[i]){
      prime.push_back(i);
    }
  }
  return prime;
}
void Merge(int* &array, const int start, const int end){  //[start,end) sorting 
  int middle=(end+start)/2; //두 vector 사이의 경계 idx
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  int tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  int temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    if(temp<array[rotateBack]||rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
      temp=tempArray[rotateFront-start];
    }else{
      array[mainRotate]=array[rotateBack];
      rotateBack++;
      mainRotate++; //하나 더 sorted 됐으므로
    }
  }
  return;
}
void MergeSort(int* &array,const int start,const int end){
  //divide
  int middle=(end+start)/2;
  if(end-start==1){
    return;
  }else{
    MergeSort(array,start,middle);
    MergeSort(array,middle,end);
  }
  //conquer
  Merge(array,start,end); //Merge를 합치고 싶다면, 여기다가 그냥 함수 내용을 붙여넣으면 된다.
}
void MergeSort(vector<int>& array,const int start,const int end){
  //divide
  int middle=(end+start)/2; //두 vector사이의 경계 idx;
  if(end-start==1){
    return;
  }else{
    MergeSort(array,start,middle);
    MergeSort(array,middle,end);
  }
  //conquer : Merge
  int mainRotate=start;     //현재 sorting을 해야하는 곳. 이것 전까진 sorted
  int rotateFront=start;    //앞의 vector의 index
  int rotateBack=middle;//뒤의 vector의 index
  int tempArray[middle-start];  //front를 저장해놓은 임시 배열. 반대로 sorting되어 있을경우, 배열내에서 요소를 계속 옮기는 것은 비용이 너무 크다. 
  for(int i=start;i<middle;i++){
    tempArray[i-start]=array[i];
  }
  int temp=tempArray[0];
  while(!(rotateFront==middle)){ //앞부분이 끝날때와 뒷부분이 끝날 때
    temp=tempArray[rotateFront-start];
    if(rotateBack==end){
      array[mainRotate]=temp;
      rotateFront++;
      mainRotate++;
    }else{
      if(temp<array[rotateBack]){
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
int Combi_nCr(int n, int r){
  int sum=1;
  for(int i=n;i>n-r;i--){
    sum*=i;
  }
  for(int i=1;i<=r;i++){
    sum/=i;
  }
  return sum;
}
bool ChkDuplicate(int x, int depth, int* num){
  for(int i=0;i<depth;i++){
    if(num[i]==x){
      return true;
    }
  }
  return false;
}
void PrintAllCombi(int n, int r, int depth, int* num){
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
void PrintAllCombi2(int n, int r, int depth, int* num, int start){
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
void PrintAllCombi3(int n, int r, int depth, int* num){
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
void PrintAllCombi4(int n, int r, int depth, int* num, int start){
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
int N_Queen(int N,vector<bool>& colQueen,vector<bool>& lineRDQueen,vector<bool>& lineLDQueen, int row){
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
bool Sdoku(int sdoku[9][9],vector<pair<int,int>>& empty,int filledNum,int emptySize){ //filledNum은 채워진 개수
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
void GetMaxMin(vector<int>& arrayV,int* AddSubMulDiv,int& max,int& min,int idx,int sum){
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
void GetLowGap(int& gap,vector<vector<int>>& table,vector<int>& startTeam,vector<int>& linkTeam,int idx){
  int len=table.size(); //N/2, 각 팀의 인원수
  //인원 배분이 완료 된 후, 각 팀의 능력치 계산 
  if(idx==len*2){
    int sum1=0;
    int sum2=0;
    for(int i=0;i<len;i++){
      for(int j=i+1;j<len;j++){
        sum1+=table[startTeam[i]][startTeam[j]]+table[startTeam[j]][startTeam[i]];
        sum2+=table[linkTeam[i]][linkTeam[j]]+table[linkTeam[j]][linkTeam[i]];
      }
    }
    int tempGap=abs(sum1-sum2);
    if(tempGap<gap){
      gap=tempGap;
    }
  }
  //인원 배분
  
}
