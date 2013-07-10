/*
** StrTransitionIterator.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 15:24:12 2006 Julien Lemoine
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

#include "StrTransitionIterator.h"

StringBTree::StrTransitionIterator::StrTransitionIterator() :
  _str(0x0), _position(0)
{
}

StringBTree::StrTransitionIterator::StrTransitionIterator(const char *str, unsigned position) :
  _str(str), _position(position)
{
}

StringBTree::StrTransitionIterator::StrTransitionIterator(const StrTransitionIterator &e) :
  _str(e._str), _position(e._position)
{
}

StringBTree::StrTransitionIterator& StringBTree::StrTransitionIterator::operator=(const StrTransitionIterator &e)
{
  _str = e._str;
  _position = e._position;
  return *this;
}

StringBTree::StrTransitionIterator::~StrTransitionIterator()
{
}

bool StringBTree::StrTransitionIterator::operator==(const StrTransitionIterator &other) const
{
  return other._str == _str && other._position == _position;
}

bool StringBTree::StrTransitionIterator::operator!=(const StrTransitionIterator &other) const
{
  return other._str != _str || other._position != _position;
}

StringBTree::StrTransitionIterator StringBTree::StrTransitionIterator::operator++(int offset)
{
  StrTransitionIterator res(_str, _position + 5); // 1 byte for char and 4 bytes for offset
  return res;
}

StringBTree::StrTransitionIterator& StringBTree::StrTransitionIterator::operator++()
{
  _position += 5; // 1 byte for char and 4 bytes for offset
  return *this;
}

StringBTree::StrTransitionIterator& StringBTree::StrTransitionIterator::operator--()
{
  _position -= 5; // 1 byte for char and 4 bytes for offset
  return *this;
}

const unsigned char StringBTree::StrTransitionIterator::operator*() const
{
  return _str[_position];
}

const unsigned char* StringBTree::StrTransitionIterator::operator->() const
{
  return (const unsigned char*)(_str + _position);
}


unsigned StringBTree::StrTransitionIterator::getPosition() const
{
  return _position;
}
