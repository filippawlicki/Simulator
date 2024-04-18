#include "Point.h"

Point::Point(const int &x, const int &y) : x(x), y(y) {}
Point::Point() : x(0), y(0) {}

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

bool Point::operator==(const Point &point) const {
  return x == point.x && y == point.y;
}

bool Point::operator!=(const Point &point) const {
  return x != point.x || y != point.y;
}

Point Point::operator+(const Point &point) const {
  return Point(x + point.x, y + point.y);
}