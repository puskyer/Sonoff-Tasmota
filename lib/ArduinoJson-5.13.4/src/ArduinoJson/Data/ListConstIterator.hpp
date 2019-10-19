// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Data/ListConstIterator.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Data/ListConstIterator.hpp

#pragma once

#include "ListNode.hpp"

namespace ArduinoJson {
namespace Internals {

// A read-only forward itertor for List<T>
template <typename T>
class ListConstIterator {
 public:
  explicit ListConstIterator(const ListNode<T> *node = NULL) : _node(node) {}

  const T &operator*() const {
    return _node->content;
  }
  const T *operator->() {
    return &_node->content;
  }

  bool operator==(const ListConstIterator<T> &other) const {
    return _node == other._node;
  }

  bool operator!=(const ListConstIterator<T> &other) const {
    return _node != other._node;
  }

  ListConstIterator<T> &operator++() {
    if (_node) _node = _node->next;
    return *this;
  }

  ListConstIterator<T> &operator+=(size_t distance) {
    while (_node && distance) {
      _node = _node->next;
      --distance;
    }
    return *this;
  }

 private:
  const ListNode<T> *_node;
};
}
}
