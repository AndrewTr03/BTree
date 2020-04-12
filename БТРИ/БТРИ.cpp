// БТРИ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

const int n = 2;        //2*n - максимальное количество ЭЛЕМЕНТОВ в листочке
static class Leaf
{
public:
    int quantity;
    int Value[10]; 
    Leaf* Node[10];
public:
    Leaf(int*);
    Leaf(int);
    void addVal(int);
    void Show();
};

Leaf::Leaf(int* Val)
{
    for (int i = 0; i < n; i++)
        this->Value[i] = *(Val + i);
}

Leaf::Leaf(int initial)
{
    this->Value[0] = initial;
    this->quantity = 1;
}

void Leaf::addVal(int what)
{
    if (this->quantity == 2 * n) { cout << "chlen" << endl; return; } //если количество больше то вызываем дележку листа
    else {
        for (int i = 0; i < this->quantity; i++)
            if (what < this->Value[i])
            {
                for (int j = this->quantity; j > i; j--)
                    this->Value[j] = this->Value[j - 1];
                this->Value[i] = what;
                break;
            }
            else if (i == quantity) this->Value[i] = what;
        this->quantity++;
    }
}

void Leaf::Show()
{
    for (int i = 0; i < this->quantity; i++) printf("%d ", this->Value[i]);
}


int main()
{
    Leaf Root(10);
    Root.addVal(8);
    Root.addVal(6);
    Root.addVal(9);
    Root.addVal(60);
    Root.Show();
    return(0);
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
