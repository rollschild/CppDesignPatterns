// This method is using RTTI

#include <iostream>
#include <sstream>

using namespace std;

template<typename Visitable>
struct Visitor {
  virtual void Visit(Visitable& obj) = 0; 
};

struct MockVisitor {
  virtual ~MockVisitor() = default;
};

struct Expression {
  virtual void Accept(MockVisitor& mock_visitor) {
    using EV = Visitor<Expression>;
    if (auto expression = dynamic_cast<EV*>(&mock_visitor)) {
      expression->Visit(*this);
    }
  }

  virtual ~Expression() = default;
};

struct DoubleExpression : Expression {
  double value_;
  DoubleExpression(const double value) : value_{value} {}
  // why don't we use override???
  void Accept(MockVisitor& mock_visitor) override {
    using DEV = Visitor<DoubleExpression>;
    if (auto expression = dynamic_cast<DEV*>(&mock_visitor)) {
      expression->Visit(*this);
    }
  }
};

struct AdditionExpression : Expression {
  Expression* left_;
  Expression* right_;
  AdditionExpression(Expression* const left, Expression* const right)
      : left_{left}, right_{right} {}

  void Accept(MockVisitor& mock_visitor) override {
    using ADV = Visitor<AdditionExpression>;
    if (auto expression = dynamic_cast<ADV*>(&mock_visitor)) {
      expression->Visit(*this); 
    }
  }

  ~AdditionExpression() {
    delete left_;
    delete right_;
  }
};

struct ExpressionPrinter : MockVisitor, 
                           Visitor<DoubleExpression>, 
                           Visitor<AdditionExpression> {
 public:
  /*
  void Visit(Expression& obj) override {
    
  }
  */
  void Visit(DoubleExpression& obj) override {
    oss_ << obj.value_;
  }

  void Visit(AdditionExpression& obj) override {
    oss_ << "(";
    obj.left_->Accept(*this);
    oss_ << " + ";
    obj.right_->Accept(*this);
    oss_ << ")";
  }

  string Str() const {
    return oss_.str();
  }

 private:
  ostringstream oss_;
};

int main() {
  auto expression = new AdditionExpression{
    new DoubleExpression{20.37},
    new AdditionExpression{
      new DoubleExpression{10.21},
      new DoubleExpression{10.26}
    }
  };

  ExpressionPrinter expression_printer;
  expression_printer.Visit(*expression);
  cout << expression_printer.Str() << endl;

  return 0;
}
