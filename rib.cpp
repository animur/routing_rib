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
        new_rib_trie->insertRouteInTrie(route);
    }
    else
    {
        /*Rib Trie corresponding to VRF already exists */
        it->second->insertRouteInTrie(route);
    }
}

bool Rib::_delete(const RtableEntry &route, std::string vrf)
{
    std::map<std::string, RibTrie *>::const_iterator it = _rib.find(vrf);

    if (it == _rib.end())
    {
        return false;
    }
    else
    {
        /*Rib Trie corresponding to VRF already exists */
        return (it->second->deleteRouteFromTrie(route));
    }
}


bool Rib::_lookup(const ipaddr prefix, const std::string vrf,
                  std::list<RtableEntry> &routes)
{
    std::map<std::string, RibTrie *>::const_iterator it = _rib.find(vrf);

    if (it == _rib.end())
    {
        /* VRF not present */
        return false;
    }
    else
    {
        /*Rib Trie corresponding to VRF already exists
         * Do longest prefix match in the corresponding Trie
         */
        it->second->searchRouteInTrie(prefix, routes);
        return true;
    }

    //std::cout << route << std::endl;
}

bool Rib::del_route(const std::string if_name, const std::string dst,
                    const std::string gw, const byte metric,
                    const std::string vrf)
{
    ipaddr gw_ip = 0;
    ipaddr dst_ip = 0;
    convStrToIp(gw_ip, gw);
    convStrToIp(dst_ip, dst);

    const RtableEntry route_to_delete(metric, dst_ip, gw_ip, if_name);
    return  _delete(route_to_delete, vrf);
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

void Rib::get_routes(const std::string prefix, const std::string vrf,
                     std::list<RtableEntry> &routes)
{
    ipaddr dst_ip = 0;
    convStrToIp(dst_ip, prefix);

    _lookup(dst_ip, vrf, routes);
}
