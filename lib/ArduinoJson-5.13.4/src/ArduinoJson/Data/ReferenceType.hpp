// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Data/ReferenceType.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Data/ReferenceType.hpp

#pragma once

namespace ArduinoJson {
namespace Internals {

// A type that is meant to be used by reference only (JsonArray and JsonObject)
class ReferenceType {
 public:
  bool operator==(const ReferenceType& other) const {
    // two JsonArray are equal if they are the same instance
    // (we don't compare the content)
    return this == &other;
  }

  bool operator!=(const ReferenceType& other) const {
    return this != &other;
  }
};
}
}
