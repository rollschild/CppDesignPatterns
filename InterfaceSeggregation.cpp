#include <iostream>

using namespace std;

struct Document;

struct Printer
{
  virtual void print(Document& doc) = 0;
};

struct Scanner
{
  virtual void scan(Document& doc) = 0;
};

struct MyPrinter : Printer
{
  void print(Document& doc) override {
    
  }
};

struct MyScanner : Scanner
{
  void scan(Document& doc) override {
  
  }
};

struct Machine : Printer, Scanner
{

};
struct MyMachine : Machine
{
  Printer& printer;
  Scanner& scanner;

  MyMachine(Printer& printer, Scanner& scanner)
      : printer(printer), scanner(scanner) {}

  void print(Document& doc) override {
    printer.print(doc);
  }

  void scan(Document& doc) override {
    scanner.scan(doc);
  }
};

int main() {
  return 0;
}
