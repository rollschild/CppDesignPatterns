#include <iostream>
#include <algorithm>

#include <boost/iterator/iterator_facade.hpp>

using namespace std;
using namespace boost;

struct Node {
  string value_;
  Node* next_ = nullptr;

  explicit Node(const string& value) : value_{value} {}

  Node(const string& value, Node* parent) : value_{value} {
    parent->next_ = this;
  }
};

struct ListIterator : iterator_facade<ListIterator, Node, forward_traversal_tag> {
  Node* current_ = nullptr;

  ListIterator() {}

  explicit ListIterator(Node* const current) : current_{current} {}

 private:
  friend class iterator_core_access;
  void increment() {
    current_ = current_->next_;
  }
  bool equal(const ListIterator& other) const {
    return current_ == other.current_;
  }

  Node& dereference() const {
    return *current_;
  }
};

int main() {
  Node alpha{"alpha"};
  Node beta{"beta", &alpha};
  Node gamma{"gamma", &beta};
  Node fai{"fai", &gamma};

  for_each(ListIterator{&alpha}, ListIterator{}, [](const Node& node) {
    cout << node.value_ << endl; 
  });

  return 0;
}
