
#ifndef __RIB_COMMON_H
#define __RIB_COMMON_H

#include <thread>
#include <mutex>
#include <stdint.h>
#include <map>
#include <list>
#include <vector>
#include <iostream>

typedef uint32_t ipaddr;
typedef unsigned short byte;

typedef enum {
  RIB_ERR_START = 15,
  RIB_ERR_INVALID_IP = 16,
  RIB_ERR_INVALID_VRF = 17,
  RIB_ERR_INVALID_METRIC = 15,
  RIB_ERR_INVALID_IF = 15,
} rib_err_t;


class RtableEntry
{
  friend class RibTrie;

private:
  byte _metric;
  ipaddr _gw_ip;
  ipaddr _dst_ip;
  std::string _if_name;
  bool _is_valid;

public:
  RtableEntry();
  RtableEntry(byte metric, ipaddr dst_ip, ipaddr gw_ip,
              std::string if_name);
  RtableEntry(const RtableEntry& other);
  void convStrToIp(ipaddr &ip, std::string str);
  bool check(RtableEntry &route, rib_err_t &err_code) const;
  friend std::ostream &operator<<(std::ostream &out, const RtableEntry &route);
  friend bool operator<(const RtableEntry &lhs, const RtableEntry &rhs);
  friend bool operator==(const RtableEntry &lhs, const RtableEntry &rhs);
  RtableEntry& operator = (const RtableEntry& rhs);
};

void convStrToIp(ipaddr &ip, std::string s);

#endif //_RIB_COMMON_H
