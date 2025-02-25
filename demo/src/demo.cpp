#include "demo.h"

#include <core/Input.h>

#include <math/vector.h>

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
  if (Vision::Input::KeyDown(SDL_SCANCODE_ESCAPE))
    Stop();
}

} // namespace flexor