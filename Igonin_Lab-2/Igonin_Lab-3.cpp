
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
    std::cout << "1. Add pipe \n2. Add CS \n3. View pipes \n4. View CS \n5. Edit pipe \n6. Edit CS \n7. Save \n8. Load \n9. Exit";
    int number = tryChoose(1, 9);
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
            Rijulka.ViewPipes();
            break;
        case 4:
            Rijulka.ViewStations();
            break;
        case 5:
            Rijulka.editPipes();
            break;
        case 6:
            Rijulka.editCS();
            break;
        case 7:
            Rijulka.DataOut();
            break;
        case 8:
            Rijulka.DataIn();
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