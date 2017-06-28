#ifndef __RIB_H
#define __RIB_H

#include "rib_common.h"
#include "rib_trie.h"

class Rib
{
private:
  static Rib* rib_instance;
  std::map<std::string, RibTrie *> _rib_vrf_tries;
  void _insert(const RtableEntry &route, std::string vrf);
  bool _delete(const RtableEntry &route, std::string vrf);
  bool _lookup(const ipaddr prefix, const std::string vrf,
               std::list<RtableEntry> &routes);

public:

  static Rib* get_instance();
  void add_route(const std::string if_name, const std::string dst_ip,
                 const std::string gw, const byte metric,
                 const std::string vrf_id);
  bool del_route(const std::string if_name, const std::string dst_ip,
                 const std::string gw, const byte metric,
                 const std::string vrf_id);
  void get_routes(const std::string prefix, std::string vrf,
                  std::list<RtableEntry> &routes);
};

#endif //__RIB_H
