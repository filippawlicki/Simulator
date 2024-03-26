#include "Point.h"

Point::Point(const int &x, const int &y) : x(x), y(y) {}

void Point::SetX(const int &x) {
  this->x = x;
}

void Point::SetY(const int &y) {
  this->y = y;
}

int Point::GetX() const {
  return x;
}

int Point::GetY() const {
  return y;
}