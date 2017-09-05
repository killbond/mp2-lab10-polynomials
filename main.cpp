#include <iostream>
#include "include/Polynom.h"

using namespace std;

int main()
{
    try
    {
        int f = 0;
        auto *p1 = new Polynom;
        cout << "Введите полином " << endl;
        cin >> (*p1);
        auto *p2 = new Polynom;
        cout << "Введите второй полином " << endl;
        cin >> (*p2);

        cout << "Первый полином p1=: " << endl << *p1 << endl;
        cout << "Второй полином p2: " << endl << *p2 << endl;
        cout << "Выберите операцию:" << endl;
        cout << "1. Сложение(p1+p2)" << endl;
        cout << "2. Вычитание(p1-p2)" << endl;
        cout << "3. Умножение(p1*p2)" << endl;
        cin >> f;
        switch (f)
        {
            case 1:
            {
                cout << "Результат: " << (*p1)+(*p2) << endl;
                break;
            }
            case 2:
            {
                cout << "Результат: " << (*p1)-(*p2) << endl;
                break;
            }
            case 3:
            {
                cout << "Результат: " << (*p1)*(*p2) << endl;
                break;
            }
            default:
            {
                cout << "Неверный выбор" << endl;
                break;
            }
        }
    }
    catch (const char* error)
    {
        cout << error << endl;
    }
    return 0;
}