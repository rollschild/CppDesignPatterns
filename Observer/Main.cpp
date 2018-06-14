#include <iostream>

#include <boost/signals2.hpp>

#include "Observer.h"
#include "Observable.h"
#include "SaferObservable.h"

using namespace std;
using namespace boost;
using namespace signals2;

class Person : public SaferObservable<Person> {
 public:
  Person(const int age) : age_{age} {}
   
  int GetAge() {
    return age_;
  }

  void SetAge(int age) {
    // age_ = age;
    if (this->age_ == age) return;
    auto old_vote_bility = GetVoteBility();
    this->age_ = age;
    Notify(*this, "age_");
    if (old_vote_bility != GetVoteBility()) {
      Notify(*this, "vote_bility");
    }
  }
  
  bool GetVoteBility() {
    return age_ >= 18;
  }
 private:
  int age_;
};

struct ConsoleObservder : public Observer<Person> {
 private:
  void FieldChanged(Person& source, const string& field_name) override {
    cout << "Person's " << field_name << " has changed to ";
    if (field_name == "age_")
      cout << source.GetAge() << endl;
    if (field_name == "vote_bility")
      cout << boolalpha << source.GetVoteBility() << endl;
  }
};

struct TrafficAdmin : Observer<Person> {
 private:
  void FieldChanged(Person& source, const string& field_name) override {
    if (field_name == "age_") {
      if (source.GetAge() < 18) {
        cout << "Not old enough to drive!\n";
      }
      else {
        cout << "We don't care anymore and will Unsubscribe!\n";
        source.Unsubscribe(*this);
      }
    }
  }
};

template<typename T>
struct BoostObservable {
  signal<void(T&, const string&)> field_changed_;
};

class PersonBoost : public BoostObservable<PersonBoost> {
 public:
  int GetAge() {
    return age_;
  }

  void SetAge(int age) {
    if (this->age_ == age) return;
    this->age_ = age;
    field_changed_(*this, "age_");
  }

 private:
  int age_{0};
};

int main() {
  Person person{25};
  ConsoleObservder console_observer;
  TrafficAdmin traffic_admin;
  person.Subscribe(console_observer);
  person.Subscribe(traffic_admin);

  person.SetAge(10);

  try {
    person.SetAge(23);
  }
  catch(const std::exception& e) {
    cout << "Error occurs! " << e.what() << endl;
  }
  person.SetAge(27);
  person.Subscribe(traffic_admin);
  person.SetAge(14);

  try {
    person.SetAge(18);
  }
  catch(const std::exception& e) {
    cout << "Error occurs! " << e.what() << endl;
  }
  person.Unsubscribe(console_observer);
  person.SetAge(29);
  cout << person.GetAge() << endl;

  cout << "Boost: " << endl;
  PersonBoost person_boost;
  auto connection = person_boost.field_changed_.connect(
    [](PersonBoost& person, const string& field_name) {
      cout << field_name << " has changed." << endl;
    }  
  );

  person_boost.SetAge(99);
  cout << person_boost.GetAge() << endl;
  connection.disconnect();
  person_boost.SetAge(19);
  cout << person_boost.GetAge() << endl;

  return 0;
}
