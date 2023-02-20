#include <cassert>
#include <cstdarg>
#include <iostream>
#include <type_traits>
#include <typeinfo>

// variadic functions are not type safe
void print(int num, double args...)
{
  va_list vaArgs;
  va_start(vaArgs, args);

  std::cout << args << std::endl;

  for (int i = 1; i < num; i++)
  {
    double arg = va_arg(vaArgs, double); // get next arg
    std::cout << arg << std::endl;
  }

  va_end(vaArgs);
}

template<typename T>
void print_vtemp(T only)
{
  if (std::is_same<T, double>::value)
  {
    // can check type at runtime
  }

  std::cout << only << "\t" << typeid(T).name() << std::endl;
}

template<typename T, typename... Targs>
void print_vtemp(T first, Targs... others)
{

  if (std::is_same<T, double>::value)
  {
    // can check type at runtime
  }

  std::cout << first << "\t" << typeid(T).name() << std::endl;

  print_vtemp(others...);
}

int main()
{
  int num = 5;
  double a = 1.5;
  double b = 2.1;
  double c = 3.2;
  int d = 1;
  char e = 'e';
  print(num, a, b, c, d, e);
  // The 1 and 'e' prints out incorrectly, because the function is expecting doubles.
  std::cout << std::endl;
  print_vtemp(a, b, c, d, e);
}
