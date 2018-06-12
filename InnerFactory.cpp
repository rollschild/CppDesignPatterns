#define _USE_MATH_DEFINES
#include <iostream>
#include <cmath>

using namespace std;

class Point
{
private:
  float x_;
  float y_;
  Point(float x, float y) : x_{x}, y_{y} {}

  class PointFactory
  {
  private:
    PointFactory() {}

  public:
    static Point NewCartesian(float x, float y) {
      return {x, y};
    }

    static Point NewPolar(float r, float theta) {
      return {r * cos(theta), r * sin(theta)};
    }
  };

public:
  static PointFactory Factory;

  friend ostream& operator<<(ostream& os, const Point& point) {
    return os
      << "x: " << point.x_
      << ", y: " << point.y_
      << "\n";
  }
};

int main() {
  cout << Point::Factory.NewPolar(5.0, M_PI / 3);

  return 0;
}
