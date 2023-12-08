
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <chrono>
#include <format>
#include "CSs.h"
#include "Pipes.h"
#include "SubFunc.h"
#include "GTN.h"

using namespace std;
using namespace chrono;

int Menu() {
    std::cout << "1.  Add pipe \n2.  Add CS \n3.  Add connection \n4.  Topological sort \n5.  View pipes \n6.  View CS \n7.  Edit pipe \n8.  Edit CS \n9.  Save \n10. Load \n11. Exit";
    int number = tryChoose(1, 11);
    return number;
    int x = 5;
    int y = 6;
}

int main()
{
    redirect_output_wrapper cerr_out(cerr);
    string time = format("{:%d_%m_%Y %H_%M_%OS}", system_clock::now() + hours(3));
    ofstream logfile("Logs/log_" + time + ".txt");
    if (logfile)
        cerr_out.redirect(logfile);

    GTN Rijulka;
    while (true) {
        int number = Menu();
        switch (number)
        {
        case 1:
            Rijulka.addPipe();
            break;
        case 2:
            Rijulka.addCS();
            break;
        case 3:
            Rijulka.addConnect();
            break;
        case 4:
            Rijulka.topologicalSorting();
            break;
        case 5:
            Rijulka.ViewPipes();
            break;
        case 6:
            Rijulka.ViewStations();
            break;
        case 7:
            Rijulka.editPipes();
            break;
        case 8:
            Rijulka.editCS();
            break;
        case 9:
            Rijulka.DataOut();
            break;
        case 10:
            Rijulka.DataIn();
            break;
        case 11:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}