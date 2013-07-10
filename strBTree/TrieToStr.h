/*							-*- C++ -*-
** TrieToStr.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:40:12 2006 Julien Lemoine
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

#ifndef   	TRIETOSTR_H_
# define   	TRIETOSTR_H_

#include <stdio.h>
#include "tools/Trie.h"

namespace StringBTree
{
  /**
   * This class convert a trie in a string that represents this trie
   * (string contains a patricia trie instead of a trie).
   * The string is size optimized and will represent the node of a
   * string B-Tree. This string is then read and interpreted by
   * another class
   * <pre>
   * Here is the format of encoding
   *
   * String B-Tree has two kind of node : internal node and final
   * node. I Choosed to have the same encoding for these two
   * different nodes (Patricia trie is used in order to reduce size of
   * trie on disk)
   *
   * Encoding of string B-Tree Node :
   *
   * There is two kinds of trie node : 
   * non final nodes :
   * | 1 byte | 1 byte        | 1 byte | 4 bytes                          |
   *
   *    ||        ||               ||       ||
   *
   *    0      Nb transitions   Char     Offset in string (unsigned int)
   *
   *                          |___________________________________________|
   *
   *                               repeted number of transitions times
   * Final Nodes :
   * | 1 byte | 2 bytes | X bytes | 8 bytes |
   *
   *    ||        ||         ||       ||
   *
   *    1       Nb of     Strings    Internal node: Adresse of next B-String 
   *            Chars                               node in file (64bits seek adress)
   *            in String            Final Node: value associed to this string
   *
   * Final Node with next nodes
   * | 1 byte | 1 byte        | 1 byte | 4 bytes |                        | 8 bytes       |
   *
   *    ||        ||               ||       ||                                 ||
   *
   *    2      Nb transitions   Char     Offset in string (unsigned int)	value
   *
   *                          |___________________________________________|
   *
   *                               repeted number of transitions times
   *
   *
   */
  class TrieToStr
    {
    public:
      TrieToStr();
      ~TrieToStr();

    private:
      /// avoid copy constructor
      TrieToStr(const TrieToStr &e);
      /// avoid affectation operator
      TrieToStr& operator=(const TrieToStr &e);

    public:
      /**
       * This trie will become a internal node of string B-Tree
       */
      void convertTrie(const ToolBox::Trie<off64_t> &trie);
      /**
       * This trie will become a final node of string B-Tree
       */
      void convertTrie(const ToolBox::Trie<unsigned> &trie);

      /**
       * get result of convertion (string)
       */ 
      const char* getString() const;
      
      /**
       * get size of string
       */
      unsigned getStringSize() const;

    protected:
      /// realloc local buffer
      void _realloc(unsigned size);
      /// compute number of sub nodes (starting at a specific node)
      template <typename T>
      unsigned _computeNbSubNode(const ToolBox::TrieNode<T> &trieNode, bool recursive = false) const;
      /// compute number of bytes needed for a sub trie
      template <typename T>
      unsigned _computeSize(const ToolBox::TrieNode<T> &trieNode) const;
      /// compute number of values stored in a sub trie
      template <typename T>
      unsigned _countNbValue(const ToolBox::TrieNode<T> &trieNode,
			     bool countBrother = false) const;
      /// get value of a sub trie (assume that _countNbValue(trieNode) == 1
      template <typename T>
      off64_t _getTrieNodeValue(const ToolBox::TrieNode<T> &trieNode) const;
      /**
       * recursive function that store trie in _str buffer
       * This function does not resize _str and buffer need to be
       * large enough before calling this method
       */
      template <typename T>
      unsigned _handleTrieNode(const ToolBox::TrieNode<T> &trieNode);

    private:
      /// buffer to store result
      char	*_str;
      /// size of buffer
      unsigned	_strSize;
      /// size of string stored in buffer
      unsigned	_strLen;
      /// position in buffer
      unsigned	_strPosition;
    };
}

#endif 	    /* !TRIETOSTR_H_ */
