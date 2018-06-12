#include <iostream>
#include <vector>

#include "Person.h"
#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

using namespace std;

int main() {
  Person p = Person::create()
    .LivesAt().AtAddress("3535 S Ball St.").WithPostcode("20212").InCity("Arlington")
    .WorksAt().AtCompany("ThinkTank").AsPosition("Intern").Earn(10e6);

  cout << p << endl;

  return 0;
}
