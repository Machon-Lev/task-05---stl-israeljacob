#include"Location.h"

Location::Location(double x, double y): x(x), y(y)
{
}


double Location::getX() const {
    return x;
}

double Location::getY() const {
    return y;
}
