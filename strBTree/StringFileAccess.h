/*							-*- C++ -*-
** StringFileAccess.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:58:02 2006 Julien Lemoine
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

#ifndef   	STRINGFILEACCESS_H_
# define   	STRINGFILEACCESS_H_

#include <string>
#include <stdio.h>
#include <string.h>

namespace StringBTree
{
  /**
   * @brief class that handle read/write of string in a file
   */
  class StringsFileAccess
    {
    public:
      StringsFileAccess(const char *filename, bool write);
      ~StringsFileAccess();

    private:
      /// avoid default constructor
      StringsFileAccess();
      /// avoid copy constructor
      StringsFileAccess(const StringsFileAccess &e);
      /// avoid affectation operator
      StringsFileAccess& operator=(const StringsFileAccess &e);

    public:
      bool eof();
      void readNextObject();
      std::pair<unsigned, const char*> getObject() const;
      void write(const std::pair<unsigned, const char*> &pair);
      void writeFreq(const std::pair<unsigned, const char*> &pair, unsigned freq);
      static bool _compareReadSortedFile(const StringsFileAccess *file1, const StringsFileAccess *file2);

    public:
      FILE	*_file;
      char	*_buff;
      unsigned	_buffSize;
      unsigned	_strLen;
    };
}

#endif 	    /* !STRINGFILEACCESS_H_ */
