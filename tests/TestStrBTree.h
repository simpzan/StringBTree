/*
** TestStrBTree.h
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 15:43:03 2006 Julien Lemoine
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

#ifndef   	TESTSTRBTREE_H_
# define   	TESTSTRBTREE_H_

#include <cppunit/extensions/HelperMacros.h>

namespace UnitTest
{

  /**
   *
   * @brief String B-Tree
   *
   * <h2>Try to create and use a string B-Tree</h2>
   *
   * @author Julien Lemoine <speedblue@happycoders.org>
   *
   */

  class TestStrBTree : public CppUnit::TestCase
  {
    CPPUNIT_TEST_SUITE(TestStrBTree);
    CPPUNIT_TEST(testSimple);
    CPPUNIT_TEST(testSimple2);
    CPPUNIT_TEST(testSimpleWithDuplicates);
    CPPUNIT_TEST(testComplex);
    CPPUNIT_TEST(testComplex2);
    CPPUNIT_TEST_SUITE_END();

  private:
    void testSimple();
    void testSimple2();
    void testSimpleWithDuplicates();
    void testComplex();
    void testComplex2();
  };
}


#endif 	    /* !TESTSTRBTREE_H_ */
