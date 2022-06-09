#pragma once

#include <stdint.h>

// cIGZUnknown -- Base object for all GZFramework objects -- and by extension,
// all objects in the RZFramework, and the actual objects in the game.

struct cIGZUnknown {
  virtual bool QueryInterface(uint32_t, void **) = 0;
  virtual uint32_t AddRef() = 0;
};