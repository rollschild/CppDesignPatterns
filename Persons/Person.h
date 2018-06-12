#ifndef PERSON_H_
#define PERSON_H_

#include <iostream>
using namespace std;
class PersonBuilder;

class Person
{
  string street_address_;
  string post_code_;
  string city_;

  string company_name_;
  string position_;
  int annual_income_ = 0;
public:
  Person() {
    cout << "Default constructor called. Person created.\n";
  }

  ~Person() {
    cout << "Destructor called. Person destroyed.\n";
  }

  static PersonBuilder create();

  Person(Person&& other)
    : street_address_{move(other.street_address_)},
      post_code_{move(other.post_code_)},
      city_{move(other.city_)},
      company_name_{move(other.company_name_)},
      position_{move(other.position_)},
      annual_income_{move(other.annual_income_)}
  {
    cout << "Copy constructor called.\n";
  }

  Person& operator=(Person&& other) {
    if(this == &other) {
      return *this;
    }

    street_address_ = move(other.street_address_);
    post_code_ = move(other.post_code_);
    city_ = move(other.city_);
    company_name_ = move(other.company_name_);
    position_ = move(other.position_);
    annual_income_ = move(other.annual_income_);
    return *this;
  }

  friend ostream& operator<<(ostream& os, const Person& kObj) {
    return os
      << "This person has: "
      << "street address: " << kObj.street_address_
      << ", post code " << kObj.post_code_
      << ", city " << kObj.city_
      << ", company " << kObj.company_name_
      << ", position " << kObj.position_
      << ", and annual income " << kObj.annual_income_
      << ".\n";
  }

  friend class PersonBuilder;
  friend class PersonAddressBuilder;
  friend class PersonJobBuilder;

};

#endif // PERSON_H_
