#pragma once

#include <string>

#include "GZFrame/GZ/IGZUnknown.hpp"

// cIGZString -- Interface for RZ's string class, cRZString.

struct cIGZString : public cIGZUnknown {

  static constexpr uint32_t kCLSID = 0x089B7DC8;

  // Conversions
  virtual cIGZString &FromChar(const char *) = 0;
  virtual cIGZString &FromChar(const char *, size_t) = 0;
  virtual const char *ToChar() = 0;
  virtual const char *Data() const = 0;
  virtual size_t Strlen() const = 0;

  // Comparisons
  virtual bool IsEmpty() = 0;
  virtual bool IsEqual(cIGZString const *, bool = false) = 0;
  virtual bool IsEqual(cIGZString const &, bool = false) = 0;
  virtual bool IsEqual(char const *, bool = false) = 0;
  virtual bool IsEqual(char const *, size_t, bool = false) = 0;
  virtual int CompareTo(char const *, bool = false) = 0;
  virtual int CompareTo(char const *, size_t, bool = false) = 0;

  // Manipulations
  virtual cIGZString &operator=(cIGZString const &) = 0;
  virtual cIGZString &Copy(cIGZString const &) = 0;
  virtual cIGZString &Resize(size_t) = 0;
  virtual cIGZString &Append(const char *) = 0;
  virtual cIGZString &Append(const char *, size_t) = 0;
  virtual cIGZString &Append(cIGZString const &) = 0;
  virtual cIGZString &Insert(size_t, const char *, size_t) = 0;
  virtual cIGZString &Insert(size_t, cIGZString const &) = 0;
  virtual cIGZString &Replace(size_t, const char *, size_t) = 0;
  virtual cIGZString &Replace(size_t, cIGZString const &) = 0;
  virtual cIGZString &Erase(size_t, size_t) = 0;

  // Finding
  virtual size_t Find(const char *, size_t, bool = false) = 0;
  virtual size_t Find(cIGZString const &, size_t, bool = false) = 0;
  virtual size_t RFind(const char *, size_t, bool = false) = 0;
  virtual size_t RFind(cIGZString const &, size_t, bool = false) = 0;

  // Formatting
  virtual cIGZString &Sprintf(const char *, ...) = 0;
  virtual cIGZString &SprintfVaList(const char *, va_list) = 0;
};