// IrinaShekhovtsova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
#include <unordered_map>
#include <set>
#include <stack>
#include "utils.h"
#include "Pipeline.h"
#include "CompressorStation.h"
#include "Network.h"

using namespace std;

//bool cycle_exists(int start, vector <vector <int>> g, vector <int>& visit)
//{
//    visit[start] = 1; // 1 - не вышли из вершины
//    for (unsigned int j = 0; j < g[start].size(); j++)
//        if (g[start][j] != 0) {
//            if (visit[j] == 0)
//                if (cycle_exists(j, g, visit)) return true;
//                else if (visit[j] == 1)
//                    return true;
//        }
//    visit[start] = 2; // 2 - вышли из вершины
//    return false;
//}
//void dfs(int start, vector <vector <int>> g, vector <bool>& visited, stack <int> &stack)
//{
//    visited[start] = true;
//    for (unsigned int j = 0; j < g[start].size(); j++) 
//        if (g[start][j] != 0 && !visited[j])
//            dfs(j, g, visited, stack);
//    stack.push(start);
//}
//void topological_sort(int n, vector <vector <int>> g)
//{
//    stack <int> sort;
//    vector <bool> visited(n, false);
//    for (int i = 0; i < n; i++)
//        if (!visited[i])
//            dfs(i, g, visited, sort);
//    while (sort.empty() == false)
//    {
//        cout << sort.top() << " ";
//        sort.pop();
//    }
//
//}
template <class T>
void DeleteObject(unordered_map <int,T>& pairs, int& ID)
{
    cout << "Enter ID: ";
    ID = CheckInt(T::GetminID(), T::GetmaxID());
    if (pairs.count(ID) == 1) pairs.erase(ID);
    else cout << "There is no object with ID " << ID << endl;
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
vector <int> FindbyFilter(const unordered_map <int,T_class>& pairs, Filter<T, T_class> f, T argument)
{
    vector <int> res;
    for (auto& pair : pairs) 
        if (f(pair.second, argument)) res.push_back(pair.first);
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
        << "12. Input gas transportation network" << endl
        << "13. View gas transportation network" << endl
        << "14. Topological sort" << endl
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
    unordered_map <int, Pipeline> pipes;
    unordered_map <int, CompressorStation> stations;
    vector <int> pipes_for_editing;
    Network Net;
    while (true)
    {
        PrintMenu();
        int i = CheckInt(0, 14);
        switch (i)
        {
        case 1:
        {
            Pipeline pipe;
            cin >> pipe;
            pipes.emplace(pipe.GetID(), pipe);
            break;
        }
        case 2: 
        {
            if (pipes.size() != 0)
            {
                for (const auto& pair : pipes)
                    cout << pair.second;
            }
            else cout << "There aren't any added pipes" << endl;
            if (stations.size() != 0)
            {
                for (const auto& pair : stations)
                    cout << pair.second;
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
                for (const auto& pair : pipes)
                    fout << pair.second;
                fout << stations.size() << endl;
                for (const auto& pair : stations)
                    fout << pair.second;
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
                while (count--) {
                    Pipeline pipe;
                    fin >> pipe;
                    pipes.emplace(pipe.GetID(), pipe);
                }

                fin >> count; 
                while (count--) {
                    CompressorStation station;
                    fin >> station;
                    stations.emplace(station.GetID(), station);
                }
                fin.close();
            }
            else cout << "Opening the file for reading failed" << endl;
            break; 
        }
        case 5: 
        {
            int ID = 0;
            if (pipes.size() != 0) DeleteObject(pipes, ID); 
            else cout << "There aren't any added pipes" << endl;
            break; 
        }
        case 6:
        {
            CompressorStation station;
            cin >> station;
            stations.emplace(station.GetID(), station);
            break;
        }
        case 7:
        {
            cout << "Enter ID: ";
            int ID = CheckInt(CompressorStation::GetminID(), CompressorStation::GetmaxID());
            if (stations.size() != 0)
                if (stations.count(ID) == 1) EditStation(stations[ID]); 
                else cout << "There is no station with ID " << ID << endl;
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
                    for (int& ID : FindbyFilter(pipes, CheckbyID, ID))
                    {
                        cout << pipes[ID];
                        pipes_for_editing.push_back(ID);
                    }
                    break;
                }
                case 2:
                {
                    bool argument;
                    cout << "Type 0 or 1 [In repair - 1, not in repair - 0]: ";
                    cin >> argument;
                    pipes_for_editing.resize(0);
                    for (int& ID : FindbyFilter(pipes, CheckbyRepair, argument))
                    {
                        cout << pipes[ID];
                        pipes_for_editing.push_back(ID);
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
                    for (int& ID : FindbyFilter(stations, CheckbyName, name))
                        cout << stations[ID];
                    break;
                }
                case 2:
                {
                    cout << "Enter percentage (0-100): ";
                    double percentage = CheckDouble(0, 100);
                    for (int& ID : FindbyFilter(stations, CheckbyPercentage, percentage))
                        cout << stations[ID];
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
                        for (int& ID : pipes_for_editing)
                            if (pipes.count(ID) == 1) ChangeStatus(pipes[ID]);
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
                            cout << "Enter ID: ";
                        int ID = CheckInt(Pipeline::GetminID(), Pipeline::GetmaxID());
                        if (pipes.count(ID) == 1) ChangeStatus(pipes[ID]);
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
            int ID = 0;
            if (stations.size() != 0) {
                DeleteObject(stations, ID);
                for (auto& pair : pipes)
                {
                    if (pair.second.in == ID) pair.second.in = -1;
                    if (pair.second.out == ID) pair.second.out = 1;
                }
            }
            else cout << "There aren't any added compressor stations" << endl;
            break;
        }
        case 12:
        {
            if (pipes.size() < 1 && stations.size() < 2)
                cout << "There are not enough pipes/stations" << endl;
            else {
                Net.Active = true;
                bool input = true;
                while (input)
                {
                    cout << "Pave the way [Pipe Start CS Finish CS]: ";
                    int ID = CheckInt(Pipeline::GetminID(), Pipeline::GetmaxID());
                    pipes[ID].in = CheckInt(CompressorStation::GetminID(), CompressorStation::GetmaxID());
                    pipes[ID].out = CheckInt(CompressorStation::GetminID(), CompressorStation::GetmaxID());
                    cout << "Would you like to continue? [Yes-1, No-0]: ";
                    input = CheckInt(0, 1);
                }
                vector<int> Station_Connection;
                vector<vector<int>> graph = Net.AdjencyMatrix(pipes, Station_Connection);
                Net.ViewNetwork(graph, Station_Connection);
            }
            break;
        }
        case 13:
        {
            if (Net.Active) {
                vector<int> Station_Connection;
                vector<vector<int>> graph = Net.AdjencyMatrix(pipes, Station_Connection);
                Net.ViewNetwork(graph, Station_Connection);
            }
            else cout << "There is no gas transportation network" << endl;
            break;
        }
        case 14:
        {
            if (Net.Active) {
                vector<int> Station_Connection;
                vector<vector<int>> graph = Net.AdjencyMatrix(pipes, Station_Connection);
                Net.topological_sort(Station_Connection.size(), graph, Station_Connection);
            }
            else cout << "There is no gas transportation network" << endl;
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
