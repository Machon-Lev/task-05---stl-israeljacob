#pragma once
#include<string>
#include"Location.h"
#include <map>
#include<vector>

class Cities {
private:
	std::map<std::string, Location> cities;

public:
	Cities();
	void addFromFile(std::string path);
	std::vector<std::pair<std::string, Location>> distanceBySquare(std::string name, double distance);

};
