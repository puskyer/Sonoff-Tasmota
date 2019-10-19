// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/StdStream.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/StdStream.hpp

#pragma once

#if ARDUINOJSON_ENABLE_STD_STREAM

#include <istream>

namespace ArduinoJson {
namespace Internals {

struct StdStreamTraits {
  class Reader {
    std::istream& _stream;
    char _current, _next;

   public:
    Reader(std::istream& stream) : _stream(stream), _current(0), _next(0) {}

    void move() {
      _current = _next;
      _next = 0;
    }

    char current() {
      if (!_current) _current = read();
      return _current;
    }

    char next() {
      // assumes that current() has been called
      if (!_next) _next = read();
      return _next;
    }

   private:
    Reader& operator=(const Reader&);  // Visual Studio C4512

    char read() {
      return _stream.eof() ? '\0' : static_cast<char>(_stream.get());
    }
  };

  static const bool has_append = false;
  static const bool has_equals = false;
};

template <typename TStream>
struct StringTraits<
    TStream,
    // match any type that is derived from std::istream:
    typename EnableIf<IsBaseOf<
        std::istream, typename RemoveReference<TStream>::type>::value>::type>
    : StdStreamTraits {};
}
}

#endif
