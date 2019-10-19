// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/StdString.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/StdString.hpp

#pragma once

#if ARDUINOJSON_ENABLE_STD_STRING || ARDUINOJSON_ENABLE_ARDUINO_STRING

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
#include <WString.h>
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
#include <string>
#endif

namespace ArduinoJson {
namespace Internals {

template <typename TString>
struct StdStringTraits {
  typedef const char* duplicate_t;

  template <typename Buffer>
  static duplicate_t duplicate(const TString& str, Buffer* buffer) {
    if (!str.c_str()) return NULL;  // <- Arduino string can return NULL
    size_t size = str.length() + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy(dup, str.c_str(), size);
    return static_cast<duplicate_t>(dup);
  }

  static bool is_null(const TString& str) {
    // Arduino's String::c_str() can return NULL
    return !str.c_str();
  }

  struct Reader : CharPointerTraits<char>::Reader {
    Reader(const TString& str) : CharPointerTraits<char>::Reader(str.c_str()) {}
  };

  static bool equals(const TString& str, const char* expected) {
    // Arduino's String::c_str() can return NULL
    const char* actual = str.c_str();
    if (!actual || !expected) return actual == expected;
    return 0 == strcmp(actual, expected);
  }

  static void append(TString& str, char c) {
    str += c;
  }

  static void append(TString& str, const char* s) {
    str += s;
  }

  static const bool has_append = true;
  static const bool has_equals = true;
  static const bool should_duplicate = true;
};

#if ARDUINOJSON_ENABLE_ARDUINO_STRING
template <>
struct StringTraits<String, void> : StdStringTraits<String> {};
template <>
struct StringTraits<StringSumHelper, void> : StdStringTraits<StringSumHelper> {
};
#endif

#if ARDUINOJSON_ENABLE_STD_STRING
template <>
struct StringTraits<std::string, void> : StdStringTraits<std::string> {};
#endif
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/StdString.hpp
}
}
=======
}  // namespace Internals
}  // namespace ArduinoJson
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/StdString.hpp

#endif
