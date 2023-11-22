#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class CSs
{
	struct CS
	{
        int id = 0;
        std::string name = "";
        int WSCnt;
        int WSOn;
        int payoff = 0;
	};
    
    int ID_max = 0;

    std::vector <CS> Stations;
    std::vector <int> filterCS();
    void ViewCS(const CS& Stations);
    void changeCS(const std::vector <int>& index);
public:
    bool isExist();
    void ViewStations();
    void addCS();
    void editCS();
    void CSDataOut(std::ofstream& fout);
    void CSDataIn(std::ifstream& in);
};

