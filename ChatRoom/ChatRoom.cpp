#include "Person.h"
#include "ChatRoom.h"

#include <vector>
#include <algorithm>

using namespace std;

void ChatRoom::Broadcast(const string& sender, const string& message) {
  for(auto person : people_) {
    if (person->name_ != sender) {
      person->Receive(sender, message);
    }
  }
}

void ChatRoom::Join(Person* member) {
  string welcome = member->name_ + " joins the chat!";
  Broadcast("room", welcome);
  member->room_ = this;
  people_.push_back(member);
}  
