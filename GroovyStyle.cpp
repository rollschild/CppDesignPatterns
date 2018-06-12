#include <iostream>
#include <vector>
#include <string>

using namespace std;

namespace html {
  struct Tag
  {
    string name;
    string text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    friend ostream& operator<<(ostream& os, const Tag& tag) {
      os << "<" << tag.name;
      
      if(tag.attributes.size() != 0) {
        for(const auto& att : tag.attributes) {
          os << " " << att.first << "\"" << att.second << "\"";
        }
      }
      /*
      else {
        os << ">" << endl;
      }
      */
      if(tag.children.size() == 0 && tag.text.size() == 0) {
        os << "/>" << endl;
        // os << "</" << tag.name << ">" << endl;
      }
      else {
        os << ">" << endl;
        if(tag.text.size() != 0) {
          os << tag.text << endl;
        }

        for(const auto& child : tag.children) {
          os << child;
        }

        os << "</" << tag.name << ">" << endl;
      }

      return os;
    }

  protected:
    Tag(const string& name, const string& text) : name{name}, text{text} {}
    Tag(const string& name, const vector<Tag>& children) : name{name}, children{children} {}
  };

  struct Paragraph : Tag
  {
    explicit Paragraph(const string& text) : Tag{"p", text} {}

    Paragraph(initializer_list<Tag> children) : Tag{"p", children} {}
  };

  struct Image : Tag
  {
    explicit Image(const string& url) : Tag{"img", ""} {
      attributes.emplace_back(make_pair("src", url));
    }
  };
}

int main() {
  using namespace html;
  cout << "Tag <p> with no children nor text nor attributes:\n";
  cout << Paragraph{""} << endl;

  cout << "Tag <p> embedding <img>:\n";
  cout << Paragraph{Paragraph{Image{"https://www3.nd.edu/~ljordan/linux/images/tuxwhitebg.jpg"}}} << endl;

  return 0;
}
