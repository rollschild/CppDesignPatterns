#include <iostream>
#include <vector>

using namespace std;

struct BankAccount {
  int balance_ = 0;
  int threshold_ = 0;
  
  void Deposit(int amount) {
    balance_ += amount;
    cout << "Deposit: " << amount << "\n" 
        << "Balance: " << balance_ << endl;
  }

  bool Withdraw(int amount) {
    if (balance_ - amount >= threshold_) {
      balance_ -= amount;
      cout << "Withdrew: " << amount << "\n"
          << "Balance: " << balance_ << endl;
      return true;
    }
    else {
      return false;
    }
  }
};

struct Command {
  bool success_;
  virtual void Do() = 0;
  virtual void Undo() = 0;
};

struct BankAccountCommand : Command {
  BankAccount& account_;
  enum Action {deposit_, withdraw_} action_;
  int amount_;

  BankAccountCommand(BankAccount& account, const Action action, const int amount)
      : account_{account}, action_{action}, amount_{amount} {
    success_ = false;    
  }

  void Do() override {
    switch (action_) {
      case deposit_:
        account_.Deposit(amount_);
        success_ = true;
        break;
      case withdraw_:
        success_ = account_.Withdraw(amount_);
        break;
    }
  }

  void Undo() override {
    if (!success_) return;
    switch (action_) {
      case deposit_:
        account_.Withdraw(amount_);
        break;
      case withdraw_:
        if (success_ == true) {
          account_.Deposit(amount_);
        }
        break;
    }
  }
};

struct CompositeBankAccountCommand : vector<BankAccountCommand>, Command {
  CompositeBankAccountCommand(const initializer_list<value_type>& actions)
      : vector<BankAccountCommand>(actions) {}

  void Do() override {
    for(auto& command : *this) {
      command.Do();
    } 
  }

  void Undo() override {
    for(auto it = rbegin(); it != rend(); ++it) {
      it->Undo();
    }
  }
};

struct DependentCompositeBankCommand : CompositeBankAccountCommand {
  explicit DependentCompositeBankCommand(const initializer_list<value_type>& actions)
      : CompositeBankAccountCommand{actions} {}

  void Do() override {
    // It depends on the success of previous command
    bool previous_command_success = true;
    for(auto& command : *this) {
      if (previous_command_success) {
        command.Do();
        previous_command_success = command.success_;
      }
      else {
        command.success_ = false;
      }
    }
  }
};

struct TransferCommand : DependentCompositeBankCommand {
  TransferCommand(BankAccount& source, BankAccount& destination, int amount)
      : DependentCompositeBankCommand{
          BankAccountCommand{source, BankAccountCommand::withdraw_, amount},
          BankAccountCommand{destination, BankAccountCommand::deposit_, amount}
        } {}
};

int main() {
  BankAccount account_source;
  BankAccount account_destination;

  CompositeBankAccountCommand commands{
    BankAccountCommand{account_source, BankAccountCommand::deposit_, 2037},
    BankAccountCommand{account_destination, BankAccountCommand::deposit_, 10}
  };

  commands.Do();
  
  cout << "Destination account: " << account_destination.balance_ << endl;

  commands.Undo();
  cout << "After undo, ";
  cout << "Source account balance: " << account_source.balance_ << endl;

  commands.Do();
  TransferCommand transfer{account_source, account_destination, 2000};
  transfer.Do();
  cout << "After redo and tranfer, ";
  cout << "Source balance: " << account_source.balance_ 
      << " and destination balance: " << account_destination.balance_ 
      << endl;

  return 0;
}
