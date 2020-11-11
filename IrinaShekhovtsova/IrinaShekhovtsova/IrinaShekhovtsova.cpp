// IrinaShekhovtsova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include "Pipeline.h"
#include "CompressorStation.h"
#include "utils.h"
using namespace std;

template <class T>
void DeleteObject(vector <T>& array)
{
    cout << "Enter ID: ";
    int ID = CheckInt(T::GetminID(), T::GetmaxID());
    unsigned int index = 0;
    bool ID_exist = false;
    for (auto& object : array)
    {
        if (object.GetID() == ID) {
            ID_exist = true;
            array.erase(array.begin() + index);
        }
        ++index;
    }
    if (ID_exist == false) cout << "There is no object with ID " << ID << endl;
}
template <class T>
T& SelectObjectbyID(vector <T>& array)
{
    cout << "Enter ID: ";
    int ID = CheckInt(T::GetminID(), T::GetmaxID());
    unsigned int index = 0;
    for (auto& object : array)
    {
        if (object.GetID() == ID) return array[index];
        ++index;
    }
}
template <class T, class T_class>
using Filter = bool(*)(const T_class& station, T argument);
bool CheckbyID(const Pipeline& pipe, int argument)
{
    return pipe.GetID() == argument;
}
bool CheckbyRepair(const Pipeline& pipe, bool argument)
{
    return pipe.GetRepairStatus() == argument;
}
bool CheckbyName(const CompressorStation& station, string argument)
{
    return station.GetName() == argument;
}
bool CheckbyPercentage(const CompressorStation& station, double argument)
{
    double percentage_unutilised_shops = 100*(1 - station.GetShopsWorking() / (double) station.GetShops());
    return abs(percentage_unutilised_shops-argument) < 0.001;
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
            string name_of_file;
            cout << "Enter the name of file: ";
            cin.ignore();
            getline(cin, name_of_file);
            fout.open(name_of_file, ios::out);
            if (fout.is_open())
            {
                fout << pipes.size() << endl;
                for (const auto& pipe : pipes)
                    fout << pipe;
                fout << stations.size() << endl;
                for (const auto& station : stations)
                    fout << station;
                fout.close();
            }
            else cout << "Opening the file for writing failed" << endl;
            break; 
        }
        case 4: 
        {
            ifstream fin;
            string name_of_file;
            cout << "Enter the name of file: ";
            cin.ignore();
            getline(cin, name_of_file);
            fin.open(name_of_file, ios::in);
            if (fin.is_open())
            {
                int count;
                fin >> count;
                pipes.reserve(count);
                while (count--) {
                    Pipeline pipe;
                    fin >> pipe;
                    pipes.push_back(pipe);
                }

                fin >> count;
                stations.reserve(count);  
                while (count--) {
                    CompressorStation station;
                    fin >> station;
                    stations.push_back(station);
                }
                fin.close();
            }
            else cout << "Opening the file for reading failed" << endl;
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
                EditStation(SelectObjectbyID(stations));
            else cout << "There aren't any added stations" << endl;
            break;
        }
        case 8:
        {
            bool MenuOpened = false;
            if (pipes.size() != 0) MenuOpened = true; else cout << "There aren't any added pipes" << endl;
            while (MenuOpened)
            {
                PrintOption("1. Search pipelines by ID", "2. Search pipelines in repair/not in repair");
                int j = CheckInt(0, 2);
                switch (j)
                {
                case 1:
                {
                    pipes_for_editing.resize(0);
                    cout << "Enter ID: ";
                    int ID = CheckInt(Pipeline::GetminID(), Pipeline::GetmaxID());
                    for (int& index : FindbyFilter(pipes, CheckbyID, ID))
                    {
                        cout << pipes[index];
                        pipes_for_editing.push_back(index);
                    }
                    break;
                }
                case 2:
                {
                    bool argument;
                    cout << "Type 0 or 1 [In repair - 1, not in repair - 0]: ";
                    cin >> argument;
                    pipes_for_editing.resize(0);
                    for (int& index : FindbyFilter(pipes, CheckbyRepair, argument))
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
                    double percentage = CheckDouble(0, 100);
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
                            ChangeStatus(pipes[index]);
                    }
                    else cout << "There aren't any pipes for editing" << endl;
                    break;
                }
                case 2:
                {
                    if (pipes.size() != 0)
                    {
                        cout << "Type amount of pipes to edit: ";
                        int n = CheckInt(1, pipes.size());
                        for (int i = 0; i < n; ++i)
                            ChangeStatus(SelectObjectbyID(pipes));
                    }
                    else cout << "There aren't any added pipes" << endl;
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