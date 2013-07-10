/*							-*- C++ -*-
** StrTrieInterpreter.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 11:10:21 2006 Julien Lemoine
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

#ifndef   	STRTRIEINTERPRETER_H_
# define   	STRTRIEINTERPRETER_H_

#include <iostream>
#include <iterator>

namespace StringBTree
{
  /**
   * @brief interpreter of string trie. A string trie represents a
   * node of string B-Tree.
   */
  class StrTrieInterpreter
    {
    public:
      StrTrieInterpreter(const char *str, unsigned strLen, bool isLeaf);
      ~StrTrieInterpreter();

    private:
      /// avoid default constructor
      StrTrieInterpreter();
      /// avoid copy constructor
      StrTrieInterpreter(const StrTrieInterpreter &e);
      /// avoid affectation operator
      StrTrieInterpreter& operator=(const StrTrieInterpreter &e);

    public:
      /**
       * try to match a string in string trie
       */
      off64_t match(const char *str, unsigned strLen) const;
      
    protected:
      /**
       * match on a leaf of string B-Tree (full text match)
       */
      off64_t _fullMatch(const char *str, unsigned strLen) const;
      
      /// dichotomic search over char transitions
      unsigned _dichotomicSearch(unsigned char chr, unsigned pos) const;
      /**
       * dichotomic search over char transitions (match transition <=
       * chr) for internal node. Return the lower bound of string
       */
      off64_t _lowerBoundDichotomicSearch(const char *str, unsigned strLen,
					  unsigned strPos, unsigned triePos, bool fullMatch) const;

      off64_t _maxSubValue(unsigned position) const;

    private:
      /// buffer
      const char	*_str;
      /// buffer size
      unsigned		_strSize;
      /// true if B-Tree node is a leaf (trie must be complet)
      bool		_isLeaf;
    };
}

#endif 	    /* !STRTRIEINTERPRETER_H_ */
