// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Polyfills/attributes.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Polyfills/attributes.hpp

#pragma once

#ifdef _MSC_VER  // Visual Studio

<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Polyfills/attributes.hpp
#define FORCE_INLINE __forceinline
=======
#define FORCE_INLINE  // __forceinline causes C4714 when returning std::string
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Polyfills/attributes.hpp
#define NO_INLINE __declspec(noinline)
#define DEPRECATED(msg) __declspec(deprecated(msg))

#elif defined(__GNUC__)  // GCC or Clang

#define FORCE_INLINE __attribute__((always_inline))
#define NO_INLINE __attribute__((noinline))
#if __GNUC__ > 4 || (__GNUC__ == 4 && __GNUC_MINOR__ >= 5)
#define DEPRECATED(msg) __attribute__((deprecated(msg)))
#else
#define DEPRECATED(msg) __attribute__((deprecated))
#endif

#else  // Other compilers

#define FORCE_INLINE
#define NO_INLINE
#define DEPRECATED(msg)

#endif
