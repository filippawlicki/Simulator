#pragma once

class Point {
private:
  int x;
  int y;
public:
  Point(const int &x, const int &y);
  Point(); // Default constructor

  void SetX(const int &x);
  void SetY(const int &y);

  int GetX() const;
  int GetY() const;

  bool operator==(const Point &point) const;
  bool operator!=(const Point &point) const;

  Point operator+(const Point &point) const;
};