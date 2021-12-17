// Algorithmic Problem Solving Strategies Book 1, 2
//대회에서 배우는 알고리즘 문제해결 전략 1, 2

#include <algorithm>
#include <cmath>
#include <ctime>
#include <iostream>
#include <map>
#include <queue>
#include <string>
#include <vector>

using namespace std;

void EDITORWARS_Input(int& peopleNum, int& commentNum, vector<int>& commentType, vector<pair<int, int>>& commentRelation) {
    cin >> peopleNum >> commentNum;
    commentType.resize(commentNum);
    commentRelation.resize(commentNum);
    for (int i = 0; i < commentNum; i++) {
        string tmpType;
        cin >> tmpType;
        cin.ignore();
        if (tmpType == "ACK") {
            commentType[i] = 1;
        } else {
            commentType[i] = 0;
        }
        cin >> commentRelation[i].first >> commentRelation[i].second;
    }
}
int EDITORWARS_Find(vector<int>& root, int idx) {
    if (root[idx] == idx) {
        return idx;
    }
    return root[idx] = EDITORWARS_Find(root, root[idx]);
}
int EDITORWARS_union(vector<int>& root, vector<int>& rank, vector<int>& numOfEle, int idxA, int idxB) {
    int rootA = EDITORWARS_Find(root, idxA), rootB = EDITORWARS_Find(root, idxB);
    if (rootA == rootB) return rootA;
    if (rank[rootA] > rank[rootB]) {
        root[rootB] = rootA;
        numOfEle[rootA] += numOfEle[rootB];
    } else if (rank[rootA] == rank[rootB]) {
        root[rootB] = rootA;
        rank[rootA]++;
        numOfEle[rootA] += numOfEle[rootB];
    } else {
        root[rootA] = rootB;
        numOfEle[rootB] += numOfEle[rootA];
    }
    return EDITORWARS_Find(root, idxA);
}
string EDITORWARS_Algo(int peopleNum, int commentNum, vector<int> commentACK, vector<pair<int, int>> commentElements) {
    // union-find prepare
    vector<int> root(peopleNum);
    for (int i = 0; i < peopleNum; i++) {
        root[i] = i;
    }
    vector<int> rank(peopleNum, 1);
    vector<int> numOfEle(peopleNum, 1);
    // disjoint[A]=B means A and B are disjoint set
    vector<int> disjoint(peopleNum, -1);
    // ACK makes union, DIS makes disjoint
    for (int i = 0; i < commentNum; i++) {
        int rootA = EDITORWARS_Find(root, commentElements[i].first);
        int rootB = EDITORWARS_Find(root, commentElements[i].second);
        if (commentACK[i]) {
            if (rootA == rootB) continue;
            if (disjoint[rootA] == rootB) {
                return string("CONTRADICTION AT ") + to_string(i + 1);
            }
            int rootNew = EDITORWARS_union(root, rank, numOfEle, rootA, rootB);
            // disjoint update, disA==-1 means disjoint[rootA] does not exist
            int disA = disjoint[rootA], disB = disjoint[rootB];
            if (disA != -1 && disB != -1) {
                int disNew = EDITORWARS_union(root, rank, numOfEle, disA, disB);
                disjoint[rootNew] = disNew, disjoint[disNew] = rootNew;
            } else if (disA != -1) {
                disjoint[rootNew] = disA;
            } else if (disB != -1) {
                disjoint[rootNew] = disB;
            }
        } else {
            if (rootA == rootB) {
                return string("CONTRADICTION AT ") + to_string(i + 1);
            }
            if (disjoint[rootA] == rootB) continue;
            // disjoint update
            int disA = disjoint[rootA], disB = disjoint[rootB];
            if (disA != -1) {
                rootB = EDITORWARS_union(root, rank, numOfEle, disA, rootB);
            }
            if (disB != -1) {
                rootA = EDITORWARS_union(root, rank, numOfEle, disB, rootA);
            }
            disjoint[rootA] = rootB, disjoint[rootB] = rootA;
        }
    }
    // return
    int maxPeople = 0;
    vector<int> counted(peopleNum, 0);
    for (int i = 0; i < peopleNum; i++) {
        if (counted[i]) continue;
        if (EDITORWARS_Find(root, i) != i) continue;
        if (disjoint[i] == -1) {
            maxPeople += numOfEle[i];
        } else {
            maxPeople += max(numOfEle[i], numOfEle[disjoint[i]]);
            counted[disjoint[i]] = 1;
        }
        counted[i] = 1;
    }
    return string("MAX PARTY SIZE IS ") + to_string(maxPeople);
}
void EDITORWARS() {
    /*설명 및 입력
    설명
        모든 회원들이 vi 혹은 Emacs를 사용하는 프로그래밍 동호회에서 연말 파티를 개최하려 합니다.
            서로 다른 편집기를 사용하는 사람들이 파티에 함께 참가하면 싸움이 나기 때문에 vi를 사용하는 사람들만 오는 파티,
            Emacs를 사용하는 사람들만 오는 파티를 따로 하기로 했습니다.
            이를 위해 지금까지 모든 회원들이 쓴 댓글을 모아 이들을 두 종류로 분류했습니다.
                상호 인정: 이 유형의 댓글은 댓글을 쓴 사람과 원글을 쓴 사람이 같은 편집기를 쓴다는 사실을 의미합니다.
                상호 비방: 이 유형의 댓글은 댓글을 쓴 사람과 원글을 쓴 사람이 다른 편집기를 쓴다는 사실을 의미합니다.
        이것만으로는 물론 각 사용자가 어떤 편집기를 쓰는지는 알 수 없지만,
            우선 서둘러 장소를 예약해야 하기 때문에 이 정보만으로 파티에 올 수 있는 최대 인원을 알아야 합니다.
        댓글 정보가 주어질 때 이 댓글 정보 중 모순되는 것은 없는지 확인하고,
            모순되는 것이 없을 때 한 파티의 가능한 최대 인원을 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1≤C≤50)가 주어집니다.
            각 테스트 케이스의 첫 줄에는 회원의 수 N (1≤N≤10000)과 분석한 댓글의 개수 M (1≤M≤100000)이 주어집니다.
            각 회원은 0에서 N - 1 범위의 숫자로 표현됩니다.
        그 후 M줄에 하나씩 각 댓글의 정보가 주어집니다. 각 댓글은 상호 인정, 혹은 상호 비방 댓글입니다.
            상호 인정 댓글은 “ACK a b”(0≤a, b<N) 형태로 주어지며 상호 비방 댓글은 “DIS a b” 형태로 주어집니다.
    출력
        각 테스트 케이스마다 한 줄을 출력합니다.
        댓글에 주어진 정보 중 모순이 없는 경우 한 파티에 올 수 있는 사람의 최대 수를 “MAX PARTY SIZE IS x”의 형태로 출력합니다.
        댓글들에 주어진 정보 중 모순이 있는 경우, 모순이 처음으로 발생하는 댓글이 몇 번인지를 “CONTRADICTION AT i” 형태로 출력합니다.
            댓글의 번호는 입력에 주어진 순서대로 1부터 시작한다고 합시다.
    제한조건
        4초, 64MB
    */
    /*힌트
        상호 배타적 집합(disjoint set) 방법
            ACK는 union-find를 통해 집합지을 수 있다.
            DIS는 추가적인 수행 방법이 필요하다.
                1) DIS는 ACK를 모두 수행하고 두 그룹을 찾은 후에 수행한다.??
                    1. 둘 모두 그룹이 있을경우, 모순 관계를 확인한다.
                    2. 하나만 그룹이 있을경우, 다른 그룹에 나머지를 포함시킨다.
                    3. 둘 모두 그룹이 없을경우
                        3.1 나중에 둘중 하나가 그룹에 포함될 경우
                        3.2 나중에도 둘 모두 그룹이 없을 경우
                            3.2.1 그룹이 없는 것들끼리, DIS관계가 있을 경우
                2) DIS가 발생하면, 각 원소를 각각 속하는 그룹의 root로 만들어버린다.??
                    ACK와 관계없이 순서대로 수행 가능하다.
                    모순이 발생한다 -> 모순 반환
                    정답 반환: ??
                3) disjoint관계를 배열로 표현한다.
                    - disjoint는 항상 set의 root간의 관계로 표시한다.
                    - set이 두개밖에 없으므로, disjoint 관계는 단 하나의 set과 가질 수 있다.
                    1. disjoint가 없다면, DIS가 발생했을 때 disjoint를 생성해준다.
                    2. disjoint가 이미 존재한다면, disjoint는 두개이상 존재할 수 없으므로, disjoint의 djsjoint를 union한다.
                        예시) A - B - C (- means disjoint)라면, A와 C를 union한다.
                        2-1. DIS의 두 원소 모두 disjoint가 존재한다면, 하나씩 union하면 문제없이 수행된다.
                    counting: disjoint가 없는 원소는 그냥 세고, 있는 원소는 더 큰 숫자로 센다.
                    수행시간
                        time complexity: union&disjoint(n)+counting(n) = O(n)
                        mem complexity: rank(n)+count(n)+parent(n) = O(n)
    */
    /*
    아이디어 1
        설명:
            disjoint set이므로, ACK는 union-find를 통해 그룹짓는다.
            그룹이 반드시 두개밖에 없으므로, DIS를 통해 disjoint를 생성하거나, 두 set을 합친다.
                disjoint: 두 set이 대립 관계임을 나타내는 Link
                set 합치기: B의 disjoint가 A와 C에대해 모두 존재한다면, A와 C는 같은 set이다.
        성능:
            time complexity: O(M)
            mem complexity: O(N)
        한계:
        피드백:
        책의 아이디어:
    */
    // Sol
    int testCase;
    cin >> testCase;
    //각 테스트케이스
    while (testCase--) {
        int peopleNum, commentNum;
        vector<int> commentType;  // 0 is ACK, 1 is DIS
        vector<pair<int, int>> commentRelation;
        EDITORWARS_Input(peopleNum, commentNum, commentType, commentRelation);
        auto result = EDITORWARS_Algo(peopleNum, commentNum, commentType, commentRelation);
        // cout << "::::";
        cout << result << endl;
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    EDITORWARS();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}