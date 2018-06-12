#ifndef DRINKFACTORY_H_
#define DRINKFACTORY_H_

#include <memory>
#include <map>
#include <functional>
#include "CoffeeFactory.h"
#include "TeaFactory.h"
#include "HotDrink.h"
#include "HotDrinkFactory.h"

class DrinkFactory
{
private:
  map<string, unique_ptr<HotDrinkFactory>> hot_factories_;
public:
  DrinkFactory() {
    hot_factories_["coffee"] = make_unique<CoffeeFactory>();
    hot_factories_["tea"] = make_unique<TeaFactory>();
  }

  unique_ptr<HotDrink> make_drink(const string& drink_name) {
    auto drink = hot_factories_[drink_name]->make();
    drink->prepare(200);
    return drink;
  }
};

class DrinkWithVolumeFactory
{
private:
  map<string, function<unique_ptr<HotDrink>()>> factories_;
public:
  DrinkWithVolumeFactory() {
    factories_["coffee"] = [] {
      auto coffee = make_unique<Coffee>();
      coffee->prepare(200);
      return coffee;
    };

    factories_["tea"] = [] {
      auto tea = make_unique<Tea>();
      tea->prepare(200);
      return tea;
    };
  }

  unique_ptr<HotDrink> make_drink(const string& drink_name);
};

inline unique_ptr<HotDrink> DrinkWithVolumeFactory::make_drink(const string& name) {
  return factories_[name]();
}

#endif // DRINKFACTORY_H_
