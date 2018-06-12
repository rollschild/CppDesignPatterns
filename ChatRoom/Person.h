#ifndef PERSON_H_
#define PERSON_H_

// #include "ChatRoom.h"
#include <vector>
#include <string>

struct ChatRoom;

using namespace std;

struct Person {
  string name_;
  ChatRoom* room_{nullptr};
  vector<string> chat_log_;

  Person(const string& name);

  void Speak(const string& message) const;
  void PrivateMessage(const string& recipient, const string& message) const;

  void Receive(const string& sender, const string& message);

  bool operator==(const Person& rhs) const;
  bool operator!=(const Person& rhs) const;
};


#endif // PERSON_H_
