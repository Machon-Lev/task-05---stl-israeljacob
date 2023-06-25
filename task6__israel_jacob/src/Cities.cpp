#include"Cities.h"
#include<iostream>
#include<fstream>

#include <cstdlib>


Cities::Cities() {
	cities = std::map<std::string, Location>();
}

std::string Cities::checkFile(std::ifstream &inputFile){

	if (!inputFile.is_open()) {
		throw std::exception("Unable to open file.");
	}

	std::string name;

	if (!std::getline(inputFile, name)) {
		inputFile.close();
		throw std::exception("The file is empty");
	}
	return name;
}

void Cities::addFromFile(std::string path)
{
	std::ifstream inputFile(path);

	std::string name;
	std::string x, y;

	try {
		name = checkFile(inputFile);
	}
	catch (std::exception& e) {
		throw e;
	}

	do {
		std::getline(inputFile, x, '-');
		std::getline(inputFile, y);
		try {
			Location loc = Location(stold(x), stold(y));
			cities.emplace(name, loc);
		}
		catch (std::exception& e) {
			inputFile.close();
			throw std::exception("The information is invalid");
		}
		
	} while (std::getline(inputFile, name));
	inputFile.close();
}

bool Cities::exsists(std::string name)
{
	auto i = cities.find(name);
	return cities.find(name) != cities.end();
}

std::vector<std::pair<std::string, Location>> Cities::nearCities(std::string name, double radius, int norm)
{
	auto cityIterator = cities.find(name);

	double x = cityIterator->second.getX();
	double y = cityIterator->second.getY();
	std::vector<std::pair<std::string, Location>> nearCities = distanceBySquare(radius, x, y);

	if(norm == 0)
		return normalEuclideanDistance(nearCities, radius, x, y);
	else if(norm == 1)
		return infinityNorm(nearCities, radius, x, y);
	else
		return manhattanDistance(nearCities, radius, x, y);
}

std::vector<std::pair<std::string, Location>> Cities::distanceBySquare(double distance, double x, double y)
{
	std::vector<std::pair<std::string, Location>> vCities;
	std::copy_if(cities.begin(), cities.end(), std::back_inserter(vCities),
		[x, y, distance](const std::pair<const std::string, const Location>& pair)
		{
			double dx =  std::abs(pair.second.getX() - x);
			double dy = std::abs(pair.second.getY() - y);
			return dx <= distance && dy <= distance && (dx != 0 || dy != 0);
		});
	return vCities;
}

std::vector<std::pair<std::string, Location>> Cities::normalEuclideanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y)
{
	vCities.erase(std::remove_if(vCities.begin(), vCities.end(),
		[x, y, radius](std::pair<std::string, Location> pair) {
			double dx = pair.second.getX() - x;
			double dy = pair.second.getY() - y;
			return (dx * dx + dy * dy) <= radius * radius; }), vCities.end());
	std::sort(vCities.begin(), vCities.end(),
		[x, y](std::pair<std::string, Location> pair1, std::pair<std::string, Location> pair2) {
			double dx1 = pair1.second.getX() - x;
			double dy1 = pair1.second.getY() - y;
			double dx2 = pair2.second.getX() - x;
			double dy2 = pair2.second.getY() - y;
			return dx1 * dx1 + dy1 * dy1 <= dx2 * dx2 + dy2 * dy2; });
	return vCities;
}

std::vector<std::pair<std::string, Location>> Cities::infinityNorm(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y)
{
	vCities.erase(std::remove_if(vCities.begin(), vCities.end(),
		[x, y, radius](std::pair<std::string, Location> pair) {
			double dx = std::abs(pair.second.getX() - x);
			double dy = std::abs(pair.second.getY() - y);
			return std::max(dx, dy) <= radius; }), vCities.end());
	std::sort(vCities.begin(), vCities.end(),
		[x, y](std::pair<std::string, Location> pair1, std::pair<std::string, Location> pair2) {
			double dx1 = std::abs(pair1.second.getX() - x);
			double dy1 = std::abs(pair1.second.getY() - y);
			double dx2 = std::abs(pair2.second.getX() - x);
			double dy2 = std::abs(pair2.second.getY() - y);
			return std::max(dx1, dy1) <= std::max(dx2, dy2); });
	return vCities;
}

std::vector<std::pair<std::string, Location>> Cities::manhattanDistance(std::vector<std::pair<std::string, Location>> vCities, double radius, double x, double y)
{
	vCities.erase(std::remove_if(vCities.begin(), vCities.end(),
		[x, y, radius](std::pair<std::string, Location> pair) {
			double dx = std::abs(pair.second.getX() - x);
			double dy = std::abs(pair.second.getY() - y);
			return dx + dy <= radius; }), vCities.end());
	std::sort(vCities.begin(), vCities.end(), 
		[x,y](std::pair<std::string, Location> pair1, std::pair<std::string, Location> pair2) {
			double dx1 = std::abs(pair1.second.getX() - x);
			double dy1 = std::abs(pair1.second.getY() - y);
			double dx2 = std::abs(pair2.second.getX() - x);
			double dy2 = std::abs(pair2.second.getY() - y);
			return dx1 + dy1 <= dx2 + dy2;});
	return vCities;
}

int Cities::northOfTheCity(std::vector<std::pair<std::string, Location>> vCities, std::string name)
{
	double y = cities.find(name)->second.getY();
	vCities.erase(
		std::remove_if(vCities.begin(), vCities.end(),
			[y](const std::pair<std::string, Location>& pair) {
				return pair.second.getY() > y;
			}),
		vCities.end());
	return vCities.size();
}



