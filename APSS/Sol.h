#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>
#include <map>

#include "useful.h"

using namespace std;
// @*: 풀었으나 참고해볼만한 문제, @*@*: 어렵게 풀었던 문제, @*@*@*: 책이나 다른 해답을 참고한 문제 

//Boggle, BruteForce, 런타임 에러 발생 Mem over?
void BoggleRandInput(vector<char>& probTable, vector<string>& wordArr);
void BoggleInput(vector<char>& probTable, vector<string>& wordArr);
vector<int> BoggleAlgo(vector<char>& probTable, vector<string>& wordArr);
vector<int> Boggle_Algo2(vector<char>& probTable, vector<string>& wordArr);
void BoggleGame();

//picnic, BruteForce, 조합에서의 중복 제거 방법 
void PicnicInput(vector<vector<bool>>& friendTable);
int PicnicAlgo(vector<vector<bool>>& friendTable,vector<bool>& toBePush);
void Picnic();

//BoardCover, BruteForce, timeComplexity보다 더 빨리 동작하는 경우
void BoardCoverInput(vector<vector<bool>>& boardTable);
bool BoradCoverNoAns(vector<vector<bool>>& boardTable);
int BoardCoverAlgo(vector<vector<bool>>& boardTable);
void BoardCover();

//ClockSync, BruteForce, 횟수가 제한되어 있을경우, 조합
void ClockSyncInput(vector<int>& clockArr);
int ClockSyncAlgo(vector<int>& clockArr,vector<vector<int>>& switchArr,int nowSwitch);
void ClockSync();

//QuadTree, Divide&Conquer, iterator을 활용하여 전달인자 간소화 
void QuadTreeInput(string& treeData);
string QuadTreeAlgo(string::iterator& iter);
void QuadTree();

//Fence, Divide&Conquer, Bk6549, stack(19장), line sweeping(15장), 상호배타적 집합(25장)
void FenceInput(vector<int>& fenceData);
int FenceAlgo(vector<int>& fenceData,int left, int right);
void Fence();

//fanMeeting, Divide&conquer, bitmask, 미완성 
// void FanmeetingInput(longNum& member,longNum& fan);
// int FanmeetingAlgo(longNum& member, longNum& fan);
// void Fanmeeting();

//WildCard, DP, Sol을 한번에 생성하려하지말고 천천히하자: 완전탐색 -> 겹치는부분 DP
void WildcardInput(string& wildcard,vector<string>& fileArr);
bool Wildcard_match(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP);
bool Wildcard_match2(string& wildcard,string& file, int w_idx,int f_idx,vector<vector<char>>& DP);  //match에서 develop
vector<string> WildcardAlgo(string& wildcard,vector<string>& fileArr);
void Wildcard();

//JLIS, DP, 최적화가 아닌 메모제이션
void JoinedLISInput(vector<int>& arrA,vector<int>& arrB);
bool joinedLIS_Afirst(vector<int>& arrA,vector<int>& arrB,int idxA,int idxB);
int JoinedLISAlgo_1(vector<int>& arrA,vector<int>& arrB);
int JoinedLISAlgo_3(vector<int>& arrA,vector<int>& arrB);
int JoinedLISAlgo_2(vector<int>& arrA,vector<int>& arrB,int idxA, int idxB,vector<vector<int>>& DP);
void JoinedLIS();

//PI 외우기, DP 최적화
void PImem_Input(string& s);
int PImem_hard(string& numbers,int start,int len);
int PImem_Algo(string& numbers, vector<int>& DP, int start);
void PImem();

//Quantization, DP 최적화, 간단한 처리를 통해 DP를 사용 가능하게 만들었다. 부분합의 이용
void Quantization_Input(vector<int>& number,int& quantRange);
void Quantization_DP_A(vector<int>& number, vector<vector<int>>& DP_A);
void Quantization_DP_A_2(vector<int>& number, vector<vector<int>>& DP_A);
int Quantization_DP_B(vector<int>& number, vector<vector<int>>& DP_A,vector<vector<int>>& DP_B,int start,int depth);
int Quantization_Algo(vector<int>& number,int quantRange);
void Quantization();

