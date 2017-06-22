
#ifndef __RIB_TRIE_H
#define __RIB_TRIE_H

#include "rib_common.h"
class RibTrieNode
{

  private:
    byte _octet;
    std::list<RtableEntry> _routes;
    int _num_children;
    std::map<byte, RibTrieNode*> _children;

  public:
    RibTrieNode();

};

class RibTrie
{
    private:
        RibTrieNode _rib_head;
        std::mutex _rib_trie_lock;
        int _vrf;

        RibTrieNode* _getTrieNode(RtableEntry& route);

  public:
    void insertRouteToTrie(RtableEntry& route);
    void deleteRouteFromTrie(RtableEntry& route);
    bool searchRouteInTrie(RtableEntry& route);

};

#endif //__RIB_TRIE_H
