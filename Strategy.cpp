#include <iostream>
#include <sstream>
#include <memory>
#include <vector>

using namespace std;

enum class OutputFormat {
  Markdown,
  Html
};

struct ListStrategy {
  virtual void Start(ostringstream& oss) {};
  virtual void AddToList(ostringstream& oss, const string& item) {};
  virtual void End(ostringstream& oss) {};
  virtual ~ListStrategy() = default;
};

struct MarkdownStrategy : ListStrategy {
  void AddToList(ostringstream& oss, const string& item) override {
    oss << "* " << item << endl;
  }
};

struct HtmlStrategy : ListStrategy {
  void Start(ostringstream& oss) override {
    oss << "<ul>" << endl;
  }

  void End(ostringstream& oss) override {
    oss << "</ul>" << endl;
  }

  void AddToList(ostringstream& oss, const string& item) override {
    oss << " " << "<li>" << item << "</li>" << endl;
  }
};

struct TextProcessor {
 public:
  void Clear() {
    oss_.str("");
    oss_.clear();
  }

  void SetOutput(const OutputFormat& format) {
    switch (format) {
      case OutputFormat::Markdown:
        list_strategy_ = make_unique<MarkdownStrategy>();
        break;
      case OutputFormat::Html:
        list_strategy_ = make_unique<HtmlStrategy>();
        break;
      default:
        throw runtime_error("Unsupported strategy!!!\n");
    }
  }

  void AppendToList(const vector<string>& items) {
    list_strategy_->Start(oss_);
    for(auto& item : items) {
      list_strategy_->AddToList(oss_, item);
    }
    list_strategy_->End(oss_);
  }

  string Str() const {
    return oss_.str();
  }

 private:
  ostringstream oss_;
  unique_ptr<ListStrategy> list_strategy_;
};

int main() {
  TextProcessor text_processor;

  text_processor.SetOutput(OutputFormat::Markdown);
  text_processor.AppendToList({"Raging Bull", "Godfather", "Ocean's Eleven"});
  cout << text_processor.Str() << endl;

  text_processor.Clear();
  
  text_processor.SetOutput(OutputFormat::Html);
  text_processor.AppendToList({"body", "text", "url"});
  cout << text_processor.Str() << endl;

  text_processor.Clear();
  return 0;
}
