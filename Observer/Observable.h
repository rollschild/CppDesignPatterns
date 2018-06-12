#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include <string>
#include <vector>
#include <algorithm>

using namespace std;

template<typename> struct Observer;

template<typename T>
struct Observable {
 public:
  void Notify(T& source, const string& field_name) {
    for(auto observer : observers_) {
      observer->FieldChanged(source, field_name);
    }
  }

  void Subscribe(Observer<T>& observer) {
    observers_.push_back(&observer);
  }

  void Unsubscribe(Observer<T>& observer) {
    observers_.erase(
      remove(observers_.begin(), observers_.end(), &observer),
      observers_.end()
    );
  }
   
 private:
  vector<Observer<T>*> observers_;
};

#endif // OBSERVABLE_H_
