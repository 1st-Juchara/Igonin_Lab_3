
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
    std::cout << "1.  Add pipe \n2.  Add CS \n3.  Add connection \n4.  View connections \n5.  Delete connection\n6.  Topological sort \n7.  Shortest path \n8.  Max Flow  \n9.  View pipes \n10. View CS \n11. Edit pipe \n12. Edit CS \n13. Save \n14. Load \n15. Exit";
    int number = tryChoose(1, 15);
    return number;
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
            Rijulka.viewConnections();
            break;
        case 5:
            Rijulka.editConnections();
            break;
        case 6:
            Rijulka.topologicalSorting();
            break;
        case 7:
            Rijulka.shortestPath();
            break;
        case 8:
            Rijulka.maxStream();
            break;
        case 9:
            Rijulka.ViewPipes();
            break;
        case 10:
            Rijulka.ViewStations();
            break;
        case 11:
            Rijulka.editPipes();
            break;
        case 12:
            Rijulka.editCS();
            break;
        case 13:
            Rijulka.shortestPath();
            break;
        case 14:
            Rijulka.DataIn();
            break;
        case 15:
            return 0;
            break;
        default:
            break;
        }
    };
    return 0;
}