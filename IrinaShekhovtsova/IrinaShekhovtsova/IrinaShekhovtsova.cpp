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
T& SelectObject(vector <T>& array)
{
    cout << "Enter index: ";
    unsigned int index = CheckInt(1,array.size());
    return array[index-1];
}
void PrintMenu()
{
    cout << "1. Input pipeline" << endl
        << "2. View all objects" << endl
        << "3. Save to file" << endl
        << "4. Load from file" << endl
        << "5. Edit pipeline" << endl
        << "6. Input station" << endl
        << "7. Edit station" << endl
        << "0. Exit" << endl;
}
int main()
{
    vector <Pipeline> pipes;
    vector <CompressorStation> stations;
    while (true)
    {
        PrintMenu();
        int i = CheckInt(0,7);
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
            if (pipes.size() != 0)
                ChangeStatus(SelectObject(pipes).repair);
            else cout << "There aren't any added pipes" << endl;
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
        case 0:
        {
            return 0;
            break;
        }
        default: cout << "Wrong action!" << endl;
        }
    }
}