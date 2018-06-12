#include <iostream>
#include <cstdint>
using namespace std;

#include <boost/bimap.hpp>
using namespace boost;

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

int main() {
  User myself{"Guangchu", "Shi"};
  User girlfriend{"Eva", "Zhang"};
  cout << myself << girlfriend;

  return 0;
}
