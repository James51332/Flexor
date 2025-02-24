#include "demo.h"

namespace flexor
{

demo::demo()
  : Vision::App("Flexor Demo")
{
  physicsWorld = std::make_unique<engine>();
}

demo::~demo()
{
}

void demo::OnUpdate(float timestep)
{
}

} // namespace flexor