/*							-*- C++ -*-
** CopyString.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:19:41 2006 Julien Lemoine
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

#include "CopyString.h"
#include <assert.h>
#include "tools/Exception.h"

StringBTree::CopyString::CopyString() :
  _buff(0x0), _buffSize(32768), _strLen(0)
{
  _buff = new char[_buffSize];
  _buff[0] = 0;
}

StringBTree::CopyString::~CopyString()
{
  delete[] _buff;
}

bool StringBTree::CopyString::cmpEqual(const std::pair<unsigned, const char*> &p1) const
{
  if (_strLen != p1.first)
    return false;
  return strcmp(_buff, p1.second) == 0;
}

void StringBTree::CopyString::affect(const std::pair<unsigned, const char*> &p1)
{
  if ((p1.first + 1) > _buffSize)
    {
      delete[] _buff;
      _buffSize = p1.first + 1;
      _buff = new char[_buffSize];
    }
  memcpy(_buff, p1.second, p1.first);
  _strLen = p1.first;
  _buff[p1.first] = 0;
}

std::pair<unsigned, const char*> StringBTree::CopyString::getObj() const
{
  return std::pair<unsigned, const char*>(_strLen, _buff);
}
