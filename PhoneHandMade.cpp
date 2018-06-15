#include <iostream>
#include <map>
#include <vector>

using namespace std;

enum class PhoneState {
  OffHook,
  Connecting,
  Connected,
  OnHold,
  OnHook
};

inline ostream& operator<<(ostream& os, const PhoneState& state) {
  switch (state) {
    case PhoneState::OffHook:
      os << "Off the hook";
      break;
    case PhoneState::Connecting:
      os << "Connecting...";
      break;
    case PhoneState::Connected:
      os << "Connected";
      break;
    case PhoneState::OnHold:
      os << "OnHold";
      break;
    case PhoneState::OnHook:
      os << "OnHook";
      break;
  }

  return os;
};

enum class Trigger {
  Dialed,
  HungUp,
  CallConnected,
  PlacedOnHold,
  TakenOffHold,
  LeftMessage,
  StopUsingPhone
};

inline ostream& operator<<(ostream& os, const Trigger& trigger) {
  switch (trigger) {
    case Trigger::Dialed:
      cout << "Call dialed";
      break;
    case Trigger::HungUp:
      cout << "Call hung up";
      break;
    case Trigger::CallConnected:
      cout << "Call is connected!";
      break;
    case Trigger::PlacedOnHold:
      cout << "Call is on hold";
      break;
    case Trigger::TakenOffHold:
      cout << "Call is taken off hold!";
      break;
    case Trigger::LeftMessage:
      cout << "Left a message!";
      break;
    case Trigger::StopUsingPhone:
      cout << "Phone ended!";
      break;
  }

  return os;
};

int main() {
  map<PhoneState, vector<pair<Trigger, PhoneState>>> actions;

  actions[PhoneState::OffHook] = {
    {Trigger::Dialed, PhoneState::Connecting},
    {Trigger::StopUsingPhone, PhoneState::OnHook}
  };

  actions[PhoneState::Connecting] = {
    {Trigger::CallConnected, PhoneState::Connected},
    {Trigger::HungUp, PhoneState::OffHook}
  };

  actions[PhoneState::Connected] = {
    {Trigger::HungUp, PhoneState::OffHook},
    {Trigger::PlacedOnHold, PhoneState::OnHold},
    {Trigger::LeftMessage, PhoneState::OffHook}
  };

  actions[PhoneState::OnHold] = {
    {Trigger::TakenOffHold, PhoneState::Connected},
    {Trigger::HungUp, PhoneState::OffHook}
  };

  PhoneState current_state{PhoneState::OffHook};
  PhoneState exit_state{PhoneState::OnHook};

  while(true) {
    cout << "The phone is currently " << current_state << endl;
  SELECT_TRIGGER:
    cout << "Select a trigger: " << endl;
    int option = 0;
    for(auto trigger : actions[current_state]) {
      // list all options
      cout << option++ << ", " << trigger.first << endl;
    }

    int input;
    cin >> input;
    if (input >= 0 && input < actions[current_state].size()) {
      current_state = actions[current_state][input].second;
      if (current_state == exit_state) break;
    }
    else {
      goto SELECT_TRIGGER;
    }
  }

  cout << "We are done using the phone." << endl;
  return 0;
}
