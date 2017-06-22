#ifndef __RIB_H
#define __RIB_H

#include "rib_common.h"
#include "rib_trie.h"

class Rib
{
private:
  static std::map<std::string, RibTrie *> _rib;
  void _insert(const RtableEntry &route, std::string vrf);
  void _lookup(const ipaddr prefix, std::string vrf);

public:
  int num_routes;
  void add_route(const std::string if_name, const std::string dst_ip,
                 const std::string gw, const byte metric,
                 const std::string vrf_id);
  void get_routes(const std::string prefix, std::list<RtableEntry> &routes);
};

#endif //__RIB_H
