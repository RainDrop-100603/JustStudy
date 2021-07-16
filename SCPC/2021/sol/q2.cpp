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

void input(vector<int>& arr, int maxIdx, int idx, int value){
  if(idx>=0&&idx<maxIdx){arr[idx]=value;}
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
      input(aGroup,length,i+kValue,bGroup[i]);
      input(aGroup,length,length-1-i-kValue,bGroup[length-1-i]);
    }
    //algo
    for(int i=0;i<length-kValue;i++){
      // cout<<":::";
      // for(auto ele:aGroup){
      //   cout<<ele<<",";
      // }cout<<endl;
      int nowIdx(i),targetIdx(i+kValue),nextIdx(i+2*kValue);
      //idx chk
      if(targetIdx>=length&&aGroup[nowIdx]==-1){aGroup[nowIdx]=0; }
      //back track
      if(aGroup[nowIdx]==1&&bGroup[targetIdx]==0){
        int tmpIdx=nowIdx;
        while(true){
          aGroup[tmpIdx]=0;
          aGroup[tmpIdx-kValue*2]=1;
          tmpIdx-=kValue*2;
          if(tmpIdx-kValue<0){break; }
        }
      }
      //go forward
      int &now=aGroup[nowIdx],target=bGroup[targetIdx];
      if(now==0){
        input(aGroup,length,nextIdx,target);
      }else if(now==-1){
        if(target==0){
          now=0;
          input(aGroup,length,nextIdx,0);
        }else{  //target==1
          if(nextIdx<length){
            if(aGroup[nextIdx]==0){
              now=1;
            }else{
              now=0;
              aGroup[nextIdx]=1;
            }
          }else{
            now=1;
          }
        }
      }
    }
    for(int i=length-kValue;i<length;i++){
      if(aGroup[i]==-1){
        aGroup[i]=0;
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
