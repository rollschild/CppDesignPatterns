#include <iostream>
#include <vector>
#include <memory>
using namespace std;

class Memento {
 public:
  Memento(const int balance) : balance_{balance} {}
  friend class BankAccount;
  friend class BetterBankAccount;
 private:
  int balance_;
};

class BankAccount {
 public:
  BankAccount(const int balance) : balance_{balance} {}
  
  Memento Deposit(int amount) {
    balance_ += amount;
    return {balance_};
  }

  void Restore(const Memento& memento) {
    balance_ = memento.balance_;
  }

  friend ostream& operator<<(ostream& os, const BankAccount& account) {
    return os
        << "The account balance is now: "
        << account.balance_
        << "\n";
  }

 private:
  int balance_{0};
};

class BetterBankAccount {
 public:
  explicit BetterBankAccount(const int balance) : balance_{balance} {
    changes_.push_back(make_shared<Memento>(balance));
    index_ = 0;
  }

  shared_ptr<Memento> Deposit(const int amount) {
    balance_ += amount;
    auto memento = make_shared<Memento>(balance_);
    changes_.push_back(memento);
    ++index_;
    return memento;
  }

  void Restore(const shared_ptr<Memento>& memento) {
    if (memento) {
      balance_ = memento->balance_;
      changes_.push_back(memento); // it's also a change
      index_ = changes_.size() - 1;
    } 
  }

  shared_ptr<Memento> Undo() {
    if (index_ > 0) {
      --index_;
      auto memento = changes_[index_];
      balance_ = memento->balance_;
      return memento;
    }
    
    return {};
  }

  shared_ptr<Memento> Redo() {
    if (index_ + 1 < changes_.size()) {
      ++index_;
      auto memento = changes_[index_];
      balance_ = memento->balance_;
      return memento;
    }

    return {};
  }

  friend ostream& operator<<(ostream& os, const BetterBankAccount& account) {
    return os
        << "Current accout balance is: "
        << account.balance_ 
        << "\n";
  }

 private:
  int balance_{0};
  vector<shared_ptr<Memento>> changes_;
  int index_;
};

int main() {
  cout << "Ordinary account: \n";
  BankAccount account{2037};
  cout << account;
  auto memento_1 = account.Deposit(100);
  cout << account;
  auto memento_2 = account.Deposit(20);

  cout << account;

  account.Restore(memento_1);
  cout << account;

  account.Restore(memento_2);
  cout << account;

  cout << "Better account: \n";
  BetterBankAccount better_account{5237};
  cout << better_account;
  auto memento_3 = better_account.Deposit(600);
  cout << better_account;
  auto memento_4 = better_account.Deposit(1234);
  cout << better_account;
  better_account.Restore(memento_3);
  cout << better_account;
  auto memento_5 = better_account.Undo();
  cout << better_account;
  auto memento_6 = better_account.Redo();
  cout << better_account;
  return 0;
}
