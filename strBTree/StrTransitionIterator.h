/*
** StrTransitionIterator.h
** Login : Julien Lemoine <speedblue@speedblue.org>
** Started on  Wed Dec 27 15:23:38 2006 Julien Lemoine
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

#ifndef   	STRTRANSITIONITERATOR_H_
# define   	STRTRANSITIONITERATOR_H_

#include <iterator>

namespace StringBTree
{

  /**
   * @brief iterate over transition of trie
   */
  class StrTransitionIterator : 
    public std::iterator<std::forward_iterator_tag, unsigned char>
    {
    public:
      StrTransitionIterator();
      StrTransitionIterator(const char *str, unsigned position);
      StrTransitionIterator(const StrTransitionIterator &e);
      StrTransitionIterator& operator=(const StrTransitionIterator &e);
      ~StrTransitionIterator();

    public:
      bool operator==(const StrTransitionIterator &other) const;
      bool operator!=(const StrTransitionIterator &other) const;
      /// postfix ++ operator (copy of object)
      StrTransitionIterator operator++(int);
      /// prefix ++ operator (copy of object)
      StrTransitionIterator& operator++();
      StrTransitionIterator& operator--();
      const unsigned char operator*() const;
      const unsigned char* operator->() const;
      unsigned getPosition() const;

    private:
      const char	*_str;
      unsigned		_position;
    };
}

#endif 	    /* !STRTRANSITIONITERATOR_H_ */
