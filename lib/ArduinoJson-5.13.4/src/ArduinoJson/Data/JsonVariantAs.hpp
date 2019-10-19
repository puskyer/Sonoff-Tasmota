// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Data/JsonVariantAs.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Data/JsonVariantAs.hpp

#pragma once

namespace ArduinoJson {
namespace Internals {

// A metafunction that returns the type of the value returned by
// JsonVariant::as<T>()
template <typename T>
struct JsonVariantAs {
  typedef T type;
};

template <>
struct JsonVariantAs<char*> {
  typedef const char* type;
};

template <>
struct JsonVariantAs<JsonArray> {
  typedef JsonArray& type;
};

template <>
struct JsonVariantAs<const JsonArray> {
  typedef const JsonArray& type;
};

template <>
struct JsonVariantAs<JsonObject> {
  typedef JsonObject& type;
};

template <>
struct JsonVariantAs<const JsonObject> {
  typedef const JsonObject& type;
};
}
}
