#include <iostream>
#include <fstream>
#include <cstdio>
#include <vector>
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

struct Journal
{
  string title;
  vector<string> entries;

  Journal(const string& title) : title(title) {}

  void add_entry(const string& entry) {
    static int count = 1;
    entries.push_back(lexical_cast<string>(count++) + ": " + entry);
  }
};

struct PersistenceManager
{
  static void save(const Journal& journal, const string& filename) {
    ofstream ofs(filename);
    for(auto& e : journal.entries) {
      ofs << e << endl;
    }
  }
};

int main() {
  Journal journal{"Posts"};
  journal.add_entry("The first post.");
  journal.add_entry("The second post.");

  PersistenceManager manager;
  manager.save(journal, "posts.txt");

  return 0;
}
