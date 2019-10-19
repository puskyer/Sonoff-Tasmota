// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/TypeTraits/EnableIf.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/TypeTraits/EnableIf.hpp

#pragma once

namespace ArduinoJson {
namespace Internals {

// A meta-function that return the type T if Condition is true.
template <bool Condition, typename T = void>
struct EnableIf {};

template <typename T>
struct EnableIf<true, T> {
  typedef T type;
};
}
}
