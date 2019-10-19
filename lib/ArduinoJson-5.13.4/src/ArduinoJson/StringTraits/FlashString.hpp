// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/FlashString.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/FlashString.hpp

#pragma once

#if ARDUINOJSON_ENABLE_PROGMEM

namespace ArduinoJson {
namespace Internals {
template <>
struct StringTraits<const __FlashStringHelper*, void> {
  class Reader {
    const char* _ptr;

   public:
    Reader(const __FlashStringHelper* ptr)
        : _ptr(reinterpret_cast<const char*>(ptr)) {}

    void move() {
      _ptr++;
    }

    char current() const {
      return pgm_read_byte_near(_ptr);
    }

    char next() const {
      return pgm_read_byte_near(_ptr + 1);
    }
  };

  static bool equals(const __FlashStringHelper* str, const char* expected) {
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/FlashString.hpp
    return strcmp_P(expected, (const char*)str) == 0;
=======
    const char* actual = reinterpret_cast<const char*>(str);
    if (!actual || !expected) return actual == expected;
    return strcmp_P(expected, actual) == 0;
  }

  static bool is_null(const __FlashStringHelper* str) {
    return !str;
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/FlashString.hpp
  }

  typedef const char* duplicate_t;

  template <typename Buffer>
  static duplicate_t duplicate(const __FlashStringHelper* str, Buffer* buffer) {
    if (!str) return NULL;
    size_t size = strlen_P((const char*)str) + 1;
    void* dup = buffer->alloc(size);
    if (dup != NULL) memcpy_P(dup, (const char*)str, size);
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/FlashString.hpp
    return static_cast<char*>(dup);
=======
    return static_cast<duplicate_t>(dup);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/FlashString.hpp
  }

  static const bool has_append = false;
  static const bool has_equals = true;
  static const bool should_duplicate = true;
};
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/FlashString.hpp
}
}
=======
}  // namespace Internals
}  // namespace ArduinoJson
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/FlashString.hpp

#endif
