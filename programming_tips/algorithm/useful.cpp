#include "useful.h"

//"에라스토테네스의 채"와 bitmask를 이용한 prime 구하기
bool useful_isPrime(int num, const vector<unsigned char>& eratosthenes) {
    // eratosthenes를 따로 입력하지 않았다면, 스스로 구하고 prime 여부를 반환한다.
    if (eratosthenes.empty()) {
        auto tmp = useful_eratosthenes(num);
        return tmp[num >> 3] & (1 << (num & 7));
    }
    return eratosthenes[num >> 3] & (1 << (num & 7));
}
bool useful_setComposite(vector<unsigned char>& eratosthenes, int num) { return eratosthenes[num >> 3] &= (~(1 << (num & 7))); }
vector<unsigned char> useful_eratosthenes(int num) {
    //한칸에 8비트씩 저장, num의 위치는 arr[num/8] & (1<<(num&7)), (num+7)/8 은 num을 8로 나눈것의 올림
    vector<unsigned char> eratosthenes((num + 7) / 8, 255);
    // 0,1,2, 짝수 처리
    useful_setComposite(eratosthenes, 0);
    useful_setComposite(eratosthenes, 1);
    for (int i = 4; i <= num; i += 2) {
        useful_setComposite(eratosthenes, i);
    }
    //에라스토테네스의 채, 짝수는 다 제외시킨다.
    int sqrtNum = sqrt(num);
    for (int i = 3; i <= sqrtNum; i += 2) {
        if (useful_isPrime(i, eratosthenes)) {
            for (int j = i * i; j <= num; j += i) {
                useful_setComposite(eratosthenes, j);
            }
        }
    }
    // return
    return eratosthenes;
}

//순열과 조합
vector<vector<int>> useful_getPermutation(vector<int> set) {
    //기저
    if (set.empty()) {
        return vector<vector<int>>();
    }
    // next_permutation함수는 더 높은(후순위)순열을 찾는 함수
    // set의 모든 순열을 찾으려면, 오름차순 정렬을 해주어야 한다.
    sort(set.begin(), set.end());
    //모든 순열 찾기
    vector<vector<int>> permutations;
    do {
        permutations.push_back(set);
    } while (next_permutation(set.begin(), set.end()));
    return permutations;
}
vector<vector<int>> useful_getCombination(vector<int> set, int select) {
    //기저
    int total = set.size();
    if (set.empty()) {
        return vector<vector<int>>();
    }
    if (total < select) {
        cout << "select exceed total" << endl;
        return vector<vector<int>>();
    }
    //순서과 상관없는 조합, select개의 1과 (set size-select)개의 0을 만들고, 0과1의 순열을 만든다.
    // set을 정렬할 필요는 없지만, 오름차순으로 조합을 만들기 위해 정렬을 해준다.
    sort(set.begin(), set.end());
    //모든 조합 찾기
    vector<vector<int>> combinations;
    vector<int> key;
    for (int i = 0; i < select; i++) {
        key.push_back(1);
    }
    for (int i = 0; i < total - select; i++) {
        key.push_back(0);
    }
    do {
        vector<int> tmp;
        for (int i = 0; i < total; i++) {
            if (key[i] == 1) {
                tmp.push_back(set[i]);
            }
        }
        combinations.push_back(tmp);
    } while (prev_permutation(key.begin(), key.end()));
    return combinations;
}

//문자열
vector<int> useful_KmpSearch(string& base, string& target) {
    vector<int> result;
    // failure function: 일치하지 않을경우, 살릴 수 있는 부분의 길이 : ex) totomato 에서 failure[4]=2, toto~ 에서 to~로
    // 살릴 수 있다.
    vector<int> failure = useful_getFailure(target);
    //탐색을 한다
    int match = 0;
    for (int idx = 0; idx < base.length(); idx++) {
        // base에서의 값과 target에서의 값이 일치하지 않는경우, target을 우측으로 민다.
        while (match > 0 && base[idx] != target[match]) {
            match = failure[match];  // match가 줄어든다 == target을 우측으로 민다.
        }
        //일치하는경우
        if (base[idx] == target[match]) {
            match++;
            if (match == target.length()) {
                result.push_back(idx - match + 1);
                match = failure[match];
            }
        }
    }
    //반환
    return result;
}
vector<int> useful_getFailure(string& str) {
    // result[len]=value: len개가 일치했을경우, value개만큼은 살릴 수 있다. totomato 에서 failure[4]=2
    vector<int> result(str.length() + 1, 0);
    int match(0);
    for (int idx = 1; idx < str.length(); idx++) {
        //일치하지 않을경우
        while (match > 0 && str[idx] != str[match]) {
            match = result[match];
        }
        //일치할경우
        if (str[idx] == str[match]) {
            match++;
            result[idx + 1] = match;
        }
    }
    return result;
}
vector<int> useful_getSuffixArr(string& str) {  // str[i:] 를 사전순으로 반환하는 접미사 배열
    int strLen = str.length();
    // group[i] = order, str[i:] 의 order
    vector<int> group(strLen + 1);  // comparator 연산시 group[strLen]까지 접근한다.
    group[strLen] = -1;             //문자열 a와 a+b는 사전순으로 a가 더 앞에 온다.
    for (int i = 0; i < strLen; i++) {
        // ASCII CODE 자체가 order라고 봐도 무방하다.
        group[i] = str[i];
    }
    // perm[order]=i, str[i:]의 order
    vector<int> perm(strLen);
    for (int i = 0; i < strLen; i++) {
        perm[i] = i;
    }
    //정렬
    int t = 1;
    while (t < strLen) {
        // 각 접미사의 2t만큼의 접두사를 비교하여 정렬한다.
        // lambda 함수: 앞선 t를 먼저 비교하고, 구분이 안된다면 2t까지 비교한다.
        sort(perm.begin(), perm.end(), [&group, t](int a, int b) -> bool {
            if (group[a] != group[b]) {
                return group[a] < group[b];
            }
            return group[a + t] < group[b + t];
        });
        if (t * 2 >= strLen) {
            break;
        }
        // group 갱신
        vector<int> tmpGroup(strLen);
        int prev = perm[0];
        tmpGroup[prev] = 0;
        for (int i = 1; i < strLen; i++) {
            int now = perm[i];
            bool isSmaller;
            if (group[prev] != group[now]) {
                isSmaller = group[prev] < group[now];
            } else {
                isSmaller = group[prev + t] < group[now + t];
            }
            if (isSmaller) {
                tmpGroup[now] = tmpGroup[prev] + 1;
            } else {
                tmpGroup[now] = tmpGroup[prev];
            }
            prev = now;
        }
        group = tmpGroup;
        t *= 2;
    }
    return perm;
}