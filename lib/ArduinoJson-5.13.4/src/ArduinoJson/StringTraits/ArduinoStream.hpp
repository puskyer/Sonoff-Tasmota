// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/StringTraits/ArduinoStream.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/StringTraits/ArduinoStream.hpp

#pragma once

#if ARDUINOJSON_ENABLE_ARDUINO_STREAM

#include <Stream.h>

namespace ArduinoJson {
namespace Internals {

struct ArduinoStreamTraits {
  class Reader {
    Stream& _stream;
    char _current, _next;

   public:
    Reader(Stream& stream) : _stream(stream), _current(0), _next(0) {}

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
    char read() {
      // don't use _stream.read() as it ignores the timeout
      char c = 0;
      _stream.readBytes(&c, 1);
      return c;
    }
  };

  static const bool has_append = false;
  static const bool has_equals = false;
};

template <typename TStream>
struct StringTraits<
    TStream,
    // match any type that is derived from Stream:
    typename EnableIf<
        IsBaseOf<Stream, typename RemoveReference<TStream>::type>::value>::type>
    : ArduinoStreamTraits {};
}
}

#endif
