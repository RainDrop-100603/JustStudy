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
int N_Queen(int N,vector<bool>& rowQueen,vector<bool>& colQueen,vector<bool>& lineRDQueen,vector<bool>& lineLDQueen, int row, int count){
  int sum=0;
  if(count==N){
    return 1; //N개가 모두 놓아야 하나의 case 이므로 
  }

  for(int i=row;i<N;i++){
    if(!rowQueen[i]){
      for(int j=0;j<N;j++){
        if(!colQueen[j]){
          if(!(lineRDQueen[N-i+j]||lineLDQueen[i+j])){
            rowQueen[i]=true;
            colQueen[j]=true;
            lineRDQueen[N-i+j]=true;
            lineLDQueen[i+j]=true;
            sum+=N_Queen(N,rowQueen,colQueen,lineRDQueen,lineLDQueen,i+1,count+1);
            rowQueen[i]=false;
            colQueen[j]=false;
            lineRDQueen[N-i+j]=false;
            lineLDQueen[i+j]=false;
          }
        }
      }
    }
  }
  
  return sum;
}
// int N_Queen(int N,vector<bool>& rowQueen,vector<bool>& colQueen,vector<Queen>& currentQ, int row, int count){
//   int sum=0;
//   if(count==N){
//     return 1; //N개가 모두 놓아야 하나의 case 이므로 
//   }

//   int count2=0;
//   for(int i=row;i<N;i++){
//     if(!rowQueen[i]){
//       for(int j=0;j<N;j++){
//         if(!colQueen[j]){
//           count2=0;
//           for(const auto& ele: currentQ){
//             if(!ele.QueenOK(i,j)){
//               break;
//             }
//             count2++;
//           }
//           if(count!=count2){
//             continue;
//           }
//           rowQueen[i]=true;
//           colQueen[j]=true;
//           currentQ.push_back(Queen(i,j));
//           sum+=N_Queen(N,rowQueen,colQueen,currentQ,i+1,count+1);
//           rowQueen[i]=false;
//           colQueen[j]=false;
//           currentQ.pop_back();
//         }
//       }
//     }
//   }
  
//   return sum;
// }

// int N_Queen(int N, table,int row, int count){
//   int sum=0;
//   if(count==N){
//     return 1; //N개가 모두 놓아야 하나의 case 이므로 
//   }
//   for(int i=row;i<N;i++){
//     for(int j=0;j<N;j++){
//       if(table[i][j]==0){ //0이 아니면 막히는게 있다는 뜻
//         for(int k=0;k<N;k++){ //table 정리 ++
//           table[i][k]++;   //세로
//           table[k][j]++;   //가로
//           if(i-k>=0&&j-k>=0){table[i-k][j-k]++;} //왼아래   
//           if(i-k>=0&&j+k<N){table[i-k][j+k]++;}//왼위
//           if(i+k<N&&j-k>=0){table[i+k][j-k]++;}//오른아래
//           if(i+k<N&&j+k<N){table[i+k][j+k]++;}//오른위
//         } 
//         sum+=N_Queen(N,table,i+1,count+1);
//         for(int k=0;k<N;k++){ //table 정리 --
//           table[i][k]--;   //세로
//           table[k][j]--;   //가로
//           if(i-k>=0&&j-k>=0){table[i-k][j-k]--;} //왼아래   
//           if(i-k>=0&&j+k<N){table[i-k][j+k]--;}//왼위
//           if(i+k<N&&j-k>=0){table[i+k][j-k]--;}//오른아래
//           if(i+k<N&&j+k<N){table[i+k][j+k]--;}//오른위
//         } 
//       }
//     }
//   }
  
//   return sum;
// }