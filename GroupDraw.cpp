#include <iostream>
#include <vector>

using namespace std;

struct GraphicObject
{
  virtual void Draw() = 0;
};

struct Circle : GraphicObject
{
  void Draw() override {
    cout << "Circle " << endl;
  }
};

struct Square : GraphicObject
{
  void Draw() override {
    cout << "Square " << endl;
  }
};

struct Triangle : GraphicObject
{
  void Draw() override {
    cout << "Triangle" << endl;
  }
};

struct Group : GraphicObject
{
  string name_;
  vector<GraphicObject*> objects_;

  Group(string name) : name_{name} {}

  void Draw() override {
    cout << "Group " << name_ << " contains " << endl;

    for(auto& o : objects_) {
      o->Draw();
    }
    // cout << endl;
  }
};

int main() {
  Group root("root");
  Circle circle;
  Square square;
  Triangle triangle;
  root.objects_.push_back(&circle);

  Group sub_node("sub_node");
  sub_node.objects_.push_back(&square);
  sub_node.objects_.push_back(&triangle);

  root.objects_.push_back(&sub_node);

  root.Draw();

  return 0;
}
