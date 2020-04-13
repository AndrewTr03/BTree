// БТРИ.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
// НАДО ДОБАВИТЬ
// 1) Чтобы программа сама искала куда добавлять число
// 2) Чтобы связи детей с родственниками добавлялилсь и делились правильно
// 3) Нормальный поиск элементов и указатель головы передвижной
// 4) Удаление

#include <iostream>
using namespace std;

const int n = 6;               //n - максимальное количество УКАЗАТЕЛЕЙ в листочке
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
    void newLeaf();             //создание нового листочка с образованием взаимных связей
    Leaf* searchRoot();         //ищет корень
    Leaf* searchVal(int);
    int childNum();
    void addNewVal(int);
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
    if (what > this->Value[this->quantity]) this->Value[this->quantity] = what;
    this->quantity++;
    if (this->quantity == n) { this->newLeaf(); return; }
}


void Leaf::newLeaf()
{
    int center = n/2;                                                               //узнаём индекс элемента посередине
    Leaf* Brother = new Leaf(this->Value[center + 1]);                          //создаём брата для листа, в основе элмент после серединного
    if (this->Parent != NULL)
    {
        this->Parent->addVal(this->Value[center]);                                  //если есть предок то добавляем в предок
        Brother->Parent = this->Parent;
        int ChildNum = this->childNum();
        for (int i = n + 1; i > ChildNum + 1; i--)
            this->Parent->Child[i] = this->Parent->Child[i - 1];
        this->Parent->Child[ChildNum + 1] = Brother;

        this->Value[center] = 0;
        this->Value[center + 1] = 0;
        for (int i = center + 2; i < this->quantity; i++)                           //переносим остаток значений в брата
        {
            Brother->addVal(this->Value[i]);
            this->Value[i] = 0;
            this->quantity--;
        }
        this->quantity = this->quantity - 2;
    }
    else
    {
        Leaf* Batya = new Leaf(this->Value[center]);                                //создаём нового предка, в основе которого серединный элемент
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

Leaf* Leaf :: searchRoot()
{
    Leaf* lost = this;
    while (lost->Parent != NULL)
        lost = lost->Parent;
    return(lost);
}

Leaf* Leaf::searchVal(int what)
{
    Leaf* found = this->searchRoot();
    while (found->Child[0] != NULL)
    {
        for (int i = 0; i < found->quantity; i++)
        {
            if (what <= found->Value[i]) found = found->Child[i];
            break;
        }
    if (what > found->Value[found->quantity - 1]) found = found->Child[found->quantity];
    }
    return(found);
}

int Leaf::childNum()
{
    Leaf* buff;
    int i = 0;
    if (this->Parent != NULL)
        buff = this->Parent;
    else return(0);
    while (buff->Child[i] != this) i++;
    return i;
}

void Leaf::addNewVal(int what)
{
    Leaf* found = this->searchVal(what);
    for (int i = 0; i < found->quantity; i++)
       if (what <= found->Value[i])
       {
               for (int j = found->quantity; j > i; j--)
                   found->Value[j] = found->Value[j - 1];
               found->Value[i] = what;
               break;
       }
   if (what > found->Value[found->quantity]) found->Value[found->quantity] = what;
   found->quantity++;
   if (found->quantity == n) { found->newLeaf(); return; }
}

void Leaf::Show()
{
    for (int i = 0; i < this->quantity; i++) printf("%d ", this->Value[i]);
}


int main()
{
    Leaf Root(10);
    Root.addNewVal(8);
    Root.addNewVal(60);
    Root.addNewVal(6);
    Root.addNewVal(9);
    Root.addNewVal(40);
    Root.addNewVal(4);
    Root.addNewVal(3);
    Root.addNewVal(2);
    Leaf* Main = Root.searchRoot();
    Main->Child[1]->Show();
    printf("\n");
    Root.Show();
    printf("\n");
    Root.Parent->Show();
    printf("\n");
    Root.Parent->Child[2]->Show();
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
