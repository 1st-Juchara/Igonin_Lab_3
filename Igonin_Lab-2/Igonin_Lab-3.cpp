
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <format>
#include "CSs.h"
#include "Pipes.h"
#include "SubFunc.h"

using namespace std;
using namespace chrono;

int Menu() {
    std::cout << "1. Add pipe \n2. Add CS \n3. View pipes \n4. View CS \n5. Edit pipe \n6. Edit CS \n7. Save \n8. Load \n9. Exit";
    int number = tryChoose(1, 9);
    return number;
}

void Save(Pipes& pipes, CSs& Stations)
{
    string name = chooseFiles("C:/U4Oba/ALG_Yaz/Igonin_Lab_2/Igonin_Lab-2/Igonin_Lab-2/Saves");
    ofstream fout("Saves/"+name, ios_base::out | ios_base::trunc);// out - открыте для записи, trunc - удаление содержимого, ios_base - класс для всех потоковых классов ввода-вывода
    if (fout.is_open())
    {
        if (pipes.isExist() || Stations.isExist())
        {
            if (pipes.isExist())
            {
                pipes.PipesDataOut(fout);
            }
            else
                fout << 0 << endl;
            if (Stations.isExist())
            {
                Stations.CSDataOut(fout);
            }
            else
                fout << 0 << endl;
            cout << "\nSave completed" << endl;
        }
        else
            cout << "Nothing to save" << endl;
        cout << endl;
        fout.close();
    }
    else
        cout << "Error: save was failed";
}

void Load(Pipes& pipes, CSs& Stations) // Несостыковочка сохр. и загр.
{
    string name = chooseFiles("C:/U4Oba/ALG_Yaz/Igonin_Lab_2/Igonin_Lab-2/Igonin_Lab-2/Saves");
    ifstream fin("Saves/"+name);
    if (fin.is_open())
    {
        pipes.PipeDataIn(fin);
        Stations.CSDataIn(fin);
        fin.close();
        cout << "\nLoad completed" << endl;
    }
    else
        cout << "Error: can't find save file" << endl;
    cout << endl;
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    Pipes pipes;
    CSs Stations;
    while (true) {
        int number = Menu();
        switch (number)
        {
        case 1:
            pipes.addPipe();
            break;
        case 2:
            Stations.addCS();
            break;
        case 3:
            pipes.ViewPipes();
            break;
        case 4:
            Stations.ViewStations();
            break;
        case 5:
            pipes.editPipes();
            break;
        case 6:
            Stations.editCS();
            break;
        case 7:
            Save(pipes, Stations);
            break;
        case 8:
            Load(pipes, Stations);
            break;
        case 9:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}