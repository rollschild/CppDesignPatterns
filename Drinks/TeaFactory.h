#ifndef TEAFACTORY_H_
#define TEAFACTORY_H_

#include "HotDrink.h"
#include "HotDrinkFactory.h"

struct TeaFactory : HotDrinkFactory
{
  unique_ptr<HotDrink> make() const override {
    return make_unique<Tea>();
  }
};

#endif // TEAFACTORY_H_
