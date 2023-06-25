#include"Cities.h"
#include<iostream>

std::string getName(Cities cities); 
double getRadius();
int getNorm();

int main()
{
	Cities cities = Cities();
	try {
		cities.addFromFile("data.txt");
	}
	catch (const std::exception& e){
		std::cout << e.what();
		return 0;
	}
	std::vector<std::pair<std::string, Location>> nearCities;
	int numOfCitiesInNorth;
	std::string name;
	double radius;
	int norm;
	
	name = getName(cities);
	while (name != "0")
	{
		radius = getRadius();
		norm = getNorm();
		nearCities = cities.nearCities(name, radius, norm);
		numOfCitiesInNorth = cities.northOfTheCity(nearCities, name);
		std::cout << "Search result:" << std::endl << nearCities.size()
			<< " city / cities found in the given radius." << std::endl
			<< numOfCitiesInNorth << " cities are to the north of the selected city."
			<< std::endl << "City list:" << std::endl;
		std::vector<std::string> names;
		std::transform(nearCities.begin(), nearCities.end(), std::back_inserter(names),
			[](const std::pair<std::string, Location>& pair) {
				return pair.first; // Extract the string from the pair
			});
		std::copy(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
		std::cin.ignore();
		name = getName(cities);
	}
	std::cout << "bye" << std::endl;
	return 0;
}


std::string getName(Cities cities) {
	std::string name;

		std::cout << "Please enter selected city name (with line break after it):" << std::endl;
	std::getline(std::cin, name);
	while (!(cities.exsists(name)) && name != "0") {
		std::cout << "ERROR: The city dos not exsists" << std::endl;
		std::cout << "Please enter selected city name (with line break after it):" << std::endl;
		std::getline(std::cin, name);
	}
	return name;
}

double getRadius() {
	double radius;
	std::cout << "Please enter the wanted radius:" << std::endl;
	try {
		std::cin >> radius;
	}
	catch (std::exception& e) {
		throw std::exception("You must not enter characters instead of numbers");
	}

	while (radius < 0) {
		std::cout << "ERROR: The radius can't be negative" << std::endl;
		std::cout << "Please enter the wanted radius:" << std::endl;
		try {
			std::cin >> radius;
		}
		catch (std::exception& e) {
			throw std::exception("You must not enter characters instead of numbers");
		}
	}
	return radius;
}

int getNorm() {
	int norm;
	std::cout << "Please enter the wanted norm"
		<< "(0 - L2, Euclidean distance, "
		<< "1 - Linf, Chebyshev distance, "
		<< "2 - L1, Manhattan distance) : "
		<< std::endl;
	try {
		std::cin >> norm;
	}
	catch (std::exception& e) {
		throw std::exception("You must not enter characters instead of numbers");
	}

	while (norm < 0 || norm > 2) {
		std::cout << "ERROR: The norm has to be an integer between 0-2" << std::endl;
		std::cout << "Please enter the wanted norm"
			<< "(0 – L2, Euclidean distance, "
			<< "1 – Linf, Chebyshev distance, "
			<< "2 – L1, Manhattan distance) : "
			<< std::endl;
		try {
			std::cin >> norm;
		}
		catch (std::exception& e) {
			throw std::exception("You must not enter characters instead of numbers");
		}
	}
	return norm;
}