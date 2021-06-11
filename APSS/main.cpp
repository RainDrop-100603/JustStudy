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

// Decision Problem, 이분법
void ROOTS_Input(int& power, vector<double>& coefficients){
  cin>>power;
  coefficients.resize(power+1);
  for(auto& ele:coefficients){
    cin>>ele;
  }
}
vector<double> ROOTS_2ndEquation(const vector<double>& coefficients){
  double varA(coefficients[0]),varB(coefficients[1]),varC(coefficients[2]);
  vector<double> result;
  result.push_back((-1*varB-sqrt(varB*varB-4*varA*varC))/(2*varA));
  result.push_back((-1*varB+sqrt(varB*varB-4*varA*varC))/(2*varA));
  return result;
}
vector<double> ROOTS_differential(const vector<double>& coefficients){
  vector<double> result;
  int power=coefficients.size()-1;
  int idx=0;
  while(power){
    result.push_back(coefficients[idx]*power);
    idx++;
    power--;
  }
  return result;
}
double ROOTS_funcValue(double variable, const vector<double>& coefficients){
  double result=0;
  int power=coefficients.size()-1;
  for(auto& ele: coefficients){
    result+=ele*pow(variable,power);
    power--;
  }
  return result;
}
vector<double> ROOTS_Algo(int power, const vector<double>& coefficients){
  //기저 
  if(power==2){
    return ROOTS_2ndEquation(coefficients);
  }
  //미분 후 극점 구하기 
  auto pole=ROOTS_Algo(power-1,ROOTS_differential(coefficients));
  pole.insert(pole.begin(),-11.0); pole.push_back(11.0); 
  //계산
  vector<double> result;
  for(int i=0;i+1<pole.size();i++){
    double lo(pole[i]),hi(pole[i+1]),loValue(ROOTS_funcValue(lo,coefficients)),hiValue(ROOTS_funcValue(hi,coefficients));
    if(loValue*hiValue>0){
      continue;
    }
    //반복문 불변식, f(lo)<=0<f(hi);
    if(hiValue<=0){
      double tmp=lo; lo=hi; hi=tmp;
    }
    for(int count=0;count<100;count++){
      double mid=(lo+hi)/2;
      double midValue=ROOTS_funcValue(mid,coefficients);
      if(midValue<=0){
        lo=mid;
      }else{
        hi=mid;
      }
    }
    result.push_back((lo+hi)/2);
  }
  return result;
}
void ROOTS(){
  // ROOTS
  /*설명 및 입력
  설명
    실수 근만을 갖는 ax2 + bx + c = 0과 같은 형태의 단변수 다항 방정식이 주어질 때, 이들의 근을 계산하는 프로그램을 작성하세요.
    다항식의 모든 해의 절대값은 10 이하라고 가정해도 좋습니다.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 C(C<=50)가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 방정식의 차수 n(2 <= n <= 5)이 주어지고, 그 다음 줄에 n+1개의 실수로 방정식의 차수가 고차항부터 주어집니다.
  출력
    각 테스트 케이스마다 n개의 실수로 오름차순으로 정렬된 방정식의 해를 출력합니다. 
    방정식의 해는 모두 다르다고 가정해도 좋습니다. 
    10-8 이하의 상대/절대 오차가 있는 답은 정답으로 처리됩니다.
  제한조건
    5초, 64MB
  */
  /*힌트
    n차 방정식 이하는 직접 구하고, 그 이상은 미분과 재귀, 이분법을 이용한다.
      1차방정식은 간단하게 계산 가능하다
      2차방정식은 근의 공식을 이용할 수 있다.
      3차이상은 극점과 근의 관계를 이용한다.
        부호가 다른 두 극점 사이에는, 한개의 해가 반드시 존재한다. 
          양 끝 극점 바깥부분에도 해가 존재할 수 있다 -> 아랫부분 참고
        각 극점은, 미분값의 해와 같다.
          미분 후 재귀하여 각 극점의 해를 구할 수 있다.
    양 끝 극점 바깥부분에도 해가 존재할 수 있다
      문제에서 해의 범위가 -10 ~ 10임을 밝혔기 때문에, 해당 범위를 양 끝이라고 가정해도 된다.
      -10 ~ 10의 범위를 벗어나는 극점을 제거할 필요는 없다.
        어차피 해당 범위 밖에는 해가 없기 때문에, 벗어나는 위치의 극점과 끝값의 부호는 같을 것이다. 
  */
  /*전략
  전략1
    이분법
    접근방법
      2차 함수는 근의 공식, 1차함수는 바로 답을 구한다.
      3차이상의 함수는 양끝점과 극점사이를 계산하여 값을 구한다.
        양 끝점은 +-11으로한다(해는 반드시 -10과 10 사이);
        각 극점은 미분값의 해 이다.
        계산은 이분법을 100회 진행한다. f(lo)<=0<f(hi)
          f(lo)*f(hi)<=0일때만 해가 존재한다.
    시간:
      1차, 2차함수: O(1)
      3차함수: O(3*100+2차함수);
      4차함수: O(4*100+3차함수)=O(4*100+3*100+2차함수);
      5차함수: O(5*100+4차함수)=O((5+4+3)*100+1);
      n차함수: O(sigma(n)*100)=O(n^2);
    크기:
      O(n)
    개선 및 보완
      
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int power;
    vector<double> coefficients;
    ROOTS_Input(power,coefficients);
    auto result=ROOTS_Algo(power,coefficients);
    cout<<fixed;
    cout.precision(10);
    for(auto& ele: result){
      cout<<ele<<" ";
    }cout<<endl;
  }
}

int main(void){
   //clock_t start,end;
   //start=clock();
 ROOTS();
   //end=clock();;
   //cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
  return 0;
}