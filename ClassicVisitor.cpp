#include <iostream>
#include <sstream>

using namespace std;

struct DoubleExpression;
struct AdditionExpression;
struct SubtractionExpression;

struct ExpressionVisitor {
  virtual void Visit(DoubleExpression* double_expression) = 0;
  virtual void Visit(AdditionExpression* addition_expression) = 0;
  virtual void Visit(SubtractionExpression* sub_expression) = 0;
};

struct ExpressionPrinter : ExpressionVisitor {
  ostringstream oss_;
  string Str() {
    return oss_.str();
  }
  void Visit(DoubleExpression* double_expression) override;
  void Visit(AdditionExpression* addition_expression) override;
  void Visit(SubtractionExpression* sub_expression) override;
};

struct ExpressionCalculator : ExpressionVisitor{
  double result_;
  void Visit(DoubleExpression* double_expression) override;
  void Visit(AdditionExpression* addition_expression) override;
  void Visit(SubtractionExpression* sub_expression) override;
};

struct Expression {
  // Accept() is a naming convention for functions like this
  virtual void Accept(ExpressionVisitor* visitor) = 0;
  virtual ~Expression() = default;
};

struct DoubleExpression : Expression {
  double value_;
  explicit DoubleExpression(const double value) : value_{value} {}
  void Accept(ExpressionVisitor* visitor) override {
    visitor->Visit(this);
  }
};

struct AdditionExpression : Expression {
  Expression* left_;
  Expression* right_;

  AdditionExpression(Expression* const left, Expression* const right) 
      : left_{left}, right_{right} {}

  void Accept(ExpressionVisitor* visitor) override {
    visitor->Visit(this);
  }

  ~AdditionExpression() {
    delete left_;
    delete right_;
  }
};

struct SubtractionExpression : Expression {
  Expression* left_;
  Expression* right_;

  SubtractionExpression(Expression* const left, Expression* const right)
      : left_{left}, right_{right} {}

  void Accept(ExpressionVisitor* visitor) override {
    visitor->Visit(this);
  }

  ~SubtractionExpression() {
    delete left_;
    delete right_;
  }
};

void ExpressionPrinter::Visit(DoubleExpression* double_expression) {
  oss_ << double_expression->value_;
}

void ExpressionPrinter::Visit(AdditionExpression* addition_expression) {
  addition_expression->left_->Accept(this);

  oss_ << " + ";

  // bool braces = dynamic_cast<SubtractionExpression*>(addition_expression->right_);
  
  // if (braces) oss_ << "(";

  addition_expression->right_->Accept(this);

  // if (braces) oss_ << ")";
}

void ExpressionPrinter::Visit(SubtractionExpression* sub_expression) {
  bool sub_braces = dynamic_cast<SubtractionExpression*>(sub_expression->right_);
  bool add_braces = dynamic_cast<AdditionExpression*>(sub_expression->right_);
  sub_expression->left_->Accept(this);
  oss_ << " - ";
  if (sub_braces || add_braces) oss_ << "(";
  // oss_ << "(";
  sub_expression->right_->Accept(this);
  if (sub_braces || add_braces) oss_ << ")";
  // oss_ << ")";
}

void ExpressionCalculator::Visit(DoubleExpression* double_expression) {
  result_ = double_expression->value_;
}

void ExpressionCalculator::Visit(AdditionExpression* addition_expression) {
  addition_expression->left_->Accept(this);
  double tmp = result_;
  addition_expression->right_->Accept(this);
  result_ += tmp;
}

void ExpressionCalculator::Visit(SubtractionExpression* sub_expression) {
  sub_expression->left_->Accept(this);
  double tmp = result_;
  sub_expression->right_->Accept(this);
  result_ = tmp - result_;
}


int main() {
  auto expression = new SubtractionExpression{
    new DoubleExpression{3.2},
    new SubtractionExpression{
      new DoubleExpression{6.6},
      new DoubleExpression{20.37}
    }
  };
  ExpressionPrinter expression_printer;
  expression_printer.Visit(expression);
  cout << expression_printer.Str() << endl;

  ExpressionCalculator expression_calculator;
  expression_calculator.Visit(expression);
  cout << expression_calculator.result_ << endl;
  delete expression;

  return 0;
}
