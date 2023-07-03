#pragma once
#include <string>
#include "Location.h"
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include"Cities.h"

class Cities {
private:
    std::map<std::string, Location> cities;

    // Helper methods for distance calculations
    std::vector<std::pair<std::string, Location>> distanceBySquare(double distance, double x, double y);
    std::vector<std::pair<std::string, Location>> normalEuclideanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
    std::vector<std::pair<std::string, Location>> infinityNorm(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
    std::vector<std::pair<std::string, Location>> manhattanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y);
    std::vector<std::pair<std::string, Location>> sortVetor(std::vector<std::pair<std::string, Location>> vCities, double x, double y);

    // Helper method for checking file validity
    std::string checkFile(std::ifstream& inputFile);

public:
    // Default ctor
    Cities();

    // Method to add cities from a file
    void addFromFile(std::string path);

    // Method to check if a city exists
    bool exists(std::string name);

    // Method to find cities near a specified city within a given radius using a specified distance norm
    std::vector<std::pair<std::string, Location>> nearCities(std::string name, double radius, int norm);

    // Method to determine the number of cities located north of a given city
    int northOfTheCity(std::vector<std::pair<std::string, Location>> vCities, std::string name);
};
