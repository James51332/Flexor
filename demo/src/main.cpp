#include "demo.h"

#include <memory>

int main()
{
  std::unique_ptr<flexor::demo> demoApp = std::make_unique<flexor::demo>();
  demoApp->Run();
}