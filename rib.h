#ifndef __RIB_H
#define __RIB_H

#include "rib_common.h"
#include "rib_trie.h"

class Rib
{
  private:
    RibTrieNode _rib_head;
    void _insert(const RtableEntry &route);
    void _lookup(const ipaddr prefix);

  public:
    int num_routes;
    static std::mutex rib_lock;
    void add_route(const std::string if_name, const std::string dst_ip,
                   const std::string gw, const byte metric);
    void get_routes(const std::string prefix, std::list<RtableEntry> &routes);
};

#endif //__RIB_H
