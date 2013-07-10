/*
** io.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 10:12:58 2006 Julien Lemoine
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

#include <iostream>
#include "io.h"
#include "tools/Exception.h"

void StringBTree::writeString(FILE *file, const char *str, unsigned strLen)
{
  unsigned short size = strLen;
  
  if (fwrite(&size, sizeof(unsigned short), 1, file) != 1 ||
      fwrite(str, strLen, 1, file) != 1)
    throw ToolBox::Exception("write error", HERE);
}

unsigned StringBTree::readStringSize(FILE *file)
{
  unsigned short strLen = 0;
  unsigned nbRead = fread(&strLen, sizeof(unsigned short), 1, file);
  if (nbRead == 0 && feof(file))
    throw ToolBox::EOFException("EOF", HERE);
  else if (nbRead != 1)
    throw ToolBox::FileException("read error", HERE);
  return strLen;
}

void StringBTree::readString(FILE *file, char *destStr, unsigned stringSize)
{
  if (fread(destStr, stringSize, 1, file) != 1)
    throw ToolBox::FileException("read error", HERE);
  destStr[stringSize] = 0;
}
