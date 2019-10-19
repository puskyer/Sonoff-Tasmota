// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonVariantImpl.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonVariantImpl.hpp

#pragma once

#include "Configuration.hpp"
#include "JsonArray.hpp"
#include "JsonObject.hpp"
#include "JsonVariant.hpp"
#include "Polyfills/isFloat.hpp"
#include "Polyfills/isInteger.hpp"
#include "Polyfills/parseFloat.hpp"
#include "Polyfills/parseInteger.hpp"

#include <string.h>  // for strcmp

namespace ArduinoJson {

inline JsonVariant::JsonVariant(const JsonArray &array) {
  if (array.success()) {
    _type = Internals::JSON_ARRAY;
    _content.asArray = const_cast<JsonArray *>(&array);
  } else {
    _type = Internals::JSON_UNDEFINED;
  }
}

inline JsonVariant::JsonVariant(const JsonObject &object) {
  if (object.success()) {
    _type = Internals::JSON_OBJECT;
    _content.asObject = const_cast<JsonObject *>(&object);
  } else {
    _type = Internals::JSON_UNDEFINED;
  }
}

inline JsonArray &JsonVariant::variantAsArray() const {
  if (_type == Internals::JSON_ARRAY) return *_content.asArray;
  return JsonArray::invalid();
}

inline JsonObject &JsonVariant::variantAsObject() const {
  if (_type == Internals::JSON_OBJECT) return *_content.asObject;
  return JsonObject::invalid();
}

template <typename T>
inline T JsonVariant::variantAsInteger() const {
  using namespace Internals;
  switch (_type) {
    case JSON_UNDEFINED:
      return 0;
    case JSON_POSITIVE_INTEGER:
    case JSON_BOOLEAN:
      return T(_content.asInteger);
    case JSON_NEGATIVE_INTEGER:
      return T(~_content.asInteger + 1);
    case JSON_STRING:
    case JSON_UNPARSED:
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonVariantImpl.hpp
      return Polyfills::parseInteger<T>(_content.asString);
=======
      return parseInteger<T>(_content.asString);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonVariantImpl.hpp
    default:
      return T(_content.asFloat);
  }
}

inline const char *JsonVariant::variantAsString() const {
  using namespace Internals;
  if (_type == JSON_UNPARSED && _content.asString &&
      !strcmp("null", _content.asString))
    return NULL;
  if (_type == JSON_STRING || _type == JSON_UNPARSED) return _content.asString;
  return NULL;
}

template <typename T>
inline T JsonVariant::variantAsFloat() const {
  using namespace Internals;
  switch (_type) {
    case JSON_UNDEFINED:
      return 0;
    case JSON_POSITIVE_INTEGER:
    case JSON_BOOLEAN:
      return static_cast<T>(_content.asInteger);
    case JSON_NEGATIVE_INTEGER:
      return -static_cast<T>(_content.asInteger);
    case JSON_STRING:
    case JSON_UNPARSED:
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonVariantImpl.hpp
      return Polyfills::parseFloat<T>(_content.asString);
=======
      return parseFloat<T>(_content.asString);
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonVariantImpl.hpp
    default:
      return static_cast<T>(_content.asFloat);
  }
}

inline bool JsonVariant::variantIsBoolean() const {
  using namespace Internals;
  if (_type == JSON_BOOLEAN) return true;

  if (_type != JSON_UNPARSED || _content.asString == NULL) return false;

  return !strcmp(_content.asString, "true") ||
         !strcmp(_content.asString, "false");
}

inline bool JsonVariant::variantIsInteger() const {
  using namespace Internals;

  return _type == JSON_POSITIVE_INTEGER || _type == JSON_NEGATIVE_INTEGER ||
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonVariantImpl.hpp
         (_type == JSON_UNPARSED && Polyfills::isInteger(_content.asString));
=======
         (_type == JSON_UNPARSED && isInteger(_content.asString));
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonVariantImpl.hpp
}

inline bool JsonVariant::variantIsFloat() const {
  using namespace Internals;

  return _type == JSON_FLOAT || _type == JSON_POSITIVE_INTEGER ||
         _type == JSON_NEGATIVE_INTEGER ||
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/JsonVariantImpl.hpp
         (_type == JSON_UNPARSED && Polyfills::isFloat(_content.asString));
=======
         (_type == JSON_UNPARSED && isFloat(_content.asString));
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/JsonVariantImpl.hpp
}

#if ARDUINOJSON_ENABLE_STD_STREAM
inline std::ostream &operator<<(std::ostream &os, const JsonVariant &source) {
  return source.printTo(os);
}
#endif

}  // namespace ArduinoJson
