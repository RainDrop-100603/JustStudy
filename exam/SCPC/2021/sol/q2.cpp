/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

string Answer;

bool zigzag(vector<int>& arr,const vector<int>& target, int kValue, int start){
  int length=arr.size();
  int nowIdx(start),targetIdx(nowIdx+kValue),nextIdx(targetIdx+kValue);
  bool valid(true);
  while(true){
    //기저
    if(nextIdx>=length){
      if(targetIdx<length){
        if(arr[nowIdx]==target[targetIdx]){return true; }
        break;
      }
      return true;
    }  
    if(arr[nextIdx]!=-1){
      if((arr[nowIdx]|arr[nextIdx])!=target[targetIdx]){break; }
      return true;
    }
    //algo
    if(target[targetIdx]==0){
      if(arr[nowIdx]==1){
        break;
      }
      arr[nextIdx]=0;
      nowIdx+=kValue*2;targetIdx+=kValue*2;nextIdx+=kValue*2;
    }else{  //target value is 1
      if(arr[nowIdx]==0){
        arr[nextIdx]=1;
        nowIdx+=kValue*2;targetIdx+=kValue*2;nextIdx+=kValue*2;
      }else{  //now=1; target=1;
        arr[nextIdx]=0;
        if(!zigzag(arr,target,kValue,nextIdx)){
          arr[nextIdx]=1;
        }
      }
    }
  }
  //only break when invalid
  while(true){
    if(nowIdx<=start){return false; }
    arr[nowIdx]=-1;
    nowIdx-=kValue*2;
  }
}

int main(int argc, char** argv)
{
	int T, test_case;
	/*
	   The freopen function below opens input.txt file in read only mode, and afterward,
	   the program will read from input.txt file instead of standard(keyboard) input.
	   To test your program, you may save input data in input.txt file,
	   and use freopen function to read from the file when using cin function.
	   You may remove the comment symbols(//) in the below statement and use it.
	   Use #include<cstdio> or #include <stdio.h> to use the function in your program.
	   But before submission, you must remove the freopen function or rewrite comment symbols(//).
	 */	

	// freopen("input.txt", "r", stdin);

	cin >> T;
	for(test_case = 0; test_case  < T; test_case++)
	{
		/////////////////////////////////////////////////////////////////////////////////////////////
    //input
    int length,kValue;
    string number;
    cin>>length>>kValue>>number;
    vector<int> aGroup(length,-1),bGroup(length);
    for(int i=0;i<length;i++){
      bGroup[i]=number[i]-'0';
    }
    //pre
    for(int i=0;i<kValue;i++){
      if(i+kValue<length){aGroup[i+kValue]=bGroup[i]; }
      if(length-1-i-kValue>=0){aGroup[length-1-i-kValue]=bGroup[length-1-i]; }
    }
    //algo
    for(int i=0;i<min(2*kValue,length);i++){
      if(aGroup[i]!=-1){
        zigzag(aGroup,bGroup,kValue,i);
      }else{
        aGroup[i]=0;
        if(!zigzag(aGroup,bGroup,kValue,i)){
          aGroup[i]=1;
          zigzag(aGroup,bGroup,kValue,i);
        }
      }
    }
    for(auto& ele:aGroup){
      if(ele==-1){
        ele=0;
      }
    }
    //make answer
    string ans;
    for(auto ele:aGroup){
      ans.push_back(ele+'0');
    }
    Answer=ans;
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}

//31점(lowest point)
//중복되는 패턴은 DP로 해결했어야 하는 문제 