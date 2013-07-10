/*							-*- C++ -*-
** SortStringsFile.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:15:14 2006 Julien Lemoine
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

#ifndef   	SORTSTRINGSFILE_H_
# define   	SORTSTRINGSFILE_H_

#include "tools/SortFile.hxx"
#include "tools/SortFileThread.hxx"
#include "CopyString.h"
#include "StringBloc.h"
#include "StringFileAccess.h"

namespace StringBTree
{
  /**
   * We are storing string as a pair on disk, first element of pair is
   * the size of string and the second element of pair is the string
   * itself.
   * 
   * Class StringBloc implement the read of a bloc of string in memory
   * with a bloc allocation (will not allocate one element for each
   * string)
   * 
   * StringFileAccess is a binding for method in io.h, it implement
   * read/write in a file.
   * 
   * CopyString implement the copy of a string and the equal
   * comparator in order to count frequencies
   */
  typedef ToolBox::SortFile<std::pair<unsigned, const char*>, 
			    StringBloc,
			    StringsFileAccess,
			    CopyString> SortStringsFile;
}

#endif 	    /* !SORTSTRINGSFILE_H_ */
