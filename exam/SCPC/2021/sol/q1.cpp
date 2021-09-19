/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

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
    int peopleNum;
    cin>>peopleNum;
    vector<int> friendship(peopleNum);
    for(auto& ele:friendship){
      cin>>ele;
    }
    //algo
    vector<int> group(peopleNum,-1);
    int count=0;
    for(int i=0;i<peopleNum;i++){
      if(group[i]!=-1){continue;}
      int now(i),groupIdx(count);
      group[now]=count;
      vector<int> tmpGroup(1,now);
      while(true){
        int next=now+friendship[now];
        if(next>=peopleNum){break;}
        if(group[next]==-1){
          tmpGroup.push_back(next);
          now=next;
        }else{
          groupIdx=group[next];
          break;
        }
      }
      for(auto& ele:tmpGroup){
        group[ele]=groupIdx;
      }
      if(count==groupIdx){
        count++;
      }
    }
    Answer=count;
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}

//만점