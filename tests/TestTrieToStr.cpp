/*
** TestTrieToStr.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 11:05:02 2006 Julien Lemoine
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

#include "TestTrieToStr.h"
#include "tools/Trie.hxx"
#include "strBTree/TrieToStr.h"

void UnitTest::TestTrieToStr::testUnsigned()
{
  ToolBox::Trie<unsigned> test(0);

  test.addEntry("abc", 3, 1);
  test.addEntry("bde", 3, 2);
  test.addEntry("fgh", 3, 3);
  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();
  CPPUNIT_ASSERT_EQUAL((unsigned)56, strLen);
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[0]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)(unsigned char)str[1]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('a', str[2]);
  unsigned val = *(unsigned*)(str + 3);
  CPPUNIT_ASSERT_EQUAL((unsigned)17, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('b', str[7]);
  val = *(unsigned*)(str + 8);
  CPPUNIT_ASSERT_EQUAL((unsigned)30, val);
  /// third transition
  CPPUNIT_ASSERT_EQUAL('f', str[12]);
  val = *(unsigned*)(str + 13);
  CPPUNIT_ASSERT_EQUAL((unsigned)43, val);

  // a[bc] -> position 17
  // final node 
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[17]);
  // nb chars
  unsigned short nbChars = *(unsigned short*)(str + 18);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('b', str[20]);
  CPPUNIT_ASSERT_EQUAL('c', str[21]);
  off64_t val64 = *(off64_t*)(str + 22);
  CPPUNIT_ASSERT_EQUAL((off64_t)1, val64);

  // b[de] -> position 30
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[30]);
  // nb chars
  nbChars = *(unsigned short*)(str + 31);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('d', str[33]);
  CPPUNIT_ASSERT_EQUAL('e', str[34]);
  val64 = *(off64_t*)(str + 35);
  CPPUNIT_ASSERT_EQUAL((off64_t)2, val64);

  // f[gh] -> position 30
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[43]);
  // nb chars
  nbChars = *(unsigned short*)(str + 44);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('g', str[46]);
  CPPUNIT_ASSERT_EQUAL('h', str[47]);
  val64 = *(off64_t*)(str + 48);
  CPPUNIT_ASSERT_EQUAL((off64_t)3, val64);
}

void UnitTest::TestTrieToStr::testOff64t()
{
  ToolBox::Trie<off64_t> test(0);
  test.addEntry("abc", 3, 1);
  test.addEntry("bde", 3, 2);
  test.addEntry("fgh", 3, 3);

  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();
  CPPUNIT_ASSERT_EQUAL((unsigned)56, strLen);
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[0]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)3, (unsigned)(unsigned char)str[1]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('a', str[2]);
  unsigned val = *(unsigned*)(str + 3);
  CPPUNIT_ASSERT_EQUAL((unsigned)17, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('b', str[7]);
  val = *(unsigned*)(str + 8);
  CPPUNIT_ASSERT_EQUAL((unsigned)30, val);
  /// third transition
  CPPUNIT_ASSERT_EQUAL('f', str[12]);
  val = *(unsigned*)(str + 13);
  CPPUNIT_ASSERT_EQUAL((unsigned)43, val);

  // a[bc] -> position 17
  // final node 
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[17]);
  // nb chars
  unsigned short nbChars = *(unsigned short*)(str + 18);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('b', str[20]);
  CPPUNIT_ASSERT_EQUAL('c', str[21]);
  off64_t val64 = *(off64_t*)(str + 22);
  CPPUNIT_ASSERT_EQUAL((off64_t)1, val64);

  // b[de] -> position 30
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[30]);
  // nb chars
  nbChars = *(unsigned short*)(str + 31);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('d', str[33]);
  CPPUNIT_ASSERT_EQUAL('e', str[34]);
  val64 = *(off64_t*)(str + 35);
  CPPUNIT_ASSERT_EQUAL((off64_t)2, val64);

  // f[gh] -> position 30
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[43]);
  // nb chars
  nbChars = *(unsigned short*)(str + 44);
  CPPUNIT_ASSERT_EQUAL((unsigned short)2, nbChars);
  CPPUNIT_ASSERT_EQUAL('g', str[46]);
  CPPUNIT_ASSERT_EQUAL('h', str[47]);
  val64 = *(off64_t*)(str + 48);
  CPPUNIT_ASSERT_EQUAL((off64_t)3, val64);
}

void UnitTest::TestTrieToStr::testComplex()
{
  ToolBox::Trie<off64_t> test(0);
  test.addEntry("abcd", 4, 1);
  test.addEntry("ace", 3, 2);
  test.addEntry("abde", 4, 3);

  StringBTree::TrieToStr trieToStr;

  trieToStr.convertTrie(test);
  const char *str = trieToStr.getString();
  unsigned strLen = trieToStr.getStringSize();
  CPPUNIT_ASSERT_EQUAL((unsigned)67, strLen);
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[0]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[1]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('a', str[2]);
  unsigned val = *(unsigned*)(str + 3);
  CPPUNIT_ASSERT_EQUAL((unsigned)7, val);

  // a*
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[7]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[8]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('b', str[9]);
  val = *(unsigned*)(str + 10);
  CPPUNIT_ASSERT_EQUAL((unsigned)19, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('c', str[14]);
  val = *(unsigned*)(str + 15);
  CPPUNIT_ASSERT_EQUAL((unsigned)55, val);

  // ab*
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[19]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[20]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('c', str[21]);
  val = *(unsigned*)(str + 22);
  CPPUNIT_ASSERT_EQUAL((unsigned)31, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('d', str[26]);
  val = *(unsigned*)(str + 27);
  CPPUNIT_ASSERT_EQUAL((unsigned)43, val);

  // first final node
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[31]);
  unsigned short nbChars = *(unsigned short*)(str + 32);
  CPPUNIT_ASSERT_EQUAL((unsigned short)1, nbChars);
  CPPUNIT_ASSERT_EQUAL('d', str[34]);
  off64_t val64 = *(off64_t*)(str + 35);
  CPPUNIT_ASSERT_EQUAL((off64_t)1, val64);

  // second final node
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[43]);
  nbChars = *(unsigned short*)(str + 44);
  CPPUNIT_ASSERT_EQUAL((unsigned short)1, nbChars);
  CPPUNIT_ASSERT_EQUAL('e', str[46]);
  val64 = *(off64_t*)(str + 47);
  CPPUNIT_ASSERT_EQUAL((off64_t)3, val64);

  // third final node
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[55]);
  nbChars = *(unsigned short*)(str + 56);
  CPPUNIT_ASSERT_EQUAL((unsigned short)1, nbChars);
  CPPUNIT_ASSERT_EQUAL('e', str[58]);
  val64 = *(off64_t*)(str + 59);
  CPPUNIT_ASSERT_EQUAL((off64_t)2, val64);

}

void UnitTest::TestTrieToStr::testComplex2()
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
  CPPUNIT_ASSERT_EQUAL((unsigned)80, strLen);
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)0, (unsigned)(unsigned char)str[0]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[1]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('a', str[2]);
  unsigned val = *(unsigned*)(str + 3);
  CPPUNIT_ASSERT_EQUAL((unsigned)7, val);

  // a*
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[7]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[8]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('b', str[9]);
  val = *(unsigned*)(str + 10);
  CPPUNIT_ASSERT_EQUAL((unsigned)27, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('d', str[14]);
  val = *(unsigned*)(str + 15);
  CPPUNIT_ASSERT_EQUAL((unsigned)69, val);
  // Check value
  off64_t val64 = *(off64_t*)(str + 19);
  CPPUNIT_ASSERT_EQUAL((off64_t)1, val64);
  
  // ab*
  // non-final node
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[27]);
  // nb nodes
  CPPUNIT_ASSERT_EQUAL((unsigned)2, (unsigned)(unsigned char)str[28]);
  // First transition
  CPPUNIT_ASSERT_EQUAL('c', str[29]);
  val = *(unsigned*)(str + 30);
  CPPUNIT_ASSERT_EQUAL((unsigned)47, val);
  // second transition
  CPPUNIT_ASSERT_EQUAL('d', str[34]);
  val = *(unsigned*)(str + 35);
  CPPUNIT_ASSERT_EQUAL((unsigned)58, val);
  // Check value
  val64 = *(off64_t*)(str + 39);
  CPPUNIT_ASSERT_EQUAL((off64_t)2, val64);

  // abc
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[47]);
  unsigned short nbChars = *(unsigned short*)(str + 48);
  CPPUNIT_ASSERT_EQUAL((unsigned short)0, nbChars);
  val64 = *(off64_t*)(str + 50);
  CPPUNIT_ASSERT_EQUAL((off64_t)4, val64);

  // abd
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[58]);
  nbChars = *(unsigned short*)(str + 59);
  CPPUNIT_ASSERT_EQUAL((unsigned short)0, nbChars);
  val64 = *(off64_t*)(str + 61);
  CPPUNIT_ASSERT_EQUAL((off64_t)5, val64);

  // ad
  CPPUNIT_ASSERT_EQUAL((unsigned)1, (unsigned)(unsigned char)str[69]);
  nbChars = *(unsigned short*)(str + 70);
  CPPUNIT_ASSERT_EQUAL((unsigned short)0, nbChars);
  val64 = *(off64_t*)(str + 72);
  CPPUNIT_ASSERT_EQUAL((off64_t)3, val64);
}
