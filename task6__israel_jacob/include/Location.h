#pragma once
#include<string>

class Location {
private:
	std::string name;
	double x;
	double y;

public:
	Location(double x, double y);
	double getX() const;
	double getY() const;

};