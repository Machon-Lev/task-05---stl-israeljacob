#pragma once
#include<string>

class Location {
private:
	double x;
	double y;

public:
	Location(long double x, long double y);
	double getX() const;
	double getY() const;
	// 41.93, 88       41.85, 87.96  
};