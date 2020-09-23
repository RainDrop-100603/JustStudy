#include <iostream>
#include <vector>

using namespace std;

//Boggle, 런타임 에러 발생 Mem over?
void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr);
void BoggleInput(vector<char>& probTable, vector<string>& wordArr);
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr);
void BoggleGame();
