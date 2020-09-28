//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>

using namespace std;

class longNum{
  vector<int> num;
public:
  //생성자
  longNum(){} 
  longNum(const vector<int>& a):num(a){}
  longNum(vector<int>&& a):num(a){}
  longNum(const string& a){
    num.reserve(a.length());
    for(auto& ele:a){
      num.push_back(ele);
    }
  }
  ~longNum(){}
  //복사 생성자, 이동 생성자
  longNum(const longNum& lN):num(lN.num){}
  longNum(longNum&& lN) noexcept :num(lN.num){}
  //대입 연산자 오버로딩
  longNum& operator=(const longNum& lN){
    num=lN.num;
  }
  longNum& operator=(longNum&& lN){
    num=lN.num;
  }
  longNum& operator*(){}
  longNum& operator+(){}
  longNum karatsuba(){}
};


void FanmeetingInput(vector<int>& member,vector<int>& fan){
  string memberTmp,fanTmp;
  cin>>memberTmp>>fanTmp;
  member.reserve(memberTmp.length());
  for(auto& ele: memberTmp){
    if(ele=='M'){
      member.push_back(1);
    }else{
      member.push_back(0);
    }
  }
  fan.reserve(fanTmp.length());
  for(auto& ele: fanTmp){
    if(ele=='M'){
      fan.push_back(1);
    }else{
      fan.push_back(0);
    }
  }
}
int FanmeetingAlgo(string& member, string& fan){
  /*
  제한시간 10초
  제한메모리 2^16kb=64MB
  전략1
    모든 멤버와 모든팬은 만난다.
    한 줄의 모든 멤버들이 포옹하는 경우 -> M & M 이없는 경우 
      M=1, F=0으로 하고 bit and(&) -> if (0)-> 모든멤버 포옹
    time complexity
    mem complexity
  전략2
  전략 3
  */
  //기저
  if(right<left){
    return 0;
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
  int rightMax=FenceAlgo(fenceData,pivot+1,right);
  return max(minValue*(right-left+1),max(leftMax,rightMax));
}
void Fanmeeting(){
  int testCase;
  cin>>testCase;
  while(testCase--){
    string member,fan;
    FanmeetingInput(member,fan);
    cout<<FanmeetingAlgo(member,fan)<<"\n";
  }
}

int main(void){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  Fanmeeting();

  return 0;
}