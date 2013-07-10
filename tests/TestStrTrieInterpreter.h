/*							-*- C++ -*-
** TestStrTrieInterpreter.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 12:09:15 2006 Julien Lemoine
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

#ifndef   	TESTSTRTRIEINTERPRETER_H_
# define   	TESTSTRTRIEINTERPRETER_H_

#include <cppunit/extensions/HelperMacros.h>

namespace UnitTest
{
  /**
   *
   * @brief string trie test suite
   *
   * <h2>Try to search string in a string trie</h2>
   *
   * @author Julien Lemoine <speedblue@happycoders.org>
   *
   */
  class TestStrTrieInterpreter : public CppUnit::TestCase
    {
      CPPUNIT_TEST_SUITE(TestStrTrieInterpreter);
      CPPUNIT_TEST(testSimple);
      CPPUNIT_TEST(testSimpleCut);
      CPPUNIT_TEST(testComplex);
      CPPUNIT_TEST(testComplexCut);
      CPPUNIT_TEST(testMix);
      CPPUNIT_TEST(testMixCut);
      CPPUNIT_TEST(testSimple2Cut);
      CPPUNIT_TEST_SUITE_END();

    public:
      /// run all test tokenizer
      void testSimple();
      void testSimpleCut();
      void testComplex();
      void testComplexCut();
      void testMix();
      void testMixCut();
      void testSimple2Cut();
    };
}

#endif 	    /* !TESTSTRTRIEINTERPRETER_H_ */
