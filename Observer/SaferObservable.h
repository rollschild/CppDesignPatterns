#ifndef SAFEROBSERVABLE_H_
#define SAFEROBSERVABLE_H_

#include <string>
#include <vector>
#include <algorithm>
#include <mutex>
// #include <thread>
using namespace std;

template<typename> struct Observer;

template<typename T>
struct SaferObservable {
 public:
  void Notify(T& source, const string& field_name) {
    lock_guard<mutx_> lock{mtx_};
    // scoped_lock<mutx_> lock{mtx_};
    for(auto observer : observers_) {
      observer->FieldChanged(source, field_name);
    }
  }

  void Subscribe(Observer<T>& observer) {
    lock_guard<mutx_> lock{mtx_};
    observers_.push_back(&observer);
  }

  void Unsubscribe(Observer<T>& observer) {
    lock_guard<mutx_> lock{mtx_};
    observers_.erase(
      remove(observers_.begin(), observers_.end(), &observer),
      observers_.end()
    );
  }
   
 private:
  vector<Observer<T>*> observers_;
  typedef mutex mutx_;
  mutx_ mtx_;
};

#endif // SAFEROBSERVABLE_H_
