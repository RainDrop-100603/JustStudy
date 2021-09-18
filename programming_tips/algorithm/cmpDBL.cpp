#include "cmpDBL.h"

int cmpDBL_abs(double a, double b, double absTolerance) {
    if (fabs(a - b) <= absTolerance) return 0;
    return a > b ? 1 : -1;
}
int cmpDBL_rel(double a, double b, double relTolerance) {
    if (fabs(a - b) <= max(fabs(a), fabs(b)) * relTolerance) return 0;
    return a > b ? 1 : -1;
}
int cmpDBL_absRel(double a, double b, double absTolerance, double relTolerance) {
    if (fabs(a - b) <= absTolerance) return 0;
    if (fabs(a - b) <= max(fabs(a), fabs(b)) * relTolerance) return 0;
    return a > b ? 1 : -1;
}
int cmpDBL_ULP(double a, double b, int ulpTolerance) {
    // bit를 double이 아닌 long long으로 해석하여(포인터 형변환), 두 값을 정수형태로 비교
    //  1ulp는 숫자의 크기에 따라 다르다 -> 상대범위 비교에 가깝다. 0에 가까울 경우 에러가 발생할 수 있다.
    double diff = a - b;
    long long na = *reinterpret_cast<long long*>(&a);  // a의 포인터를 long long으로 바꾸고, 그 값을 읽음
    long long nb = *reinterpret_cast<long long*>(&b);
    //부호비트를 비교, 부호가 다를경우 처리
    if ((na & 0x8000000000000000) != (nb & 0x8000000000000000)) {
        if (a == b)  // 0은 double에서 +0과 -0으로 처리되므로, 부호비트가 다를수도 있다.
            return 0;
        return diff > 0 ? 1 : -1;  //부호가 다르면 비교가 easy
    }
    long long ulpsDiff = abs(na - nb);  // ulps 비교
    if (ulpsDiff <= ulpTolerance) return 0;
    return (diff > 0) ? 1 : -1;
}
int cmpDBL_absULP(double a, double b, double absTolerance, int ulpTolerance) {
    double diff = a - b;
    // absolute
    if (fabs(diff) <= absTolerance) return 0;
    // unit in the last place
    long long na = *reinterpret_cast<long long*>(&a);  // a의 포인터를 long long으로 바꾸고, 그 값을 읽음
    long long nb = *reinterpret_cast<long long*>(&b);
    //부호비트를 비교, 부호가 다를경우 처리
    if ((na & 0x8000000000000000) != (nb & 0x8000000000000000)) {
        return diff > 0 ? 1 : -1;  //부호가 다르면 비교가 easy
    }
    long long ulpsDiff = abs(na - nb);  // ulps 비교
    if (ulpsDiff <= ulpTolerance) return 0;
    return (diff > 0) ? 1 : -1;
}
