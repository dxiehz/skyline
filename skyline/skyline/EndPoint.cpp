//
//  EndPoint.cpp
//  skyline
//
//  Created by Daniel Xie on 9/23/16.
//  Copyright © 2016 Daniel Xie. All rights reserved.
//

#include "EndPoint.hpp"

EndPoint::EndPoint(const struct in_addr & addr, in_port_t port)
: _port(port) {
  _addr._ip4.s_addr = addr.s_addr;
}

EndPoint::EndPoint(const struct in6_addr& addr, in_port_t port)
: _port(port) {
  memcpy(&_addr._ip6, &addr, sizeof(in6_addr));
}

EndPoint::EndPoint(const EndPoint& ep) {
  _port = ep.port();
  memcpy(&_addr._ip6, &ep.addr6(), sizeof(in6_addr));
}

std::size_t EndPoint::hash() {
  std::size_t seed = 0;
  hash_combine(seed, _port);
  hash_combine(seed, _addr._addr32[0]);
  hash_combine(seed, _addr._addr32[1]);
  hash_combine(seed, _addr._addr32[2]);
  hash_combine(seed, _addr._addr32[3]);
//  hash_combine(seed, _addr._addr32[0], _addr._addr32[1], _addr._addr32[2], _addr._addr32[3]);
  return seed;
}

EndPointPair::EndPointPair(const EndPoint& src, const EndPoint& dst)
: _src(src), _dst(dst) {
}

std::size_t EndPointPair::hash() {
  std::size_t seed = 0;
  hash_combine(seed, _src.hash());
  hash_combine(seed, _dst.hash());
  return seed;
}

std::size_t EndPointPair::rhash() {
  std::size_t seed = 0;
  hash_combine(seed, _dst.hash());
  hash_combine(seed, _src.hash());
  return seed;
}
