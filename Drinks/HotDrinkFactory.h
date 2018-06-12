#ifndef HOTDRINKFACTORY_H_
#define HOTDRINKFACTORY_H_
#include "HotDrink.h"

struct HotDrinkFactory
{

  virtual ~HotDrinkFactory() {}
  virtual unique_ptr<HotDrink> make() const = 0;
};

#endif // HOTDRINKFACTORY_H_
