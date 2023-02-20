#include "Singleton.h"
#include <thread>
#include <vector>

int main()
{
  const int numThreads = 32;

  std::cout << "Number of instances: " << Singleton::numberOfInstances << std::endl;

  auto threadFunc = []()
  {
    Singleton::Float();
  };

  std::vector<std::thread> workers;
  for (int i = 0; i < numThreads; i++)
  {
    workers.push_back(std::thread(threadFunc));
  }

  for (auto& w : workers)
  {
    w.join();
  }

  std::cout << "Called the Singleton from " << numThreads << " worker threads: " << std::endl;
  std::cout << "Number of calls to GetInstance: " << Singleton::numberOfGetInstanceCalls
            << std::endl;
  std::cout << "Number of instances: " << Singleton::numberOfInstances << std::endl;
  if (Singleton::numberOfInstances == 1)
  {
    std::cout << "passed" << std::endl;
  }
  else
  {
    std::cout << "failed" << std::endl;
  }
}