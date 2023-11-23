#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include "SubFunc.h"
#include "CSs.h"
#include "Pipes.h"

class GTN
{
private:
	int ID_max = 0;

	std::map <int, CSs> Stations;
	std::map <int, Pipes> pipes;

	void CSDataOut(std::ofstream& fout);
	void CSDataIn(std::ifstream& in);
	void PipesDataOut(std::ofstream& fout);
	void PipesDataIn(std::ifstream& in);
	void changeCS(const std::vector <int>& index);
	void changePipe(const std::vector <int>& index);
	std::vector <int> filterCS();
	std::vector <int> filterPipes();
public:
	bool isExistCS();
	bool isExistPipes();
	void ViewStations();
	void ViewPipes();
	void addCS();
	void addPipe();
	void DataOut();
	void DataIn();
	void editCS();
	void editPipes();
};

