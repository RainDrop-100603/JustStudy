#ifndef __CMPDBL_H__
#define __CMPDBL_H__

#include <cmath>
#include <iostream>

using namespace std;

int cmpDBL_abs(double a, double b, double absTolerance = 1e-10);            //작은 수 비교
int cmpDBL_rel(double a, double b, double relTolerance = __DBL_EPSILON__);  //큰 수 비교
int cmpDBL_absRel(double a, double b, double absTolerance = 1e-10, double relTolerance = __DBL_EPSILON__);
int cmpDBL_ULP(double a, double b, int ulpTolerance = 4);  // 큰 수 비교
int cmpDBL_absULP(double a, double b, double absTolerance = 1e-10, int ulpTolerance = 4);

class cmpDBLclass {
   private:
    double absTolerance;
    double relTolerance;
    int ulpTolerance;

   public:
    //생성자
    cmpDBLclass(double absTol = 1e-10, double relTol = __DBL_EPSILON__, int ulpTol = 4)
        : absTolerance(absTol), relTolerance(relTol), ulpTolerance(ulpTol) {}
    //-1: a<b, 0: a==b, 1: a>b
    int absolute(double a, double b) { return cmpDBL_abs(a, b, absTolerance); }
    int relevance(double a, double b) { return cmpDBL_rel(a, b, relTolerance); }
    int absRel(double a, double b) { return cmpDBL_absRel(a, b, absTolerance, relTolerance); }
    int unitInTheLastPlace(double a, double b) { return cmpDBL_ULP(a, b, ulpTolerance); }
    int absULP(double a, double b) { return cmpDBL_absULP(a, b, absTolerance, ulpTolerance); }
};

#endif
