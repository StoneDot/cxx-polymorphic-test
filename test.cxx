#include <functional>
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>

using namespace std;

class Base {
  int num;

public:
  Base(int num) : num(num) {
    cout << "Base constructor is called" << endl;
  }

  virtual ~Base() {
    cout << "Base destructor is called" << endl;
  }

  int& getNum() {
    return num;
  }

  const int& getNum() const {
    return num;
  }

  virtual void hello() const {
    cout << "Hello Base. num is " << getNum() << endl;
  }

private:
  Base(Base const&) = delete;
  Base(Base &&) = delete;
  Base& operator=(Base const&) = delete;
  Base& operator=(Base &&) = delete;
};

class Derived : public Base {
  const double PI = 3.14159265358979;
  int hoge = 7;

public:

  Derived() : Base(2) {
    cout << "Derived constructor is called" << endl;
  }

  ~Derived() {
    cout << "Derived destructor is called" << endl;
  }

  void hello() const override {
    for(int i = 0; i < getNum(); i++) {
      cout << "Hello Derived. num is " << getNum() << ", PI is " << PI;
      cout << ", and hoge is " << hoge << endl;
    }
  }

private:
  Derived(Base const&) = delete;
  Derived(Base &&) = delete;
  Derived& operator=(Base const&) = delete;
  Derived& operator=(Base &&) = delete;

};

int digit(int number) {
  int cnt = 0;
  do {
    number /= 10;
  } while(number != 0);
  return cnt;
}

template<class T>
void dump_class(string className, T *instance) {
  size_t size= sizeof(T);
  cout << endl << className << " class size: " << size << endl;
  cout << "Dump information:" << endl;
  int* pointer = reinterpret_cast<int*>(instance);
  int loop = (size + 3) / 4;
  int d = digit(loop - 1);
  for(int i = 0; i < loop; i++) {
    cout << setw(d) << i << ": " << hex << setw(8)
         << setfill('0') << *(pointer + i) << dec << endl;
  }
  cout << endl;
}

template<class T>
void replace_bin(T *instance, int offset, int content) {
  *(reinterpret_cast<int*>(instance) + offset) = content;
}

template<class T>
int get_bin(T *instance, int offset) {
  return *(reinterpret_cast<int*>(instance) + offset);
}

template<class T>
double get_double(T *instance, int offset) {
  return *reinterpret_cast<double*>((reinterpret_cast<int*>(instance) + offset));
}

int main(void) {
  unique_ptr<Base> ins = make_unique<Base>(1);
  unique_ptr<Derived> ins2 = make_unique<Derived>();
  dump_class("Base", ins.get());
  dump_class("Derived", ins2.get());
  cout << "Extracted double: " << get_double(ins2.get(), 4) << endl;
  ins->hello();
  ins2->hello();
  replace_bin(ins2.get(), 0, get_bin(ins.get(), 0));
  dump_class("Base", ins.get());
  dump_class("Derived", ins2.get());
  ins->hello();
  ins2->hello();
  return 0;
}
