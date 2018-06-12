#ifndef PERSONBUILDER_H_
#define PERSONBUILDER_H_

#include "Person.h"

class PersonAddressBuilder;
class PersonJobBuilder;

class PersonBuilderBase
{
protected:
  Person& person_;

  explicit PersonBuilderBase(Person& person) : person_{person}
  {
  }

public:
  operator Person() const {
    return move(person_);
  }

  PersonAddressBuilder LivesAt() const;
  PersonJobBuilder WorksAt() const;
};

class PersonBuilder : public PersonBuilderBase
{
  Person p_;
public:
  PersonBuilder() : PersonBuilderBase{p_} {}
};

#endif // PERSONBUILDER_H
