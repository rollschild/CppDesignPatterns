#include "Person.h"

class Person::PersonImplementation
{
public:
  void greet(Person* person);
};

void Person::PersonImplementation::greet(Person* person) {
  cout << "Hello, my name is " << person->name_ << endl;
}

Person::Person() : person_implementation_{new PersonImplementation} {}

Person::~Person() {
  delete person_implementation_;
}

void Person::greet() {
  person_implementation_->greet(this);
}
