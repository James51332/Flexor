#pragma once

#include <memory>

#include <core/App.h>
#include <engine.h>

namespace flexor
{

/**
 * This class implements some simple interactive examples using flexor and
 * vision.
 */
class demo : public Vision::App
{
public:
  demo();
  ~demo();

  virtual void OnUpdate(float timestep) override;

private:
  std::unique_ptr<engine> physicsWorld;
};

} // namespace flexor