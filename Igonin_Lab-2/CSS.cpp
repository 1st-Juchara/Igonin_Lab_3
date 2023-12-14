#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "CSs.h"
#include "SubFunc.h"

using namespace std;

void CSs::addCS()
{
    WSOn = 0;
    std::cout << "Enter CS name:\n\n> ";
    inputString(cin, name);
    cout << endl;
    std::cout << "Enter count of workshops: ";
    WSCnt = tryChoose(1, 10000);
    std::cout << "Enter station productivity (1..100): ";
    payoff = tryChoose(1, 100);
}

void CSs::printCS(std::ofstream& fout)
{
    fout << name << endl;
    fout << WSCnt << ' ' << WSOn << ' ' << payoff << endl;
}

void CSs::loadCS(std::ifstream& in)
{
    in.ignore(10000, '\n');
    getline(in, name);
    in >> WSCnt;
    in >> WSOn;
    in >> payoff;
}

bool CSs::filter(int percent, char p_way, std::string name_s)
{
    switch (p_way)
    {
    case '>':
        return (((percent == -1) or ((WSOn * 100 / WSCnt) >= percent)) and inString(name, name_s));
        break;
    case '<':
        return (((percent == -1) or ((WSOn * 100 / WSCnt) >= percent)) and inString(name, name_s));
        break;
    case '=':
        return (((percent == -1) or ((WSOn * 100 / WSCnt) >= percent)) and inString(name, name_s));
        break;
    default:
        return false;
        break;
    }
}

void CSs::View(int id)
{
    if (id != -1)
        cout << "\t\t" << "ID: " << id << endl;
    cout << "\t\t" << "Name: " << name << endl;
    cout << "\t\t" << "Number of workshops: " << WSCnt << endl;
    cout << "\t\t" << "Workshops online: " << WSOn << endl;
    cout << "\t\t" << "Payoff: " << payoff << endl;
    cout << endl;
}

void CSs::editWS(int delta)
{
    if ((delta + WSOn >= 0) and (delta + WSOn <= WSCnt))
        WSOn += delta;
    else
        cout << "Failed change workstations on " + name << endl;
}

std::string CSs::getName()
{
    return name;
}