//AsymTiling, DP 메모제이션, 비대칭타일을 세는 것이 아닌, 전체타일 - 대칭타일 (비대칭 타일도 DP로 해결 가능하지만 전자가 더 간단.)
void AsymTiling_Input(int& tileLen);
int AsymTiling_DP(vector<int>& DP,int tileLen);
int AsymTiling_Algo(int tileLen);
void AsymTiling();

//Poly-omino, DP 최적화, optimal substructrue를 잘 찾자.
void Poly_Input(int& block);
int Poly_DP(vector<vector<int>>& DP,int blockNum,int topNum);
int Poly_Algo(int block);
void Poly();

//numb3rs, DP 최적화, 마르코프 연쇄, double 사용 테크닉
void Numb3rs_Input(int& dayPast,int& prison,vector<vector<int>>& townGraph,vector<int>& chkTown);
double Numb3rs_DP(vector<vector<int>>& townGraph,vector<int>& degree,vector<vector<double>>& DP, int dayPast, int town);
vector<double> Numb3rs_Algo(int dayPast,int prison,vector<vector<int>>& townGraph,vector<int>& chkTown);
void Numb3rs();

//Packing, DP최적화, 함수내부의 루프를 제거하도록 노력하자
void Packing_Input(int& weight,vector<string>& itemName,vector<int>& itemWeight,vector<int>& itemDesp);
int Packing_DP(vector<vector<int>>& DP_desp,vector<int>& itemWeight,vector<int>& itemDesp,int nowChoice,int weightRemain);
vector<int> Packing_Algo(int weight,vector<int>& itemWeight,vector<int>& itemDesp);
void Packing();

//@*@*@* Ocr, DP최적화,은닉 마르코프 모델,viterbi 알고리즘, P(A|B)=P(B|A)P(A)/P(B) 와 같은 변환을 유용하게 이용하자, string 처리할 때 유의하여 처리하자,
void Ocr_Input(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr);
void Ocr_Input_test(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr);
void Ocr_randInput(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr);
void Ocr_input_simpleT(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,vector<vector<double>>& nextPoss,
                vector<vector<double>>& classifiPoss,vector<string>& sentenceArr);
double Ocr1_DP1(vector<vector<double>>& DP_Ocr1,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,int now, int nextGuess);
double Ocr1_DPposs(vector<vector<double>>& DP_Ocr1,vector<double>& firstPoss,vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,
                  vector<vector<double>>& DP_Poss,vector<vector<int>>& DP_Path, vector<int>& wordOfSentence,int idx,int nowWord);
vector<string> Ocr1_Algo(int& wordNum,int& sentenceNum,vector<string>& wordArr,map<string,int>& wordArrMap,vector<double>& firstPoss,
                        vector<vector<double>>& nextPoss,vector<vector<double>>& classifiPoss,vector<string>& sentenceArr);
double Ocr2_possQ(const vector<vector<double>>& DP, int prev, int now);
double Ocr2_DPposs(const vector<vector<double>>& DP_possQ,const vector<vector<double>>& DP_RgivenQ,vector<vector<double>>& DP_Poss,
                    vector<vector<int>>& DP_Path,const vector<int>& wordOfSentence,int nextIdx,int nowWord);
vector<string> Ocr2_Algo(int wordNum,int sentenceNum,const vector<string>& wordArr,const map<string,int>& wordArrMap,const vector<double>& firstPoss,
                        const vector<vector<double>>& nextPoss,const vector<vector<double>>& classifiPoss,const vector<string>& sentenceArr);
void Ocr();

