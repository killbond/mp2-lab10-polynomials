#include "../include/Monom.h"


Monom::Monom(int coeff_,int deg_,Monom *next_)
{
    SetDegree(deg_);
    SetCoeff(coeff_);
    SetNext(next_);
}

Monom::Monom(const Monom &m)
{
    SetDegree(m.deg);
    SetCoeff(m.coeff);
    SetNext(m.next);
}

void Monom::SetCoeff(int coeff_)
{
    coeff=coeff_;
}

int Monom::GetCoeff()
{
    return coeff;
}

void Monom::SetDegree(int deg_)
{
    if ((deg_>=0) && (deg_<1000)) deg=deg_;
    else if (deg_<0) throw "Степень должна быть положительной ";
    else if (deg_>10) throw "Степень должна быть < 10 ";
}

int Monom::GetDegree()
{
    return deg;
}
void Monom::SetNext(Monom *_next)
{
    next=_next;
}

Monom* Monom::GetNext()
{
    return next;
}

Monom& Monom::operator=(const Monom &m)
{
    SetCoeff(m.coeff);
    SetDegree(m.deg);
    return *this;
}


bool Monom::operator==(const Monom &m) const
{
    if ((coeff==m.coeff)&&(deg==m.deg)) return true;
    else return false;
}