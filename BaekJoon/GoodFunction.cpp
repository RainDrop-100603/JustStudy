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
  delete[] array;
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

int getGCD(int A, int B){     //유클리드 호제법을 이용한 A와 B의 GCD
  return A%B ? getGCD(B,A%B) : B; //A=qB+r, r=A%B, GCD(A,B)=GCD(B,r)=GCD(B,A%B), r==0이면 B가 최대공약수 
}
pair<long long,long long> EuclidAlgo(long long A,long long B){      //조건: A>B  ____  Ax+By=d, d=gcd(A,B). 유클리드 알고리즘의 해(x,y)
  if(B!=0){ //B=r==0이면 A가 최대공약수
    pair<long long,long long> temp=EuclidAlgo(B,A%B);
    return make_pair(temp.second,temp.first-(A/B)*temp.second);
  }else{
    return make_pair(1,0);  // GCD(d,0) = dx+0y=d: 
  }
} 
vector<vector<long long>> FibonacciMatrix(long long m){ //Fibonacci identity: 도가뉴 항등식, d'Ocagne's identity, f_m matrix 반환, important 참고 
  vector<vector<long long>> matrix_m(2,vector<long long>(2));
  //m==1일 경우, f0, f1, f1, f2 반환, 즉 f_1 matrix 반환 
  if(m==1){
    matrix_m[0][0]=0;
    matrix_m[0][1]=1;
    matrix_m[1][0]=1;
    matrix_m[1][1]=1;
    return matrix_m;
  }
  //m>0일 경우 f_m matrix 반환 : f_m matrix == f_(m-1), f_m, f_m, f_(m+1)
  vector<vector<long long>> matrix_m2=FibonacciMatrix(m/2);
  long long a=matrix_m2[0][0];
  long long b=matrix_m2[0][1];
  long long c=matrix_m2[1][0];
  long long d=matrix_m2[1][1];
  
  if(m%2==0){
    matrix_m[0][0]=a*a+b*c;
    matrix_m[0][1]=b*(a+d);
    matrix_m[1][0]=c*(a+d);
    matrix_m[1][1]=d*d+b*c;
  }else{
    matrix_m[0][0]=b*(a+d);
    matrix_m[0][1]=d*d+b*c;
    matrix_m[1][0]=d*d+b*c;
    matrix_m[1][1]=d*d+b*c+b*(a+d);
  }
  
  matrix_m[0][0]%=1000000;
  matrix_m[0][1]%=1000000;
  matrix_m[1][0]%=1000000;
  matrix_m[1][1]%=1000000;
  
  return matrix_m;
}
void Dijkstra(const vector<map<int,int>>& graph, vector<int>& cost_V, int start){ //음수 가중치 불가능. vertex 중심
  /*
  Dijkstra Algorithm
    음수 cost 경로 불가능
    가장 cost가 낮은 vertex기준으로 다른 vertex를 갱신한다
      priority queue를 이용 
        cost뿐 아니라 다른 우선순위가 있을 경우에도 이용 가능{priority1,priority2,...priorityN,dest_vertex}
      vertex의 기본값은 -1로하여, -1인 경우 갱신되지 않은 것으로 감안한다.
    priority queue가 빌 때까지 실행하면 모든 vertex가 갱신된다.
      start가 맨 처음 pq에 들어간다.
      이후 가장 낮은 값의 vertex를 기준으로 갱신한다.
        음의 경로가 존재하지 않으므로, 가장낮은 값은 절대 변하지 않기 때문 
  */
  for(auto& ele:cost_V){  //cost 초기화
    ele=-1;
  }
  priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;  //0 return = Ok, 1 return = minus cycle, 음수 가중치 불가능, edge 중심
  pq.push({0,start});
  while(!pq.empty()){
    auto tmp=pq.top();
    pq.pop();
    int cost(tmp.first),from_V(tmp.second);
    if(cost_V[from_V]!=-1){ //there is minimum already
      continue;
    }
    cost_V[from_V]=cost; //갱신
    for(auto& ele:graph[from_V]){
      pq.push({cost+ele.second,ele.first});
    }
  }
}
int BellmanFord(const vector<map<int,int>>& graph, vector<long long>& cost_V, int start, int INF){  //0 return = Ok, 1 return = minus cycle
  /*
  Bellman-Ford Algorithm
    음수 cost 경로 가능
    모든 edge를 chk하여 vertex를 갱신한다. 
      갱신되지 않은 vertex에서 출발하는 edge는 감안하지 않는다.
      vertex의 기본값은 INF로 하여, INF값인 경우 갱신되지 않은 것으로 감안한다.
    #vertex -1 번 실행하면 최단거리를 찾을 수 있게 된다.
      시작 vertex는 갱신되어 있다. 
      edge chk 마다 최소 한개의 vertex가 갱신된다.
      즉  #vertex-1 번이면 반드시 모든 vertex가 갱신된다.
    #vertex 번째 실행에서 바뀌는 값이 있다면, 음의 사이클이 있는 것으로 간주한다.
      양의 사이클이 존재할 경우에는, 기존값 보다 커지기 때문에 "갱신" 이 일어나지 않는다.
    #vertex 번째 실행에서 갱신이 일어난 모든 vertex는 -INF로 간주한다.
      이때 vertex에서는 cycle 내부가 아닌 바깥으로만 이동하며 갱신이 가능하다.
        즉 cycle을 판별할 수 있어야 한다.
    ***음의 cycle 판별 추가바람
  */
  int num_V=cost_V.size();  //even if range 1~N, its OK, because there is no edge from vertex 0
  for(auto& ele:cost_V){  //cost 초기화, INF==possible max Cost +1
    ele=INF;
  } 
  cost_V[start]=0;          //start==0
  for(int i=1;i<num_V;i++){ // #vertex -1 loop
    for(int j=0;j<num_V;j++){
      long long cost=cost_V[j]; //starting point cost
      if(cost!=INF){
        for(auto& ele:graph[j]){  //first=dest, second= cost
          if(cost+ele.second<cost_V[ele.first]){
            cost_V[ele.first]=cost+ele.second;
          }
        }
      }
    }
  }
  for(int j=0;j<num_V;j++){
    long long cost=cost_V[j]; //starting point cost
    if(cost!=INF){
      for(auto& ele:graph[j]){  //first=dest, second= cost
        if(cost+ele.second<cost_V[ele.first]){
          return 1;
        }
      }
    }
  }
  return 0;
}
void FloydWarshall(const vector<map<int,int>>& graph, vector<vector<int>>& cost_V,vector<vector<int>>& prev_V){ //음수 가중치도 허용한다, DP 이용
  /*
  Floyd-Warshall Algorithm
    DP table 두개를 이용하는 Algorithm
      1. Vertex간 최단거리를 저장하는 table A
      2. 최단거리일 때, 도착 Vertex의 직전 Vertex를 저장하는 table B
      # table의 갱신: 경유하는 vertex가 0개 ~ #vertex 개 일때까지 차례로 DP
        ==모든 vertex를 경유 가능하도록 추가할 때까지
    A(i,j)=i에서 j로 가는 최단거리 cost
    B(i,j)=i에서 j로 가는 최단거리일때, j의 직전 vertex
    DP(x)->DP(x+1)에서 vertex k가 경유지로 추가될 경우, Edge(K,dest)
      A(i,dest)=min(A(i,dest),A(i,k)+Edge(k,dest))
      B(i,dest)=k, iff A(i,dest) is changed
  */
  int num_V(cost_V.size()),INF(INT32_MAX),NIL(-1);  //there is no "-1" vertex, so NIL==-1 
  //initialize
  for(int i=0;i<num_V;i++){ 
    for(int j=0;j<num_V;j++){ //default value
      cost_V[i][j]=INF;
      prev_V[i][j]=NIL;
    }
    cost_V[i][i]=0; //vertex i to i == 0
    for(auto& ele: graph[i]){ //default Edge,first==dest, second==cost
      cost_V[i][ele.first]=ele.second;
      prev_V[i][ele.first]=i;
    }
  }
  //Dynamic Programing
  for(int mid=0;mid<num_V;mid++){
    for(int dest=0;dest<num_V;dest++){
      for(int from=0;from<num_V;from++){
        if(cost_V[mid][dest]!=INF&&cost_V[from][mid]!=INF&&cost_V[from][mid]+cost_V[mid][dest]<cost_V[from][dest]){
           cost_V[from][dest]=cost_V[from][mid]+cost_V[mid][dest];
           prev_V[from][dest]=mid;
         }
      }
    }
  }
}