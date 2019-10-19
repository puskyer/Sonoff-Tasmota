// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonBufferBase.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonBufferBase.hpp

#pragma once

#include "Deserialization/JsonParser.hpp"

namespace ArduinoJson {
namespace Internals {
template <typename TDerived>
class JsonBufferBase : public JsonBuffer {
 public:
  // Allocates and populate a JsonArray from a JSON string.
  //
  // The First argument is a pointer to the JSON string, the memory must be
  // writable
  // because the parser will insert null-terminators and replace escaped chars.
  //
  // The second argument set the nesting limit
  //
  // Returns a reference to the new JsonObject or JsonObject::invalid() if the
  // allocation fails.
  // With this overload, the JsonBuffer will make a copy of the string
  //
  // JsonArray& parseArray(TString);
  // TString = const std::string&, const String&
  template <typename TString>
  typename Internals::EnableIf<!Internals::IsArray<TString>::value,
                               JsonArray &>::type
  parseArray(const TString &json,
             uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseArray();
  }
  //
  // JsonArray& parseArray(TString);
  // TString = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  JsonArray &parseArray(
      TString *json, uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseArray();
  }
  //
  // JsonArray& parseArray(TString);
  // TString = std::istream&, Stream&
  template <typename TString>
  JsonArray &parseArray(
      TString &json, uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseArray();
  }

  // Allocates and populate a JsonObject from a JSON string.
  //
  // The First argument is a pointer to the JSON string, the memory must be
  // writable
  // because the parser will insert null-terminators and replace escaped chars.
  //
  // The second argument set the nesting limit
  //
  // Returns a reference to the new JsonObject or JsonObject::invalid() if the
  // allocation fails.
  //
  // JsonObject& parseObject(TString);
  // TString = const std::string&, const String&
  template <typename TString>
  typename Internals::EnableIf<!Internals::IsArray<TString>::value,
                               JsonObject &>::type
  parseObject(const TString &json,
              uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseObject();
  }
  //
  // JsonObject& parseObject(TString);
  // TString = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  JsonObject &parseObject(
      TString *json, uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseObject();
  }
  //
  // JsonObject& parseObject(TString);
  // TString = std::istream&, Stream&
  template <typename TString>
  JsonObject &parseObject(
      TString &json, uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseObject();
  }

  // Generalized version of parseArray() and parseObject(), also works for
  // integral types.
  //
  // JsonVariant parse(TString);
  // TString = const std::string&, const String&
  template <typename TString>
  typename Internals::EnableIf<!Internals::IsArray<TString>::value,
                               JsonVariant>::type
  parse(const TString &json,
        uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseVariant();
  }
  //
  // JsonVariant parse(TString);
  // TString = const char*, const char[N], const FlashStringHelper*
  template <typename TString>
  JsonVariant parse(TString *json,
                    uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseVariant();
  }
  //
  // JsonVariant parse(TString);
  // TString = std::istream&, Stream&
  template <typename TString>
  JsonVariant parse(TString &json,
                    uint8_t nestingLimit = ARDUINOJSON_DEFAULT_NESTING_LIMIT) {
    return Internals::makeParser(that(), json, nestingLimit).parseVariant();
  }

 protected:
  ~JsonBufferBase() {}

 private:
  TDerived *that() {
    return static_cast<TDerived *>(this);
  }
};
}
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonBufferBase.hpp
=======
}
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonBufferBase.hpp
