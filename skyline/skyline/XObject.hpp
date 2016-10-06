//
//  XObject.hpp
//  skyline
//
//  Created by Daniel Xie on 9/24/16.
//  Copyright © 2016 Daniel Xie. All rights reserved.
//

#ifndef XObject_hpp
#define XObject_hpp

#include <stdio.h>

#include <functional>

// combine one object into the same seed
template<class T>
inline void hash_combine(std::size_t& seed, const T& v)
{
  std::hash<T> hasher;
  seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}

// combine multiplie objects into the same seed
template <typename T, typename... Rest>
inline void hash_combine(std::size_t& seed, const T& v, Rest... rest) {
  std::hash<T> hasher;
  seed ^= hasher<v> + 0x9e3779b9 + (seed<<6) + (seed>>2);
  hash_combine(seed, rest...);
}

// object with hashcode
class XObject {
public:
  virtual std::size_t hash() = 0;  
};

#endif /* XObject_hpp */
