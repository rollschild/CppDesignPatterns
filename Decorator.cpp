// Dydamic and static decorator

#include <iostream>
#include <sstream>

using namespace std;

struct Shape
{
  virtual string Str() const = 0;
};

struct Circle : Shape
{
  float radius_;

  Circle() {}

  Circle(float radius) : radius_{radius} {}

  void Resize(float factor) {
    radius_ *= factor;
  }

  string Str() const override {
    ostringstream oss;
    oss << "A circle of radius " << radius_ << ".\n";
    return oss.str();
  }
};

struct Square : Shape
{
  float side_;

  Square() {}

  Square(float side) : side_{side} {}

  string Str() const override {
    ostringstream oss;
    oss << "A square with side " << side_ << ".\n";
    return oss.str();
  }
};

struct ColoredShape : Shape
{
  // You do NOT have access to Resize()
  Shape& shape_;
  string color_;

  ColoredShape(Shape& shape, const string& color)
    : shape_{shape}, color_{color}
  {}

  string Str() const override {
    ostringstream oss;
    oss << shape_.Str() << " has the color " << color_ << ".\n";
    return oss.str();
  }
};

struct TransparentShape : Shape
{
  Shape& shape_;
  uint8_t transparency_;

  // ERROR:
  // error: constructor for 'TransparentShape' must explicitly 
  // ... initialize the reference member 'shape_'
  // TransparentShape() {}

  TransparentShape(Shape& shape, uint8_t transparency) 
    : shape_{shape}, transparency_{transparency}
  {
  }

  string Str() const override {
    ostringstream oss;
    oss << shape_.Str() << " has "
        << static_cast<float>(transparency_) / 255.f * 100.f
        << "% transparency.\n";
    return oss.str();
  }
};

template<typename T>
struct AnotherColoredShape : T
{
  static_assert(is_base_of<Shape, T>::value, "Tempalte argument must be a Shape!\n");

  string color_;

  AnotherColoredShape() {}

  template<typename ...Arguments>
  AnotherColoredShape(const string& color, Arguments... arguments)
      : T(forward<Arguments>(arguments)...), color_{color}
  {
  }

  string Str() const override {
    ostringstream oss;
    oss << T::Str() << " has the color " << color_ << ".\n";
    return oss.str();
  }
};

template<typename T>
struct AnotherTransparentShape : T
{
  static_assert(is_base_of<Shape, T>::value, "Template argument must be a Shape!\n");

  uint8_t transparency_;

  AnotherTransparentShape() {}

  template<typename ...Arguments>
  AnotherTransparentShape(const uint8_t transparency, Arguments... arguments)
      : T(forward<Arguments>(arguments)...), transparency_{transparency}
  {
  }

  string Str() const override {
    ostringstream oss;
    oss << T::Str() << " has "
        << static_cast<float>(transparency_) * 255.f / 100.f
        << "% transparency.\n";
    return oss.str();
  }
};

int main() {
  Square square{5};
  ColoredShape blue_square{square, "blue"};
  cout << "Dynamic: \n";
  cout << square.Str();
  cout << blue_square.Str();

  Circle circle{6.6};
  cout << circle.Str();
  circle.Resize(2.0);
  cout << circle.Str();
  ColoredShape yellow_circle{circle, "yellow"};
  cout << yellow_circle.Str();

  TransparentShape transparent_square{blue_square, 51};
  cout << transparent_square.Str();

  cout << "Static: \n";
  AnotherColoredShape<Circle> purple_circle{"purple", 12.8};
  cout << purple_circle.Str();
  purple_circle.Resize(0.5);
  cout << purple_circle.Str();

  AnotherTransparentShape<AnotherColoredShape<Square>> 
      another_square{38, "obsidian", 20.37};
  cout << another_square.Str();

  return 0;
}
