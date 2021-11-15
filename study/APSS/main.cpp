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

class MEASURETIME_fenwicktree {
    vector<int> tree;
    int size;

   public:
    MEASURETIME_fenwicktree(int size_) : tree(size_ + 1), size(size_) {}
    void add(int pos) {
        pos++;
        while (pos <= size) {
            tree[pos] += 1;
            pos += (pos & -pos);  // pos += pos' last bit, -pos == ~pos + 1
        }
    }
    int pSum(int pos) {
        pos++;
        int result = 0;
        while (pos > 0) {
            result += tree[pos];
            pos -= (pos & -pos);
        }
        return result;
    }
};

void MEASURETIME_Input(int& eleNum, vector<int>& unsorted) {
    cin >> eleNum;
    unsorted.resize(eleNum);
    for (auto& ele : unsorted) {
        scanf("%d", &ele);
    }
}
int MEASURETIME_Algo(int eleNum, vector<int> unsorted) {
    int result = 0;
    // unsorted를 sort한다. O(nlgn)
    vector<int> sorted = unsorted;
    sort(sorted.begin(), sorted.end());
    // fenwicktree을 선언한다. O(n)
    MEASURETIME_fenwicktree fenwicktree(eleNum);
    // 각 n개의 원소에 대해 아래 작업을 수행한다. O(nlgn)
    for (int idx = 0; idx < eleNum; idx++) {
        // 원소의 sorted에서의 위치를 구한다. O(lgn)
        int position = lower_bound(sorted.begin(), sorted.end(), unsorted[idx]) - sorted.begin();
        // fenwicktree을 이용해 sorted중에 현재 원소보다 작거나 같은것의 개수를 구한다. O(1)
        int smaller = fenwicktree.pSum(position);
        //움직이는 횟수 = idx - 작거나 같은것의 개수
        result += idx - smaller;
        // fenwicktree을 갱신한다. O(lgn)
        fenwicktree.add(position);
    }
    return result;
}
void MEASURETIME() {
    /*설명 및 입력
    설명
        길이 N 인 수열 A[] 가 주어집니다.
        수열을 Insertion Sort 하는 과정에서 숫자들을 총 몇 번이나 옮기는지를 계산하는 프로그램을 작성하세요.
    입력
        입력의 첫 줄에는 테스트 케이스의 수 C (1 <= C <= 50) 가 주어집니다.
        각 테스트 케이스의 첫 줄에는 원 배열의 길이 N (1 <= N <= 50000) 이 주어집니다.
        그 다음 줄에 N개의 정수로 A의 원소 Ai가 주어집니다. (0 <= Ai < 1,000,000)
    출력
        각 테스트 케이스마다 한 줄에 A를 삽입정렬하는 과정에서 숫자를 옮기는 총 횟수를 출력합니다.
    제한조건
        2초, 256MB
    */
    /*힌트
        입력이 크므로, 빠른 입력을 이용한다.
        시간제한: n^2 미만이어야 한다.
        중복되는 입력이 있음에 유의하자.
    */
    /*
    아이디어 1
        설명:
            fenwicktree으로 구현한 부분합을 이용하여, insertion sort를 할 때, 현재 값보다 작은 값의 갯수가 몇개인지 알 수 있다.
        개념:
            unsorted는 O(nlgn)에 sort할 수 있다.
            unsorted의 각 원소의 sorted에서의 위치는, O(lgn)에 구할 수 있다.
            부분합을 이용하여, insertion sort를 할 때, 현재 값보다 작은 값의 갯수를  O(1)에 구할 수 있다.
                sorted[i]가 insertion sort 되었으면 1, 아니면 0으로 한다.
                ->부분합[i]는 sorted[0]~sorted[i]중 insertion sort된 것의 개수를 나타낸다.
                ->즉, input되는 원소가 몇번 움직여야 하는지를 알 수 있다.
            fenwicktree을 이용하여 부분합을 빠르게 구한다.
                부분합의 갱신은 기본적으로 O(n)이 걸린다.
                fenwicktree을 이용한다면, O(lgn)으로 갱신이 가능하다.
        구현:
            unsorted를 sort한다. O(nlgn)
            fenwicktree을 선언한다. O(n)
            각 n개의 원소에 대해 아래 작업을 수행한다. O(nlgn)
                원소의 sorted에서의 위치를 구한다. O(lgn)
                fenwicktree을 이용해 sorted중에 현재 원소보다 작거나 같은것의 개수를 구한다. O(lgn)
                    -> 움직이는 횟수 = idx - 작거나 같은것의 개수
                fenwicktree을 갱신한다. O(lgn)
        성능:
            time complexity: O(ngln)
            mem complexity: O(n)
        한계:
        피드백:
    책의 아이디어:
        fenwick tree를 이용해 풀기
            원소의 입력 범위가 제한적이므로, 각 원소의 등장 횟수를 나타내는 fenwicktree를 만들어서, 움직이는 횟수를 계산한다.
            한계점: 원소의 범위가 넓을수록 이용하기 어렵다. 원소의 범위가 넓다면 아이디어1 더 유용하다.
        segment tree를 이용해 풀기
            fenwick tree로 구현 가능한 것은 segment tree로도 구현이 가능하다.
            한계점: 구현이 복잡하다. 원소의 범위가 넓을수록 이용하기 어렵다.
        binary search tree(treap)을 이용하여 풀기
            treap을 이용하면 입력은 lgn, 출력은 O(1)에 가능하다. 원소의 범위의 제약을 받지 않는다.
            한계점: treap이 fenwick tree 보다는 복잡하다.
        merge sort를 이용해 풀기 - 수열의 반전(inversion)을 수를 세기
            수열의 반전(inversion): 큰 수가 작은 수보다 앞에있는 경우를 말한다.
            삽입 정렬 과정에서 숫자를 한번 옮길 때, 반전의 갯수가 하나씩 줄어든다.
                즉 수열의 반전의 수는 숫자를 옮기는 횟수이다.
            merge sort를 이용하기
                merge sort는 수열을 left와 right로 분류한다.
                수열의 반전의 경우의 수
                    1. 반전을 이루는 두 수가 모두 left에 포함되어 있다. -> 재귀
                    2. 반전을 이루는 두 수가 모두 right에 포함되어 있다. -> 재귀
                    3. 큰 수는 left, 작은 수는 right에 포함되어 있다.
                        -> merge sort의 merge과정에서 구할 수 있다.
                            left.first가 right.first보다 크다면, left.remain만큼 inversion이 추가된다.
                merge sort의 이러한 사용 방식은 다른 문제에도 이용할 수 있으니 참고하자
                한계점: merge sort를 직접 구현하므로 구현이 약간 복잡하다.
    */
    // Sol
    int testCase;
    cin >> testCase;
    //각 테스트케이스
    while (testCase--) {
        int eleNum;
        vector<int> unsorted;
        MEASURETIME_Input(eleNum, unsorted);
        auto result = MEASURETIME_Algo(eleNum, unsorted);
        // cout << "::::";
        cout << result << endl;
    }
}

int main(void) {
    // clock_t start,end;
    // start=clock();
    MEASURETIME();
    // end=clock();;
    // cout<<"time(s): "<<(double)(end-start)/CLOCKS_PER_SEC<<endl;
    return 0;
}