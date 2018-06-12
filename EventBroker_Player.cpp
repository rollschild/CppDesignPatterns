#include <iostream>
#include <vector>

#include <boost/signals2.hpp>

using namespace std;
using namespace boost;
using namespace signals2;

struct EventData {
  virtual void Print() const = 0;
  virtual ~EventData() = default;
};

struct PlayerScoreData : EventData {
  string player_name_;
  int score_so_far_;

  PlayerScoreData(const string& name, const int goals)
      : player_name_{name}, score_so_far_{goals} {}

  void Print() const override {
    cout << "Player " << player_name_ << " scored " << score_so_far_ << " goals!" << endl;
  }
};

struct Game {
  signal<void(EventData*)> events_;
};

struct Player {
  Game& game_;
  string name_;
  int goals_ = 0;

  Player(const string& name, Game& game) : name_{name}, game_{game} {} 

  void Score() {
    ++goals_;
    PlayerScoreData player_socre_data{name_, goals_};
    player_socre_data.Print();
    game_.events_(&player_socre_data);
  }
};

struct Coach {
  Game& game_;

  explicit Coach(Game& game) : game_{game} {
    game_.events_.connect([](EventData* event_data) {
      PlayerScoreData* player_socre_data_ptr = dynamic_cast<PlayerScoreData*>(event_data);
      if (player_socre_data_ptr && player_socre_data_ptr->score_so_far_ < 3) {
        cout << "Coach says: well done, " << player_socre_data_ptr->player_name_ << "!\n";
      }
    });
  }
};

int main() {
  Game game;
  Player player{"Tony", game};
  Coach coach{game};

  player.Score();
  player.Score();
  player.Score();
  player.Score();

  return 0;
}
