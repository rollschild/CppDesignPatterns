#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <string>

using namespace std;

template<typename T>
struct Observer {
  virtual void FieldChanged(T& source, const string& field_name) = 0;
};

#endif // OBSERVER_H_
