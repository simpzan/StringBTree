/*
** TestStrTrieInterpreter.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 12:19:13 2006 Julien Lemoine
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

#include "TestStrTrieInterpreter.h"
#include "tools/Trie.hxx"
#include "strBTree/TrieToStr.h"
#include "strBTree/StrTrieInterpreter.h"

void UnitTest::TestStrTrieInterpreter::testSimple()
{
  ToolBox::Trie<unsigned> test(0);

  test.addEntry("abc", 3, 1);
  test.addEntry("bde", 3, 2);
  test.addEntry("fgh", 3, 3);
  test.addEntry("abdef", 5, 4);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, true); // is leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("", 0));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("b", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("d", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("z", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("\0", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ksdlf", 5));

  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ab", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("bde", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("bdef", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("bd", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("fgh", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("fghi", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("fg", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abdef", 5));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abdefg", 6));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abdefgh", 7));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abde", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ab", 2));
}

void UnitTest::TestStrTrieInterpreter::testSimpleCut()
{
  ToolBox::Trie<off64_t> test(0);

  test.addEntry("abc", 3, 1);
  test.addEntry("cde", 3, 2);
  test.addEntry("fgh", 3, 3);
  test.addEntry("abdef", 5, 4);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, false); // is not leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("", 0));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("b", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("d", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("z", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("\0", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("ksdlf", 5));

  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ab", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("bde", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("bdef", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("bd", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("cde", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("cdef", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("cd", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("fgh", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("fghi", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("fg", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abdef", 5));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abdefg", 6));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abdefgh", 7));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abde", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ab", 2));
}

void UnitTest::TestStrTrieInterpreter::testSimple2Cut()
{
  ToolBox::Trie<off64_t> test(0);

  test.addEntry("Dykedye", 7, 1);
  test.addEntry("Jievtorp", 8, 2);
  test.addEntry("Phetgi", 6, 3);
  test.addEntry("ZelIdDo", 7, 4);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, false); // is not leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("Dykedye", 7));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("Jievtorp", 8));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("Phetgi", 6));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("ZelIdDo", 7));

  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("Zwuss7", 6));
}

void UnitTest::TestStrTrieInterpreter::testComplex()
{
  ToolBox::Trie<unsigned> test(0);

  test.addEntry("a", 1, 1);
  test.addEntry("ab", 2, 2);
  test.addEntry("ad", 2, 3);
  test.addEntry("abc", 3, 4);
  test.addEntry("abd", 3, 5);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, true); // is a leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("ab", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("ad", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("abd", 3));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ac", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abe", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("b", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("z", 1));
}

void UnitTest::TestStrTrieInterpreter::testComplexCut()
{
  ToolBox::Trie<off64_t> test(0);

  test.addEntry("a", 1, 1);
  test.addEntry("ab", 2, 2);
  test.addEntry("ad", 2, 3);
  test.addEntry("abc", 3, 4);
  test.addEntry("abd", 3, 5);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, false); // non-leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("ab", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("ad", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("abd", 3));

  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("ac", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("abe", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("b", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("z", 1));
}

void UnitTest::TestStrTrieInterpreter::testMix()
{
  ToolBox::Trie<unsigned> test(0);

  test.addEntry("abc", 3, 1);
  test.addEntry("ab", 2, 2);
  test.addEntry("abu", 3, 3);
  test.addEntry("pbc", 3, 4);
  test.addEntry("pbcd", 4, 5);
  test.addEntry("zbc", 3, 6);
  test.addEntry("z", 1, 7);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, true); // leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("ab", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abcde", 5));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("ac", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abt", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("abu", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("abv", 3));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("p", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pa", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pb", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pc", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pab", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pba", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("pbc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbca", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbcb", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbcc", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pbcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbce", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("pbcf", 4));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("f", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("h", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("p", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("z", 1));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("za", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zb", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zc", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zd", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zba", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zbb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)6, (unsigned)interpreter.match("zbc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("zbd", 3));
}

void UnitTest::TestStrTrieInterpreter::testMixCut()
{
  ToolBox::Trie<off64_t> test(0);

  test.addEntry("abc", 3, 1);
  test.addEntry("ab", 2, 2);
  test.addEntry("abu", 3, 3);
  test.addEntry("pbc", 3, 4);
  test.addEntry("pbcd", 4, 5);
  test.addEntry("zbc", 3, 6);
  test.addEntry("z", 1, 7);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();

  StringBTree::StrTrieInterpreter interpreter(str, strLen, false); // non-leaf
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)interpreter.match("a", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("ab", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abcde", 5));

  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("ac", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)interpreter.match("abb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)interpreter.match("abt", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("abu", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("abv", 3));

  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("p", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("pa", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("pb", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pc", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("pab", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("pba", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("pbb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("pbc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pbd", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("pbca", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("pbcb", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)4, (unsigned)interpreter.match("pbcc", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pbcd", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pbce", 4));
  CPPUNIT_ASSERT_EQUAL((unsigned)5, (unsigned)interpreter.match("pbcf", 4));

  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("f", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("h", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)interpreter.match("p", 1));
  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("z", 1));

  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("za", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("zb", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)6, (unsigned)interpreter.match("zc", 2));
  CPPUNIT_ASSERT_EQUAL((unsigned)6, (unsigned)interpreter.match("zd", 2));

  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("zba", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)7, (unsigned)interpreter.match("zbb", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)6, (unsigned)interpreter.match("zbc", 3));
  CPPUNIT_ASSERT_EQUAL((unsigned)6, (unsigned)interpreter.match("zbd", 3));
}
