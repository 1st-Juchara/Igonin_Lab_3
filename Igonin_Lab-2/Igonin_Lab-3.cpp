
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
    std::cout << "1.  Add pipe \n2.  Add CS \n3.  Add connection \n4.  Topological sort \n5.  Shortest path \n6.  View pipes \n7.  View CS \n8.  Edit pipe \n9.  Edit CS \n10. Save \n11. Load \n12. Exit";
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
            Rijulka.shortestPath();
            break;
        case 6:
            Rijulka.ViewPipes();
            break;
        case 7:
            Rijulka.ViewStations();
            break;
        case 8:
            Rijulka.editPipes();
            break;
        case 9:
            Rijulka.editCS();
            break;
        case 10:
            Rijulka.shortestPath();
            break;
        case 11:
            Rijulka.DataIn();
            break;
        case 12:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}