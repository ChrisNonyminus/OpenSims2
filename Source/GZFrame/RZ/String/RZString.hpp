#pragma once

#include <stdarg.h>
#include <stdio.h>
#include <string.h>

#include <vector>

#include "GZFrame/GZ/String/IGZString.hpp"

// cRZString -- Reimplementation of RZ's string utility class.

class cRZString : public std::string, public cIGZString {
private:
  std::string str;
  uint32_t refs;

public:
  cRZString() { str = ""; }
  ~cRZString() { str.clear(); }
  cRZString(const std::string &str) { this->str = str; }
  cRZString(const cRZString &str, size_t pos, size_t len = std::string::npos) {
    this->str = str.substr(pos, len);
  }
  cRZString(const char *str) { this->str = std::string(str); }
  bool QueryInterface(uint32_t clsid, void **ppv) {
    if (clsid == cIGZString::kCLSID) {
      *ppv = static_cast<cIGZString *>(this);
      return true;
    }
    return false;
  }
  uint32_t AddRef() { return ++refs; }
  uint32_t Release() {
    if (--refs <= 0) {
      delete this;
      return 0;
    }
    return refs;
  }
  cRZString &Copy(const cIGZString &rhs) {
    return FromChar(rhs.Data(), rhs.Strlen());
  }
  bool SplitTokenDelimited(char token) {
    size_t pos = str.find(token);
    if (pos == std::string::npos) {
      str.erase(str.begin(), str.end());
      return false;
    }
    str = str.substr(0, pos);
    return true;
  }
  bool SplitTokenDelimited(char token, cRZString &rhs) {
    size_t pos = str.find(token);
    if (pos == std::string::npos) {
      rhs.str.erase(str.begin(), str.end());
      str = rhs.str;
      return false;
    }
    rhs.str = str.substr(pos + 1, std::string::npos);
    str = rhs.str.substr(0, pos);
    return true;
  }
  cRZString &Strcpy(const char *str) {
    this->str.assign(str);
    return *this;
  }
  cRZString &Strcat(const char *str) {
    this->str.append(str);
    return *this;
  }
  cRZString &LTrim() {
    size_t first_not_of = str.find_first_not_of(" \t");
    str.erase(0, first_not_of);
    return *this;
  }
  cRZString &RTrim() {
    size_t last_not_of = str.find_last_not_of(" \t");
    str.erase(last_not_of + 1);
    return *this;
  }
  cRZString &Trim() { return LTrim().RTrim(); }
  cRZString &operator=(const cIGZString &rhs) { return Copy(rhs); }
  cRZString &FromChar(const char *str) {
    if (!str) {
      this->str.clear();
      return *this;
    }
    this->str.assign(str, strlen(str));
    return *this;
  }
  cRZString &FromChar(const char *str, size_t len) {
    if (!str) {
      this->str.clear();
      return *this;
    }
    this->str.assign(str, len);
    return *this;
  }
  bool IsEqual(cIGZString const &rhs, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str.c_str(), rhs.Data(), str.length()) == 0
                       : str == rhs.Data();
  }
  bool IsEqual(const char *str, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str, this->str.c_str(), strlen(str)) == 0
                       : std::string(str) == this->str;
  }
  int CompareTo(const char *str, bool use_strncmp = false) {
    return CompareTo(str, strlen(str), use_strncmp);
  }
  cRZString &Append(const char *str) {
    this->str.append(str);
    return *this;
  }
  cRZString &Append(const char *str, size_t len) {
    this->str.append(str, len);
    return *this;
  }
  cRZString &Append(const cIGZString &rhs) {
    this->str.append(rhs.Data(), rhs.Strlen());
    return *this;
  }
  cRZString &Insert(size_t pos, const char *str,
                    size_t len = std::string::npos) {
    if (len == std::string::npos)
      len = strlen(str);
    this->str.insert(pos, str, len);
    return *this;
  }
  cRZString &Insert(size_t pos, const cIGZString &rhs) {
    this->str.insert(pos, rhs.Data(), rhs.Strlen());
    return *this;
  }
  cRZString &Replace(size_t pos, const char *str,
                     size_t len = std::string::npos) {
    if (len == std::string::npos)
      len = strlen(str);
    this->str.replace(pos, len, str);
    return *this;
  }
  cRZString &Replace(size_t pos, const cIGZString &rhs) {
    this->str.replace(pos, rhs.Strlen(), rhs.Data());
    return *this;
  }
  cRZString &Erase(size_t pos, size_t len = std::string::npos) {
    this->str.erase(pos, len);
    return *this;
  }
  int CompareTo(const char *str, size_t len, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str, this->str.c_str(), len)
                       : strcmp(str, this->str.c_str());
  }
  cRZString &Sprintf(const char *format, ...) {
    va_list args;
    va_start(args, format);
    return SprintfVaList(format, args);
  }
  cRZString &Resize(size_t len) {
    this->str.resize(len);
    return *this;
  }
  bool IsEmpty() { return str.empty(); }
  cRZString &SprintfVaList(const char *format, va_list args) {
    char *buf = new char[256];
    vsnprintf(buf, 256, format, args);
    str = buf;
    delete[] buf;
    return *this;
  }
  size_t Strlen() const { return str.length(); }
  const char *Data() const { return str.c_str(); }
  bool IsEqual(const cIGZString *rhs, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str.c_str(), rhs->Data(), str.length()) == 0
                       : str == rhs->Data();
  }
  bool IsEqual(const char *str, size_t len, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str, this->str.c_str(), len) == 0
                       : std::string(str, len) == this->str;
  }
  size_t CountChars(char c) {
    size_t count = 0;
    for (size_t i = 0; i < str.length(); i++) {
      if (str[i] == c) {
        count++;
      }
    }
    return count;
  }
  void MakeLower() {
    for (size_t i = 0; i < str.length(); i++) {
      str[i] = tolower(str[i]);
    }
  }
  void MakeUpper() {
    for (size_t i = 0; i < str.length(); i++) {
      str[i] = toupper(str[i]);
    }
  }
  const char *ToChar() { return str.c_str(); }
  int CompareTo(const cIGZString &rhs, bool use_strncmp = false) {
    return use_strncmp ? strncmp(str.c_str(), rhs.Data(), str.length())
                       : str.compare(rhs.Data());
  }
  bool SplitTokenSeperated(char token, cRZString &rhs) {
    size_t pos = str.find(token);
    if (pos == std::string::npos) {
      rhs.str = str;
      str.clear();
      return true;
    }
    rhs.str = str.substr(0, pos);
    str = str.substr(pos + 1);
    return false;
  }
  cRZString &Mid(size_t pos, size_t len = std::string::npos) {
    str = str.substr(pos, len);
    return *this;
  }
  cRZString &Right(size_t len) {
    str = str.substr(str.length() - len);
    return *this;
  }
  cRZString &Left(size_t len) {
    str = str.substr(0, len);
    return *this;
  }
  cRZString &SplitToken(const char *token) {
    size_t pos = str.find(token);
    if (pos == std::string::npos) {
      return *this;
    }
    str = str.substr(0, pos);
    return *this;
  }
  size_t RFind(const char *str, size_t pos, bool case_sensitive = false) {
    if (case_sensitive)
      return this->str.rfind(str, pos);
    cRZString str2(*this);
    str2.MakeLower();
    cRZString str3(str);
    str3.MakeLower();
    return str2.str.rfind(str3.str, pos);
  }
  bool BeginsWith(const char *str, size_t max_len,
                  bool case_sensitive = false) {
    if (case_sensitive)
      return this->str.substr(0, max_len).compare(str) == 0;
    cRZString str2(*this);
    str2.MakeLower();
    cRZString str3(str);
    str3.MakeLower();
    return str2.BeginsWith(str3.str.c_str(), max_len, true);
  }
  bool BeginsWith(cIGZString const &rhs, bool case_sensitive = false) {
    return BeginsWith(rhs.Data(), rhs.Strlen(), case_sensitive);
  }
  bool EndsWith(const char *str, size_t max_len, bool case_sensitive = false) {
    if (case_sensitive)
      return this->str.substr(this->str.length() - max_len).compare(str) == 0;
    cRZString str2(*this);
    str2.MakeLower();
    cRZString str3(str);
    str3.MakeLower();
    return str2.EndsWith(str3.str.c_str(), max_len, true);
  }
  bool EndsWith(cIGZString const &rhs, bool case_sensitive = false) {
    return EndsWith(rhs.Data(), rhs.Strlen(), case_sensitive);
  }
  size_t Find(const char *str, size_t pos, bool case_sensitive = false) {
    if (case_sensitive)
      return this->str.find(str, pos);
    cRZString str2(*this);
    str2.MakeLower();
    cRZString str3(str);
    str3.MakeLower();
    return str2.str.find(str3.str, pos);
  }
  size_t RFind(cIGZString const &rhs, size_t pos, bool case_sensitive = false) {
    return RFind(rhs.Data(), pos, case_sensitive);
  }
  size_t Find(cIGZString const &rhs, size_t pos, bool case_sensitive = false) {
    return Find(rhs.Data(), pos, case_sensitive);
  }
  void Split(const char *delim, std::vector<cRZString> &tokens) {
    size_t pos = 0;
    size_t lastPos = 0;
    while (pos < str.length()) {
      pos = str.find(delim, pos);
      if (pos == std::string::npos) {
        pos = str.length();
      }
      cRZString token(str.substr(lastPos, pos - lastPos).c_str());
      tokens.push_back(token);
      lastPos = pos + 1;
      pos++;
    }
  }
  cRZString(const char *str, size_t len) { this->str = std::string(str, len); }
  cRZString(cIGZString const &rhs) { this->str = rhs.Data(); }
  cRZString(char c, size_t len) {
    for (size_t i = 0; i < len; i++) {
      str += c;
    }
  }

  // custom-made functions not in the original version of cRZString
  cRZString &operator=(const cRZString &rhs) {
    str = rhs.str;
    return *this;
  }
  cRZString &operator+=(const cIGZString &rhs) {
    this->str.append(rhs.Data(), rhs.Strlen());
    return *this;
  }
};