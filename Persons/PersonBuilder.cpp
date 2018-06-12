#include "PersonBuilder.h"
#include "PersonAddressBuilder.h"
#include "PersonJobBuilder.h"

PersonAddressBuilder PersonBuilderBase::LivesAt() const {
  return PersonAddressBuilder{person_};
}

PersonJobBuilder PersonBuilderBase::WorksAt() const {
  return PersonJobBuilder{person_};
}
