#include <iostream>
#include <sstream>

using namespace std;

struct Expression {
  virtual void Print(ostringstream& oss) = 0;
};

struct DoubleExpression : Expression {
  double value_;

  explicit DoubleExpression(const double value) : value_{value} {}

  void Print(ostringstream& oss) override {
    oss << value_;
  }
};

struct AdditionExpression : Expression {
  Expression* left_;
  Expression* right_;

  AdditionExpression(Expression* const left, Expression* const right) 
      : left_{left}, right_{right} {}

  void Print(ostringstream& oss) override {
    oss << "(";
    left_->Print(oss);
    oss << " + ";
    right_->Print(oss);
    oss << ")";
  }

  ~AdditionExpression() {
    delete left_;
    delete right_;
  }
};

int main() {
  auto expression = new AdditionExpression{
    new DoubleExpression{3.2},
    new AdditionExpression{
      new DoubleExpression{6.6},
      new DoubleExpression{20.37}
    }
  };

  ostringstream oss;
  expression->Print(oss);

  cout << oss.str() << endl;

  delete expression;

  return 0;
}
