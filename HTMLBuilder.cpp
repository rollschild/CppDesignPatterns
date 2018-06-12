#include <iostream>
#include <sstream>
#include <vector>
#include <memory>

using namespace std;

struct HtmlBuilder;

struct HtmlElement
{
  string name;
  string text;
  vector<HtmlElement> elements;
  const size_t indent_size = 2;
  HtmlElement() {}
  HtmlElement(const string& name, const string& text)
    : text(text), name(name)
  {
  }

  string str(int indent = 0) const {
    ostringstream oss;
    string idt(indent * indent_size, ' ');
    oss << idt << "<" << name << ">" << endl;
    if(text.size() > 0) {
      oss << string((indent + 1) * indent_size, ' ') << text << endl;
    }

    for(const auto& element : elements) {
      oss << element.str(indent + 1);
    }

    oss << idt << "</" << name << ">" << endl;
    return oss.str();
  }

  static unique_ptr<HtmlBuilder> build(string root_name) {
      return make_unique<HtmlBuilder>(root_name);
  }
};

struct HtmlBuilder
{
  HtmlElement root;
  HtmlBuilder(string root_name) {
    root.name = root_name;
  }

  HtmlBuilder& add_element(string ele_name, string ele_text) {
    HtmlElement element{ele_name, ele_text};
    root.elements.emplace_back(element);
    
    return *this;
  }

  string str() const {
    return root.str();
  }
};

int main() {
  HtmlBuilder builder{"ul"};

  // Fluent interface
  builder.add_element("li", "hello").add_element("li", "world");
  cout << builder.str() << endl;

  return 0;
}
