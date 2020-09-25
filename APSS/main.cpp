//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;
void FenceInput(vector<int>& fenceData){
  int fenceNum,tmp;
  cin>>fenceNum;
  fenceData.reserve(fenceNum);
  for(int i=0;i<fenceNum;i++){
    cin>>tmp;
    fenceData.push_back(tmp);
  }
}
int FenceAlgo(vector<int>& fenceData,int left, int right){
  /*
  제한시간 1초
  제한메모리 2^16kb=64MB
  전략1
    기저: left==right일 때, max=leftmax=rightmax=fenceData[left];
    재귀: L(left,mid), R(mid+1,right) 재귀
    반환: max, leftmax, right max
      leftmax= L's leftmax
      rightmax= R's right max
      newMax=if(fenceData[mid]<fenceData[mid+1])
        L's rightmax + R's leftmax*fenceData[mid]/fenceData[mid+1]
        else: vice versa
      max=max(newMax, L's max, R's max);
    time complexity
      O(NlgN): lgN 번 호출, O(n) 비교
    mem complexity
      O(N)
  전략2
    앞에서부터 뒤로 search
      key, prev, now 존재
        key 왼쪽으로는 모두 key보다 크거나 같다
        prev는 now 직전
          now가 prev보다 작다면,
    stack을 이용하는 건데 헷갈려
  전략 3
    quick sort 전략을 이용한다.
      가장 작은 pivot을 구한다
        분할: (left,pivot-1), (pivot+1,right)로 분리
        반환: result= max(pivot*(right-left),func(left,pivot-1),func(pivot+1,right));
        기저: right=left -> return fenceData[left];
      총 lgN번 구한다
      time complexity: NlgN
      mem complexity: N
  */
  //기저, left==right일 때, max=leftmax=rightmax=fenceData[left];
  if(right==left){
    return fenceData[left];
  }
  //Algo, 
  int pivot,minValue(12345);
  for(int i=left;i<=right;i++){
    if(fenceData[i]<minValue){
      minValue=fenceData[i];
      pivot=i;
    }
  }
  int leftMax=FenceAlgo(fenceData,left,pivot-1);
  return result;
}
void Fence(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    vector<int> fenceData;
    FenceInput(fenceData);
    cout<<FenceAlgo(fenceData)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Fence();

  return 0;
}