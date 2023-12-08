#pragma once
#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <unordered_map>
#include "SubFunc.h"
#include "CSs.h"
#include "Pipes.h"

class GTN
{
private:
	int ID_max = 0;

	std::map <int, CSs> Stations;
	std::map <int, Pipes> pipes;
	std::map <std::pair<int, int>, int> connections;

	void CSDataOut(std::ofstream& fout);
	void CSDataIn(std::ifstream& in);
	void PipesDataOut(std::ofstream& fout);
	void PipesDataIn(std::ifstream& in);
	void WaysDataOut(std::ofstream& fout);
	void WaysDataIn(std::ifstream& in);
	void changeCS(const std::vector <int>& index);
	void changePipe(const std::vector <int>& index);
	std::vector <int> filterCS();
	std::vector <int> filterPipes(int d = -1, bool use = true);
public:
	bool isExistCS();
	bool isExistPipes();
	void ViewStations();
	void ViewPipes();
	void addCS();
	void addPipe(int d = -1);
	void addConnect();
	void DataOut();
	void DataIn();
	void editCS();
	void editPipes();
	void topologicalSorting();
};

