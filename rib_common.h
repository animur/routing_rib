
#ifndef __RIB_COMMON_H
#define __RIB_COMMON_H

#include <thread>
#include <mutex>
#include <stdint.h>
#include <map>
#include <list>

typedef uint32_t ipaddr;
typedef uint8_t byte;

class RtableEntry
{

  private:
    unsigned int _metric;
    ipaddr _gw;
    ipaddr _dst_ip;
    std::string _if_name;
    bool _is_valid;

  public:
};

#endif //_RIB_COMMON_H