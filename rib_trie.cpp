#include "rib_trie.h"
#include "rib_common.h"

RibTrieNode::RibTrieNode()
{
}

RibTrie::~RibTrie()
{
    _rib_node_list.clear();
}


RibTrie::RibTrie(std::string vrf) : _vrf(vrf)
{

}

void RibTrie::insertRouteToTrie(const RtableEntry &route)
{
    RibTrieNode* nav = &_rib_head;
    ipaddr ip_to_insert = route._dst_ip;
    std::map<byte, RibTrieNode*>::const_iterator it;

    for (int byte_count = 0; byte_count < 4; byte_count++) {
        byte curr_octet = ip_to_insert & (0xff << byte_count);

        it = nav->_children.find(curr_octet);
        if(it == nav->_children.end()) {
            //create new TrieNode for this octet
            RibTrieNode* new_trie_node = new RibTrieNode();

            _rib_node_list.push_back(new_trie_node);

            nav->_children.insert(std::pair<byte, RibTrieNode*>
                                (curr_octet, new_trie_node));
        } else {
            nav = it->second;
        }
    }

}

void RibTrie::deleteRouteFromTrie(const RtableEntry &route)
{
}

bool RibTrie::searchRouteInTrie(const RtableEntry &route)
{

    return false;
}
