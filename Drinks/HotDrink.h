#ifndef HOTDRINK_H_
#define HOTDRINK_H_

#include <iostream>
#include <map>
#include <memory>

using namespace std;

struct HotDrink
{
  virtual ~HotDrink() = default;

  virtual void prepare(int volume) = 0;
};

// Is the default to be public???
// Well, I guess it makes no differences here.
struct Tea : HotDrink
{
  void prepare(int volume) override {
    cout << "Preparing " << volume <<"ml" << " of tea.\n";
  }
};

struct Coffee : HotDrink
{
  void prepare(int volume) override {
    cout << "Prepare " << volume << "ml" << " of coffee.\n";
  }
};

#endif // HOTDRINK_H_
