#ifndef __RIB_H
#define __RIB_H

#include "rib_common.h"
#include "rib_trie.h"

class Rib
{
  private:
    RibTrieNode _rib_head;
    void _insert(RtableEntry &route);
    void _lookup(ipaddr prefix);

  public:
    int num_routes;
    static std::mutex rib_lock;
    void add_route(std::string dst_ip, std::string gw, byte metric);
    void get_routes(std::string prefix, std::list<RtableEntry> &routes);
};

#endif //__RIB_H