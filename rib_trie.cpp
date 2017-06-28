#include "rib_trie.h"
#include "rib_common.h"

RibTrieNode::RibTrieNode(byte octet) : _octet(octet)
{
}

RibTrieNode::RibTrieNode()
{
    _octet = 0;
}

RibTrie::~RibTrie()
{
    _rib_node_list.clear();
}

RibTrie::RibTrie(std::string vrf) : _vrf(vrf)
{
}

void RibTrie::insertRouteInTrie(const RtableEntry &route)
{
    RibTrieNode *nav = &_rib_head;
    ipaddr ip_to_insert = route._dst_ip;
    std::map<byte, RibTrieNode *>::const_iterator it;

     _rib_trie_lock.lock();
    // std::cout << std::hex << ip_to_insert << std::endl;
    for (int byte_count = 0; byte_count < 4; byte_count++)
    {
        byte curr_octet = (ip_to_insert >> (8 * (3 - byte_count))) & 0xff;

        it = nav->_children.find(curr_octet);
        if (it == nav->_children.end())
        {
            //create new TrieNode for this octet
            RibTrieNode *new_trie_node = new RibTrieNode(curr_octet);

            _rib_node_list.push_back(new_trie_node);
            //std::cout << curr_octet << std::endl;
            nav->_children.insert(std::pair<byte, RibTrieNode *>(curr_octet, new_trie_node));
            nav = new_trie_node;
            nav->_num_children++;
        }
        else
        {
            nav = it->second;
        }
    }

    std::list<RtableEntry>::const_iterator find_route = std::find(nav->_routes.begin(),
            nav->_routes.end(),
            route);

    if (find_route == nav->_routes.end()) {

        nav->_routes.push_back(route);
        nav->_routes.sort();

    }
    // Sort the routes by the route metric
    _rib_trie_lock.unlock();
}

bool RibTrie::deleteRouteFromTrie(const RtableEntry &route)
{

    RibTrieNode *nav = &_rib_head;
    bool res = true;
    ipaddr ip_to_delete = route._dst_ip;
    std::map<byte, RibTrieNode *>::const_iterator it;

    _rib_trie_lock.lock();

    for (int byte_count = 0; byte_count < 4; byte_count++)
    {
        byte curr_octet = (ip_to_delete >> (8 * (3 - byte_count))) & 0xff;

        it = nav->_children.find(curr_octet);

        if (it == nav->_children.end() &&
                (byte_count < 4))
        {
            /* If we dont find an octet before reaching the end of
             * the ip address to delete, the route to delete doesn't exist
             */
            res = false;
            break;

        }
        else
        {
            nav = it->second;
        }
    }



    if (res) {

        /* RtableEntry class has an == operator. remove is sufficient*/
        nav->_routes.remove(route);

        /*
        for (auto list_itr = nav->_routes.begin();
                list_itr !=nav->_routes.end();) {

            if (*list_itr == route) {
                  list_itr = nav->_routes.erase(list_itr);

            } else {
                ++list_itr;
            }
        }
        */

        nav->_routes.sort();
    }

    _rib_trie_lock.unlock();

    return res;
}

void RibTrie::searchRouteInTrie(const ipaddr prefix,
                                std::list<RtableEntry> &routes)
{
    RibTrieNode *nav = &_rib_head;
    std::map<byte, RibTrieNode *>::const_iterator it;
    bool match_octet_found = true;
    int byte_count = 0;

    _rib_trie_lock.lock();
    while (match_octet_found)
    {

        byte curr_octet = (prefix >> (8 * (3 - byte_count))) & 0xff;
        it = nav->_children.find(curr_octet);

        if (it == nav->_children.end())
        {
            match_octet_found = false;
        }
        else
        {
            nav = it->second;
            match_octet_found = true;
        }
        byte_count++;
    }
    routes = nav->_routes;
    _rib_trie_lock.unlock();
}
