/*
You should use the standard input/output

in order to receive a score properly.

Do not use file input and output

Please be very careful. 
*/

#include <iostream>
#include <vector>

using namespace std;

void func_input(int& nodeNum, int& edgeNum, int& segNum, vector<vector<int>>& graph, vector<pair<int,int>>& segment){
	cin>>nodeNum>>edgeNum>>segNum;
	graph.resize(nodeNum);
	for(int i=0;i<nodeNum;i++){
		int from,to;
		cin>>from>>to;
		graph[from].push_back(to);
	}
	for(int i=0;i<segNum;i++){
		pair<int,int> tmp;
		cin>>tmp.first>>tmp.second;
		segment.push_back(tmp);
	}
}

void func_canGo(vector<vector<int>>& canGo,const vector<vector<int>>& graph){
	int nodeNum=graph.size();
	for(int i=0;i<nodeNum;i++){
		vector<int> stack;
		stack.push_back(i);
		vector<int>& visited=canGo[i];
		while(!stack.empty()){
			int nowNode=stack.back();
			stack.pop_back();
			for(auto ele: graph[nowNode]){
				if(visited[ele]){continue; }
				visited[ele]=1;
				stack.push_back(ele);
			}
		}
	}
}

void func_canGoUpdate(int from, int to, vector<vector<int>>& canGo){
	int nodeNum=canGo.size();
	for(int j=0;j<nodeNum;j++){
		canGo[from][j]|=canGo[to][j];
	}
	//from node를 갈 수 있는 다른 node 연산
	for(int j=0;j<nodeNum;j++){
		if(canGo[j][from]==1){
			for(int k=0;k<nodeNum;k++){
				canGo[j][k]|=canGo[from][k];
			}
		}
	}
}

bool func_algo1(vector<vector<int>>& canGo,vector<pair<int,int>>& segment,vector<int>& segUsed){
	int segNum=segment.size();
	int nodeNum=canGo.size();
	//선택지 만들기
	vector<int> segChoice(segNum,-1);
	for(int i=0;i<segNum;i++){
		if(segUsed[i]!=-1){continue; }
		int from(segment[i].first),to(segment[i].second);
		//from->to
		bool cycleExist(false);
		for(int j=0;j<nodeNum;j++){
			if(canGo[to][j]==0){continue; }
			if(j==from){
				cycleExist=true;
				break;
			}
		}
		if(cycleExist){
			segChoice[i]=0;
		}else{
			segChoice[i]=1; 
		}
		//to -> from
		cycleExist=false;
		for(int j=0;j<nodeNum;j++){
			if(canGo[from][j]==0){continue; }
			if(j==to){
				cycleExist=true;
				break;
			}
		}
		if(!cycleExist){
			segChoice[i]+=2;
		}
		//error
		if(segChoice[i]==0){
			return false;
		}
	}
	//1개인것 입력
	bool inputExist=false;
	for(int i=0;i<segNum;i++){
		int choice=segChoice[i];
		if(choice==-1||choice==3){continue; }
		int from,to;
		if(choice==1){
			from=segment[i].first; to=segment[i].second;
		}else if(choice==2){
			to=segment[i].first; from=segment[i].second;
		}
		segUsed[i]=choice-1;
		//from node 연산
		func_canGoUpdate(from,to,canGo);
	}
	return true;
}

bool func_algoRepeat(vector<vector<int>>& canGo,vector<pair<int,int>>& segment,vector<int>& segUsed){
	int segChange=-1;
	int segNum=segment.size();
	while(segChange!=0){
		auto tmpSegUsed(segUsed);
		if(func_algo1(canGo,segment,tmpSegUsed)==false){
			return false;
		}
		segChange=0;
		for(int i=0;i<segNum;i++){
			if(segUsed[i]!=tmpSegUsed[i]){
				segChange++;
			}
		}
	}
	return true;
}

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
		int nodeNum, edgeNum, segNum;	//seg는 방향없는 edge
		vector<vector<int>> graph;
		vector<pair<int,int>> segment;
		func_input(nodeNum,edgeNum,segNum,graph,segment);
    //graph 전처리
		vector<vector<int>> canGo(nodeNum,vector<int>(nodeNum,0));
		func_canGo(canGo,graph);
		//선택지가 1개인 edge들 입력 -> 더 입력 불가능할때까지
		vector<int> segUsed(segNum,-1);
		func_algoRepeat(canGo,segment,segUsed);
		while(true){
			int first=-1;
			for(int i=0;i<segNum;i++){
				if(ele[i]==-1){
					first=i;
					break;
				}
			}
			if(first==-1){
				break;
			}
			//
			auto tmpSegUsed(segUsed);
			tmpSegUsed[first]=0;
			auto tmpCanGo(canGo);
			func_canGoUpdate(segment[first].first,segment[first].second,tmpCanGo);
			auto valid=func_algoRepeat(tmpCanGo,segment,tmpSegUsed);
			if(valid){
				canGo=tmpCanGo;
			}
		}
		/////////////////////////////////////////////////////////////////////////////////////////////
		
		// Print the answer to standard output(screen).
		cout << "Case #" << test_case+1 << endl;
		cout << Answer << endl;
	}

	return 0;//Your program should return 0 on normal termination.
}