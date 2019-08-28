#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
  os << "{";
  bool first = true;
  for (const auto& x : s) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << x;
  }
  return os << "}";
}

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
  os << "{";
  bool first = true;
  for (const auto& kv : m) {
    if (!first) {
      os << ", ";
    }
    first = false;
    os << kv.first << ": " << kv.second;
  }
  return os << "}";
}

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint = {}) {
  if (t != u) {
    ostringstream os;
    os << "Assertion failed: " << t << " != " << u;
    if (!hint.empty()) {
       os << " hint: " << hint;
    }
    throw runtime_error(os.str());
  }
}

void Assert(bool b, const string& hint) {
  AssertEqual(b, true, hint);
}

class TestRunner {
public:
  template <class TestFunc>
  void RunTest(TestFunc func, const string& test_name) {
    try {
      func();
      cerr << test_name << " OK" << endl;
    } catch (exception& e) {
      ++fail_count;
      cerr << test_name << " fail: " << e.what() << endl;
    } catch (...) {
      ++fail_count;
      cerr << "Unknown exception caught" << endl;
    }
  }

  ~TestRunner() {
    if (fail_count > 0) {
      cerr << fail_count << " unit tests failed. Terminate" << endl;
      exit(1);
    }
  }

private:
  int fail_count = 0;
};

bool IsPalindrom(const string& str) {

    string s = str;

    // переберём все символы s[i] из первой половины строки
    for (size_t i = 0; i < s.size() / 2; ++i) {
        // s[s.size() - i - 1] — символ, симметричный символу s[i]
        if (s[i] != s[s.size() - i - 1]) {
            return false;  // если они не совпадают, строка точно не палиндром
        }
    }

    // если все пары символов совпадают, строка — палиндром
    return true;
}

void TestIsPalindrom(){
    Assert(IsPalindrom("aaa"), "");
    Assert(IsPalindrom("aba"), "");
    Assert(IsPalindrom(""), "");
    Assert(IsPalindrom("aa"), "");
    Assert(IsPalindrom("a"), "");
    Assert(IsPalindrom("aaa bb aaa"), "");
    Assert(IsPalindrom("baaab"), "");
    Assert(IsPalindrom("baab"), "");
    Assert(IsPalindrom(" "), "");
    Assert(!IsPalindrom("aaab"), "");
    Assert(!IsPalindrom("baaa"), "");
    Assert(!IsPalindrom("aaa bbaaa"), "");
}


int main() {
  TestRunner runner;
  runner.RunTest(TestIsPalindrom, "TestIsPalindrome");
  // добавьте сюда свои тесты
  return 0;
}
