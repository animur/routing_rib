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

    nav->_routes.push_back(route);
    // Sort the routes by the route metric
    nav->_routes.sort();
}

void RibTrie::deleteRouteFromTrie(const RtableEntry &route)
{
}

void RibTrie::searchRouteInTrie(const ipaddr prefix,
                                std::list<RtableEntry> &routes)
{
    RibTrieNode *nav = &_rib_head;
    std::map<byte, RibTrieNode *>::const_iterator it;
    bool match_octet_found = true;
    int byte_count = 0;

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
}
