/*							-*- C++ -*-
** TestTrieToStr.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 11:02:12 2006 Julien Lemoine
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

#ifndef   	TESTTRIETOSTR_H_
# define   	TESTTRIETOSTR_H_

#include <cppunit/extensions/HelperMacros.h>

namespace UnitTest
{
  /**
   *
   * @brief Trie to string test suite
   *
   * <h2>Try to convert a trie to string</h2>
   *
   * @author Julien Lemoine <speedblue@happycoders.org>
   *
   */
  class TestTrieToStr : public CppUnit::TestCase
    {
      CPPUNIT_TEST_SUITE(TestTrieToStr);
      CPPUNIT_TEST(testUnsigned);
      CPPUNIT_TEST(testOff64t);
      CPPUNIT_TEST(testComplex);
      CPPUNIT_TEST(testComplex2);
      CPPUNIT_TEST_SUITE_END();

    public:
      /// run all test tokenizer
      void testUnsigned();
      void testOff64t();
      void testComplex();
      void testComplex2();
    };
}

#endif 	    /* !TESTTRIETOSTR_H_ */
