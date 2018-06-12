#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
using namespace std;
class Person
{
public:
  string name_;

  class PersonImplementation;
  PersonImplementation* person_implementation_;

  Person();
  ~Person();

  void greet();
};

#endif // PERSON_H_
