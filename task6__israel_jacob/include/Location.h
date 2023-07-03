#pragma once
#include <string>

class Location {
private:
	double x;  // Private member variable to store the x-coordinate
	double y;  // Private member variable to store the y-coordinate

public:
	Location(long double x, long double y);
	// Constructor - Initializes the Location object with the given x and y coordinates

	double getX() const;
	// Getter method for retrieving the x-coordinate of the Location object

	double getY() const;
	// Getter method for retrieving the y-coordinate of the Location object
};