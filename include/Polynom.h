#ifndef POLYNOMIALS_POLINOM_H
#define POLYNOMIALS_POLINOM_H


#include "Monom.h"

class Polynom : public Monom
{
    Monom *head;
public:
    Polynom();
    ~Polynom();
    Polynom(const Polynom &p);
    void Clean();
    void AddMonom(int coeff, int deg);
    void Parser(string s);
    Polynom& operator+(const Polynom &p) const;
    Polynom& operator-(const Polynom &p) const;
    Polynom& operator*(const Polynom &p) const;
    Polynom& operator=(const Polynom &p);
    bool operator==(const Polynom &p) const;
    Monom* GetHead();
    friend istream& operator>>(istream &in, Polynom &p)
    {
        string input, monom;
        int deg_ = 0, coef_ = 0, i = 0;
        unsigned long length;
        Polynom tmp;

        in>>input;
        length = input.length();
        for (int j = 0; j < length; j++)
        {
            if ((input[j] >= 'А') && (input[j] <= 'я')) throw ("Полином содержит неверный символ");
            if ((input[j] >= 'A') && (input[j] <= 'w'))
            {
                if ((input[j] == '^') && (!isdigit(input[j + 1]))) throw ("Ошибка ввода");
                else continue;
            }
        }

        while (!input.empty())
        {
            if (input[0] == '-')
            {
                i = 1;
                monom = "-";
                while ((input[i] != '\0'))
                {
                    if (input[i] == '+') break;
                    if (input[i] == '-') break;
                    monom += input[i];
                    i++;
                }
                p.Parser(monom);
                unsigned long pos = input.find(monom);
                input.erase(pos, monom.size());
                monom.clear();
            }
            else if (input[0] == '+')
            {
                i = 1;
                monom = "+";
                while ((input[i] != '\0'))
                {
                    if (input[i] == '+') break;
                    if (input[i] == '-') break;
                    monom += input[i];
                    i++;
                }
                p.Parser( monom);
                unsigned long pos = input.find(monom);
                input.erase(pos, monom.size());
                monom.clear();
            }
            else
            {
                while ((input[i] != '\0'))
                {
                    if (input[i] == '+') break;
                    if (input[i] == '-') break;
                    monom += input[i];
                    i++;
                }
                p.Parser( monom);
                unsigned long pos = input.find(monom);
                input.erase(pos, monom.size());
                monom.clear();
            }
        }
        return in;
    }
    friend ostream& operator<<(ostream &out, const Polynom &p)
    {
        const Polynom &q(p);
        Monom *t = q.head;
        if (t==NULL)
        {
            out<<t->GetCoeff();
            return out;
        }
        if (t->GetNext()==NULL)
        {
            if (t->GetCoeff()==0)
            {
                out<<t->GetCoeff();
                return out;
            }
            else if (t->GetDegree()==0) out<<t->GetCoeff();
            else
            {
                if((t->GetCoeff()) ==-1 )	out << "-";
                else if ((t->GetCoeff()) != 1)	out << t->GetCoeff();

                if ((t->GetDegree() / 100) == 1) out << "x";
                else if (t->GetDegree() / 100) out << "x^" << t->GetDegree() / 100;

                if (((t->GetDegree() / 10) % 10) == 1) out << "y";
                else if ((t->GetDegree() / 10) % 10) out << "y^" << (t->GetDegree() / 10) % 10;

                if (t->GetDegree() % 10 == 1) out;
                else if (t->GetDegree() % 10) out << "z^" << t->GetDegree() % 10;
            }
            return out;
        }
        while (t->GetNext()!=NULL)
        {
            if (t->GetCoeff()==0) t=t->GetNext();
            else if (t->GetDegree()==0)
            {
                if (t->GetCoeff() > 0) out << t->GetCoeff();
                else out << t->GetCoeff();
                t=t->GetNext();
                if (t->GetCoeff() > 0) out << "+";
            }
            else
            {
                if ((t->GetCoeff()) == -1)	out << "-";
                else if ((t->GetCoeff()) != 1)	out<<t->GetCoeff();

                if ((t->GetDegree() / 100) == 1) out << "x";
                else if (t->GetDegree() / 100) out << "x^" << t->GetDegree() / 100;

                if (((t->GetDegree() / 10) % 10) == 1) out << "y";
                else if ((t->GetDegree() / 10) % 10) out << "y^" << (t->GetDegree() / 10) % 10;

                if (t->GetDegree() % 10 == 1) out << "z" ;
                else if (t->GetDegree() % 10) out << "z^" << t->GetDegree() % 10 ;

                t=t->GetNext();
                if (t->GetCoeff() > 0) out << "+";
            }
        }
        if (t->GetCoeff()==0) return out;
        else if (t->GetDegree()==0) out<<t->GetCoeff();
        else
        {
            if ((t->GetCoeff()) == -1)	out << "-";
            else if ((t->GetCoeff()) != 1)	out << t->GetCoeff();

            if ((t->GetDegree() / 100) == 1) out << "x";
            else if (t->GetDegree() / 100) out << "x^" << t->GetDegree() / 100;

            if (((t->GetDegree() / 10) % 10) == 1) out << "y";
            else if ((t->GetDegree() / 10) % 10) out << "y^" << (t->GetDegree() / 10) % 10;

            if (t->GetDegree() % 10 == 1) out << "z";
            else if (t->GetDegree() % 10) out << "z^" << t->GetDegree() % 10;

            if (t->GetCoeff() > 0) out << "+";
        }
        return out;
    }
};


#endif //POLYNOMIALS_POLINOM_H
