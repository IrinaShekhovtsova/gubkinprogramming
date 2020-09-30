// IrinaShekhovtsova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

/*
#include <iostream>

int main()
{
    std::cout << "Hello World!\n";
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
*/

/*
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello World" << endl;
    int ch;
    cin >> ch;
    cout << 10 / ch;
    return 0;
}
*/

#include <iostream>
#include <stdlib.h>
#include <fstream>
using namespace std;
struct Pipeline
{
    string ID = "NULL";
    float dlina;
    float diam;
    bool remont = false;
};
struct KompressorStation
{
    string ID = "NULL";
    string Name = "NULL";
    float plants;
    float plants_working;
    float efficiency;
};
float CheckInput(float x)
{
      if (cin.fail() || x < 0)
        {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Try to type again: ";
            cin >> x;
            x = CheckInput(x);
        }
        else
        {
            cin.ignore(1000, '\n');
            return x;
        }
      return x;
}
float CheckEfficiency(float x)
{
    if (cin.fail() || x <= 0 || x > 1)
    {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "Try to type again: ";
        cin >> x;
        CheckInput(x);
    }
    else
    {
        cin.ignore(1000, '\n');
        return x;
    }
}
Pipeline Create_Pipe()
{
    Pipeline newpipe;
    while (true)
    {
        cout << "Type the length: ";
        cin >> newpipe.dlina;
        newpipe.dlina = CheckInput(newpipe.dlina);
        cout << "Type the diametr: ";
        cin >> newpipe.diam;
        newpipe.diam = CheckInput(newpipe.diam);
        break;
    }
    return newpipe;
}
KompressorStation Create_Station()
{
    KompressorStation newstation;
    cout << "Type the amount of plants: ";
    cin >> newstation.plants;
    newstation.plants = CheckInput(newstation.plants);
    cout << "Type the amount of working plants: ";
    cin >> newstation.plants_working;
    newstation.plants_working = CheckInput(newstation.plants_working);
    cout << "Type the efficiency: ";
    cin >> newstation.efficiency;
    newstation.efficiency = CheckEfficiency(newstation.efficiency);
    return newstation;
}
void PrintPipeline(const Pipeline& newpipe)
{
    cout << "The length: " << newpipe.dlina << "\n";
    cout << "The diametr: " << newpipe.diam << "\n";
    (newpipe.remont == false) ? cout << "Not in repair\n" : cout << "In repair\n";
}
void PrintStation(const KompressorStation& newstation)
{
    cout << "The amount of plants: " << newstation.plants << "\n";
    cout << "The amount of working plants: " << newstation.plants_working << "\n";
    cout << "The efficiency: " << newstation.efficiency << "\n";
}
void ChangeStatus(bool& status)
{
    status = !status;
}
void SaveToFile1(const Pipeline& newpipe)
{
    ofstream fout;
    fout.open("data1.txt", ios::out);
    if (fout.is_open())
    {
        fout << newpipe.ID << endl << newpipe.dlina << endl << newpipe.diam << endl << newpipe.remont << endl;
        fout.close();
    }
}
void SaveToFile2(const KompressorStation& newstation)
{
    ofstream fout;
    fout.open("data2.txt", ios::out);
    if (fout.is_open())
    {
        fout << newstation.ID << endl << newstation.Name << endl << newstation.plants << endl << newstation.plants_working << endl
            << newstation.efficiency << endl;
        fout.close();
    }
}
Pipeline LoadFromFile1()
{
    Pipeline newpipe;
    ifstream fin;
    fin.open("data1.txt",ios::in);
    if (fin.is_open())
    {
        fin >> newpipe.ID;
        fin >> newpipe.dlina;
        fin >> newpipe.diam;
        fin >> newpipe.remont;
        fin.close();
    }
    return newpipe;
}
KompressorStation LoadFromFile2()
{
    KompressorStation newstation;
    ifstream fin;
    fin.open("data2.txt",ios::in);
    if (fin.is_open())
    {
        fin >> newstation.ID >> newstation.Name >> newstation.plants >> newstation.plants_working >> newstation.efficiency;
        fin.close();
    }
    return newstation;
}
void PrintMenu()
{
    cout << "1. Input pipeline" << endl
        << "2. Print pipeline" << endl
        << "3. Save to file" << endl
        << "4. Load from file" << endl
        << "5. Edit pipeline" << endl
        << "0. Exit" << endl;
}
int main()
{
    Pipeline pipe1;
    bool ability = false;
    while (true)
    {
        PrintMenu();
        int i = 0;
        cin >> i;
        i = CheckInput(i);
        switch (i)
        {
        case 1:
        {
            ability = true;
            pipe1 = Create_Pipe();
            break;
        }
        case 2: 
        {
            if (ability) PrintPipeline(pipe1);  else cout << "Pipeline wasn't created\n";
            break; 
        }
        case 3: 
        {
            if (ability) SaveToFile1(pipe1); else cout << "Pipeline wasn't created\n";
            break; 
        }
        case 4: 
        {
            ability = true;
            pipe1 = LoadFromFile1();
            break; 
        }
        case 5: 
        {
            if (ability) ChangeStatus(pipe1.remont); else cout << "Pipeline wasn't created\n";
            break; 
        }
        case 0: return 0;
            break;
        default: cout << "Wrong action!" << endl;
        }
    }
}