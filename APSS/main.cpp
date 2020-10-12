//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>

using namespace std;

void Quantization_Input(vector<int>& number,int& quantRange){
  int numSize;
  cin>>numSize>>quantRange;
  number.resize(numSize);
  for(auto& ele:number){
    scanf("%d",&ele);
  }
}
void Quantization_DP_A(vector<int>& number, vector<vector<int>>& DP_A){
  for(int i=0;i<number.size();i++){
    for(int j=i;j<number.size();j++){
      int sum(0),avg(0),len(j-i+1),result(0);
      for(int k=i;k<=j;k++){
        sum+=number[k];
      }
      //반올림
      avg=int(0.5+static_cast<double>(sum)/len);
      //제곱합
      for(int k=i;k<=j;k++){
        result+=(number[k]-avg)*(number[k]-avg);
      }
      DP_A[i][j]=result;
    }
  }
}
void Quantization_DP_A_2(vector<int>& number, vector<vector<int>>& DP_A){
  //부분합을 이용해 계산시간을 줄인다. 합, 제곱합을 n에서 1로 최적화
  int numLen=number.size();
  vector<int> DP_pSum(numLen); //A(i)=for(x=0~i)sum(number[x])
  vector<int> DP_pSqSum(numLen);//A(i)=for(x=0~i)sum(number[x]^2)
  DP_pSum[0]=number[0];DP_pSqSum[0]=number[0]*number[0];
  for(int i=1;i<numLen;i++){
    DP_pSum[i]=DP_pSum[i-1]+number[i];
    DP_pSqSum[i]=DP_pSqSum[i-1]+number[i]*number[i];
  }
  //DP_A 계산
  for(int i=0;i<numLen;i++){
    for(int j=i;j<numLen;j++){
      int sum=DP_pSum[j]-(i==0? 0 : DP_pSum[i-1]);
      int sqSum=DP_pSqSum[j]-(i==0? 0 : DP_pSqSum[i-1]);
      //반올림
      int avg=int(0.5+static_cast<double>(sum)/(j-i+1));
      //제곱합최소값
      DP_A[i][j]=sqSum-2*avg*sum+avg*avg*(j-i+1);
    }
  }
}
int Quantization_DP_B(vector<int>& number, vector<vector<int>>& DP_A,vector<vector<int>>& DP_B,int start,int depth){
  //기저, 모든 숫자를 양자화, 숫자는 남았는데 더 양자화 할 수 없을때
  if(start==number.size()) return 0;
  if(depth==0) return 123456789;
  //메모제이션
  int& result=DP_B[start][depth];
  if(result!=-1) return result;
  //substructure
  result=123456789;
  for(int i=0;start+i<number.size();i++){
    result=min(result,DP_A[start][start+i]+Quantization_DP_B(number,DP_A,DP_B,start+i+1,depth-1));
  }
  return result;
}
int Quantization_Algo(vector<int>& number,int quantRange){
  /*
  제한시간 2초
  제한메모리 64MB
  테스트 케이스 50개
  수열의 길이 1~100, 사용할 숫자의 수 1~10
  전략1
    Dynamic Programming
      두개의 DP 배열
        첫번째 DP_A
          수열 오름차순 정렬
          수열의 길이 * 수열의 길이
          A(ij)=i~j를 한 숫자로 양자화 했을때의 제곱합 최소치 
        두번째 DP_A
          수열의 길이 * 양자화에 사용할 숫자의 수
          B(i,j)=i번째 숫자부터 j번째 양자화 수를 사용할 때, i번째 숫자부터 제곱합최소치
      A(i,j)
        arr[i]~arr[j]범위의 양자화 값 하나를 이용할 때, 제곱합 최소치를 구한다.
          양자화 값은 arr[i]~arr[j]의 평균
            증명: 평균보다 a만큼 차이가 나면, (gap1-a)^2+(gap2+a)^2+... > gap1^2+gap2^2+...
            미분을 이용해서도 증명 가능
        A(ij)=sum((x-avg)^2), x=i~j
      substructure  
        B(i,j)= for(k=i~ last) 
          B(i,j)=C(i~k-1)+B(k,j+1)
          오름차순 정렬이기 때문에, optimal substructure가 성립한다.
        제한조건
          최대값=1000^2*100=100,000,000, INF=123456789
          j가 10이면 return 0
          i가 last를 벗어나면 return INF
    time complexity
      sorting(nlgn)+#A(1)*A(n^3)+#B(n^2)*B(n) = O(n^3)
        optimize: #A2(1)*A2(n^2)
    mem complexity
      #arr(n)=O(n)
  */
  //정렬
  sort(number.begin(),number.end());
  //DP_A, i~j를 한 숫자로 양자화 했을때의 제곱합 최소치
  vector<vector<int>> DP_A(number.size(),vector<int>(number.size(),-1));
  Quantization_DP_A_2(number,DP_A);
  //DP_B
  vector<vector<int>> DP_B(number.size(),vector<int>(quantRange+1,-1));
  return Quantization_DP_B(number,DP_A,DP_B,0,quantRange);
}
void Quantization(){
  int testCase;
  cin>>testCase;
  vector<int> result;
  while(testCase--){
    vector<int> number;
    int quantRange;
    Quantization_Input(number,quantRange);
    cout<<Quantization_Algo(number,quantRange)<<'\n';
  }
}

int main(void){
  Quantization();
  return 0;
}
