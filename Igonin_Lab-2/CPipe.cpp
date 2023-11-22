#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "Pipes.h"
#include "SubFunc.h"

using namespace std;

vector<int> Pipes::filterPipes()
{
    vector <int> index;
    string name = "";
    int status = -1;
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

        cout << "1. Search by status \n2. Any status";
        if (tryChoose(1, 2) == 1)
        {
            cout << "1. EXPLOITED \n2. IN REPAIR";
            status = tryChoose(1, 2) - 1;
        }

        for (int i = 0; i < pipes.size(); i++)
            if (((pipes[i].inRepare == bool(status)) or (status == -1)) and inString(pipes[i].name, name))
                index.push_back(i);
    }
    else
        for (int i = 0; i < pipes.size(); i++)
            index.push_back(i);
    return index;
}

void Pipes::ViewPipe(const Pipe& pipe)
{
    cout << "\t\t" << "Name: " << pipe.name << ' ' << pipe.id << endl;
    cout << "\t\t" << "Length: " << pipe.length << endl;
    cout << "\t\t" << "Diameter: " << pipe.diameter << endl;
    if (pipe.inRepare)
        cout << "\t\t" << "Status: IN REPAIR" << endl;
    else
        cout << "\t\t" << "Status: EXPLOITED \n" << endl;
}

void Pipes::changePipe(const vector<int>& index)
{
    cout << "1. Change pipe status\n2. Delete pipe";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "Pipe status:" << endl;
        cout << "\t1. UNDER REPAIR \n\t2. IS FUNCTIONING";
        bool status = tryChoose(1, 2) == 1;
        for (int i = 0; i < index.size(); i++)
            pipes[index[i]].inRepare = status;
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
        {
            pipes.erase(pipes.begin() + index[i]);
        }
}

bool Pipes::isExist()
{
	return pipes.size() > 0 ? true : false;;
}

void Pipes::ViewPipes() 
{
    #pragma message("Pipes viewing");
    if (isExist())
    {
        vector <int> index = filterPipes();
        cout << "Pipes:" << endl;
        for (int i = 0; i < index.size(); i++)
            ViewPipe(pipes[index[i]]);
    }
    cout << endl;
}

void Pipes::addPipe()
{
    #pragma message("Add pipe");
    
    int id = ++ID_max;
    cout << "Enter pipe name:\n\n> ";
    string name;
    inputString(cin, name);
    #pragma message("Enter name " + string(name));
    cout << endl;
    cout << "Enter pipe length:";
    float length = tryInputNum(0, INT_MAX);
    cout << "Enter pipe diameter: ";
    float diameter = tryInputNum(0, INT_MAX);
    pipes.push_back({ id, name, length, diameter , false });
}

void Pipes::editPipes()
{ // +
    if (isExist()) {
        vector <int> index = filterPipes();
        for (int i = 0; i < index.size(); i++)
        {
            cout << "pipe " << i + 1 << endl;
            ViewPipe(pipes[index[i]]);
        }
        vector <int> index_ch;
        choosingElements(index, index_ch);
        changePipe(index_ch);
    }
}

void Pipes::PipesDataOut(std::ofstream& fout)
{
    fout << ID_max << ' ';
    fout << pipes.size() << endl;
    for (int i = 0; i < pipes.size(); i++)
    {
        fout << pipes[i].name << endl;
        fout << pipes[i].id << ' ' << pipes[i].length << ' ' << pipes[i].diameter << ' ' << pipes[i].inRepare << endl;
    }
}

void Pipes::PipeDataIn(std::ifstream& in)
{
    in >> ID_max;
    int pipesCnt = 0;
    in >> pipesCnt;
    for (int i = 0; i < pipesCnt; i++)
    {
        in.ignore(10000, '\n');
        Pipe pipe;
        getline(in, pipe.name);
        in >> pipe.id;
        in >> pipe.length;
        in >> pipe.diameter;
        in >> pipe.inRepare;
        pipes.push_back(pipe);
    }
}
