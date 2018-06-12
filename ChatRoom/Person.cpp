#include "Person.h"
#include "ChatRoom.h"

#include <vector>
#include <iostream>

Person::Person(const string& name) : name_{name} {}

void Person::Speak(const string& message) const {
  room_->Broadcast(name_, message);
}

void Person::PrivateMessage(const string& recipient, const string& message) const {
  room_->Message(name_, recipient, message);
}

void Person::Receive(const string& sender, const string& message) {
  string whole_message = sender + ": \"" + message + "\"";
  cout << "[" << name_ <<"'s chat session" << "]" << whole_message << endl;
  chat_log_.push_back(whole_message);
}

bool Person::operator==(const Person& rhs) const {
  return rhs.name_ == name_;
}

bool Person::operator!=(const Person& rhs) const {
  // return rhs.name_ != name_;
  return !(rhs == *this);
}
