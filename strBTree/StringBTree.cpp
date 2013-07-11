/*
 ** StringBTree.cpp
 ** Login : Julien Lemoine <speedblue@happycoders.org>
 ** Started on  Wed Dec 27 13:10:58 2006 Julien Lemoine
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

#include "StringBTree.h"
#include <stdint.h>
#include <cmath>
#include <assert.h>
#include "io.h"
#include "tools/Exception.h"
#include "tools/Trie.hxx"
#include "TrieToStr.h"
#include "StrTrieInterpreter.h"

StringBTree::StrBTree::StrBTree() : _nbValuesPerNode(0), _btree(0x0), _buff(0x0), 
  _buffSize(32768), _finalNode(0x0), _rootNode(0x0), _middleNode(0x0),
  _nbValuesCurrentFinalNode(0),  _nbValuesCurrentMiddleNode(0), _nbValuesRootNode(0), 
  _cnt(0), _trieToStr(0x0), _filePos(0) 
{ 
  unsigned dummy = 0;
  _init(dummy);
}

StringBTree::StrBTree::StrBTree(const std::string &inputFile, uint64_t nbValuesInFile) :
  _inputFile(inputFile), _nbValuesPerNode(0), _btree(0x0), _buff(0x0), 
  _buffSize(32768), _finalNode(0x0), _rootNode(0x0), _middleNode(0x0), _nbValuesCurrentFinalNode(0), 
  _nbValuesCurrentMiddleNode(0), _nbValuesRootNode(0), _cnt(0),
  _trieToStr(0x0), _filePos(0)
{
  _nbValuesPerNode = (unsigned)cbrt(nbValuesInFile) + 1;
  assert(_nbValuesPerNode > 1);
  _init(nbValuesInFile);
}

StringBTree::StrBTree::~StrBTree()
{
  delete[] _buff;
  delete _trieToStr;
  if (_finalNode)
    delete _finalNode;
  if (_rootNode)
    delete _rootNode;
  if (_middleNode)
    delete _middleNode;
  if (_btree)
    fclose(_btree);
}

void StringBTree::StrBTree::_init(unsigned nbValuesInFile)
{
  _buff = new char[_buffSize];
  _trieToStr = new TrieToStr();
  _finalNodeFirstString.reserve(32768);
  _middleNodeFirstString.reserve(32768);
  _finalNode = new ToolBox::Trie<off64_t>(0);
  _rootNode = new ToolBox::Trie<off64_t>(0);
  _middleNode = new ToolBox::Trie<off64_t>(0);
}

bool StringBTree::StrBTree::load(const std::string &idxFile) {
  _btree = fopen64(idxFile.c_str(), "rb");
  assert(_btree);

  off64_t root_offset;
  fread(&root_offset, sizeof(root_offset), 1, _btree);

  fseeko64(_btree, root_offset, SEEK_SET);
  fgetc(_btree);  // skip node type.

  unsigned root_size;
  fread(&root_size, sizeof(unsigned), 1, _btree);
  _root_buff.resize(root_size);
  fread((char *)_root_buff.data(), 1, root_size, _btree);

  return true;
}

bool StringBTree::StrBTree::build(const std::string &idxFile, 
    const std::string &inputFile, uint64_t nbValuesInFile) {
  _nbValuesPerNode = (unsigned)cbrt(nbValuesInFile) + 1;
  assert(_nbValuesPerNode > 1);
  _inputFile = inputFile;
  constructBTree(idxFile);
  return true;
}

void StringBTree::StrBTree::_preConstruct() {
  // placeholder for the root offset.
  int size = sizeof(_filePos);
  fwrite(&_filePos, size, 1, _btree);
  _filePos += size;
}

void StringBTree::StrBTree::_postConstruct() {
  off64_t root_offset = _filePos;
  _writeTrie(*_rootNode, false);
  _root_buff.append(_trieToStr->getString(), _trieToStr->getStringSize());

  fseeko64(_btree, 0, SEEK_SET);
  fwrite(&root_offset, sizeof(root_offset), 1, _btree);
  fflush(_btree);
}

void StringBTree::StrBTree::constructBTree(const std::string &outFilename)
{
  assert(_rootNode);
  assert(_finalNode);
  assert(_middleNode);

  FILE *input = fopen64(_inputFile.c_str(), "rb");
  if (!input)
    throw ToolBox::Exception("Could not open : " + _inputFile, HERE);
  _btree = fopen64(outFilename.c_str(), "w+b");
  if (!_btree)
  {
    delete input;
    throw ToolBox::Exception("Could not open : " + outFilename, HERE);
  }

  _preConstruct();

  try
  {
    while (!feof(input))
    {
      unsigned strSize = readStringSize(input);
      _realloc(strSize);
      readString(input, _buff, strSize);
      ++_cnt;
      _finalNode->addEntry(_buff, strSize, _cnt);
      ++_nbValuesCurrentFinalNode;
      if (_nbValuesCurrentFinalNode == _nbValuesPerNode)
        _flushFinalNode(false);
      else if (_nbValuesCurrentFinalNode == 1)
        _finalNodeFirstString.assign(_buff, strSize);
    }
  }
  catch (ToolBox::EOFException &e) {}
  if (_nbValuesCurrentFinalNode > 0)
    _flushFinalNode(true);
  fclose(input);

  _postConstruct();

  delete _rootNode;
  delete _finalNode;
  delete _middleNode;
  _rootNode = _finalNode = _middleNode = 0x0;
}

off64_t StringBTree::StrBTree::getEntry(const char *str, unsigned strLen)
{
  assert(_btree);
  assert(_trieToStr);

  // Test Root Node;
  StrTrieInterpreter vmRoot(_root_buff.c_str(), _root_buff.size(), false); // root
  off64_t middle = vmRoot.match(str, strLen);
  if (!middle)
    return 0;
  // Seek to middle Node
  if (fseeko64(_btree, middle - 1, SEEK_SET) != 0)
    throw ToolBox::Exception("Seek error", HERE);
  // Read Middle Node
  bool isLeaf = fgetc(_btree) == 1;
  assert(isLeaf == false);
  unsigned strSize;
  if (fread(&strSize, sizeof(unsigned), 1, _btree) != 1)
    throw ToolBox::Exception("read error", HERE);
  _realloc(strSize);
  if (fread(_buff, strSize, 1, _btree) != 1)
    throw ToolBox::Exception("read error", HERE);
  // Test Middle Node
  StrTrieInterpreter vmMiddle(_buff, strSize, false); // middle node
  off64_t final = vmMiddle.match(str, strLen);
  if (!final)
    return 0;
  // Seek to final node
  if (fseeko64(_btree, final - 1, SEEK_SET) != 0)
    throw ToolBox::Exception("Seek error", HERE);
  // Read Final Node
  isLeaf = fgetc(_btree) == 1;
  assert(isLeaf == true);
  if (fread(&strSize, sizeof(unsigned), 1, _btree) != 1)
    throw ToolBox::Exception("read error", HERE);
  _realloc(strSize);
  if (fread(_buff, strSize, 1, _btree) != 1)
    throw ToolBox::Exception("read error", HERE);
  StrTrieInterpreter vmFinal(_buff, strSize, true); // final node
  return vmFinal.match(str, strLen);
}

inline void StringBTree::StrBTree::_realloc(unsigned size)
{
  if (size + 1 > _buffSize)
  {
    delete[] _buff;
    _buff = new char[size + 1];
    _buffSize = size + 1;
  }
}

void StringBTree::StrBTree::_writeTrie(const ToolBox::Trie<off64_t> &trie, bool leaf)
{
  assert(_trieToStr);
  assert(_btree);

  _trieToStr->convertTrie(trie);
  unsigned strLen = _trieToStr->getStringSize();
  const char *buff = _trieToStr->getString();
  int charToWrite = (leaf ? 1 : 0);
  if (fputc(charToWrite, _btree) == EOF) // leaf == 1, non-leaf == 0
    throw ToolBox::Exception("write error", HERE);
  if (fwrite(&strLen, sizeof(unsigned), 1, _btree) != 1)
    throw ToolBox::Exception("write error", HERE);
  if (fwrite(buff, strLen, 1, _btree) != 1)
    throw ToolBox::Exception("write error", HERE);
  _filePos += 1 + sizeof(unsigned) + strLen;
}

void StringBTree::StrBTree::_flushFinalNode(bool force)
{
  assert(_finalNode);
  assert(_middleNode);

  off64_t pos = _filePos;
  _writeTrie(*_finalNode, true);
  _nbValuesCurrentFinalNode = 0;
  _middleNode->addEntry(_finalNodeFirstString.c_str(), _finalNodeFirstString.size(), pos + 1);
  ++_nbValuesCurrentMiddleNode;
  _finalNode->clear();
  if (_nbValuesCurrentMiddleNode == 1)
    _middleNodeFirstString = _finalNodeFirstString;
  if (force || _nbValuesCurrentMiddleNode == _nbValuesPerNode)
  {
    pos = _filePos;
    _writeTrie(*_middleNode, false);
    _nbValuesCurrentMiddleNode = 0;
    _rootNode->addEntry(_middleNodeFirstString.c_str(), _middleNodeFirstString.size(), pos + 1);
    ++_nbValuesRootNode;
    assert(_nbValuesRootNode <= _nbValuesPerNode);
    _middleNode->clear();
  }
}
