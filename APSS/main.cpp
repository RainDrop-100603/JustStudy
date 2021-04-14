//Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>
#include <queue>

using namespace std;

//https://www.youtube.com/watch?v=x7STjpcKZP8 
//사회복무요원 교육 

// greedy, Huffman code, 교재 참고, 생각이 어려우면 그림을 그려보자 
void MINASTIRITH_Input(int& pointNum,vector<vector<double>>& pointArr){
  cin>>pointNum;
  pointArr=vector<vector<double>>(pointNum,vector<double>(3));
  for(auto& ele: pointArr){
    cin>>ele[0];
    cin>>ele[1];
    cin>>ele[2];
  }
}
double circleAngle(double pointX, double pointY, double radius){
  // (0,0) r=radius circle, angle from Y-axis and clockwise direction, radian
  if(pointX>=0){
    if(pointY>=0){
      //1st quadrant
      return asin(pointX/radius);
    }else{
      //4nd quadrant
      return acos(0)+acos(pointX/radius);
    }
  }else{
    if(pointY>=0){
      //2rd quadrant
      return acos(0)*4-acos(pointY/radius);
    }else{
      //3th quadrant
      return acos(0)*2+asin(-1*pointX/radius);
    }
  }
}
int MINASTIRITH_func(const vector<pair<double,double>>& pointAngleArr,const vector<int>& cache, int idx){
  int count(1),correction(pointAngleArr[idx].first);
  while(idx!=-1){
    if(pointAngleArr[idx].second>=acos(0)*4+correction){
      return count;
    }
    idx=cache[idx];
    count++;
  }
  return 1000;
}
int MINASTIRITH_Algo(int pointNum,const vector<vector<double>>& pointArr){
  //변환
  vector<pair<double,double>> pointAngleArr;
  for(auto& ele: pointArr){
    double pointAngle=circleAngle(ele[1],ele[0],8);
    double oversightAngle=asin(ele[2]/16)*2;
    pointAngleArr.push_back(make_pair(pointAngle-oversightAngle,pointAngle+oversightAngle));
  }
  sort(pointAngleArr.begin(),pointAngleArr.end());
  //cache 생성, n번째 초소에서
  vector<int> cache(pointNum,-1); 
  for(int i=0;i<pointNum;i++){
    double prev_end=pointAngleArr[i].second;
    double tmp_end=prev_end;
    for(int j=i+1;j<pointNum;j++){
      if(pointAngleArr[j].first>prev_end){
        break;
      }
      if(pointAngleArr[j].second>tmp_end){
        cache[i]=j;
        tmp_end=pointAngleArr[j].second;
      }
    }
  }
  //algo
  int tmp,result(1000),idx(0);
  while ((tmp=MINASTIRITH_func(pointAngleArr,cache,idx))!=1000){
    result=min(tmp,result);
    idx++;
  }
  //debug
  // double rad1=acos(0)/90;
  // for(auto& ele:pointAngleArr){
  //   cout<<"("<<ele.first/rad1<<","<<ele.second/rad1<<") ";
  // }cout<<"\n";
  // for(auto& ele:pointAngleArr){
  //   cout<<"("<<(ele.first+ele.second)/2/rad1<<","<<(ele.second-ele.first)/2/rad1<<") ";
  // }cout<<"\n";
  // for(auto& ele: cache){
  //   cout<<"["<<ele<<"] ";
  // }cout<<"\n";
  return result;
}
void MINASTIRITH(){
  //MINASTIRITH
  /*설명 및 입력
  설명
    반지름이 8 킬로미터나 되는 거대한 원형 성벽, n 개의 초소
      각 초소들은 해당 위치를 중심으로 반지름 ri 의 원 내부를 감시
    최소의 인원으로 성벽의 모든 부분을 감시하기 위해, 일부 초소에만 병사를 배치하려고 합니다. 
    각 초소의 위치와 감시 범위가 주어질 때, 성벽의 모든 부분을 감시하기 위해 필요한 최소한의 병사 수를 계산하는 프로그램을 작성하세요.
  입력
    입력의 첫 줄에는 테스트 케이스의 수 c (c <= 50) 가 주어집니다. 
    각 테스트 케이스의 첫 줄에는 초소의 개수 n (1 <= n <= 100) 이 주어지며, 
    그 후 n 줄에 각 3 개의 실수로 각 초소의 위치 yi, xi, 그리고 감시 범위 ri (0 < ri <= 16.001) 가 주어집니다.
  성벽은 (0,0) 을 중심으로 하는 반지름 8 인 원으로, 모든 초소는 이 성벽 위에 위치합니다.
  출력
    각 테스트 케이스마다 한 줄에 필요한 최소의 병사 위치를 출력합니다. 
    만약 어떻게 하더라도 성벽의 모든 부분을 감시할 수 없다면 IMPOSSIBLE 을 대신 출력합니다. 
    입력에 주어지는 초소의 좌표, 혹은 감시 범위가 최대 0.0000001 만큼 변하더라도 답은 변하지 않는다고 가정해도 좋습니다.
  제한조건
    2초, 64MB
  */
  /*힌트
    실수 자릿수를 사용한다
      0.0000001만큼 변해도 답은 변하지 않는다 -> 소수점 7자리까지는 정확하며, 넉넉하게 범위를 줬다고 생각하자 
      변환은 최대한 줄이는것이 오차를 줄인다.
    한바퀴 도는법
      원의 둘레를 기준으로 한다.
      중심에서의 각도를 기준으로 한다.
    풀이법 직관
      한 초소가 끝나는 위치를 포함하는 모든 초소중에, 가장 먼 범위까지 포함하는 초소를 선택한다.
        좌우 모두 선택? 한 방향으로만 선택?
      생긴건 원이지만, 직선으로 치환해서 생각할 수 있다.
        모든 범위를 포함하며, 가장적은 갯수를 사용하게 하는법
        초소의 각도, 초소가 감시하는 범위의 각도를 이용하자
          pair 자료형(감시시작위치, 감시 끝 위치) 이용하면 편할듯
    최저값을 구해야 하므로 IMPOSSIBLE은 초소의 갯수 + 100로 정하자 
    Greedy
      직선으로 치환하여 생각하자, 결과 x의 n번째 선택은 x(n), 
        x(n+1).start가 x(n).end보다 뒤에 있으며, x(n+1).end가 가장 큰 n+1을 선택하자.
      시작위치는 반드시 포함된다. 그러나 Sol은 시작위치를 포함하지 않을 수 있다.
        시작위치를 제거하고 다시 Algo를 돌린다.
          IMPOSSIBLE가 나올 때 까지 반복한다. 
          IMPOSSIBLE이 나올 때의 최솟값이 정답이다.
      Greedy Choice Property: 
        greedy 하지 않은 sol a가 있다고 하자.
          a(n+1).start<=a(n).end, a(n+2).start<=a(n+1).end 관계가 성립할 것이다.
        a(n+1)을 greedy한 선택 x(n+1)로 대체했다고 가정하자
          x(n+1).start<=a(n).end, a(n+2).start<=a(n+1).end<=x(n+1).end
        a(n+1)을 x(n+1)로 바꾸어도 sol이므로, greedy한 선택을 포함하는 sol이 있음을 알 수 있다.
      Optimal Substructure:
        S(n)=greedy(n)+S(n-1)
        n개에서의 sol은, n개에서의 greedy 한 선택과 남은 n-1개에서의 sol과 같다. (표현 책보고 다듬기)
  */
  /*전략
  전략1
    Greedy Algorithm
      각 점을 pair(감시시작위치, 감시 끝 위치)로 변환
        감시 시작 위치를 기준으로 정렬
        choice(n).start <= choice(n+1).start <= choice(n).end 인 choice(n+1)에 대해, choice(n+1).end가 가장 큰 값 선택 
      IMPOSSIBLE=초소의 갯수 + 100
      시작위치에서 (360도 + 보정치)가 넘을때까지 greedy한 선택을 한다. -> O(n)
        choice(n).start <= choice(n+1).start <= choice(n).end 인 choice(n+1)에 대해, choice(n+1).end가 가장 큰 값 선택 -> O(n)
        보정치: 시작초소의 시작위치 
      시작위치를 포함하지 않는것이 답일 수 있으므로, 시작위치를 삭제하고 다음위치부터 시작하는 것을 반복한다. -> O(n)
        IMPOSSIBLE이 뜨면 stop
    시간:
      O(N^3) 
    크기:
      O(N)
  */
  //Sol
  int testCase;
  cin>>testCase;
  while(testCase--){
    int pointNum;
    vector<vector<double>> pointArr;
    MINASTIRITH_Input(pointNum,pointArr);
    auto result=MINASTIRITH_Algo(pointNum,pointArr);
    if(result==1000){
      cout<<"IMPOSSIBLE"<<"\n";
    }else{
      cout<<result<<"\n";
    }
  }
}

int main(void){
  MINASTIRITH();
  return 0;
}