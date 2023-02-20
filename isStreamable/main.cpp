#include <iostream>
#include <sstream>
#include <string>
#include <type_traits>

class NonStreamable
{
 public:

  int val{0};
};

class Streamable
{
 public:

  int val{1};
};

std::ostream& operator<<(std::ostream& os, const Streamable& a)
{
  os << a.val;
  return os;
}

template<typename T>
struct has_ostream
{

  template<typename U>
  static constexpr decltype(operator<<(std::cout, std::declval<U&>()), bool()) test_ostream(int)
  {
    return true;
  }

  template<typename U>
  static constexpr bool test_ostream(...)
  {
    return false;
  }

  static constexpr bool value = test_ostream<T>(int());
};

template<typename T>
void print(const T& t, typename std::enable_if<has_ostream<T>::value>::type* = 0)
{
  std::cout << "Value: " << t << std::endl;
}

template<typename T>
void print(const T& t, typename std::enable_if<!has_ostream<T>::value>::type* = 0)
{
  std::cout << "Type " << typeid(T).name() << " is not streamable" << std::endl;
}

int main()
{
  Streamable a;
  NonStreamable b;

  std::cout << "Printing Streamable" << std::endl;
  print(a);

  std::cout << std::endl;

  std::cout << "Printing NonStreamable" << std::endl;
  print(b);
}
