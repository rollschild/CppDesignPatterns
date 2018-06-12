#include <iostream>
#include <vector>
#include <sstream>
#include <memory>
#include <boost/lexical_cast.hpp>
using namespace std;
struct Token {
  enum Type {intger_, plus_, minus_, l_paren_, r_paren_} type_;
  string text_;

  Token(Type type, const string text) : type_{type}, text_{text} {}

  friend ostream& operator<<(ostream& os, const Token& token) {
    return os
        << "`" << token.text_ << "`";
  }
};

vector<Token> Lex(string input) {
  vector<Token> result;

  for(int i = 0; i < input.length(); ++i) {
    switch (input[i]) {
      case '+':
        result.push_back(Token{Token::plus_, "+"});
        break;
      case '-':
        result.push_back(Token{Token::minus_, "-"});
        break;
      case '(':
        result.push_back(Token{Token::l_paren_, "("});
        break;
      case ')':
        result.push_back(Token{Token::r_paren_, ")"});
        break;
      default:
        ostringstream buffer;
        buffer << input[i];
        for(int j = i + 1; j < input.length(); ++j) {
          if (isdigit(input[j])) {
            buffer << input[j];
            ++i;
          }
          else {
            result.push_back(Token{Token::intger_, buffer.str()});
            // We do NOT increase index i here!!!
            break;
          }
        }
    }
  }

  return result;
}

struct Element {
  virtual int Evaluation() const = 0;
};

struct Integer : Element {
  int value_;
  Integer(int value) : value_{value} {}

  int Evaluation() const override {
    return value_;
  }
};

struct BinaryOperation : Element {
  enum Operation {addition_, subtraction_} operation_;
  shared_ptr<Element> lhs_, rhs_;

  int Evaluation() const override {
    if (operation_ == addition_) {
      return lhs_->Evaluation() + rhs_->Evaluation();
    }
    else {
      return lhs_->Evaluation() - rhs_->Evaluation();
    }
  }
};

shared_ptr<Element> Parse(vector<Token>& tokens) {
  auto result_ = make_unique<BinaryOperation>();
  bool lhs_exist_ = false;

  for(int i = 0; i < tokens.size(); ++i) {
    auto token = tokens[i];
    switch (token.type_) {
      case Token::intger_:
      {
        int value = boost::lexical_cast<int>(token.text_);
        auto integer = make_shared<Integer>(value);
        if (!lhs_exist_) {
          result_->lhs_ = integer;
          lhs_exist_ = true;
        }
        else {
          result_->rhs_ = integer;
        }
        // break;
      }
        break;
      case Token::plus_:
        result_->operation_ = BinaryOperation::addition_;
        break;
      case Token::minus_:
        result_->operation_ = BinaryOperation::subtraction_;
        break;
      case Token::l_paren_:
      {
        int j = i;
        for(; j < tokens.size(); ++j) {
          auto expression = tokens[j];
          if (expression.type_ == Token::r_paren_) {
            break;
          }
        }
        vector<Token> sub_expression(&tokens[i + 1], &tokens[j]);
        auto element = Parse(sub_expression);
        if (!lhs_exist_) {
          result_->lhs_ = element;
          lhs_exist_ = true;
        }
        else {
          result_->rhs_ = element;
        }
        i = j;
      }
        break;
      case Token::r_paren_:
        break;
    }
  }

  return result_;
}

int main() {
  string input{"(1222+43)-(16-55)"};
  auto tokens = Lex(input);

  for(auto& t : tokens) {
    cout << t << " ";
  }
  cout << endl;

  try {
    auto cooked = Parse(tokens);
    int result = cooked->Evaluation();
    cout << input << " = " << result << endl;
  }
  catch (const exception& e){
    cout << e.what() << endl;
  }
  return 0;
}
