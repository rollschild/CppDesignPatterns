#include <iostream>

using namespace std;

class Game {
 public:
  Game(int num_of_players) : num_of_players_{num_of_players} {}

  void Run() {
    Start();
    while(!HaveWinner()) {
      TakeTurn();  
    }
    cout << "Player " << GetWinner() << " wins the game.\n";
  }

 protected:
  virtual void Start() = 0;
  virtual bool HaveWinner() = 0;
  virtual void TakeTurn() = 0;
  virtual int GetWinner() = 0;
  int num_of_players_;
  int current_player_{0};
};

class Chess : public Game {
 public:
  Chess() : Game{2} {}
 
 protected:
  void Start() override {
    cout << "Game of Chess starts with " << num_of_players_ << " players!\n";
  }

  bool HaveWinner() override {
    return turns == max_turns;
  }

  void TakeTurn() {
    cout << "Turn " << turns << " taken by player " << current_player_ << "\n";
    ++turns;
    current_player_ = (current_player_ + 1) % num_of_players_;
  }

  int GetWinner() {
    return current_player_; 
  }

 private:
  int turns{0};
  int max_turns{12};
};

int main() {
  Chess chess;

  chess.Run();

  return 0;
}