//@*@* KLIS, DP최적화, overflow 처리, 함수 모듈화 깔끔하게, error발생시 return발생 확인,
void KLIS_Input(int& arrLen,int& orderK,vector<int>& array);
void KLIS_getHistory(vector<int>& array, vector<vector<pair<int,int>>>& history, vector<int>& tmpLIS, int idx);
int KLIS_DP(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases, int LISidx, int reverse_Seq);
vector<int> KLIS_kthLIS(vector<vector<pair<int,int>>>& history, vector<int>& cache_numOfCases,int LISidx, int orderK, pair<int,int> prevPair);
void KLIS_funcTest(vector<vector<pair<int,int>>>& history,vector<int>& cache_numOfCases);
vector<int> KLIS_Algo(int arrLen,int orderK,vector<int>& array);
void KLIS();

// @*@*@* 지나친 수학적 접근이 문제, 프로그래밍적으로 접근필요, overflow의 다양한 처리법, 함수내에서 한번에 하나의 행동만 
//skip번째 ele를 구하는 프로그램을 len번 반복하게 만들어도 큰 무리가 없다. 오히려 내 방법보다 더 간단할 수도 있음(내 방법은 substr을 많이 사용함)
void Dragon_example();
void Dragon_Input(int& nthGen,int& skip,int& len);
int Dragon_getCases(int nthGen);
void Dragon_del_skip_make_history(int nthGen, int skip,vector<pair<string,int>>& history);
string Dragon_getDragon(vector<pair<string,int>>& history, int len);
string Dragon_Algo(int nthGen,int skip,int len);
void Dragon();

// @*@* 조건을 이용하여 연산을 줄인다. 특정 순열보다 작은 순열에 대한 계산. history의 필요유무에 따라 다른 DP, 숫자는 arr보다는 str
void ZIMBABWE_Input(long long& nowPrice,long long&  mFactor);
int ZIMBABWE_bitmaskCount(long long bitmask);
int ZIMBABWE_DP(vector<vector<int>>& DP_ZIMBABWE,vector<int>& arr_price, long long used_bitmask,int mfactor_remain);
int ZIMBABWE_func1(vector<vector<int>>& DP_ZIMBABWE,vector<int>& arr_price, int digit, int mfactor_remain);
int ZIMBABWE_Algo(long long nowPrice,long long mFactor);
void ZIMBABWE();

// @*@* 정답에서 하나씩 빼는 DP, boundary 조건 확실히
void RESTORE_Input(int& strNum,vector<string>& strArr);
int RESTORE_isInValid(const string& shortStr,const string& longStr);
vector<string> RESTORE_strOptimize(const vector<string>& strArr);
void RESTORE_DP_prepare(vector<vector<int>>& DP_strSaved,vector<string>& strArr_opti);
int RESTORE_DP(vector<vector<int>>& dp_bitmask,int now_bitmask,int add_str);
string RESTORE_result(vector<vector<int>>& DP_strSaved,const vector<string>& strArr_opti);
string RESTORE_Algo(int strNum,vector<string> strArr);
void RESTORE();

// 연산자 확인, pseudo-code 잘 짜기 
void TICTACTOE_Input(vector<vector<string>>& board);
int TICTACTOE_bijection(vector<vector<string>>& board);
bool TICTACTOE_isFinished(vector<vector<string>>& board, string turn);
int TICTACTOE_result(vector<vector<string>>& board, vector<int>& cache_result,string turn_last);
string TICTACTOE_Algo(vector<vector<string>>& board);
void TICTACTOE();

// 전략 짜는것 완벽했음, minimax algorithm과 유사하다(책 참고 343p)
void NUMBERGAME_Input(vector<int>& board);
int NUMBERGAME_cache(const vector<int>& board, vector<vector<int>>& DP_cache, int left, int len);
int NUMBERGAME_Algo(const vector<int>& board);
void NUMBERGAME();

