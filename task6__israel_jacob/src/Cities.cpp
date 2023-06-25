#include"Cities.h"
#include<iostream>
#include<fstream>
#include<algorithm>


Cities::Cities(){
	cities = std::map<std::string, Location>();
}

void Cities::addFromFile(std::string path)
{
    std::ifstream inputFile(path);
    if (inputFile.is_open()) {
        std::string name;
        std::string x;
        std::string y;

        while (std::getline(inputFile, name)) {
            std::getline(inputFile, x, '-');
            std::getline(inputFile, y);
            Location loc = Location(stold(x), stold(y));
            cities.emplace(name, loc);
        }
        inputFile.close();
    }
    else {
        std::cout << "Unable to open file." << std::endl;
    }
}

std::vector<std::pair<std::string, Location>> Cities::distanceBySquare(std::string name, double distance)
{

    auto cityIterator = cities.find(name);
    if (cityIterator == cities.end()) {
        // City not found in the map
        return std::vector<std::pair<std::string, Location>>();  // Return an empty vector
    }

    double x = cityIterator->second.getX();
    double y = cityIterator->second.getY();
    std::vector<std::pair<std::string, Location>> vCities;
    std::copy_if(cities.begin(), cities.end(), std::back_inserter(vCities),
        [x, y, distance](const std::pair<const std::string, const Location>& pair)
        {
            double dx = pair.second.getX() - x;
            double dy = pair.second.getY() - y;
            return dx <= distance && dy <= distance;
        });
    return vCities;
}

