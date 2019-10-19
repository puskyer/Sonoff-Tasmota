// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Data/JsonVariantDefault.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Data/JsonVariantDefault.hpp

#pragma once

namespace ArduinoJson {
namespace Internals {

template <typename T>
struct JsonVariantDefault {
  static T get() {
    return T();
  }
};

template <typename T>
struct JsonVariantDefault<const T> : JsonVariantDefault<T> {};

template <typename T>
struct JsonVariantDefault<T&> : JsonVariantDefault<T> {};
}
}
