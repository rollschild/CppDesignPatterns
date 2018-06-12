#include <iostream>
#include <functional>

using namespace std;

struct Logger
{
  function<void()> func_;
  string name_;

  Logger(const function<void()>& func, const string& name)
      : func_{func}, name_{name} {}

  void operator()() const {
    cout << "Entering... " << name_ << endl;
    func_();
    cout << "Exiting... " << name_ << endl;
  }
};

template<typename Func>
struct FuncLogger
{
  Func func_;
  string name_;

  FuncLogger(const Func& func, const string& name)
      : func_{func}, name_{name} {}

  void operator()() const {
    cout << "Entering... " << name_ << endl;
    func_();
    cout << "Exiting... " << name_ << endl;
  }
};

template<typename Func>
auto GenerateFuncLogger(const Func& func, const string& name) {
  return FuncLogger<Func>{func, name};
  // It lets you infer type of Func from the argument list
}

double AddDouble(double left, double right) {
  cout << left << " + " << right << " = ";
  auto result = left + right;
  cout << result << endl;
  return result;
}

template<typename> struct AdvancedLogger;

template<typename R, typename ...Arguments>
struct AdvancedLogger<R(Arguments...)>
{
  function<R(Arguments...)> func_;
  string name_;

  AdvancedLogger(const function<R(Arguments...)>& func, const string& name)
      : func_{func}, name_{name} {}

  R operator()(Arguments... arguments) {
    cout << "Entering... " << name_ << endl;
    R result = func_(arguments...);
    cout << "Exiting... " << name_ << endl;
    return result;
  }
};

template<typename R, typename ...Arguments>
// It takes a function pointer
auto GenerateAdvancedLogger(R (*func)(Arguments...), const string& name) {
  return AdvancedLogger<R(Arguments...)>{function<R(Arguments...)>(func), 
                                         "AdvancedLogger"};
}

int main() {
  Logger([]() {cout << "Try this lamda." << endl;}, "TryThisFunction")();

  auto logger_name = GenerateFuncLogger(
      []() {cout << "Try this FuncLogger generator!" << endl;},
      "FuncLoggerGenerator");
  logger_name();

  auto advanced_logger = GenerateAdvancedLogger(AddDouble, "AddDouble_Logger");
  auto result = advanced_logger(100, 200);
  cout << result << endl;

  return 0;
}
