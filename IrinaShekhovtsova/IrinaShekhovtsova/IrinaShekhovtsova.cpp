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
    string ID;
    int dlina;
    int diam;
    bool remont = false;
};
struct Kompressor_Station
{
    string ID;
    string Name;
    int plant;
    int plant_working;
    float efficiency;
};

Pipeline Create_Pipe()
{
    Pipeline newpipe;
    cout << "Dlina: ";
    cin >> newpipe.dlina;
    cout << "Diametr: ";
    cin >> newpipe.diam;
    newpipe.ID = " ";
    return newpipe;
}

void VivodPipeline(Pipeline newpipe)
{
    cout << "Dlina: " << newpipe.dlina << "\n";
    cout << "Diametr: " << newpipe.diam << "\n";
}

void ChangeStatus(bool& status)
{
    status = !status;
}

void SaveToFile(Pipeline newpipe)
{
    ofstream fout;
    fout.open("data.txt");
    fout << newpipe.ID << endl << newpipe.dlina << endl << newpipe.diam << endl << newpipe.remont;
    fout.close();
}

Pipeline LoadFile()
{
    ifstream fin;
    fin.open("data.txt");
    Pipeline newpipe;
    fin >> newpipe.ID >> newpipe.dlina >> newpipe.diam >> newpipe.remont;
    fin.close();
    return newpipe;
}



int main()
{
   
    Pipeline pipe1;
    pipe1 = LoadFile();
    //pipe1 = Create_Pipe();
    VivodPipeline(pipe1);
   // ChangeStatus(pipe1.remont);
   // SaveToFile(pipe1);
    


   /* Kompressor_Station newstation;
    cin >> newstation.Name;
    cin >> newstation.plant;
    cin >> newstation.plant_working;
    cin >> newstation.efficiency; */
}