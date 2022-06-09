#pragma once

#include "GZFrame/GZ/String/IGZString.hpp"

// cRZString -- RZ's string class.
// (Why would Maxis make an std::string alternative?)

struct cRZString : public std::string, public cIGZString {
  cRZString() { cIGZString::cIGZString(); }
  ~cRZString() {}
};