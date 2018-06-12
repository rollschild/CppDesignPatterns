#ifndef CHATROOM_H_
#define CHATROOM_H_

#include "Person.h"
#include <vector>
#include <algorithm>

using namespace std;

struct ChatRoom {
  vector<Person*> people_;

  void Broadcast(const string& sender, const string& message);
  void Join(Person* member);
  void Message(const string& sender, const string& recipient,
               const string& message) {
    auto target = find_if(
        begin(people_),
        end(people_),
        [&](const Person* person) {
          return person->name_ == recipient;
        });
    
    if(target != end(people_)) {
      (*target)->Receive(sender, message);
    }
  }
};

#endif // CHATROOM_H_
