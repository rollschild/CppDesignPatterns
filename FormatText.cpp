#include <iostream>
#include <vector>
using namespace std;

class GoodFormat
{
 public:
  struct TextRange
  {
    int start_, end_;
    bool capitalize_;

    bool IsCovered(int position) const {
      return (position >= start_ && position <= end_);
    }
  };
    
  TextRange& SetRange(int start, int end) {
    formatting_.emplace_back(TextRange{start, end});
    return *formatting_.rbegin();
  }
  
  GoodFormat(const string& plain_text) : plain_text_{plain_text} {}

  friend ostream& operator<<(ostream& os, const GoodFormat& obj) {
    string result;
    for(int i = 0; i < obj.plain_text_.length(); ++i) {
      auto c = obj.plain_text_[i];
      for(const auto& range : obj.formatting_) {
        if(range.IsCovered(i) && range.capitalize_) {
          result += toupper(c);
        }
        else {
          result += c;
        }
      }
    }
    return os << result;
  }
 private:
  string plain_text_;
  vector<TextRange> formatting_;
};

int main() {
   GoodFormat plain_text{"I still believe in you."};

   plain_text.SetRange(8, 14).capitalize_ = true;

   cout << plain_text << endl;

   return 0;
}
