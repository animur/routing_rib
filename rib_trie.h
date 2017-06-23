
#ifndef __RIB_TRIE_H
#define __RIB_TRIE_H

#include "rib_common.h"
class RibTrieNode
{

  friend class RibTrie;

private:
  byte _octet;
  std::list<RtableEntry> _routes;
  int _num_children;
  std::map<byte, RibTrieNode *> _children;

public:
  RibTrieNode(byte octet);
  RibTrieNode();
};

class RibTrie
{
private:
  RibTrieNode _rib_head;
  std::mutex _rib_trie_lock;
  std::string _vrf;
  std::vector<RibTrieNode *> _rib_node_list;
  RibTrieNode *_getTrieNode(RtableEntry &route);

public:
  void insertRouteToTrie(const RtableEntry &route);
  void deleteRouteFromTrie(const RtableEntry &route);
  bool searchRouteInTrie(const RtableEntry &route);
  RibTrie(std::string);
  ~RibTrie();
};

#endif //__RIB_TRIE_H
