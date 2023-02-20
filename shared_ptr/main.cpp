#include <iostream>
#include <memory>
#include <type_traits>
#include <typeinfo>
#include <utility>
#include <vector>

struct C
{
  C(int i)
      : i(i){};
  int i;
};

struct D : public C
{
  D(int i)
      : C(i){};
};

int main()
{
  int valueA = 1;
  int valueB = 2;

  std::cout << "Make a shared_ptr of type C with value " << valueA << std::endl;
  auto sp = std::make_shared<C>(valueA);
  static_assert(std::is_same<decltype(sp), std::shared_ptr<C>>::value);

  std::cout << "Make a shared_ptr of type D with " << valueB << std::endl;
  auto spD = std::make_shared<D>(valueB);
  static_assert(std::is_same<decltype(spD), std::shared_ptr<D>>::value);
  std::cout << "Are the types different? "
            << (std::is_same<decltype(spD), std::shared_ptr<D>>::value ? "Yes" : "No") << std::endl;

  std::cout << "Hold both shared_ptrs in the same vector of shared_ptrs of C" << std::endl;
  std::cout << "Iterate through" << std::endl;
  std::vector<std::shared_ptr<C>> vec{sp, spD};
  for (auto& p : vec)
  {
    std::cout << "\t" << p->i << '\n';
  }
}
