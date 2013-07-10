/*							-*- C++ -*-
** StringBloc.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:22:14 2006 Julien Lemoine
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

#ifndef   	STRINGBLOC_H_
# define   	STRINGBLOC_H_

#include <string>
#include <vector>
#include <string.h>

namespace StringBTree
{
  /**
   * @brief class that store a set of string
   */
  class StringBloc
    {
    public:
      StringBloc(unsigned blocSize);
      ~StringBloc();

    private:
      /// avoid default constructor
      StringBloc();
      /// avoid copy constructor
      StringBloc(const StringBloc &e);
      /// avoid affectation operator
      StringBloc& operator=(const StringBloc &e);

    public:
      /// return true if the vector is full
      bool isFull() const;
      /// reset the vector of string
      void clear();
      /// add a new element
      void add(const std::pair<unsigned, const char*> &el);
      /// sort the elements
      void sortLess();
      /// return the number of elements (N)
      unsigned getNbElements() const;
      /// get element after sort (pos must be between [0..N-1]
      const std::pair<unsigned, const char*> getElement(unsigned pos) const;

    private:
      char			*_buff;
      unsigned			_buffSize;
      unsigned			_nbChars;
      std::vector<unsigned>	_strings;
    };
}

#endif 	    /* !STRINGBLOC_H_ */
