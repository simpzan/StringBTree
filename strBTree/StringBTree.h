/*
** StringBTree.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 12:51:03 2006 Julien Lemoine
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

#ifndef   	STRINGBTREE_H_
# define   	STRINGBTREE_H_

#include <stdint.h>
#include <string>
#include <vector>
#include <stdio.h>
#include "tools/Trie.h"
#include "io.h"

namespace StringBTree
{
  class TrieToStr;
  /**
   * @brief convert a input file containing sorted sequence of string
   * in a String B-Tree. This string B-Tree will perform only two disc
   * access to test presence of any entry
   */
  class StrBTree
    {
    public:
      StrBTree();
      StrBTree(const std::string &inputFile, uint64_t nbValuesInFile);
      ~StrBTree();

    private:
      /// avoid default constructor
      //StrBTree();
      /// avoid copy constructor
      StrBTree(const StrBTree &e);
      /// avoid affectation operator
      StrBTree& operator=(const StrBTree &e);

    public:
      /**
       * create the string B-Tree structure using _inputFile as entry
       * and outFilename as output
       */
      void constructBTree(const std::string &outFilename);
      /**
       * get the value associed to string(str, strlen) in string
       * B-Tree, return 0 if string is not in string B-Tree
       */
      off64_t getEntry(const char *str, unsigned strLen);

      // load the existing string B-tree.
      bool load(const std::string &idxFile);
      bool build(const std::string &idxFile, const std::string &inputFile, uint64_t nbValuesInFile);

    protected:
      void _realloc(unsigned size);
      void _writeTrie(const ToolBox::Trie<off64_t> &trie, bool leaf);
      void _flushFinalNode(bool force);
      void _init(unsigned nbValuesInFile);
      void _preConstruct();
      void _postConstruct();
      void _flushMiddleNode();

    private:
      std::string		_inputFile;
      unsigned			_nbValuesPerNode;
      FILE			*_btree;
      char			*_buff;
      unsigned			_buffSize;
      ToolBox::Trie<off64_t>	*_finalNode;
      ToolBox::Trie<off64_t>	*_rootNode;
      ToolBox::Trie<off64_t>	*_middleNode;
      unsigned			_nbValuesCurrentFinalNode;
      unsigned			_nbValuesCurrentMiddleNode;
      unsigned			_nbValuesRootNode;
      off64_t			_cnt;
      TrieToStr			*_trieToStr;
      off64_t			_filePos;
      std::string		_finalNodeFirstString;
      std::string		_middleNodeFirstString;

      std::string   _root_buff;
  };
}


#endif 	    /* !STRINGBTREE_H_ */
