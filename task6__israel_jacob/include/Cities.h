#pragma once
#include<string>
#include"Location.h"
#include <map>
#include<vector>
#include<algorithm>

class Cities {
private:
	std::map<std::string, Location> cities;

	std::vector<std::pair<std::string, Location>> distanceBySquare(double distance, double x, double y);
	std::vector<std::pair<std::string, Location>> normalEuclideanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
	std::vector<std::pair<std::string, Location>> infinityNorm(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
	std::vector<std::pair<std::string, Location>> manhattanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
	std::string checkFile(std::ifstream& inputFile);
	

public:
	Cities();
	void addFromFile(std::string path);
	bool exsists(std::string name);
	std::vector<std::pair<std::string, Location>> nearCities(std::string name, double radius, int norm);
	int northOfTheCity(std::vector<std::pair<std::string, Location>> vCities, std::string name);
};
