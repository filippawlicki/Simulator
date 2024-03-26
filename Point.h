#pragma once

class Point {
private:
  int x;
  int y;
public:
  Point(const int &x, const int &y);

  void SetX(const int &x);
  void SetY(const int &y);

  int GetX() const;
  int GetY() const;
};