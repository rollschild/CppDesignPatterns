#include <iostream>
#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace signals2;
struct Query {
  string creature_name_;
  enum Argument {attack_, defense_} argument_;
  int result_;

  Query(const string& creature_name, Argument argument, int result)
      : creature_name_{creature_name}, 
        argument_{argument},
        result_{result} {}
};

// This is a mediator
struct Game {
  signal<void(Query&)> queries_;
};

struct Creature {
  Game& game_;
  int attack_, defense_;
  string name_;
  
 public:
  Creature(Game& game, int attack, int defense, const string& name)
      : game_{game}, attack_{attack}, defense_{defense}, name_{name} {}

  int GetAttack() const {
    // To perform a query
    // attack_ is the initial value which might be modified later on
    Query query{name_, Query::Argument::attack_, attack_};
    game_.queries_(query);
    return query.result_;
  }

  int GetDefense() const {
    Query query{name_, Query::Argument::defense_, defense_};
    game_.queries_(query);
    return query.result_;
  }

  friend ostream& operator<<(ostream& os, const Creature& creature) {
    return os
        << "Name: " << creature.name_
        << "\nAttack: " << creature.GetAttack()
        << "\nDefense: " << creature.GetDefense()
        << "\n";
  }
/*
 private:
  Game& game_;
  int attack_;
  int defense_;
  string name_;
*/
};

class CreatureModifier {
 public:
  CreatureModifier(Game& game, Creature& creature)
      : game_{game}, creature_{creature} {}

  virtual ~CreatureModifier() = default;

 private:
  Game& game_;
  Creature& creature_;
};

class DoubleAttackModifier : public CreatureModifier {
 public:
  DoubleAttackModifier(Game& game, Creature& creature) 
      : CreatureModifier{game, creature} {
    connection_ = game.queries_.connect([&](Query& query) {
      if(query.creature_name_ == creature.name_ && 
          query.argument_ == Query::Argument::attack_) {
        query.result_ *= 2;
      }
      if(query.creature_name_ == creature.name_ &&
          query.argument_ == Query::Argument::defense_) {
        query.result_ *= 3;
      }
    });  
  }

  ~DoubleAttackModifier() {
    connection_.disconnect();
  }

 private:
  connection connection_;
};

int main() {
  Game game;
  Creature dragon{game, 20, 15, "Drcular!"};

  cout << dragon;

  {
    DoubleAttackModifier double_attack{game, dragon};
    cout << dragon;
  }

  cout << dragon;

  return 0;
}

