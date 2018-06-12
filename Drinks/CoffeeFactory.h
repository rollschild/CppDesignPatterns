#ifndef COFFEEFACTORY_H_
#define COFFEEFACTORY_H_

#include "HotDrink.h"
#include "HotDrinkFactory.h"

struct CoffeeFactory : HotDrinkFactory
{
  unique_ptr<HotDrink> make() const override {
    return make_unique<Coffee>();
  }
};

#endif // COFFEEFACTORY_H_
