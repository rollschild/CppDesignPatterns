#include <iostream>

using namespace std;

class LightSwitch;

struct State {
  virtual void On(LightSwitch* light_switch) {
    cout << "Hey! The light is already on!\n";
  }

  virtual void Off(LightSwitch* light_switch) {
    cout << "Hey! The light is already off!\n";
  }
};

struct OnState : State {
  OnState() {
    cout << "Light is on.\n";
  }

  void Off(LightSwitch* light_switch) override;
};

struct OffState : State {
  OffState() {
    cout << "Light is off.\n";
  }

  void On(LightSwitch* light_switch) override;
};

class LightSwitch {
 public:
  LightSwitch() {
    state_ = new OffState();
  }

  void SetState(State* state) {
    this->state_ = state;
  }

  void On() {
    state_->On(this);
  }

  void Off() {
    state_->Off(this);
  }

 private:
  State* state_;
};

void OnState::Off(LightSwitch* light_switch) {
  cout << "Turning light off...\n";
  light_switch->SetState(new OffState());
  delete this;
}

void OffState::On(LightSwitch* light_switch) {
  cout << "Turning light on...\n";
  light_switch->SetState(new OnState());
  delete this;
}

int main() {
  LightSwitch light_switch;
  light_switch.On();
  light_switch.Off();
  light_switch.Off();

  return 0;
}

