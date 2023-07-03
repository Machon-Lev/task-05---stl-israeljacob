#include"Cities.h"
#include<iostream>
#include<vector>
#include <iostream>

std::string getName(Cities cities);
double getRadius();
int getNorm();
int readFromFile(Cities& cities);
void getCities(Cities& cicities, std::string name, double radius, int nurm);

int main()
{
	Cities cities = Cities();
	// Create an instance of the Cities class

	if (!readFromFile(cities))
		return 0;

	std::vector<std::pair<std::string, Location>> nearCities;
	// Variable to store the number of cities to the north
	std::string name;
	double radius;
	int norm;

	name = getName(cities);
	// Get the name of the selected city from the user
	while (name != "0")
	{
		try {
		// Get the desired search radius from the user
		radius = getRadius();

		// Get the desired norm from the user
		norm = getNorm();
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
			return 0;
		}
		getCities(cities, name, radius, norm);
		// Ignore any remaining input in the buffer
		name = getName(cities);
		// Get the name of the next selected city from the user
	}

	std::cout << "bye" << std::endl;
	return 0;
}


std::string getName(Cities cities) {
	std::string name;

	std::cout << "Please enter selected city name (with line break after it):" << std::endl;
	std::getline(std::cin, name);
	// Prompt the user to enter the name of the selected city

	while (!(cities.exists(name)) && name != "0") {
		std::cout << "ERROR: The city does not exist" << std::endl;
		std::cout << "Please enter selected city name (with line break after it):" << std::endl;
		std::getline(std::cin, name);
		// Continue prompting the user until a valid city name is entered
	}
	return name;
	// Return the valid city name entered by the user
}


double getRadius() {
	std::string radius;
	double dradius;
	std::cout << "Please enter the wanted radius:" << std::endl;
	try {
		std::cin >> radius;
		dradius = stod(radius);
	}
	catch (std::exception& e) {
		throw std::exception("You must not enter characters instead of numbers");
	}

	while (dradius < 0) {
		std::cout << "ERROR: The radius can't be negative" << std::endl;
		std::cout << "Please enter the wanted radius:" << std::endl;
		try {
			std::cin >> radius;
		}
		catch (std::exception& e) {
			throw std::exception("You must not enter characters instead of numbers");
		}
	}
	return dradius; // Return the valid radius entered by the user
}

int getNorm() {
	std::string norm;
	int inorm;
	std::cout << "Please enter the wanted norm"
		<< "(0 - L2, Euclidean distance, "
		<< "1 - Linf, Chebyshev distance, "
		<< "2 - L1, Manhattan distance) : "
		<< std::endl;
	try {
		std::cin >> norm;
		inorm = stod(norm);
	}
	catch (std::exception& e) {
		throw std::exception("You must not enter characters instead of numbers");
	}

	while (inorm < 0 || inorm > 2) {
		std::cout << "ERROR: The norm has to be an integer between 0-2" << std::endl;
		std::cout << "Please enter the wanted norm"
			<< "(0 – L2, Euclidean distance, "
			<< "1 – Linf, Chebyshev distance, "
			<< "2 – L1, Manhattan distance) : "
			<< std::endl;
		try {
			std::cin >> inorm;
		}
		catch (std::exception& e) {
			throw std::exception("You must not enter characters instead of numbers");
		}
	}
	return inorm; // Return the valid norm entered by the user
}

int readFromFile(Cities& cities)
{
	try {
		cities.addFromFile("data.txt");
		// Attempt to load city data from the "data.txt" file
	}
	catch (const std::exception& e) {
		std::cout << e.what();
		return 0;
	}
	return 1;
}

void getCities(Cities& cities, std::string name, double radius, int norm)
{
	std::vector<std::pair<std::string, Location>> nearCities;
	nearCities = cities.nearCities(name, radius, norm);
	// Retrieve the cities within the specified radius using the specified norm
	int numOfCitiesInNorth = cities.northOfTheCity(nearCities, name);
	// Count the number of cities to the north of the selected city
	std::cout << "Search result:" << std::endl << nearCities.size()
		<< " city / cities found in the given radius." << std::endl
		<< numOfCitiesInNorth << " cities are to the north of the selected city."
		<< std::endl << "City list:" << std::endl;
	std::vector<std::string> names;
	std::transform(nearCities.begin(), nearCities.end(), std::back_inserter(names),
		[](const std::pair<std::string, Location>& pair) {
			return pair.first; // Extract the string from the pair
		});
	// Extract only the city names from the pairs and store them in the 'names' vector
	std::copy(names.begin(), names.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
	// Print the city names to the console
	std::cin.ignore();
	// Ignore any remaining input in the buffer
}
