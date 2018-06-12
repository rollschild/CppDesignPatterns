#include <iostream>

using namespace std;

struct Creature {
  string name_;
  int attack_;
  int defense_;

  Creature(const string& name, int attack, int defense)
      : name_{name}, attack_{attack}, defense_{defense} {}

  friend ostream& operator<<(ostream& os, const Creature& creature) {
    return os
        << "The creature's name is: " << creature.name_
        << "\nattack: " << creature.attack_
        << "\ndefense: " << creature.defense_
        << "\n";
  }
};

class CreatureModifier {
 private:
  CreatureModifier* next_{nullptr};
 protected:
  Creature& creature_;
 public:
  CreatureModifier(Creature& creature) : creature_{creature} {}

  void Add(CreatureModifier* modifier) {
    if(next_) {
      next_->Add(modifier);
    }
    else {
      next_ = modifier;
    }
  }

  virtual void Handle() {
    if(next_) {
      next_->Handle();
    }
  }
};

class DoubleAttackModifier : public CreatureModifier {
 public:  
  DoubleAttackModifier(Creature& creature) 
      : CreatureModifier{creature} {}

  void Handle() override {
    creature_.attack_ *= 2;
    CreatureModifier::Handle();
  }
};

class IncreaseDefenseModifier : public CreatureModifier {
 public:
  IncreaseDefenseModifier(Creature& creature)
      : CreatureModifier{creature} {}

  void Handle() override {
    if(creature_.attack_ >= 10) {
      creature_.defense_++;
    }

    CreatureModifier::Handle();
  }
};

class NoModifier : public CreatureModifier {
 public:
  NoModifier(Creature& creature) : CreatureModifier{creature} {}

  void Handle() override {
    // empty here
  }
};

int main() {
  Creature dragon{"Dragon", 10, 10};
  CreatureModifier root{dragon};
  DoubleAttackModifier double_attack_1{dragon};
  DoubleAttackModifier double_attack_2{dragon};
  IncreaseDefenseModifier increase_defense{dragon};
  NoModifier curse{dragon};
  
  root.Add(&curse);
  root.Add(&double_attack_1);
  root.Add(&double_attack_2);
  root.Add(&increase_defense);

  root.Handle();

  cout << dragon;

  return 0;
}
