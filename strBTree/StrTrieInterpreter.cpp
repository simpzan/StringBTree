/*
 ** StrTrieInterpreter.cpp
 ** Login : Julien Lemoine <speedblue@happycoders.org>
 ** Started on  Wed Dec 27 11:12:03 2006 Julien Lemoine
 ** $Id$
 **
 ** Copyright (C) 2006 Julien Lemoine
 ** This program is free software; you can redistribute it and/or modify
 ** it under the terms of the GNU Lesser General Public License as published by
 ** the Free Software Foundation; either version 2 of the License, or
 ** (at your option) any later version.
 **
 ** This program is distributed in the hope that it will be useful,
 ** but WITHOUT ANY WARRANTY; without even the implied warranty of
 ** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 ** GNU Lesser General Public License for more details.
 **
 ** You should have received a copy of the GNU Lesser General Public License
 ** along with this program; if not, write to the Free Software
 ** Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "StrTrieInterpreter.h"
#include <assert.h>
#include <algorithm>
#include "StrTransitionIterator.h"

StringBTree::StrTrieInterpreter::StrTrieInterpreter(const char *str, unsigned strLen, bool isLeaf) :
_str(str), _strSize(strLen), _isLeaf(isLeaf)
{
}

StringBTree::StrTrieInterpreter::~StrTrieInterpreter()
{
}

off64_t StringBTree::StrTrieInterpreter::match(const char *str, unsigned strLen) const
{
  if (_isLeaf)
    return _fullMatch(str, strLen);
  return _lowerBoundDichotomicSearch(str, strLen, 0, 0, true);
}

unsigned StringBTree::StrTrieInterpreter::_dichotomicSearch(unsigned char chr, unsigned pos) const
{
  assert(_str[pos] == 0 || _str[pos] == 2);
  
  // Node position is pos
  // First char position is pos + 2
  // Last char position is
  
  unsigned nbNodes = (unsigned char)_str[pos + 1];
  
  StrTransitionIterator begin(_str, pos + 2);
  StrTransitionIterator end(_str, pos + 2 + nbNodes * 5);
  StrTransitionIterator it = std::lower_bound(begin, end, chr);
  if (it != end && *it == chr)
  {
    unsigned val = *(const unsigned *)(_str + it.getPosition() + 1);
    return val;
  }
  return 0;
}

off64_t StringBTree::StrTrieInterpreter::_lowerBoundDichotomicSearch(const char *str, unsigned strLen,
                                                                     unsigned strPos, unsigned triePos, bool fullMatch) const
{
  if (strPos == strLen) // string is totally parsed
  {
    if (_str[triePos] == 0) // non-leaf
    { // string is smaller than trie entry
      if (fullMatch)
        return 0;
      return _maxSubValue(triePos);
    }
    if (_str[triePos] == 2) // final node with transitions
    {
      unsigned nbTrans = *(unsigned char*)(_str + triePos + 1);
      off64_t res = *(off64_t*)(_str + triePos + 2 + nbTrans * 5);
      return res;
    }
    // we are on a leaf node
    unsigned short nbChars = *(unsigned short*)(_str + triePos + 1);
    off64_t res = *(off64_t*)(_str + triePos + 3 + nbChars);
    if (nbChars == 0) // string match totaly dictionary
      return res;
    // string is smaller than trie entry
    if (fullMatch)
      return 0;
    return _maxSubValue(triePos);
  }
  
  // non-leaf node
  if (_str[triePos] == 0 || _str[triePos] == 2)
  {
    unsigned nbNodes = (unsigned char)_str[triePos + 1];
    off64_t res = 0;
    StrTransitionIterator begin(_str, triePos + 2);
    StrTransitionIterator end(_str, triePos + 2 + nbNodes * 5);
    unsigned char ch = str[strPos];
    StrTransitionIterator it = std::lower_bound(begin, end, ch);
    if (it != end && *it == (unsigned char)str[strPos])
    {
      unsigned newTriePos = *(unsigned*)(_str + it.getPosition() + 1);
      res = _lowerBoundDichotomicSearch(str, strLen, strPos + 1, newTriePos, fullMatch);
    }
    if (!res && it != begin)
    {
      --it; // we need the previous element
      unsigned newTriePos = *(unsigned*)(_str + it.getPosition() + 1);
      res = _maxSubValue(newTriePos);
    }
    if (!res && _str[triePos] == 2 && strPos > 0)
    {
      // We have matched a start of string in full text and the
      // end of string does not match. For example we have in trie
      // "ab" and we are trying to match "abc". So "ab" is the
      // value <= to the string, return value
      res = *(off64_t*)(_str + triePos + 2 + nbNodes * 5);
    }
    return res;
  }
  // leaf-node
  unsigned nbChars = *(unsigned short*)(_str + triePos + 1);
  off64_t res = *(off64_t*)(_str + triePos + 3 + nbChars);
  unsigned nbCharToCmp = std::min(nbChars, strLen - strPos);
  int cmp = strncmp(str + strPos, _str + triePos + 3, nbCharToCmp);
  if (cmp < 0) // string < trie
    return 0;
  if (cmp > 0 ||  // string is greater than trie
      (cmp == 0 && strLen - strPos >= nbChars)) // string is bigger than trie
    return res;
  if (fullMatch) // string is smaller
    return 0;
  return res;
}

off64_t StringBTree::StrTrieInterpreter::_fullMatch(const char *str, unsigned strLen) const
{
  unsigned position = 0;
  unsigned strPos = 0;
  bool end = false;
  
  while (!end && position < _strSize && (_str[position] == 0 || _str[position] == 2)
         && strPos < strLen) // internal node of trie
  {
    position = _dichotomicSearch(str[strPos], position);
    if (!position)
      end = true;
    ++strPos;
  }
  // Final node with transitions reached
  if (!end && _str[position] == 2 && strPos == strLen)
  {
    unsigned nbTrans = *(unsigned char*)(_str + position + 1);
    unsigned offset = position + 2 + nbTrans * 5;
    off64_t val = *(const off64_t*)(_str + offset);
    return val;
  }
  // Final node without transitions reached
  else if (!end && _str[position] == 1 && strPos <= strLen)
  {
    unsigned short nbChars = *(unsigned short*)(_str + position + 1);
    if (strPos + nbChars == strLen &&
        (!nbChars || strncmp(_str + position + 3, str + strPos, nbChars) == 0))
    {
      off64_t val = *(const off64_t*)(_str + position + 3 + nbChars);
      return val;
    }
  }
  return 0;
}

off64_t StringBTree::StrTrieInterpreter::_maxSubValue(unsigned position) const
{
  if (position == 0)
    return 0;
  while (_str[position] == 0 || _str[position] == 2)
  {
    // Node position is pos
    // First char position is pos + 2
    // Last char position is
    unsigned nbNodes = (unsigned char)_str[position + 1];
    position = *(const unsigned*)(_str + position + 3 + (nbNodes - 1) * 5);
    if (position == 0)
      return 0;
  }
  unsigned short nbChars = *(unsigned short*)(_str + position + 1);
  off64_t val = *(const off64_t*)(_str + position + 3 + nbChars);
  return val;
}
