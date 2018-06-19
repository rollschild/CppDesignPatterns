// CRTP
#include <iostream>
#include <typeinfo>
#include <typeindex>
#include <map>

using namespace std;

struct GameObject;

void Collide(GameObject& obj_1, GameObject& obj_2);

struct GameObject {
  virtual type_index Type() const = 0;

  void Collide(GameObject& other) {
    ::Collide(*this, other);
  }

  virtual ~GameObject() = default;
};

template<typename T>
struct GameImplementation : GameObject {
  type_index Type() const override {
    return typeid(T);
  }
};

struct Asteroid : GameImplementation<Asteroid> {};
struct Spaceship : GameImplementation<Spaceship> {};
struct Planet : GameImplementation<Planet> {};
struct ArmedSpaceship : GameImplementation<ArmedSpaceship> {
  type_index Type() const override {
    return typeid(ArmedSpaceship);
    // Why do we need this?
  }
};

void Asteroid_Spaceship() {cout << "Spaceship destroyed!!!" << endl;}
void Asteroid_Planet() {cout << "Explosion!!!" << endl;}
void Spaceship_Planet() {cout << "Spaceship lands on planet." << endl;}
void Asteroid_ArmedSpaceship() {cout << "Spaceship shoots asteroid." << endl;}

map<pair<type_index, type_index>, void(*)(void)> dictionary{
  {{typeid(Asteroid), typeid(Spaceship)}, Asteroid_Spaceship},
  {{typeid(Asteroid), typeid(Planet)}, Asteroid_Planet},
  {{typeid(Spaceship), typeid(Planet)}, Spaceship_Planet},
  {{typeid(ArmedSpaceship), typeid(Asteroid)}, Asteroid_ArmedSpaceship}
};

void Collide(GameObject& obj_1, GameObject& obj_2) {
  // Check in both directions
  auto itr = dictionary.find({obj_1.Type(), obj_2.Type()});
  if (itr == dictionary.end()) {
    itr = dictionary.find({obj_2.Type(), obj_1.Type()});
    if (itr == dictionary.end()) {
      cout << "They pass by each other safely." << endl;
      return;
    }
  }

  // Below does NOT work
  // *(itr->second);
  itr->second();
  return;
}

int main() {
  Asteroid asteroid;
  Spaceship spaceship;
  Planet planet;
  ArmedSpaceship armed_spaceship;

  Collide(asteroid, spaceship);
  Collide(asteroid, planet);
  Collide(spaceship, planet);
  Collide(armed_spaceship, asteroid);
  Collide(planet, armed_spaceship);

  cout << "Member collision: \n";
  spaceship.Collide(asteroid);
  spaceship.Collide(planet);

  return 0;
}
