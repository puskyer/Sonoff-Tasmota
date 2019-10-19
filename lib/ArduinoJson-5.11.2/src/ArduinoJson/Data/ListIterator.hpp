// ArduinoJson - arduinojson.org
// Copyright Benoit Blanchon 2014-2018
// MIT License
<<<<<<< HEAD:lib/ArduinoJson-5.11.2/src/ArduinoJson/Data/ListIterator.hpp
//
// Arduino JSON library
// https://bblanchon.github.io/ArduinoJson/
// If you like this project, please add a star!
=======
>>>>>>> 9818f8b8195a63f8c1526e82cf08c0f6f43b7347:lib/ArduinoJson-5.13.4/src/ArduinoJson/Data/ListIterator.hpp

#pragma once

#include "ListConstIterator.hpp"
#include "ListNode.hpp"

namespace ArduinoJson {
namespace Internals {

template <typename T>
class List;

// A read-write forward iterator for List<T>
template <typename T>
class ListIterator {
  friend class List<T>;

 public:
  explicit ListIterator(ListNode<T> *node = NULL) : _node(node) {}

  T &operator*() const {
    return _node->content;
  }
  T *operator->() {
    return &_node->content;
  }

  bool operator==(const ListIterator<T> &other) const {
    return _node == other._node;
  }

  bool operator!=(const ListIterator<T> &other) const {
    return _node != other._node;
  }

  ListIterator<T> &operator++() {
    if (_node) _node = _node->next;
    return *this;
  }

  ListIterator<T> &operator+=(size_t distance) {
    while (_node && distance) {
      _node = _node->next;
      --distance;
    }
    return *this;
  }

  operator ListConstIterator<T>() const {
    return ListConstIterator<T>(_node);
  }

 private:
  ListNode<T> *_node;
};
}
}
