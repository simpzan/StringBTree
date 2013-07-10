/*							-*- C++ -*-
** StringFileAccess.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 11:02:29 2006 Julien Lemoine
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

#include "StringFileAccess.h"
#include <assert.h>
#include "tools/Exception.h"
#include "io.h"

StringBTree::StringsFileAccess::StringsFileAccess(const char *filename, bool write) :
  _file(0x0), _buff(0), _buffSize(32768), _strLen(0)
{
  if (write)
    _file = fopen64(filename, "w+b");
  else
    _file = fopen64(filename, "rb");
  if (!_file)
    throw ToolBox::Exception("Could not open : " + std::string(filename), HERE);
  _buff = new char[_buffSize];
}

StringBTree::StringsFileAccess::~StringsFileAccess()
{
  if (_file)
    fclose(_file);
  delete[] _buff;
}

void StringBTree::StringsFileAccess::readNextObject()
{
  _strLen = readStringSize(_file);
  if (_strLen + 1 > _buffSize)
    {
      delete[] _buff;
      _buff = new char[_buffSize + 1];
    }
  readString(_file, _buff, _strLen);
}

std::pair<unsigned, const char*> StringBTree::StringsFileAccess::getObject() const
{
  return std::pair<unsigned, const char*>(_strLen, _buff);
}

bool StringBTree::StringsFileAccess::eof()
{
  if (_file)
    return feof(_file);
  return true;
}

void StringBTree::StringsFileAccess::write(const std::pair<unsigned, const char*> &pair)
{
  writeString(_file, pair.second, pair.first);
}

void StringBTree::StringsFileAccess::writeFreq(const std::pair<unsigned, const char*> &pair, unsigned freq)
{
  fprintf(_file, "%d\t%s\n", freq, pair.second);
}

bool StringBTree::StringsFileAccess::_compareReadSortedFile(const StringsFileAccess *file1, const StringsFileAccess *file2)
{
  /// Should use greater than here (opposite of sort because we are in
  /// a heap)
  const std::pair<unsigned, const char*> p1 = file1->getObject();
  const std::pair<unsigned, const char*> p2 = file2->getObject();

  return strcmp(p1.second, p2.second) > 0;
}
