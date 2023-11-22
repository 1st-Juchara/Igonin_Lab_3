#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

class Pipes
{
    struct Pipe
    {
        int id = 0;
        std::string name = "";
        float length = 0;
        float diameter = 0;
        bool inRepare = false;
    };

    int ID_max = 0;

    std::vector <Pipe> pipes;
    std::vector <int> filterPipes();
    void ViewPipe(const Pipe& pipe);
    void changePipe(const std::vector <int>& index);
public:
    bool isExist();
    void ViewPipes();
    void addPipe();
    void editPipes();
    void PipesDataOut(std::ofstream& fout);
    void PipeDataIn(std::ifstream& in);
};

