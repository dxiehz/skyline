//
//  EndPoint.hpp
//  skyline
//
//  Created by Daniel Xie on 9/23/16.
//  Copyright © 2016 Daniel Xie. All rights reserved.
//

#ifndef EndPoint_hpp
#define EndPoint_hpp

#include <stdio.h>

#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/ip6.h>

#include "XObject.hpp"

// address + port
class EndPoint : public XObject {
public:
  // Constructors
  EndPoint(const struct in_addr & addr, in_port_t port);
  EndPoint(const struct in6_addr& addr, in_port_t port);
  EndPoint(const EndPoint& ep);
  
  // accessors
  const struct in_addr & addr4() const { return _addr._ip4; }
  const struct in6_addr& addr6() const { return _addr._ip6; }
  in_port_t port() const { return _port; }
  
  // hash function
  virtual std::size_t hash();

private:
  // address and port
  union {
    struct in_addr  _ip4; // ipv4 address
    struct in6_addr _ip6; // ipv6 address
    uint32_t  _addr32[4]; // used in hash_combine
  } _addr;
  in_port_t _port;
};

// src + dst
class EndPointPair : public XObject {
public:
  // Constructors
  EndPointPair(const EndPoint& src, const EndPoint& dst);
  
  // accessors
  const EndPoint& src() { return _src; }
  const EndPoint& dst() { return _dst; }
  
  // hash functions
  virtual std::size_t hash();
  std::size_t rhash();
  
private:
  // source endpoint
  EndPoint _src;
  EndPoint _dst;
};

#endif /* EndPoint_hpp */
