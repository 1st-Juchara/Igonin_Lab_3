#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class CSs
{
    std::string name = "";
    int WSCnt;
    int WSOn;
    int payoff = 0;

public:
    void addCS();
    void printCS(std::ofstream& fout);
    void loadCS(std::ifstream& in);
    bool filter(int percent, char p_way, std::string name_s);
    void View();
    void editWS(int delta);
};

