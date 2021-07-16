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

int Answer;

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

		Answer = 0;
		/////////////////////////////////////////////////////////////////////////////////////////////
    //input
    int length,kValue;
    string number;
    cin>>length>>kValue>>number;
    vector<int> aGroup(length,-1),bGroup(length);
    for(int i=0;i<length;i++){
      bGroup[i]=number[length-1-i];
    }
    //pre
    for(int i=0;i<kValue;i++){
      if(bGroup[i]==1){aGroup[i+kValue]=1; }
      if(bGroup[length-1-i]==1){aGroup[length-1-i-kValue]=1; }
    }
    //algo
    for(int i=length-1;i>=0;i--){
      int& now=aGroup[i];
      if(now!=-1){continue; }
      if(bGroup[i-kValue]==0){
        now=0;
      }else{
        if(i-kValue*2>=0){
          int& another=aGroup[i-kValue*2];
          if(another!=-1){now=!another;}
          another=1;
          now=0;
        }else{
          now=1;
        }
      }
    }
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}

/*
  힌트
  aGroup[idx]==2^idx를 표현하는 것이라고 간주하자
  0~t-1, n-t~n-1의 값은 확정적으로 구해진다.
  높은 idx가 0인것이 무조건적으로 이득이다.-> 여러가지 경우를 찾을 필요가 없이 원서치가 된다는 뜻
  방법1: 
    확정값을 구한다.
    높은 idx부터 시작하여, a group에 해당하는 b group을 찾는다.
      b group이 0이다 -> a group은 0
      b group이 1이다 ->
        다른 a group이 fix되어 있다 -> a group은 !(다른 a group)
        다른 a group이 fix되어있지 않다 -> 다른 a group은 1, 이번 a group은 0
      가장 낮은 idx까지 돌면 끝이다.
*/