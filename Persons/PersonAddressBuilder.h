#ifndef PERSONADDRESSBUILDER_H_
#define PERSONADDRESSBUILDER_H_

#include "PersonBuilder.h"

class PersonAddressBuilder : public PersonBuilderBase
{
  typedef PersonAddressBuilder P;
public:
  explicit PersonAddressBuilder(Person& person) : PersonBuilderBase{person} {}
  
  P& AtAddress(string street_address) {
    person_.street_address_ = street_address;
    return *this;
  }

  P& WithPostcode(string post_code) {
    person_.post_code_ = post_code;
    return *this;
  }

  P& InCity(string city) {
    person_.city_ = city;
    return *this;
  }
  
};

#endif // PERSONADDRESSBUILDER_H_
