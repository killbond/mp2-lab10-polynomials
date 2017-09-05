//
// Created by user on 05.09.17.
//

#ifndef POLYNOMIALS_MONOM_H
#define POLYNOMIALS_MONOM_H


#include <iostream>
#include <sstream>
#include <locale>

using namespace std;
class Monom
{
    double coeff;
    int deg;
    Monom *next;
public:
    explicit Monom(int = 0, int = 0, Monom* = NULL);
    Monom(const Monom &m);
    void SetCoeff(int coeff);
    int GetCoeff();
    void SetDegree(int deg);
    int GetDegree();
    void SetNext(Monom *_next);
    Monom* GetNext();
    Monom& operator=(const Monom &m);
    bool operator==(const Monom &m) const;
};


#endif //POLYNOMIALS_MONOM_H