// memOver 대비 필요, 특정 조건을 만족하면 바로 ret하게 만들어 수행시간 향상 
void BLOCKGAME_Input(vector<vector<string>>& board);
char BLOCKGAME_cache(vector<char>& DP_cache, int can_use_bitmask);
string BLOCKGAME_Algo(vector<vector<string>>& board);
void BLOCKGAME();

// @* sliding window, algo와 algo2의 속도차이에 유의하자(하드웨어적 원인). 속도가 느린 장치에 자주 접근할수록, 속도는 느려진다.
void SUSHI_Input(vector<pair<int,int>>& menu, int& budget);
int SUSHI_Algo2(vector<pair<int,int>> menu,int budget);
int SUSHI_Algo(vector<pair<int,int>> menu,int budget);
void SUSHI();

// @*@*, c(i)=W^(i) * c(0), W는 단순히 확률 관련 부분이고, 실제로 고민할 것은 열벡터 c 부분이다.
// p(x)=w1p(x-1)+...+wnp(x-n)과 같이 여러 시간대의 항목이 필요할경우, 모두 열벡터에 넣어주면 된다.
void GENIUS_Input(int& songNum,int& targetTime,int& favSongNum,vector<int>& songPlaytime,
      vector<int>& favSongList,vector<vector<double>>& possibility);
vector<double> GENIUS_Algo(int& songNum,int& targetTime,int& favSongNum,vector<int>& songPlaytime,
      vector<int>& favSongList,vector<vector<double>>& possibility);
void GENIUS();

// greedy, 증명부분에 더 신경쓰자
void MATCHORDER_Input(int& number,vector<int>& ourRating,vector<int>& enemyRating);
int MATCHORDER_Algo(int number,vector<int> ourRating,vector<int> enemyRating);
void MATCHORDER();

// greedy, 증명부분 괜찮았음, 참고하자 
void LUNCHBOX_Input(int& number,vector<int>& warmTime,vector<int>& eatingTime);
int LUNCHBOX_Algo(int number,const vector<int>& warmTime,const vector<int>& eatingTime);
void LUNCHBOX();

// @*@*@* greedy, Huffman code, 교재 참고, 증명을 생각하기 어려우면 그림을 그려보자 
void STRJOIN_Input(int& strNum,vector<int>& strLen);
int STRJOIN_Algo(int strNum,const vector<int>& strLen);
void STRJOIN();

// @* greedy, atan2 함수, 원에서의 각도를 이용할땐, 2pi마다 반복되는것을 고려하고 정규화, 자료형 잘 확인하기  
void MINASTIRITH_Input(int& pointNum,vector<vector<double>>& pointArr);
int MINASTIRITH_func(const vector<pair<double,double>>& pointAngleArr,const vector<int>& cache, int idx);
int MINASTIRITH_Algo(int pointNum,const vector<vector<double>>& pointArr);
void MINASTIRITH();

// combination, 답이 맞는지부터 확인, 시간조건을 맞추기 위해 최적화 하나씩 추가하면서 확인(한번에 추가 x), 함수가 너무 많다
void BOARDCOVER2_Input(vector<vector<char>>& board, vector<vector<char>>& block);
vector<vector<char>> BOARDCOVER2_block_turn(const vector<vector<char>>& block);
void BOARDCOVER2_BlockArr_input(vector<vector<vector<char>>>& block_arr, const vector<vector<char>>& block);
vector<vector<vector<char>>> BOARDCOVER2_BlockArr(const vector<vector<char>>& block);
bool BOARDCOVER2_board_can_input(const vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col);
void BOARDCOVER2_board_input(vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col);
void BOARDCOVER2_board_output(vector<vector<char>>& board, const vector<vector<char>>& block,int row,int col);
int BOARDCOVER2_func(vector<vector<char>>& board, const vector<vector<vector<char>>>& block_arr, int& tmp_max,pair<int,int> heuristic1,int prev_value,int now_idx);
int BOARDCOVER2_Algo(vector<vector<char>> board, vector<vector<char>> block);
void BOARDCOVER2();

