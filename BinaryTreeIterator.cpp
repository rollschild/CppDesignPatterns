#include <iostream>
// #include <experimental/coroutine>
// #include <experimental/generator>

using namespace std;
// using namespace experimental;
template<typename T>
struct BinaryTree;

template<typename T>
struct Node {
  T value_{};
  Node<T>* left_{nullptr}; 
  Node<T>* right_{nullptr};
  Node<T>* parent_{nullptr};

  BinaryTree<T>* tree_{nullptr};

  Node(T value) : value_{value} {}

  Node(T value, Node<T>* left, Node<T>* right)
      : value_{value}, left_{left}, right_{right} {
    this->left_->tree_ = this->right_->tree_ = tree_;
    this->left_->parent_ = this->right_->parent_ = this;
  }

  Node(T value, Node<T>* left) 
      : value_{value}, left_{left} {
    this->left_->tree_ = tree_;
    this->left_->parent_ = this;
  }

  void SetTree(BinaryTree<T>* tree) {
    tree_ = tree;
    if (left_) left_->SetTree(tree);
    if (right_) right_->SetTree(tree);
  }

  ~Node() {
    if (left_) delete left_;
    if (right_) delete right_;
  }
};

template<typename T>
struct BinaryTree {
  // I guess it's a wrapper for root node.
  Node<T>* root_{nullptr};

  BinaryTree(Node<T>* root) : root_{root}, pre_order{*this} {
    root_->SetTree(this);
  }

  ~BinaryTree() {
    if (root_) delete root_;
  }

  template<typename U>
  struct PreOrderIterator {
    Node<U>* current_;

    PreOrderIterator(Node<U>* current) : current_{current} {}

    bool operator!=(const PreOrderIterator<U>& other) {
      return current_ != other.current_;
    }

    PreOrderIterator<U>& operator++() {
      if (current_->left_) {
        current_ = current_->left_;
      }
      else if (current_->right_) {
        current_ = current_->right_;
      }
      // current_ is a leaf
      else {
        Node<T>* p = current_->parent_;
        if (current_ == p->left_) {
          if (p->right_) {
            current_ = p->right_;
            return *this;
          }
        }
        current_ = p;
        p = p->parent_;
        while(p && current_ == p->left_) {
          if (p->right_) {
            current_ = p->right_;
            return *this;
          }
          current_ = p;
          p = p->parent_;
        }
        if (p)
          current_ = current_->right_;
        else 
          current_ = p;
      }
      return *this;
    }
    Node<U>& operator*() {
      return *current_;
    }
  }; // PreOrederIterator

  typedef PreOrderIterator<T> iterator;

  iterator begin() {
    Node<T>* node = root_;
    return iterator{node};
  }

  iterator end() {
    return iterator{nullptr};
  }

  class PreOrderTraversal {
   public:
    PreOrderTraversal(BinaryTree& tree) : tree_{tree} {}
    iterator begin() {
      return tree_.begin();
    }
    iterator end() {
      return tree_.end();
    }
   private:
    BinaryTree& tree_;
  } pre_order;
  /*
  generator<Node<T>*> PostOrder() {
    return PostOrderImplementation(root_);
  }
  */
 private:
  /*
  generator<Node<T>*> PostOrderImplementation(Node<T>* node) {
    if(node) {
      for(auto left : PostOrderImplementation(node->left_))
        co_yield left;
      for(auto right : PostOrderImplementation(node->right_))
        co_yield right;
      co_yield node;
    }
  }
  */
};

int main() {
  BinaryTree<string> family{
    new Node<string>{
      "me",
      new Node<string>{
        "mother", 
        new Node<string>{"mom's mom"},
        new Node<string>{"mom's dad"}
      },
      new Node<string>{
        "father",
        new Node<string>{"father's mom"}
      }
    }
  };

  for(auto itr = family.begin(); itr != family.end(); ++itr) {
    cout << (*itr).value_ << endl;
  }

  for(const auto& memeber : family.pre_order) {
    cout << memeber.value_ << endl;
  }
  /*
  cout << "User coroutine: " << endl;
  for(auto person : family.PostOrder()) {
    cout << person->value_ << endl;
  }
  */
  return 0;
}
