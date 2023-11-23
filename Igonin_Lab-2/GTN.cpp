#include "GTN.h"

using namespace std;

void GTN::CSDataOut(std::ofstream& fout)
{
    fout << Stations.size() << endl;
    for (auto it = Stations.begin(); it != Stations.end(); it++)
    {
        fout << it->first << endl;
        it->second.printCS(fout);
    }
}

void GTN::CSDataIn(std::ifstream& in)
{
    in.ignore(10000, '\n');
    int CSCnt = 0;
    in >> CSCnt;
    for (int i = 0; i < CSCnt; i++)
    {
        int id;
        in >> id;
        CSs Station;
        Station.loadCS(in);
        Stations.insert({ id, Station });
    }
}

void GTN::PipesDataOut(std::ofstream& fout)
{
    fout << pipes.size() << endl;
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        fout << it->first << endl;
        it->second.printPipe(fout);
    }
}

void GTN::PipesDataIn(std::ifstream& in)
{
    in.ignore(10000, '\n');
    int pipesCnt = 0;
    in >> pipesCnt;
    for (int i = 0; i < pipesCnt; i++)
    {
        int id;
        in >> id;
        Pipes pipe;
        pipe.loadPipe(in);
        pipes.insert({ id, pipe });
    }
}

void GTN::changeCS(const std::vector<int>& index)
{
    cout << "1. Change WS status\n2. Delete CS";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "1. Turn off workshops" << endl << "2. Turn on workshops";
        int inst = tryChoose(1, 2) == 1;
        cout << "How many?";
        int delta = inst == 1 ? -tryChoose(0, 999999) : tryChoose(0, 999999);
        for (int i = 0; i < index.size(); i++)
        {
            Stations[index[i]].editWS(delta);
                
        }
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
        {
            Stations.erase(index[i]);
        }
}

void GTN::changePipe(const std::vector<int>& index)
{
    cout << "1. Change pipe status\n2. Delete pipe";
    int number = tryChoose(1, 2);
    if (number == 1)
    {
        cout << "Pipe status:" << endl;
        cout << "\t1. UNDER REPAIR \n\t2. IS FUNCTIONING";
        bool status = tryChoose(1, 2) == 1;
        for (int i = 0; i < index.size(); i++)
            pipes[index[i]].changeStatus(status);
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
        {
            pipes.erase(index[i]);
        }
}

std::vector<int> GTN::filterCS()
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
        /*auto percent_choose = [&number, &workshops](int x) -> bool {
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
         */
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

        char p_way = number == 1 ? '>' : number == 2 ? '<' : '=';

        for (auto it = Stations.begin(); it != Stations.end(); it++)
            if (it->second.filter(workshops, p_way, name))
                index.push_back(it->first);
    }
    else
        for (auto it = Stations.begin(); it != Stations.end(); it++)
            index.push_back(it->first);
    return index;
}

std::vector<int> GTN::filterPipes()
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

        for (auto it = pipes.begin(); it != pipes.end(); it++)
            if (it->second.filter(status, name))
                index.push_back(it->first);
    }
    else
        for (auto it = pipes.begin(); it != pipes.end(); it++)
            index.push_back(it->first);
    return index;
}

bool GTN::isExistCS()
{
	return Stations.size() > 0;
}

bool GTN::isExistPipes()
{
	return pipes.size() > 0;
}

void GTN::ViewStations()
{
    if (isExistCS())
    {
        vector <int> index = filterCS();
        cout << "Stations:" << endl;
        for (int i = 0; i < index.size(); i++)
            Stations[index[i]].View();
    }
}

void GTN::ViewPipes()
{
    if (isExistPipes())
    {
        vector <int> index = filterPipes();
        cout << "Pipes:" << endl;
        for (int i = 0; i < index.size(); i++)
            pipes[index[i]].View();
    }
    cout << endl;
}

void GTN::addCS()
{
    int id = -(++ID_max);
    CSs Station;
    Station.addCS();
    Stations.insert({ id, Station});
}

void GTN::addPipe()
{
    int id = ++ID_max;
    Pipes pipe;
    pipe.addPipe();
    pipes.insert({ id, pipe});
}

void GTN::DataOut()
{
    string name = chooseFiles("C:/U4Oba/ALG_Yaz/Igonin_Lab_2/Igonin_Lab-2/Igonin_Lab-2/Saves");
    ofstream fout("Saves/" + name, ios_base::out | ios_base::trunc);// out - открыте для записи, trunc - удаление содержимого, ios_base - класс для всех потоковых классов ввода-вывода
    if (fout.is_open())
    {
        fout << ID_max << endl;
        PipesDataOut(fout);
        CSDataOut(fout);
        cout << "\nSave completed" << endl;
        fout.close();
    }
    else
        cout << "Error: save was failed";
}

void GTN::DataIn()
{
    string name = chooseFiles("C:/U4Oba/ALG_Yaz/Igonin_Lab_2/Igonin_Lab-2/Igonin_Lab-2/Saves");
    ifstream fin("Saves/" + name);
    if (fin.is_open())
    {
        fin >> ID_max;
        PipesDataIn(fin);
        CSDataIn(fin);
        fin.close();
        cout << "\nLoad completed" << endl;
    }
    else
        cout << "Error: can't find save file" << endl;
    cout << endl;
}

void GTN::editCS()
{
    if (isExistCS()) {
        vector <int> index = filterCS();
        for (int i = 0; i < index.size(); i++)
        {
            cout << "Station " << i + 1 << endl;
            Stations[index[i]].View();
        }
        vector <int> index_ch;
        choosingElements(index, index_ch);
        changeCS(index_ch);
    }
}

void GTN::editPipes()
{
    if (isExistPipes()) {
        vector <int> index = filterPipes();
        for (int i = 0; i < index.size(); i++)
        {
            cout << "pipe " << i + 1 << endl;
            pipes[index[i]].View();
        }
        vector <int> index_ch;
        choosingElements(index, index_ch);
        changePipe(index_ch);
    }
}
