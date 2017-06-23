#include "rib_common.h"
#include "rib.h"

/* Definition of the static variable */
std::map<std::string, RibTrie *> Rib::_rib;

void Rib::_insert(const RtableEntry &route, std::string vrf)
{
    std::map<std::string, RibTrie *>::const_iterator it = _rib.find(vrf);

    if (it == _rib.end())
    {
        /*New VRF. Create the RibTrie corresponding to the VRF*/
        RibTrie *new_rib_trie = new RibTrie(vrf);
        _rib.insert(std::pair<std::string, RibTrie *>(vrf, new_rib_trie));
        new_rib_trie->insertRouteToTrie(route);
    } else {
        /*Rib Trie corresponding to VRF already exists */
        it->second->insertRouteToTrie(route);
    }

    std::cout << route << std::endl;
}

void Rib::_lookup(const ipaddr prefix, std::string vrf)
{
}

void Rib::add_route(const std::string if_name, const std::string dst,
                    const std::string gw, const byte metric,
                    const std::string vrf)
{
    ipaddr gw_ip = 0;
    ipaddr dst_ip = 0;
    convStrToIp(gw_ip, gw);
    convStrToIp(dst_ip, dst);

    const RtableEntry route_to_insert(metric, dst_ip, gw_ip, if_name);

    _insert(route_to_insert, vrf);
}

void Rib::get_routes(const std::string prefix, std::list<RtableEntry> &routes)
{
}
