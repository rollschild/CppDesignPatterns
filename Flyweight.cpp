// To compile;
// clang++ Flyweight.cpp -lpthread -o auto_flyweight
#include <iostream>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
#include <boost/flyweight.hpp>
#include <boost/flyweight/key_value.hpp>
using namespace boost;
using namespace boost::flyweights;
// using namespace flyweights;
typedef uint32_t key;

struct User
{
  User(const string first_name, const string& last_name)
      : first_name_key_{AddName(first_name)},
        last_name_key_{AddName(last_name)}
  {
  }

  const string& GetFirstName() const {
    return names_dictionary_.left.find(first_name_key_)->second;
  }

  const string& GetLastName() const {
    return names_dictionary_.left.find(last_name_key_)->second;
  }
 protected:
  static bimap<key, string> names_dictionary_;
  key first_name_key_, last_name_key_;
  static key seed_;

  static key AddName(const string& name) {
    auto it = names_dictionary_.right.find(name);
    if(it == names_dictionary_.right.end()) {
      auto id = ++seed_;
      names_dictionary_.insert({seed_, name});
      return id;
    }
    else {
      // key returned
      return it->second;
    }
  }
};

struct FlyUser
{
  flyweight<string> first_name_, last_name_;
  FlyUser(const string& first_name, const string& last_name) 
      : first_name_{first_name}, last_name_{last_name}
  {
  }
};

// Is this necessary???
key User::seed_{0};
bimap<key, string> User::names_dictionary_{};

ostream& operator<<(ostream& os, const User& user) {
  return os 
      << "The user's name is: \n"
      << "First name: " << user.GetFirstName()
      << "\nLast name: " << user.GetLastName()
      << "\n";
}

ostream& operator<<(ostream& os, const FlyUser& user) {
  return os
      << "FlyUser's name is \n"
      << "First name: " << user.first_name_
      << "\nLast name: " << user.last_name_
      << "\n";
}

int main() {
  User myself{"Guangchu", "Shi"};
  User girlfriend{"Eva", "Zhang"};
  cout << myself << girlfriend;

  FlyUser another_me{"Jovi", "Shi"};
  FlyUser another_girl{"Hui", "Shi"};
  // cout << another_me.first_name_ << endl;
  cout << another_me << another_girl;

  cout << boolalpha;
  cout << (&another_me.first_name_.get() == &another_girl.first_name_.get()) 
      << endl;
  cout << (&another_me.last_name_.get() == &another_girl.last_name_.get())
      << endl;
  return 0;
}
