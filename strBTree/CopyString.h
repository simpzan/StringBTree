/*							-*- C++ -*-
** CopyString.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:17:21 2006 Julien Lemoine
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

#ifndef   	COPYSTRING_H_
# define   	COPYSTRING_H_

#include <string>

namespace StringBTree
{

  /**
   * class used to store an old string and compare if a new one if
   * equal or not to this one
   */
  class CopyString
    {
    public:
      CopyString();
      ~CopyString();

    private:
      /// avoid copy constructor
      CopyString(const CopyString &e);
      /// avoid affectation operator
      CopyString& operator=(const CopyString &e);

    public:
      bool cmpEqual(const std::pair<unsigned, const char*> &p1) const;
      void affect(const std::pair<unsigned, const char*> &p1);
      std::pair<unsigned, const char*> getObj() const;

    private:
      char	*_buff;
      unsigned	_buffSize;
      unsigned	_strLen;
    };
}

#endif 	    /* !COPYSTRING_H_ */
