#include <iostream>

using namespace std;

struct Renderer
{
  virtual void RenderCircle(int x, int y, int radius) = 0;
};

struct VectorRenderer : Renderer
{
  void RenderCircle(int x, int y, int radius) override {
    cout << "Now rendering vector circle of radius " << radius << ".\n";
  }
};

struct RasterRenderer : Renderer
{
  void RenderCircle(int x, int y, int radius) override {
    cout << "Now rendering raster circle of radius " << radius << ".\n";
  }
};

struct Shape
{
protected:
  Renderer& renderer_;
  Shape(Renderer& renderer) : renderer_{renderer} {}
public:
  virtual void Draw() = 0;
  virtual void Resize(int new_radius) = 0;
};

struct Circle : Shape
{
private:
  int x_;
  int y_;
  int radius_;
  // Renderer& renderer;
public:
  Circle(int x, int y, int radius, Renderer& renderer) 
    : x_{x}, y_{y}, radius_{radius}, Shape(renderer)
  {
  }
public:
  void Draw() override {
    renderer_.RenderCircle(x_, y_, radius_);  
  }

  void Resize(int new_radius) override {
    radius_ = new_radius;
  }
};

int main() {
  RasterRenderer raster_renderer;
  VectorRenderer vector_renderer;
  Circle circle(3, 4, 12,raster_renderer);
  Circle vector_circle(1, -1, 6, vector_renderer);
  circle.Draw();
  vector_circle.Draw();
  vector_circle.Resize(100);
  vector_circle.Draw();

  return 0;
}