// combination, set cover, 책에 더 최적화 하는 방법들이 있다.
void ALLERGY_Input(vector<string>& friendsName, vector<vector<string>>& foodsInfo);
vector<pair<int,long long>> ALLERGY_food_opti(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo);
void ALLERGY_func(const vector<pair<int,long long>>& foods_bitmask,int friendsNum, long long friends_bitmask, int& tmp_min, int prev_count, int food_idx);
int ALLERGY_Algo(const vector<string>& friendsName, const vector<vector<string>>& foodsInfo);
void ALLERGY();

// @* combination, Constraint Satisfaction Problem, 두가지 버전 비교해보기
void KAKURO2_Input(vector<vector<int>>& board, vector<vector<int>>& hint);
void KAKURO2_preTreat(vector<vector<int>>& board,vector<vector<int>>& hint);
pair<int,int> KAKURO2_hintChk(const vector<vector<int>>& board,const vector<vector<int>>& hint,int xAxis, int yAxis);
pair<int,int> KAKURO2_findHint(const vector<vector<int>>& board,const vector<vector<int>>& hint,
            const vector<vector<int>>& hint_remain_arr,const vector<vector<pair<int,int>>> board_hint);
bool KAKURO2_validChk2(int bitmask, int count, int target);
bool KAKURO2_validChk(const vector<int>& hHint,const vector<int>& vHint,int input);
void KAKURO2_set(vector<vector<int>>& board,vector<vector<int>>& hint,vector<vector<int>>& hint_remain_arr,pair<int,int> twoHint,int input,int mode);
bool KAKURO2_func(vector<vector<int>>& board,vector<vector<int>>& hint,vector<vector<int>>& hint_remain_arr,const vector<vector<pair<int,int>>> board_hint);
vector<vector<int>> KAKURO2_Algo(vector<vector<int>> board,vector<vector<int>> hint);
void KAKURO2_set2(vector<vector<int>>& board,vector<vector<int>>& hint,int input,pair<int,int> hint_pair, int mode);
bool KAKURO2_func2(vector<vector<int>>& board,vector<vector<int>>& hint,vector<vector<vector<int>>>& cache,const vector<vector<pair<int,int>>> board_hint);
void KAKURO2_setCache(vector<vector<vector<int>>>& cache);
vector<vector<int>> KAKURO2_Algo2(vector<vector<int>> board,vector<vector<int>> hint);
void KAKURO2();

// Decision Problem, 이분법 사용시 유의, 13.2절을 공부한 후 다시 보기 
void DARPA_Input(int& cameraNum, vector<double>& cameraPoint);
double DARPA_func(int cameraNum, const vector<double>& cameraDistance, const vector<double>& cameraPoint, int left, int right);
double DARPA_Algo(int cameraNum, vector<double> cameraPoint);
void DARPA();

// Decision Problem, 이분법의 적절한 사용예
void ARCTIC_Input(int& pointNum, vector<pair<double,double>>& pointLoc);
double ARCTIC_func(int pointNum, const vector<pair<double,double>>& pointLoc,int count, double left, double right);
double ARCTIC_Algo(int pointNum, vector<pair<double,double>> pointLoc);
void ARCTIC();

// Decision Problem, 재귀를 이용함, while문을 이용하여 재귀를 대신할 수 있음, input 방식 유의  
void CANADATRIP_Input(int& cityNum,int& order,vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap);
void CANADATRIP_Input2(int& cityNum,int& order,vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap);
int CANADATRIP_func(int order, vector<int>& cityLoc,vector<int>& signBegin,vector<int>& signGap, int left, int right);
int CANADATRIP_Algo(int cityNum,int order,vector<int> cityLoc,vector<int> signBegin,vector<int> signGap);
void CANADATRIP();

