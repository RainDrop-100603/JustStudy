#ifndef __DOUBLECONTROL_H__
#define __DOUBLECONTROL_H__

#include<iostream>
#include<cmath>

using namespace std;

class doubleControl{
  private:
    double absTolerance;
    double relTolerance;
    int ulpTolerance;
  public:
    //생성자
    doubleControl(double absTol=1e-10,double relTol=__DBL_EPSILON__, int ulpTol=4):absTolerance(absTol),relTolerance(relTol), ulpTolerance(ulpTol){}
    //-1: a<b, 0: a==b, 1: a>b
    int absolute(double a, double b, double absTol=-1); //작은 수 비교
    int relevance(double a, double b, double relTol=-1);//큰 수 비교
    int absRel(double a, double b, double absTol=-1, double relTol=-1);
    int unitInTheLastPlace(double a, double b, int ulpTol=-1);// 큰 수 비교
    int absULP(double a, double b, double absTol=-1, double ulpTol=-1);
};

#endif
