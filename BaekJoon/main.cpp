#include <iostream>
#include <cmath>
#include <vector>
#include <cstring>

// #include "GoodFunction.h"

using namespace std;

// vector<int>& Merge(vector<int> &v1, vector<int> &v2){  //v1에 v2 v1을 합친다.
//   vector<int>::iterator iter1;
//   vector<int>::iterator iter2;

//   return v1;
// }


// vector<int> MergeSort(vector<int> arrayV){
//   //divide


//   //merge & conquer



//   vector<int> mergedVector;

//   return mergedVector;
// }

int main(){
  cin.tie(NULL);
  cin.sync_with_stdio(false);
  
  // //입력 받기 및 벡터 형성
  // int vectorSize, num;
  // cin>>vectorSize;
  // vector<int> arrayV;
  // for(int i=0;i<vectorSize;i++){
  //   cin>>num;
  //   arrayV.push_back(num);
  // }
  // //sorting
  // arrayV=MergeSort(arrayV);
  // //출력 
  // vector<int>::iterator iter;
  // for(iter=arrayV.begin();iter!=arrayV.end();iter++){
  //   cout<<*iter<<"\n";
  // }

  vector<int> v;
  v.push_back(7);
  vector<int>::iterator iter;
  iter=v.begin();
  cout<<*iter<<endl;

  v.insert(iter,3);
  iter=v.begin();
  cout<<*iter<<endl;

  iter=v.begin();
  v.insert(iter+1,4);

  v.insert(v.begin(),10);
  iter=v.begin();

  cout<<*iter<<' '<<*(iter+1)<<' '<<*(iter+2)<<' '<<*(iter+3);
  
  return 0;
}

