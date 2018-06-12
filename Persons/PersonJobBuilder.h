#ifndef PERSONJOBBUILDER_H_
#define PERSONJOBBUILDER_H_

#include "PersonBuilder.h"

class PersonJobBuilder : public PersonBuilderBase
{
  typedef PersonJobBuilder P;
public:
  explicit PersonJobBuilder(Person& person) : PersonBuilderBase{person} {}

  P& AtCompany(string company_name) {
    person_.company_name_ = company_name;
    return *this;
  }

  P& AsPosition(string position) {
    person_.position_ = position;
    return *this;
  }

  P& Earn(int annual_income) {
    person_.annual_income_ = annual_income;
    return *this;
  }
};

#endif

