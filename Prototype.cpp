// To complie using g++:
// g++ Prototype.cpp -lboost_serialization -o proto

#include <iostream>
#include <memory>
#include <string>
#include <functional>
#include <sstream>
#include <boost/serialization/serialization.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

using namespace std;
using namespace boost;
struct Address
{
  string street_;
  string city_;
  int suite_;

  Address() {}

  Address(const string& street, const string& city, const int suite) 
    : street_{street}, city_{city}, suite_{suite}
  {
  }

  Address(const Address& other) 
    : street_{other.street_}, city_{other.city_}, suite_{other.suite_}
  {
    cout << "Copy consturctor called.\n";
  }

  friend ostream& operator<<(ostream& os, const Address& kObj) {
    return os
      << "street: " << kObj.street_
      << ", city: " << kObj.city_
      << ", and suite: " << kObj.suite_
      << ".\n";
  }

  private:
  friend class serialization::access;
  template<class archive>
  void serialize(archive& ar, const unsigned version) {
    ar & street_;
    ar & city_;
    ar & suite_;
  }

};

struct Contact
{
  string name_;
  Address* address_;

  Contact() {}

  Contact& operator=(const Contact& kOther) {
    if(this == &kOther) {
      return *this;
    }

    name_ = kOther.name_;
    address_ = kOther.address_;

    return *this;
  }

  // Contact() : name_(nullptr), address_(nullptr) {}

  Contact(const string& name, Address* address)
    : name_{name}, address_{address}
  {
  }

  Contact(const Contact& kOther) {
    name_ = kOther.name_;
    address_ = new Address {
      kOther.address_->street_,
      kOther.address_->city_,
      kOther.address_->suite_
    };
  }

  ~Contact() {
    delete address_;
  }

  friend ostream& operator<<(ostream& os, const Contact& kObj) {
    return os
      << "name: " << kObj.name_
      << ", and address: " << *kObj.address_
      << "\n";
  }

private:
  friend class serialization::access;
  template<class archive>
  void serialize(archive& ar, const unsigned version) {
    ar & name_;
    ar & address_;
  }

  // BOOST_SERIALIZATION_SPLIT_MEMBER()

};

struct EmployeeFactory
{
  static Contact main_;
  static Contact aux_;

  static unique_ptr<Contact> NewMainOfficeEmployee(string name, int suite) {
    return NewEmployee(name, suite, main_);
  }

  static unique_ptr<Contact> NewAuxOfficeEmployee(string name, int suite) {
    return NewEmployee(name, suite, aux_);
  }

private:
  static unique_ptr<Contact> NewEmployee(string name, int suite, const Contact& proto) {
    auto result = make_unique<Contact>(proto);
    result->name_ = name;
    result->address_->suite_ = suite;
    return result;
  }
};


Contact EmployeeFactory::main_{"", new Address{"3535 S Ball St.", "Arlington", 0}};
Contact EmployeeFactory::aux_{"", new Address{"3535B S Ball St.", "Arlington", 0}};

int main() {

  // Contact main = EmployeeFactory::main_{"", new Address{"3535 S Ball St.", "Arlington", 0}};

  auto clone = [](const Contact& contact) {
    ostringstream oss;
    archive::text_oarchive oa(oss);
    oa << contact;
    string s = oss.str();
    cout << s << endl;

    istringstream iss(s);
    archive::text_iarchive ia(iss);
    Contact result;
    ia >> result;
    return result;
  };

  auto john = EmployeeFactory::NewMainOfficeEmployee("John", 123);
  auto jane = clone(*john);

  jane.name_ = "Jane";
  jane.address_->suite_ = 110;

  cout << "John: " << *john;
  cout << "Jane: " << jane;

  return 0;
}

