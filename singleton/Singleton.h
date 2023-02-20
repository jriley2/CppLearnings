#include <atomic>
#include <iostream>

class Singleton final
{
 private:

  Singleton()
  {
    std::cout << "constructor" << std::endl;
    numberOfInstances++;
  };

 public:

  Singleton(const Singleton&) = delete;
  Singleton(Singleton&&) = delete;
  Singleton& operator=(const Singleton& other) = delete;
  Singleton& operator=(Singleton&& other) = delete;
  ~Singleton() = default;

  static float Float()
  {
    return GetInstance().ImplFloat();
  }

  static std::atomic<int> numberOfInstances;
  static std::atomic<int> numberOfGetInstanceCalls;

 private:

  float ImplFloat()
  {
    return m_val;
  }

  static Singleton& GetInstance()
  {
    // static variables with block scope are threadsafe
    static Singleton instance;
    numberOfGetInstanceCalls++;
    return instance;
  }

  float m_val = 0.5;
};

std::atomic<int> Singleton::numberOfInstances = 0;
std::atomic<int> Singleton::numberOfGetInstanceCalls = 0;
