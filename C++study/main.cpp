#include <iostream>
#include "questionSol.h"
#include "important.h"
#include "BankingSystemMain.h"

using namespace std;

//단축기에서 아래 찾아보기 
//workbench.action.tasks.build : 빌드
//workbench.action.tasks.test : 실행 
/*
{
  "key": "ctrl+shift+b",
  "command": "workbench.action.tasks.build"
}
{
  "key": "ctrl+alt+r",
  "command": "workbench.action.tasks.test"
}

gram - build: ctrl + alt + a
		 - test : ctrl + shift + a
*/

//https://modoocode.com/134
//https://moodle.ufsc.br/pluginfile.php/2377667/mod_resource/content/0/Effective_Modern_C__.pdf

//Solutions of each chapter

int main(void) {

	cout << "Hello World" << endl << endl;
//important 정리 필요(이건 천천히)
//작업중: Banking Project ver6

//Question 08_1에서 자료형 자동변환에 따른 실수 발생 가능성(특히 return 부분)을 잘 정리하자 
	//Question13_2(); 
	//PtrRefTest();
	//enumTest();
	BankProgram();
	//matrixProblem();
	//StringClass();
	return 0;
}