/*
** TrieToStr.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:41:18 2006 Julien Lemoine
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

#include "TrieToStr.h"
#include <assert.h>
#include <string.h>
#include "tools/Trie.hxx"

StringBTree::TrieToStr::TrieToStr() :
  _str(0x0), _strSize(100000), _strLen(0)
{
  _str = new char[_strSize];
}

StringBTree::TrieToStr::~TrieToStr()
{
  delete[] _str;
}

void StringBTree::TrieToStr::convertTrie(const ToolBox::Trie<off64_t> &trie)
{
  _strLen = 0;
  assert(trie.getInitialNode() != 0x0);
  unsigned strSize = _computeSize(*trie.getInitialNode());
  _realloc(strSize);
  _strPosition = 0;
  _handleTrieNode(*trie.getInitialNode());
  _strLen = _strPosition;
}

void StringBTree::TrieToStr::convertTrie(const ToolBox::Trie<unsigned> &trie)
{
  _strLen = 0;
  assert(trie.getInitialNode() != 0x0);
  unsigned strSize = _computeSize(*trie.getInitialNode());
  _realloc(strSize);
  _strPosition = 0;
  _handleTrieNode(*trie.getInitialNode());
  _strLen = _strPosition;
}

void StringBTree::TrieToStr::_realloc(unsigned size)
{
  if (size + 1 > _strSize)
    {
      delete[] _str;
      _str = new char[size + 1];
      _strSize = size + 1;
    }
}

template <typename T>
unsigned StringBTree::TrieToStr::_computeNbSubNode(const ToolBox::TrieNode<T> &trieNode, bool recursive) const
{
  const ToolBox::TrieNode<T> *sub = trieNode.getSubNode();
  if (sub)
    {
      unsigned res = 0;
      while (sub)
	{
	  ++res;
	  if (recursive)
	    res += _computeNbSubNode(*sub, true);
	  sub = sub->getBrother();
	}
      return res;
    }
  else
    return 0; // No sub Node
}

template <typename T>
unsigned StringBTree::TrieToStr::_computeSize(const ToolBox::TrieNode<T> &trieNode) const
{
  if (_countNbValue(trieNode) == 1)
    { // Final node
      return 11 + _computeNbSubNode(trieNode, true);	// 1 byte for kind + 2 bytes for string size + X
							// bytes for substring + 8 byte for value
    }
  unsigned nbSubNode = _computeNbSubNode(trieNode);
  assert(nbSubNode < 256);

  unsigned size = 2 + // 1 byte for kind + 1 byte for nb sub node
    nbSubNode * 5; // 1 byte for char and 4 bytes for string offset (unsigned int)
  if (trieNode.getValue() != 0)
    size += sizeof(off64_t); // 8 bytes for value

  const ToolBox::TrieNode<T> *sub = trieNode.getSubNode();
  while (sub)
    {
      size += _computeSize(*sub);
      sub = sub->getBrother();
    }
  return size;
}

template <typename T>
unsigned StringBTree::TrieToStr::_countNbValue(const ToolBox::TrieNode<T> &trieNode,
					       bool countBrother) const
{
  unsigned nb = 0;
  if (trieNode.getValue() != 0)
    nb = 1;
  if (countBrother)
    {
      const ToolBox::TrieNode<T> *brother = trieNode.getBrother();
      if (brother)
	nb += _countNbValue(*brother, true);
    }
  const ToolBox::TrieNode<T> *sub = trieNode.getSubNode();
  if (sub)
    nb += _countNbValue(*sub, true);
  return nb;
}

template <typename T>
off64_t StringBTree::TrieToStr::_getTrieNodeValue(const ToolBox::TrieNode<T> &trieNode) const
{
  assert(_countNbValue(trieNode) == 1);
  if (trieNode.getValue() != 0)
    return trieNode.getValue();
  assert(trieNode.getSubNode() != 0x0);
  return _getTrieNodeValue(*trieNode.getSubNode());
}

template <typename T>
unsigned StringBTree::TrieToStr::_handleTrieNode(const ToolBox::TrieNode<T> &trieNode)
{
  unsigned p = _strPosition;
  assert(_strPosition < _strSize);
  if (_countNbValue(trieNode) == 1)
    { // Final node
      assert(sizeof(off64_t) == 8);
      assert(sizeof(unsigned short) == 2);
      assert(_strPosition + 11 + _computeNbSubNode(trieNode, true) < _strSize);

      _str[_strPosition] = (unsigned char)1;
      // Store string
      unsigned index = _strPosition + 3;
      const ToolBox::TrieNode<T> *node = trieNode.getSubNode();
      unsigned char label = trieNode.getSubNodeLabel();
      unsigned short strSize = 0;
      while (node)
	{
	  _str[index] = label;
	  ++index;
	  ++strSize;
	  assert(node->getBrother() == 0x0);
	  label = node->getSubNodeLabel();
	  node = node->getSubNode();
	}
      // Store string size
      memcpy(_str + _strPosition + 1, &strSize, sizeof(unsigned short));
      // Store value
      _strPosition = index;
      off64_t val = _getTrieNodeValue(trieNode);
      memcpy(_str + _strPosition, &val, sizeof(off64_t));
      _strPosition += sizeof(off64_t);
      return p;
    }
  unsigned nbSubNode = _computeNbSubNode(trieNode);
  assert(nbSubNode < 256);
  if (trieNode.getValue() == 0)
    _str[_strPosition] = (unsigned char)0;
  else
    _str[_strPosition] = (unsigned char)2;
  ++_strPosition;
  _str[_strPosition] = (unsigned char)nbSubNode;
  ++_strPosition;
  unsigned currentPos = _strPosition, cnt = 0;
  _strPosition += nbSubNode * 5;
  const ToolBox::TrieNode<T> *sub = trieNode.getSubNode();
  unsigned char label = trieNode.getSubNodeLabel();

  if (trieNode.getValue() > 0)
    {
      off64_t val = trieNode.getValue();
      memcpy(_str + _strPosition, &val, sizeof(off64_t));
      _strPosition += sizeof(off64_t);
    }
  while (sub)
    {
      _str[currentPos] = label;
      ++currentPos;
      unsigned offset = _handleTrieNode(*sub);
      assert(sizeof(unsigned) == 4);
      memcpy(_str + currentPos, &offset, sizeof(unsigned));
      currentPos += 4;
      ++cnt;
      label = sub->getBrotherLabel();
      sub = sub->getBrother();
    }
  assert(cnt == nbSubNode);
  return p;
}

const char* StringBTree::TrieToStr::getString() const
{
  return _str;
}
      
unsigned StringBTree::TrieToStr::getStringSize() const
{
  return _strLen;
}
