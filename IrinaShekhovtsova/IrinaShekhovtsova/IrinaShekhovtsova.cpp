// IrinaShekhovtsova.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <fstream>
#include <string> 
#include <vector>
using namespace std;
struct Pipeline
{
    string ID = "NULL";
    double length;
    int diameter;
    bool repair = false;
};
struct CompressorStation
{
    string ID = "NULL";
    string Name = "NULL";
    int shops;
    int shops_working = 0;
    double efficiency;
};
int CheckInt(int min, int max)
{
    double x;
    while ((cin >> x).fail() || x<min || x>max || x - (int)x != 0)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type again in the range from " << min << " to " << max << ": ";
    }
    return (int)x;
}
double CheckDouble(double min, double max)
{
    double x;
    while ((cin >> x).fail() || x<min || x>max)
    {
        cin.clear();
        cin.ignore(10000, '\n');
        cout << "Type again in the range from " << min << " to " << max << ": ";
    }
    return x;
}
Pipeline Create_Pipe()
{
    Pipeline newpipe;
    cout << "Type the length (0-2000): ";
    newpipe.length = CheckDouble(0,2000);
    cout << "Type the diametr (0-1420): ";
    newpipe.diameter = CheckInt(0,1420);
    return newpipe;
}
CompressorStation Create_Station()
{
    CompressorStation newstation;
    cout << "Type the name: ";
    cin >> newstation.Name;
    cout << "Type the amount of shops (0-200): ";
    newstation.shops = CheckInt(0,200);
    cout << "Type the efficiency (0-1): ";
    newstation.efficiency = CheckDouble(0,1);
    return newstation;
}
void PrintPipeline(const Pipeline& newpipe)
{
    cout << "The length: " << newpipe.length << "\n";
    cout << "The diametr: " << newpipe.diameter << "\n";
    (newpipe.repair == false) ? cout << "Not in repair\n" : cout << "In repair\n";
}
void PrintStation(const CompressorStation& newstation)
{
    cout << "The name: " << newstation.Name << "\n";
    cout << "The amount of shops: " << newstation.shops << "\n";
    cout << "The amount of working shops: " << newstation.shops_working << "\n";
    cout << "The efficiency: " << newstation.efficiency << "\n";
}
void ChangeStatus(bool& status)
{
    status = !status;
}
void EditStation(CompressorStation& newstation)
{
    cout << "To run a shop type 1, to stop a shop type 0: ";
    int n = CheckInt(0,1);
    if (newstation.shops_working == 0 && n == 0) cout << "There are no working shops" << endl;
    else if (newstation.shops_working == newstation.shops && n == 1) cout << "All shops are working" << endl;
    else if (n == 1) newstation.shops_working += 1; else newstation.shops_working -= 1;
}
void SavePipeToFile(ofstream& fout, const Pipeline& newpipe)
    {
        fout << newpipe.ID << endl << newpipe.length << endl << newpipe.diameter << endl << newpipe.repair << endl;
    }

void SaveStationToFile(ofstream& fout, const CompressorStation& newstation)
    {
        fout << newstation.ID << endl << newstation.Name << endl << newstation.shops << endl << newstation.shops_working << endl
            << newstation.efficiency << endl;
    }
Pipeline LoadPipeFromFile(ifstream& fin)
{
    Pipeline newpipe;
    fin >> newpipe.ID >> newpipe.length >> newpipe.diameter >> newpipe.repair;
    return newpipe;
}
CompressorStation LoadStationFromFile(ifstream& fin)
{
    CompressorStation newstation;
    fin >> newstation.ID >> newstation.Name >> newstation.shops >> newstation.shops_working >> newstation.efficiency;
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
        int i = CheckInt(0,10);
        switch (i)
        {
        case 1:
        {
            pipes.push_back(Create_Pipe());
            break;
        }
        case 2: 
        {
            if (pipes.size() != 0)
            {
                for (auto& pipe : pipes)
                    PrintPipeline(pipe);
            }
            else cout << "There aren't any added pipes" << endl;
            if (stations.size() != 0)
            {
                for (auto& station : stations)
                    PrintStation(station);
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
                for (Pipeline pipe : pipes)
                    SavePipeToFile(fout,pipe);
                fout << stations.size() << endl;
                for (CompressorStation station : stations)
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
                while (count--)
                    pipes.push_back(LoadPipeFromFile(fin));
                fin >> count;
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
            stations.push_back(Create_Station());
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