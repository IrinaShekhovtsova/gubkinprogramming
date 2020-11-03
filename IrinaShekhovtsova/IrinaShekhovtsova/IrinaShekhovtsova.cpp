// IrinaShekhovtsova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"
using namespace std;

void ChangeStatus(bool& status)
{
    status = !status;
}
void SavePipeToFile(ofstream& fout, const Pipeline& newpipe)
    {
        fout << newpipe.length << endl << newpipe.diameter << endl << newpipe.repair << endl;
    }

void SaveStationToFile(ofstream& fout, const CompressorStation& newstation)
    {
        fout << newstation.Name << endl << newstation.shops << endl << newstation.shops_working << endl
            << newstation.efficiency << endl;
    }
Pipeline LoadPipeFromFile(ifstream& fin)
{
    Pipeline newpipe;
    fin >> newpipe.length >> newpipe.diameter >> newpipe.repair;
    return newpipe;
}
CompressorStation LoadStationFromFile(ifstream& fin)
{
    CompressorStation newstation;
    fin >> newstation.Name >> newstation.shops >> newstation.shops_working >> newstation.efficiency;
    return newstation;
}
template <class T>
void DeleteObject(vector <T>& array)
{
    cout << "Enter ID: ";
    int ID = CheckInt(1001, T::maxID);
    unsigned int index = 0;
    bool ID_exist = false;
    for (auto& object : array)
    {
        if (object.ID == ID) {
            ID_exist = true;
            array.erase(array.begin() + index);
        }
        ++index;
    }
    if (ID_exist == false) cout << "There is no object with ID " << ID << endl;
}
template <class T>
T& SelectObject(vector <T>& array)
{
    cout << "Enter index: ";
    unsigned int index = CheckInt(1,array.size());
    return array[index-1];
}
template <class T>
T& SelectObjectbyID(vector <T>& array)
{
    cout << "Enter ID: ";
    unsigned int ID = CheckInt(1001, T::maxID);
    unsigned int index = 0;
    for (auto& object : array)
    {
        if (object.ID == ID) return array[index];
        ++index;
    }
}
template <class T, class T_class>
using Filter = bool(*)(const T_class& station, T argument);
bool CheckbyID(const Pipeline& pipe, int argument)
{
    return pipe.ID == argument;
}
bool CheckbyRepair(const Pipeline& pipe, bool argument)
{
    return pipe.repair == argument;
}
bool CheckbyName(const CompressorStation& station, string argument)
{
    return station.Name == argument;
}
bool CheckbyPercentage(const CompressorStation& station, int argument)
{
    int percentage_unutilised_shops = 100 - int(100 * station.efficiency);
    return percentage_unutilised_shops == argument;
}
template <class T, class T_class>
vector <int> FindbyFilter(const vector <T_class>& array, Filter<T, T_class> f, T argument)
{
    vector <int> res;
    int i = 0;
    for (auto& object : array) {
        if (f(object, argument)) res.push_back(i);
        i++;
    }
    return res;
}
void PrintMenu()
{
    cout << "1. Input pipeline" << endl
        << "2. View all objects" << endl
        << "3. Save to file" << endl
        << "4. Load from file" << endl
        << "5. Delete pipeline" << endl
        << "6. Input station" << endl
        << "7. Edit station" << endl
        << "8. Search pipelines by filter" << endl
        << "9. Search compressor stations by filter" << endl
        << "10. Burst editing of pipelines" << endl
        << "11. Delete compressor station" << endl
        << "0. Exit" << endl;
}
void PrintOption(string option1, string option2)
{
    cout << option1 << endl
        << option2 << endl
        << "0. Return to menu" << endl;
}
int main()
{
    vector <Pipeline> pipes;
    vector <CompressorStation> stations;
    vector <int> pipes_for_editing;
    while (true)
    {
        PrintMenu();
        int i = CheckInt(0,11);
        switch (i)
        {
        case 1:
        {
            Pipeline pipe;
            cin >> pipe;
            pipes.push_back(pipe);
            break;
        }
        case 2: 
        {
            if (pipes.size() != 0)
            {
                for (const auto& pipe : pipes)
                    cout << pipe;
            }
            else cout << "There aren't any added pipes" << endl;
            if (stations.size() != 0)
            {
                for (const auto& station : stations)
                    cout << station;
            }
            else cout << "There aren't any added stations" << endl;
            break; 
        }
        case 3: 
        {
            ofstream fout;
            fout.open("data1.txt", ios::out);
            if (fout.is_open())
            {
                fout << pipes.size() << endl;
                for (const auto& pipe : pipes)
                    SavePipeToFile(fout, pipe);
                fout << stations.size() << endl;
                for (const auto& station : stations)
                    SaveStationToFile(fout, station);
                fout.close();
            }
            break; 
        }
        case 4: 
        {
            ifstream fin;
            fin.open("data1.txt", ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                pipes.reserve(count);
                while (count--)
                    pipes.push_back(LoadPipeFromFile(fin));

                fin >> count;
                stations.reserve(count);
                while (count--)
                    stations.push_back(LoadStationFromFile(fin));    
                fin.close();
            }
            break; 
        }
        case 5: 
        {
            if (pipes.size() != 0) DeleteObject(pipes); else cout << "There aren't any added pipes" << endl;
            break; 
        }
        case 6:
        {
            CompressorStation station;
            cin >> station;
            stations.push_back(station);
            break;
        }
        case 7:
        {
            if (stations.size() != 0)
                EditStation(SelectObject(stations));
            else cout << "There aren't any added stations" << endl;
            break;
        }
        case 8:
        {
            bool MenuOpened = false;
            if (pipes.size() != 0) MenuOpened = true; else cout << "There aren't any added pipes" << endl;
            while (MenuOpened)
            {
                PrintOption("1. Search pipelines by ID", "2. Search pipelines in repair");
                int j = CheckInt(0, 2);
                switch (j)
                {
                case 1:
                {
                    pipes_for_editing.resize(0);
                    cout << "Enter ID: ";
                    int ID = CheckInt(1001, Pipeline::maxID);
                    for (int& index : FindbyFilter(pipes, CheckbyID, ID))
                    {
                        cout << pipes[index];
                        pipes_for_editing.push_back(index);
                    }
                    break;
                }
                case 2:
                {
                    pipes_for_editing.resize(0);
                    for (int& index : FindbyFilter(pipes, CheckbyRepair, true))
                    {
                        cout << pipes[index];
                        pipes_for_editing.push_back(index);
                    }
                    break;
                }
                case 0:
                {
                    MenuOpened = false;
                    break;
                }
                default: cout << "Wrong action!" << endl;
                }
            }
            break;
        }
        case 9:
        {
            bool MenuOpened = false;
            if (stations.size() != 0) MenuOpened = true; else cout << "There aren't any added stations" << endl;
            while (MenuOpened)
            {
                PrintOption("1. Search compressor stations by name", "2. Search compressor stations by percentage of unutilised shops");
                int j = CheckInt(0, 2);
                switch (j)
                {
                case 1:
                {
                    cout << "Enter name: ";
                    string name;
                    cin >> name;
                    for (int& index : FindbyFilter(stations, CheckbyName, name))
                        cout << stations[index];
                    break;
                }
                case 2:
                {
                    cout << "Enter percentage (0-100): ";
                    int percentage = CheckInt(0, 100);
                    for (int& index : FindbyFilter(stations, CheckbyPercentage, percentage))
                        cout << stations[index];
                    break;
                }
                case 0:
                {
                    MenuOpened = false;
                    break;
                }
                default: cout << "Wrong action!" << endl;
                }
            }
            break;
        }
        case 10:
        {
            bool MenuOpened = true;
            while (MenuOpened)
            {
                PrintOption("1. Editing all found pipelines", "2. Editing by choice");
                int j = CheckInt(0, 2);
                switch (j)
                {
                case 1:
                {
                    if (pipes_for_editing.size() != 0)
                    {
                        for (int& index : pipes_for_editing)
                            ChangeStatus(pipes[index].repair);
                    }
                    else cout << "There aren't any pipes for editing" << endl;
                    break;
                }
                case 2:
                {
                    cout << "Type amount of pipes to edit: ";
                    int n = CheckInt(1, pipes.size());
                    for (int i = 0; i < n; ++i)
                        ChangeStatus(SelectObjectbyID(pipes).repair);
                    break;
                }
                case 0:
                {
                    MenuOpened = false;
                    break;
                }
                default: cout << "Wrong action!" << endl;
                }
            }
            break;
        }
        case 11:
        {
            if (stations.size() != 0) DeleteObject(stations); else cout << "There aren't any added compressor stations" << endl;
            break;
        }
        case 0:
        {
            return 0;
            break;
        }
        default: cout << "Wrong action!" << endl;
        }
    }
}