#include <iostream>
#include <map>
#include <memory>

#include "HotDrink.h"
#include "DrinkFactory.h"

using namespace std;

unique_ptr<HotDrink> make_drink(const string& drink_name) {
  unique_ptr<HotDrink> drink;

  if(drink_name == "tea") {
    drink = make_unique<Tea>();
    drink->prepare(150);
  }
  else {
    drink = make_unique<Coffee>();
    drink->prepare(150);
  }

  return drink;
}

int main() {
  auto drink_tea = make_drink("tea");
  auto drink_coffee = make_drink("coffee");

  DrinkFactory drink_factory;
  drink_factory.make_drink("coffee");

  DrinkFactory drink_with_volume_factory;
  drink_with_volume_factory.make_drink("tea");

  return 0;
}