// @*@*@* Decision Problem, 이분법, 문제가 안풀리면 수식을 작성해보자 
void WITHDRAWL_Input(int& classNum,int& requiredNum,vector<int>& order,vector<int>& students);
bool WITHDRAWL_decision(int classNum,int requiredNum,vector<int>& order,vector<int>& students, double left, double right);
double WITHDRAWL_Algo(int classNum,int requiredNum,vector<int> order,vector<int> students);
void WITHDRAWL();


// 수치해석, 이분법
void ROOTS_Input(int& power, vector<double>& coefficients);
vector<double> ROOTS_2ndEquation(const vector<double>& coefficients);
vector<double> ROOTS_differential(const vector<double>& coefficients);
double ROOTS_funcValue(double variable, const vector<double>& coefficients);
vector<double> ROOTS_Algo(int power, const vector<double>& coefficients);
void ROOTS();

// 수치해석, 이분법, 최초 lo, hi를 넉넉하게 결정하자
void LOAN_Input(double& loan,int& month,double& interest);
double LOAN_funcValue(double loan,int month,double interest, double pay);
double LOAN_Algo(double loan,int month,double interest);
void LOAN();

// 수치해석, 이분법, 자료형 유의, 수학적 해법도 생각은 해보자 
void RATIO_Input(int& playTime,int& winTime);
bool RATIO_decision(long long playTime,long long winTime,long long addWin);
int RATIO_Algo(int playTime,int winTime);
void RATIO();

//철인 2종경기, 수치해석, 삼분탐색, local minimum, 그래프를 그려서 조건 확인 
/*
  삼분탐색
    달리기거리(r)에 따른 시간(time)그래프, 시간이 낮을수록 좋은것
      부정행위자의 그래프는 선형증가함수이다.
      time_min(정상참가자)의 그래프는 위로 볼록한 2차함수 모양이다(모양만 그렇다는것, concave function) 
      따라서 정상참가자 그래프-부정행위자 그래프는 위로 볼록한 2차함수 모양이다.
      local maximun이 존재하고, 남은 구간에서 strictly decresing(increasing) 하므로 삼분탐색 이용가능
    삼분탐색 함수
      f(r) = min(정상참가자 time) - 부정행위자 time
    개선점
      사실 삼분탐색 조건을 완전히 만족하는 것이 아니다. 두 그래프의 기울기가 일치하는 지점이 있을 수 있기 때문이다.
        두 그래프의 기울기가 일치하면, 합친 그래프의 기울기는 0이 되는것을 의미한다.
        그러나 기울기가 0이 되는 부분은 반드시 최대(최소)이기 때문에, 여전히 삼분탐색을 이용할 수 있다.
*/

// @* 수치해석, 삼분탐색, 차분히 힌트를 찾아서 풀자
void FOSSIL_Input(int& fig1Num,int& fig2Num,vector<pair<double,double>>& figure1,vector<pair<double,double>>& figure2);
double FOSSIL_yPos(pair<double,double>& point1,pair<double,double>& point2,double xPos);
double FOSSIL_yRange(vector<pair<double,double>>& figure1, vector<pair<double,double>>& figure2,double xPos);
pair<double,double> FOSSIL_getLoHi(vector<pair<double,double>>& figure1, vector<pair<double,double>>& figure2);
double FOSSIL_Algo(int fig1Num,int fig2Num,vector<pair<double,double>> figure1, vector<pair<double,double>> figure2);
void FOSSIL();

// @* 정수론, 약수계산, 에라스토테네스의채, DP와 전역변수등을 적절히 이용하자, brute force도 고려할만 하다. 
void PASS486_Input(int& number,int& low,int& hi);
void PASS486_GetPrime(vector<int>& primeArr);
int PASS486_GetFactor(vector<int>& primeArr, vector<int>& factorArr,vector<int>& minFactorNum,int num);
int PASS486_Algo(vector<int>& primeArr,vector<int>& factorArr,vector<int>& minFactorNum,int number,int low,int hi);
void PASS486();
