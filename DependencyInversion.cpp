#include <iostream>
#include <vector>
#include <tuple>

using namespace std;

enum class Relationship {parent, child, sibling,};

struct Person
{
  string name;
};

struct RelationshipBrowser
{
  virtual vector<Person> find_all_children_of(const string& name) = 0;
};

struct Relationships : RelationshipBrowser
{
  vector<tuple<Person, Relationship, Person>> relations;

  void add_parent_and_child(const Person& parent, const Person& child) {
    relations.push_back({parent, Relationship::parent, child});
    relations.push_back({child, Relationship::child, parent});
  }

  vector<Person> find_all_children_of(const string& name) override {
    vector<Person> result;
    
    for(auto&& [lhs, rel, rhs] : relations) {
      if(lhs.name == name && rel == Relationship::parent) {
        result.push_back(rhs);
      }
    }
    return result;
  }
};

struct Research
{
  Research(RelationshipBrowser& browser) {
    for(auto& child : browser.find_all_children_of("John")) {
      cout << "John has a child called " << child.name << ".\n";
    }
  }
};

int main() {
  Person parent{"John"};
  Person child_1{"James"}, child_2{"Susan"}, child_3{"Christohper"};
  Relationships relationships;
  relationships.add_parent_and_child(parent, child_1);
  relationships.add_parent_and_child(parent, child_2);
  relationships.add_parent_and_child(parent, child_3);

  Research _(relationships);

  return 0;
}
