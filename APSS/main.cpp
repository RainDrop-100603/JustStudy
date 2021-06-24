//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>
#include <ctime>

using namespace std;

class vector2{  //2차원벡터
  const double PI=2.0*acos(0.0);
public:
  double x,y;
  vector2(double x_=0, double y_=0):x(x_),y(y_){}
  bool operator==(const vector2& rhs)const {return x==rhs.x&&y==rhs.y; }
  bool operator<(const vector2& rhs)const {return x!=rhs.x ? x<rhs.x : y<rhs.y; }
  vector2 operator+(const vector2& rhs)const {return vector2(x+rhs.x,y+rhs.y); }
  vector2 operator-(const vector2& rhs)const {return vector2(x-rhs.x,y-rhs.y); }
  vector2 operator*(double rhs)const {return vector2(x*rhs,y*rhs); }  //실수 곱
  double length()const {return hypot(x,y); }
  vector2 normalize()const {return vector2(x/length(),y/length()); }
  vector2 polar()const {return fmod(atan2(x,y)+2*PI, 2*PI); }
  double dot(const vector2& rhs)const {return x*rhs.x+y*rhs.y; }
  double cross(const vector2& rhs)const {return x*rhs.y-y*rhs.x; }
  vector2 project(const vector2& rhs)const {return rhs.normalize()*(rhs.normalize().dot(*this)); }
};

// 정수론, 유클리드 알고리즘 최대공약수를 이용
void POTION_Input(int& num,vector<int>& recipe,vector<int>& used){
  cin>>num;
  recipe.resize(num);
  for(auto& ele:recipe){
    cin>>ele;
  }
  used.resize(num);
  for(auto& ele:used){
    cin>>ele;
  }
}
int POTION_getGCD(int p,int q){
  return q==0 ? p : POTION_getGCD(q,p%q);
}
vector<int> POTION_Algo(int num,vector<int> recipe,vector<int> used){
  //get ratio and factor
  vector<int> ratio(recipe);
  int factor=0;
  for(int i=0;i<num;i++){
    factor=POTION_getGCD(factor,recipe[i]);
  }
  for(auto& ele:ratio){
    ele/=factor;
  }
  //get new factor
  int newFactor=0;
  for(int i=0;i<num;i++){
    int tmp=ceil(static_cast<double>(used[i])/ratio[i]);
    newFactor=max(newFactor,tmp);
  }
  newFactor=max(newFactor,factor);
  //get result
  vector<int> result(num);
  for(int i=0;i<num;i++){
    result[i]=ratio[i]*newFactor-used[i];
  } 
  return result;
}
void POTION(){
  // POTION
  /*설명 및 입력
  설명
    마법의 약은 n 종류의 재료를 각 ri 숟가락씩 넣어서 만들어야 합니다. 
      모든 재료를 정확히 넣었을 경우 만들어진 마법의 약은 정확히 한 병 분량이 됩니다.
    헤리가 이미 냄비에 넣은 각 재료들의 양은 pi 로 주어집니다. 
      헤리는 적절히 냄비에 재료를 최소한으로 더 넣어 각 재료의 비율을 정확히 맞추고 싶습니다.
      이를 위해 한 병보다 많은 약을 만들어도 상관 없지만, 최소한 한 병은 만들어야 합니다. 
    헤리는 항상 숟가락 단위로만 재료를 넣을 수 있기 때문에, 반 숟가락의 재료를 더 넣는다거나 하는 일은 불가능합니다.
    넣어야 할 각 재료의 최소량을 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 
    각 테스트 케이스는 세 줄로 구성됩니다. 
      첫 줄에는 재료의 수 n (1 <= n <= 200) 이 주어지고, 
      다음 줄에는 n 개의 정수로 약에 들어가야 하는 각 재료의 양 ri (1 <= ri <= 1000), 
      그 다음 줄에는 n 개의 정수로 이미 냄비에 넣은 재료의 양 pi (0 <= pi <= 1000) 가 주어집니다.
  출력
    각 테스트 케이스마다 한 줄에 n 개의 정수로 각 재료마다 더 넣어야 하는 양을 출력합니다.
  제한조건
    1초, 64MB
  */
  /*힌트
    반 숟가락을 더 넣을수는 없지만, 1.5병, 1.333병등의 분량은 만들 수 있다.
    풀이법
      1.각 재료의 비율을 구한다.
          기존 레시피의 최대공약수를 구한 후, 각 값을 최대공약수로 나눠주면 된다.
      2. 비율에 몇배를 해야 조건을 만족하는지 구한다. (배율을 구한다)
          넣은 재료에 대해, 각각의 재료를 비율로 나눠주어 올림하고, 해당 값의 최대치를 구한다.
            기존 레시피에 대한 수행값은 최대공약수와 같다.
          max(새로 구한 배율, 기존 최대공약수)
  */
  /*전략
  전략1
    최대공약수의 이용
      1.각 재료의 비율을 구한다.  -> O(n)
          기존 레시피의 최대공약수를 구한 후, 각 값을 최대공약수로 나눠주면 된다.
      2. 비율에 몇배를 해야 조건을 만족하는지 구한다. (배율을 구한다) -> O(n)
          넣은 재료에 대해, 각각의 재료를 비율로 나눠주어 올림하고, 해당 값의 최대치를 구한다.  ->O(n)
            기존 레시피에 대한 수행값은 최대공약수와 같다.
          max(새로 구한 배율, 기존 최대공약수)
    시간
      O(n)
    크기
      O(1)
    개선 및 보완
  */
  //Sol
  int testCase;
  cin>>testCase;
  //전역변수
  //각 테스트케이스
  while(testCase--){
    int num;
    vector<int> recipe,used;
    POTION_Input(num,recipe,used);
    auto result=POTION_Algo(num,recipe,used);
    //cout<<"::::";
    for(auto& ele:result){
      cout<<ele<<" ";
    }cout<<endl;
  }
}

int main(void){
    //clock_t start,end;
    //start=clock();
  POTION();
    //end=clock();;
    //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}

