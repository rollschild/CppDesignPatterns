#include <iostream>

#include "Observer.h"
#include "Observable.h"

using namespace std;

class Person : public Observable<Person> {
 public:
  Person(const int age) : age_{age} {}
   
  int GetAge() {
    return age_;
  }

  void SetAge(int age) {
    // age_ = age;
    if (this->age_ == age) return;
    this->age_ = age;
    Notify(*this, "age_");
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
  }
};

int main() {
  Person person{25};
  ConsoleObservder console_observer;
  person.Subscribe(console_observer);

  person.SetAge(23);
  person.SetAge(27);

  person.Unsubscribe(console_observer);
  person.SetAge(29);
  cout << person.GetAge() << endl;
  return 0;
}
