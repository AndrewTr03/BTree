// БТРИ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
using namespace std;

const int n = 5;               //n - максимальное количество УКАЗАТЕЛЕЙ в листочке
class Leaf
{
public:
    int quantity;               //текущее количество элементов в листочке
    int Value[10];              //массив со значениями
    Leaf* Child[10];            //массив с указателями
    Leaf* Parent;               //указатель на предка
public:
    Leaf(int);                  //для первого создания 
    void addVal(int);           //добавление значения
    void newLeaf();          //создание нового листочка с образованием взаимных связей
    void Show();
};

Leaf :: Leaf(int initial)
{
    this->Value[0] = initial;
    this->quantity = 1;
}

void Leaf :: addVal(int what)
{
        for (int i = 0; i < this->quantity; i++)
            if (what <= this->Value[i])
            {
                for (int j = this->quantity; j > i; j--)
                    this->Value[j] = this->Value[j - 1];
                this->Value[i] = what;
                break;
            }
        if (what > this->Value[this->quantity]) this->Value[quantity] = what;
        this->quantity++;
        if (this->quantity == n) { this->newLeaf(); return; }
}


void Leaf::newLeaf()
{
    int center = n/2;                                                               //узнаём индекс элемента посередине
    if (this->Parent != NULL) this->Parent->addVal(this->Value[center]);            //если есть предок то добавляем в предок
    else
    {
        Leaf* Batya = new Leaf(this->Value[center]);                                //создаём нового предка, в основе которого серединный элемент
        Leaf* Brother = new Leaf(this->Value[center + 1]);                          //создаём брата для листа, в основе элмент после серединного
        this->Parent = Batya;                                                       //указатели на родителей
        Brother->Parent = Batya;
        this->Value[center] = 0;
        this->Value[center + 1] = 0;
        for (int i = center + 2; i < this->quantity; i++)                           //переносим остаток значений в брата
        {
            Brother->addVal(this->Value[i]);
            this->Value[i] = 0;
            this->quantity--;
        }
        this->quantity = this->quantity - 2;
        for (int i = center + 1; i < n; i++)
        {
            Brother->Child[i - (center + 1)] = this->Child[i];
            this->Child[i] = NULL;
        }
        Batya->Child[0] = this;
        Batya->Child[1] = Brother;
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
    Root.addVal(60);
    Root.addVal(6);
    Root.addVal(9);
    printf("%d\n", Root.quantity);
    Root.Show();
    printf("\n");
    printf("%d\n", Root.Parent->quantity);
    Root.Parent->Show();
    printf("\n");
    printf("%d\n", Root.Parent->Child[1]->quantity);
    Root.Parent->Child[1]->Show();
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
