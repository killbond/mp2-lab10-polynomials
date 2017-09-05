#include "../include/Polynom.h"


void Polynom::Parser( string s_) {
    string s(s_);
    int length = s.length();
    int i = 0, coeff_ = 0, dx = 0, dy = 0, dz = 0,deg_=0;
    string co;

    if (s[0] == '+')
        s.erase(0, 1);

    if ((s[0] == '-') && ((s[1] == 'x') || (s[1] == 'y') || (s[1] == 'z')))
    {
        coeff_ = -1;
    }
    else if ((s[0] == '-') && (isdigit(s[1])))
    {
        i++;
        while (isdigit(s[i]))
        {
            co = co + s[i];
            i++;
        }

        istringstream(co) >> coeff_;
        coeff_ = -coeff_;
    }

    if ((s[0] == 'x') || (s[0] == 'y') || (s[0] == 'z'))
    {
        coeff_ = 1;
    }

    if (isdigit(s[0]))
    {
        while ((s[i])!='\0')
        {
            co = co + s[i];
            i++;
        }
        istringstream(co) >> coeff_;
    }

    co.clear();
    length = s.length();
    i = 0;
    while (i < length)
    {
        if ((s[i] == 'x') && (s[i + 1] == '^'))
        {
            int t = i+2;
            while (isdigit(s[t]))
            {
                co += s[t++];
                if (t == length)
                    break;
            }
            istringstream(co) >> dx;
            if (dy > 9) throw ("Degree must be <10");
            co.clear();
        }
        if ((s[i] == 'x') && (s[i + 1] != '^')) dx = 1;
        if ((s[i] == 'y') && (s[i + 1] == '^'))
        {
            int t = i + 2;
            while (isdigit(s[t]))
            {
                co += s[t++];
                if (t == length)
                    break;
            }
            istringstream(co) >> dy;
            if (dy > 9) throw ("Degree must be <10");
            co.clear();
        }
        if ((s[i] == 'y') && (s[i + 1] != '^')) dy = 1;
        if ((s[i] == 'z') && (s[i + 1] == '^'))
        {
            int t = i + 2;
            while (isdigit(s[t]))
            {
                co += s[t++];
                if (t == length)
                    break;
            }
            istringstream(co) >> dz;
            if (dz > 9) throw ("Degree must be <10");
            co.clear();
        }
        if ((s[i] == 'z') && (s[i + 1] != '^')) dz = 1;
        i++;
    }
    deg_ = dx * 100 + dy * 10 + dz;
    (*this).AddMonom(coeff_, deg_);
}

Polynom::Polynom()
{
    head=NULL;
}

Polynom::~Polynom()
{
    Clean();
}

Polynom:: Polynom(const Polynom &p)
{
    head = new Monom;
    head->SetNext(NULL);
    Monom *cur = new Monom;
    cur = p.head;
    while (cur!=NULL)
    {
        AddMonom(cur->GetCoeff(),cur->GetDegree());
        cur = cur->GetNext();
    }
}

Monom* Polynom::GetHead()
{
    return head;
}

void Polynom::Clean()
{
    Monom *t=new Monom;
    while(head!=NULL)
    {
        t=head->GetNext();
        delete head;
        head=t;
    }
}

void Polynom::AddMonom(int a, int N)
{
    if (a==0) return;
    if (head == NULL) head = new Monom(a,N,NULL);
    else
    {
        if (head->GetDegree() < N)
        {
            Monom *tmp = new Monom(a,N,NULL);
            tmp->SetNext(head);
            head = tmp;
        }
        else
        {
            Monom *cur, *last;
            for (cur=head;cur!=NULL;cur=cur->GetNext())
            {
                if (cur->GetDegree() < N) break;
                if (cur->GetDegree() == N)
                {
                    if ((a+cur->GetCoeff())!=0) cur->SetCoeff(a+cur->GetCoeff());
                    else
                    {
                        Monom *tmp = head;
                        if (cur==head) head = cur->GetNext();
                        else
                        {
                            while (tmp->GetNext()!=cur) tmp=tmp->GetNext();
                            tmp->SetNext(cur->GetNext());
                        }
                        delete cur;
                    }
                    return;
                }
                last = cur;
            }
            if (cur != NULL)
            {
                Monom *p = new Monom(a,N,cur);
                last->SetNext(p);
            }
            else
            {
                Monom *p = new Monom(a,N,NULL);
                last->SetNext(p);
            }
        }
    }
}


Polynom& Polynom:: operator+(const Polynom &p) const
{
    Polynom *res = new Polynom(*this);
    Monom *t=p.head;
    while (t!=NULL)
    {
        (*res).AddMonom(t->GetCoeff(),t->GetDegree());
        t=t->GetNext();
    }
    return *res;
}

Polynom& Polynom:: operator-(const Polynom &p) const
{
    Polynom *res = new Polynom(*this);
    Monom *t=p.head;
    while (t!=NULL)
    {
        (*res).AddMonom(-t->GetCoeff(),t->GetDegree());
        t=t->GetNext();
    }
    return *res;
}

Polynom& Polynom::operator*(const Polynom &p) const
{
    Polynom *res = new Polynom;
    Polynom q(*this);
    for (Monom *t1=p.head;t1!=NULL;t1=t1->GetNext())
        for (Monom *t2=q.GetHead();t2!=NULL;t2=t2->GetNext())
        {
            int dx,dy,dz;
            dx=(t1->GetDegree())%10 + (t2->GetDegree())%10;
            dy=((t1->GetDegree())/10)%10 + ((t2->GetDegree())/10)%10;
            dz=(t1->GetDegree())/100 + (t2->GetDegree())/100;
            if (dx>9||dy>9||dz>9)
                throw ("Result degree must be < 10");
            else (*res).AddMonom(t1->GetCoeff() * t2->GetCoeff(), t1->GetDegree() + t2->GetDegree());
        }
    return *res;
}

Polynom& Polynom:: operator=(const Polynom &p)
{
    this->Clean();
    head=p.head;
    Monom *l1=p.head;
    Monom *l2=(*this).GetHead();
    l2=l1;
    while (l1!=NULL)
    {
        l2=l1;
        l1=l1->GetNext();
        l2=l2->GetNext();
    }
    return *this;
}

bool Polynom:: operator==(const Polynom &p) const
{
    Polynom *q = new Polynom(p);
    if (head==NULL)
    {
        if (q->head==NULL) return true;
        else return false;
    }
    Monom *t1=head;
    Monom *t2=q->head;
    int flag(1);
    while (t1!=NULL)
    {
        if ((t1->GetCoeff()!=t2->GetCoeff())||(t1->GetDegree()!=t2->GetDegree()))
        {
            flag=0;
            break;
        }
        t1=t1->GetNext();
        t2=t2->GetNext();
    }
    if (flag==1) return true;
    else return false;
}