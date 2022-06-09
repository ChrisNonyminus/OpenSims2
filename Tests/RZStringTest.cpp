#include <chrono>

#include "GZFrame/RZ/String/RZString.hpp"

int main() {
  // Performs cRZString utility functions while calculating how long it takes to
  // do them, and prints the results.

  // Create a new string.
  auto time_start = std::chrono::high_resolution_clock::now();
  cRZString str(" Hello World!\n ");
  auto time_end = std::chrono::high_resolution_clock::now();
  auto time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString constructor: %ld nanoseconds\n", time_duration.count());
  // Get the length of the string.
  time_start = std::chrono::high_resolution_clock::now();
  size_t len = str.Strlen();
  time_end = std::chrono::high_resolution_clock::now();
  time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString Strlen: %ld nanoseconds\n", time_duration.count());
  // Make another string.
  cRZString str2(" It's time to kick ass and chew bubblegum.\n ");
  // Get the length of the string.
  size_t len2 = str2.Strlen();
  // RTrim the first string.
  time_start = std::chrono::high_resolution_clock::now();
  str = str.RTrim();
  time_end = std::chrono::high_resolution_clock::now();
  time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString RTrim: %ld nanoseconds\n", time_duration.count());
  // Append the second string to the first.
  time_start = std::chrono::high_resolution_clock::now();
  str = str.Append(str2);
  time_end = std::chrono::high_resolution_clock::now();
  time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString Append: %ld nanoseconds\n", time_duration.count());
  // Get the length of the string.
  size_t len3 = str.Strlen();
  // Trim the string.
  str = str.RTrim();
  // Insert a string at the beginning of the string.
  time_start = std::chrono::high_resolution_clock::now();
  str.Insert(strlen(" Hello World!\n"), "");
  time_end = std::chrono::high_resolution_clock::now();
  time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString Insert: %ld nanoseconds\n", time_duration.count());
  // Append one more string.
  str.Append(" And I'm all out of bubblegum.\n");
  // Replace a substring with a new string.
  time_start = std::chrono::high_resolution_clock::now();
  str.Replace(str.Find("ass", strlen("ass")), "***");
  time_end = std::chrono::high_resolution_clock::now();
  time_duration = std::chrono::duration_cast<std::chrono::nanoseconds>(
      time_end - time_start);
  printf("cRZString Replace: %ld nanoseconds\n", time_duration.count());
  // Get the final length of the string.
  size_t len4 = str.Strlen();
  // Print everything out.
  printf("Final string:\n%s\n", str.Data());
}