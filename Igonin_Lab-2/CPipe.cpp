#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Pipes.h"
#include "SubFunc.h"

using namespace std;

void Pipes::addPipe()
{
    cout << "Enter pipe name:\n\n> ";
    inputString(cin, name);
    cout << endl;
    cout << "Enter pipe length:";
    length = tryInputNum(0, INT_MAX);
    cout << "Enter pipe diameter: ";
    diameter = tryInputNum(0, INT_MAX);
}

void Pipes::printPipe(std::ofstream& fout)
{
    fout << name << endl;
    fout << length << ' ' << diameter << ' ' << inRepare << endl;
}

void Pipes::loadPipe(std::ifstream& in)
{
    in.ignore(10000, '\n');
    getline(in, name);
    in >> length;
    in >> diameter;
    in >> inRepare;
}

bool Pipes::filter(int status, string name_str)
{
    return (((inRepare == bool(status)) or (status == -1)) and inString(name, name_str));
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

void Pipes::changeStatus(bool status)
{
    inRepare = status;
}
