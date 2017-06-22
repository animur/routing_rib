#include "rib_trie.h"
#include "rib_common.h"

RibTrieNode::RibTrieNode()
{
}

RibTrie::RibTrie(std::string vrf) : _vrf(vrf)
{
}

void RibTrie::insertRouteToTrie(RtableEntry &route)
{
}

void RibTrie::deleteRouteFromTrie(RtableEntry &route)
{
}

bool RibTrie::searchRouteInTrie(RtableEntry &route)
{

    return false;
}
