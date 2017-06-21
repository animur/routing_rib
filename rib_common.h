
#ifndef __RIB_COMMON_H
#define __RIB_COMMON_H

#include <thread>
#include <mutex>
#include <stdint.h>
#include <map>
#include <list>
#include <iostream>

typedef uint32_t ipaddr;
typedef uint8_t byte;

class RtableEntry
{

  private:
    byte _metric;
    ipaddr _gw_ip;
    ipaddr _dst_ip;
    std::string _if_name;
    bool _is_valid;

  public:
    RtableEntry(byte metric, ipaddr dst_ip, ipaddr gw, std::string if_name);
    void convStrToIp(ipaddr& ip, std::string str);
    friend std::ostream& operator <<( std::ostream& out, const RtableEntry& route) ;

};

void convStrToIp(ipaddr& ip, std::string s);

#endif //_RIB_COMMON_H


