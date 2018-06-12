#include <iostream>
#include <vector>
#include <sstream>

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

int main() {
  string input{"(1222+43)-(16-55)"};
  auto tokens = Lex(input);

  for(auto& t : tokens) {
    cout << t << " ";
  }
  cout << endl;
  return 0;
}
