#include <iostream>
#include <type_traits>
#include <variant>

using namespace std;

struct AddressPrinter {
  void operator()(const string& house_name) const {
    cout << "A house called " << house_name << endl;
  }
  void operator()(const int house_number) const {
    cout << "House number " << house_number << endl;
  }
};

int main() {
  variant<string, int> house;
  // house = "3535 S Ball St.";
  house = 515;
  AddressPrinter address_printer;
  visit(address_printer, house);

  visit([](auto& arg) {
    using T = decay_t<decltype(arg)>;
    if constexpr (is_same_v<T, string>) {
      cout << "A house called " << arg.c_str() << endl;
    }
    else {
      cout << "House number is " << arg << endl;
    }
  }, house);

  return 0;
}
