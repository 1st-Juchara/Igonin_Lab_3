#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CSs.h"
#include "SubFunc.h"

using namespace std;

vector<int> CSs::filterCS()
{
    vector <int> index;
    string name = "";
    int workshops = -1;
    cout << "1. Choose by filter \n2. Display all";
    if (tryChoose(1, 2) == 1)
    {
        cout << "1. Search by name \n2. All names";
        if (tryChoose(1, 2) == 1)
        {
            cout << "Name: ";
            inputString(cin, name);
            cout << endl;
        }

        cout << "1. Search by worksops status \n2. Any status";

        int number;
        auto percent_choose = [&number, &workshops](int x) -> bool {
            switch (number)
            {
            case 1:
                return x >= workshops;
                break;
            case 2:
                return x <= workshops;
                break;
            case 3:
                return x == workshops;
                break;
            default:
                return false;
                break;
            }
            };

        if (tryChoose(1, 2) == 1)
        {
            cout << "Choose percantage of online ws (0%..100%)";
            workshops = tryChoose(0, 100);

            cout << "Choose selection method:" << endl
                << "1. More than the selected percentage" << endl
                << "2. Less than the selected percentage" << endl
                << "3. According the selected percentage";
            number = tryChoose(1, 3);
        }

        for (int i = 0; i < Stations.size(); i++)
            if (((workshops == -1) or percent_choose(Stations[i].WSOn * 100 / Stations[i].WSCnt)) and inString(Stations[i].name, name))
                index.push_back(i);
    }
    else
        for (int i = 0; i < Stations.size(); i++)
            index.push_back(i);
    return index;
}

void CSs::ViewCS(const CS& Stations)
{
    cout << "\t\t" << "Name: " << Stations.name << ' ' << Stations.id << endl;
    cout << "\t\t" << "Number of workshops: " << Stations.WSCnt << endl;
    cout << "\t\t" << "Workshops online: " << Stations.WSOn << endl;
    cout << "\t\t" << "Payoff: " << Stations.payoff << endl;
    cout << endl;
}

void CSs::changeCS(const vector<int>& index)
{
    cout << "1. Change WS status\n2. Delete CS";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "1. Turn off workshops" << endl << "2. Turn on workshops";
        int inst = tryChoose(1, 2) == 1;
        cout << "How many?";
        int delta = tryChoose(0, 999999);
        for (int i = 0; i < index.size(); i++)
        {
            Stations[index[i]].WSOn = inst ? delta > Stations[index[i]].WSOn ? 0 : Stations[index[i]].WSOn - delta :
                delta + Stations[index[i]].WSOn > Stations[index[i]].WSCnt ? Stations[index[i]].WSCnt : delta + Stations[index[i]].WSOn;
        }
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
        {
            Stations.erase(Stations.begin() + index[i]);
        }
}

bool CSs::isExist()
{
    return Stations.size() > 0 ? true : false;
}

void CSs::ViewStations()
{
    if (isExist())
    {
        vector <int> index = filterCS();
        cout << "Stations:" << endl;
        for (int i = 0; i < index.size(); i++)
            ViewCS(Stations[index[i]]);
    }
}

void CSs::addCS()
{
    int id = --ID_max;
    int wsOn = 0;
    std::cout << "Enter CS name:\n\n> ";
    string name;
    inputString(cin, name);
    cout << endl;
    std::cout << "Enter count of workshops: ";
    int workshops = tryChoose(1, 10000);
    std::cout << "Enter station productivity (1..100): ";
    int prod = tryChoose(1, 100);
    Stations.push_back({ id, name, workshops, 0, prod });
}

void CSs::editCS()
{
    if (isExist()) {
        vector <int> index = filterCS();
        for (int i = 0; i < index.size(); i++)
        {
            cout << "Station " << i + 1 << endl;
            ViewCS(Stations[index[i]]);
        }
        vector <int> index_ch;
        choosingElements(index, index_ch);
        changeCS(index_ch);
    }
}

void CSs::CSDataOut(std::ofstream& fout)
{
    fout << ID_max << ' ';
    fout << Stations.size() << endl;
    for (int i = 0; i < Stations.size(); i++)
    {
        fout << Stations[i].name << endl;
        fout << Stations[i].id << ' ' << Stations[i].WSCnt << ' ' << Stations[i].WSOn << ' ' << Stations[i].payoff << endl;
    }
}

void CSs::CSDataIn(std::ifstream& in)
{
    in >> ID_max;
    int StationsCnt = 0;
    in >> StationsCnt;
    for (int i = 0; i < StationsCnt; i++)
    {
        in.ignore(10000, '\n');
        CS Station;
        getline(in, Station.name);
        in >> Station.id;
        in >> Station.WSCnt;
        in >> Station.WSOn;
        in >> Station.payoff;
        Stations.push_back(Station);
    }
}

