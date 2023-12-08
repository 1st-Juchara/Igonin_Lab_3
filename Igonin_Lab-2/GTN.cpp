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
    for (auto it = Stations.begin(); it != Stations.end(); it++)
    {
        Stations[-(-it->first + ID_max)] = it->second;
        Stations.erase(it);
    }

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

    ID_max = Stations.size() + pipes.size();
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
    for (auto it = pipes.begin(); it != pipes.end(); it++)
    {
        pipes[it->first + ID_max] = it->second;
        pipes.erase(it);
    }
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

void GTN::WaysDataOut(std::ofstream& fout)
{
    fout << connections.size() << endl;
    for (auto it = connections.begin(); it != connections.end(); it++)
    {
        fout << it->first.first << ' ' << it->first.second << ' ' << it->second << endl;
    }
}

void GTN::WaysDataIn(std::ifstream& in)
{
    in.ignore(10000, '\n');
    int waysCnt = 0;
    in >> waysCnt;
    for (int i = 0; i < waysCnt; i++)
    {
        int cs1, cs2, pipe;
        in >> cs1;
        in >> cs2;
        in >> pipe;
        connections.insert({ make_pair(cs1, cs2), pipe });
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
            cout << endl;
        }
    }
    else
        for (int i = index.size() - 1; i >= 0; i--)
        {
            int t = -1;
            for (auto it = connections.begin(); it != connections.end(); it++)
            {
                if ((it->first.first == index[i] or it->first.second == index[i]) and (t == -1))
                {
                    cout << "Are you shure to delete this CS?" << endl
                         << "1. Yes\n2. No" << endl;
                    Stations[index[i]].View(); 
                    cout << "It connected with others";
                    t = tryChoose(0, 1);
                    if (t == 0)
                        connections.erase(it->first);
                    else
                        break;
                }
                else if ((it->first.first == index[i] or it->first.second == index[i]) and (t == 0))
                {
                    connections.erase(it->first);
                }
            }
            if (t != 1)
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
    char p_way = '=';
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

            char p_way = number == 1 ? '>' : number == 2 ? '<' : '=';
        }

        for (auto it = Stations.begin(); it != Stations.end(); it++)
            if (it->second.filter(workshops, p_way, name))
                index.push_back(it->first);
    }
    else
        for (auto it = Stations.begin(); it != Stations.end(); it++)
            index.push_back(it->first);
    return index;
}

std::vector<int> GTN::filterPipes(int d, bool use)
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
    }
    else
    {
        for (auto it = pipes.begin(); it != pipes.end(); it++)
            if (it->second.filter(status, name, d, use))
                index.push_back(it->first);
    }
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

void GTN::addPipe(int d)
{
    int id = ++ID_max;
    Pipes pipe;
    pipe.addPipe(d);
    pipes.insert({ id, pipe});
}

void GTN::addConnect()
{
    while (true)
    {
        if (Stations.size() >= 2)
        {
            vector <int> index = filterCS();
            for (int i = 0; i < index.size(); i++)
            {
                cout << "Station " << i + 1 << endl;
                Stations[index[i]].View();
            }

            int index_1;
            int index_2;

            while (1)
            {
                cout << "Choose first CS for connecting ";
                index_1 = index[tryChoose(1, index.size()) - 1];
                cout << "Choose second CS for connecting ";
                index_2 = index[tryChoose(1, index.size()) - 1];
                if (index_1 == index_2)
                    cout << "Second CS must be different" << endl;
                else
                    break;
            }

            cout << "Choose pipe diameter:" << endl
                << "1. 500" << endl
                << "2. 700" << endl
                << "3. 1000" << endl
                << "4. 1400";
            int num = tryChoose(1, 4);
            int diameter = num == 1 ? 500 : num == 2 ? 700 : num == 3 ? 1000 : 1400;

            int pipe_cnt = 0;
            index.clear();

            index = filterPipes(diameter, false);

            if (index.size() == 0)
            {
                cout << "There is no pipes with same diameter.\n\nWould you like to add some?" << endl
                    << "1. Add pipe" << endl
                    << "2. Return to menu";
                if (!(tryChoose(1, 2) - 1))
                {
                    addPipe(diameter);
                    index.push_back(ID_max);
                } 
                else
                    break;
            }

            for (int i = 0; i < index.size(); i++)
            {
                cout << "Pipe " << i + 1 << endl;
                pipes[index[i]].View();
            }
                

            cout << "Choose pipe";
            num = tryChoose(1, index.size()) - 1;
            int length = pipes[index[num]].getLength();
            pipes[index[num]].inUse = true;


            connections.insert({ make_pair(index_1, index_2) , index[num] });
            break;
        }
        else
        {
            cout << "Not enough CS.\n\nWould you like to add some?" << endl
                << "1. Add CS" << endl
                << "2. Return to menu";
            if (!(tryChoose(1, 2) - 1))
                addCS();
            else
                break;
        }
    }
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
        WaysDataOut(fout);
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
        WaysDataIn(fin);
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

void GTN::topologicalSorting()
{
    vector <int> vert;
    int n = 0;

    for (auto it = connections.begin(); it != connections.end(); it++)
    {
        bool t1 = true;
        bool t2 = true;
        for (int i = 0; i < vert.size(); i++)
        {
            if (vert[i] == it->first.first)
                t1 = false;
            if (vert[i] == it->first.second)
                t2 = false;
        }
        
        if (t1)
            vert.push_back(it->first.first);
        if (t2)
            vert.push_back(it->first.second);
        n += int(t1) + int(t2);
    }

    vector<vector<int>> matrix(n, vector<int>(n, INF));

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = connections.contains(make_pair(vert[i], vert[j])) ? connections[make_pair(vert[i], vert[j])] : INF;
        }
    
    if (!loopcheck(matrix))
    {
        vector <int> visited(n);
        vector <int> order;
        for (int i = 0; i < n; i++)
        {
            if (visited[i] == false)
            {
                dfs(matrix, i, visited, order);
                reverse(order.begin(), order.end());
                for (int j = 0; j < order.size(); j++)
                    cout << vert[order[j]] << ' ';
            }
        }
        cout << "\n\n";
    }
    else
    {
        cout << "ALARM: loop is disapear" << endl;
    }
    
}
