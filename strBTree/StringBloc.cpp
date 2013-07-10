/*							-*- C++ -*-
** StringBloc.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:32:21 2006 Julien Lemoine
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

#include "StringBloc.h"
#include <assert.h>
#include <algorithm>
#include "tools/Exception.h"

StringBTree::StringBloc::StringBloc(unsigned blocSize) :
  _buff(0), _buffSize(1000000), _nbChars(0)
{
  _buff = new char[_buffSize];
  _strings.reserve(blocSize);
}

StringBTree::StringBloc::~StringBloc()
{
  delete[] _buff;
}

bool StringBTree::StringBloc::isFull() const
{
  return _strings.capacity() == _strings.size();
}

void StringBTree::StringBloc::clear()
{
  _nbChars = 0;
  _strings.resize(0);
}

void StringBTree::StringBloc::add(const std::pair<unsigned, const char*> &el)
{
  assert(el.first > 0);
  assert(el.second[0] != 0);

  if (_strings.capacity() == _strings.size())
    throw ToolBox::Exception("Vector is already full", HERE);
  if (_nbChars + el.first + 1 > _buffSize)
    { // resize buffer
      _buffSize = 2 * _buffSize + el.first + 1;
      char *buff = new char[_buffSize];
      memcpy(buff, _buff, _nbChars);
      delete[] _buff;
      _buff = buff;
    }
  // add string in vector
  _strings.push_back(_nbChars);
  // Copy String
  memcpy(_buff + _nbChars, el.second, el.first);
  _nbChars += el.first;
  // add null terminal
  _buff[_nbChars] = 0;
  ++_nbChars;
}

// Class used for sortLess method
class SortStrings
{
public:
  SortStrings(const char *buff, unsigned buffSize) :
    _buff(buff), _buffSize(buffSize)
  {}
  ~SortStrings() {}
  
  bool operator()(const unsigned v1, const unsigned v2)
  {
    assert(v1 < _buffSize);
    assert(v2 < _buffSize);
    /// oposite comparison function of StringFileAccess::compareReadSortedFile
    return strcmp(_buff + v1, _buff + v2) < 0;
  }
private:
  const char		*_buff;
  const unsigned	_buffSize;
};

void  StringBTree::StringBloc::sortLess()
{
  SortStrings sort(_buff, _nbChars);
  std::sort(_strings.begin(), _strings.end(), sort);
}

unsigned StringBTree::StringBloc::getNbElements() const
{
  return _strings.size();
}

const std::pair<unsigned, const char*> StringBTree::StringBloc::getElement(unsigned pos) const
{
  assert(pos < _strings.size());
  assert(_strings[pos] < _nbChars);

  const char *str = _buff + _strings[pos];
  return std::pair<unsigned, const char*>(strlen(str), str);
}
