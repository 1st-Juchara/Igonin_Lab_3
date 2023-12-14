#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Pipes.h"
#include "SubFunc.h"

using namespace std;

void Pipes::addPipe(int d)
{
    cout << "Enter pipe name:\n\n> ";
    inputString(cin, name);
    cout << endl;

    
    cout << "Enter pipe length: ";
    length = tryInputNum(0, INT_MAX);

    if (d == -1)
    {
        cout << "Choose pipe diameter:" << endl
            << "1. 500" << endl
            << "2. 700" << endl
            << "3. 1000" << endl
            << "4. 1400";
        int num = tryChoose(1, 4);
        diameter = num == 1 ? 500 :
            num == 2 ? 700 :
            num == 3 ? 1000 :
            1400;
    }
    else
        diameter = d;
}

void Pipes::printPipe(std::ofstream& fout)
{
    fout << name << endl;
    fout << length << ' ' << diameter << ' ' << inRepare << ' ' << inUse << endl;
}

void Pipes::loadPipe(std::ifstream& in)
{
    in.ignore(10000, '\n');
    getline(in, name);
    in >> length;
    in >> diameter;
    in >> inRepare;
    in >> inUse;
}

bool Pipes::filter(int status, string name_str, int d, bool use)
{
    return (((inRepare == bool(status)) or (status == -1)) and (!inUse or (d == -1)) and ((diameter == d) or (d == -1)) and inString(name, name_str));
}

void Pipes::View()
{
    cout << "\t\t" << "Name: " << name << endl;
    cout << "\t\t" << "Length: " << length << endl;
    cout << "\t\t" << "Diameter: " << diameter << endl;
    if (inRepare)
        cout << "\t\t" << "Status: IN REPAIR" << endl;
    else
        cout << "\t\t" << "Status: EXPLOITED \n" << endl;
}

int Pipes::getDiameter()
{
    return diameter;
}

int Pipes::getLength()
{
    return length;
}

float Pipes::getProductivity()
{
    return diameter * diameter * diameter * diameter * diameter / length;
}

void Pipes::changeStatus(bool status)
{
    inRepare = status;
}
