/*
** TestStrBTree.cpp
** Login : Julien Lemoine <speedblue@happycoders.org>
** Started on  Wed Dec 27 15:44:54 2006 Julien Lemoine
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

#include "TestStrBTree.h"
#include <stdio.h>
#include "tools/ports.h"
#include "tools/Exception.h"
#include "strBTree/io.h"
#include "strBTree/SortStringsFile.h"
#include "strBTree/StringBTree.h"

void UnitTest::TestStrBTree::testSimpleWithDuplicates()
{
  try
    {
      FILE *f = fopen("test", "wb");
      CPPUNIT_ASSERT(f != 0x0);

      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "pbcd", 4);

      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "pbcd", 4);
      fclose(f);
  
      // Sort file
      StringBTree::SortStringsFile sort("test", false, false);
      sort.start("/tmp", 2);
      uint64_t nbValues = sort.getNbValues();
      CPPUNIT_ASSERT_EQUAL((uint64_t)20, nbValues);
  
      f = fopen64("test", "rb");
      assert(f);
      char	str[32768];
      unsigned	strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)1, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("a"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)1, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("a"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)2, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("ab"), std::string(str));
 
      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)2, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("ab"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("abc"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("abu"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("abu"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("bez"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("bez"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("pbc"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("pbc"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)4, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("pbcd"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)4, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("pbcd"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)2, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("qt"), std::string(str));
 
      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)2, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("qt"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)1, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("z"), std::string(str));
 
      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)1, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("z"), std::string(str));

      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("zbc"), std::string(str));
 
      strLen = StringBTree::readStringSize(f);
      CPPUNIT_ASSERT_EQUAL((unsigned)3, strLen);
      StringBTree::readString(f, str, strLen);
      CPPUNIT_ASSERT_EQUAL(std::string("zbc"), std::string(str));

      fclose(f);
      ToolBox::unlink("test");
    }
  catch (ToolBox::Exception &e)
    {
      std::cerr << e;
      throw e;
    } 
}

void UnitTest::TestStrBTree::testSimple2()
{
  try
    {
      FILE *f = fopen("test", "wb");
      CPPUNIT_ASSERT(f != 0x0);

      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "pbcd", 4);

      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "pbcd", 4);

      const char *token = "中文";
      StringBTree::writeString(f, token, strlen(token));
      fclose(f);
  
      // Sort file
      StringBTree::SortStringsFile sort("test", false);
      sort.start("/tmp", 2);
      uint64_t nbValues = sort.getNbValues();
      CPPUNIT_ASSERT_EQUAL((uint64_t)11, nbValues);

      StringBTree::StrBTree bTree;
  
      // Create String B Tree
      bTree.build("btree", "test", nbValues);

      StringBTree::StrBTree bTree2;
      bTree2.load("btree");
  
      CPPUNIT_ASSERT_EQUAL((off64_t)1, bTree2.getEntry("a", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("b", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("c", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("d", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("p", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("k", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree2.getEntry("z", 1));
      
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("aa", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)2, bTree2.getEntry("ab", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("ac", 2));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("abb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)3, bTree2.getEntry("abc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("abd", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("abt", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)4, bTree2.getEntry("abu", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("abv", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("bey", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)5, bTree2.getEntry("bez", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("beA", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("pbb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)6, bTree2.getEntry("pbc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("pbd", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("pbcc", 4));
      CPPUNIT_ASSERT_EQUAL((off64_t)7, bTree2.getEntry("pbcd", 4));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("pbce", 4));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("qs", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)8, bTree2.getEntry("qt", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("qu", 2));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("x", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("y", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree2.getEntry("z", 1));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("zbb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)10, bTree2.getEntry("zbc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree2.getEntry("zbd", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)11, bTree2.getEntry(token, strlen(token)));



      ToolBox::unlink("test");
      ToolBox::unlink("btree");
    }
  catch (ToolBox::Exception &e)
    {
      std::cerr << e;
      throw e;
    } 
}

void UnitTest::TestStrBTree::testSimple()
{
  try
    {
      FILE *f = fopen("test", "wb");
      CPPUNIT_ASSERT(f != 0x0);

      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "pbcd", 4);

      StringBTree::writeString(f, "bez", 3);
      StringBTree::writeString(f, "ab", 2);
      StringBTree::writeString(f, "z", 1);
      StringBTree::writeString(f, "abc", 3);
      StringBTree::writeString(f, "zbc", 3);
      StringBTree::writeString(f, "pbc", 3);
      StringBTree::writeString(f, "qt", 2);
      StringBTree::writeString(f, "a", 1);
      StringBTree::writeString(f, "abu", 3);
      StringBTree::writeString(f, "pbcd", 4);
      fclose(f);
  
      // Sort file
      StringBTree::SortStringsFile sort("test", false);
      sort.start("/tmp", 2);
      uint64_t nbValues = sort.getNbValues();
      CPPUNIT_ASSERT_EQUAL((uint64_t)10, nbValues);
      StringBTree::StrBTree bTree("test", nbValues);
  
      // Create String B Tree
      bTree.constructBTree("btree");
  
      CPPUNIT_ASSERT_EQUAL((off64_t)1, bTree.getEntry("a", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("b", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("c", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("d", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("p", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("k", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree.getEntry("z", 1));
      
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("aa", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)2, bTree.getEntry("ab", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("ac", 2));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("abb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)3, bTree.getEntry("abc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("abd", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("abt", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)4, bTree.getEntry("abu", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("abv", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("bey", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)5, bTree.getEntry("bez", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("beA", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("pbb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)6, bTree.getEntry("pbc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("pbd", 3));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("pbcc", 4));
      CPPUNIT_ASSERT_EQUAL((off64_t)7, bTree.getEntry("pbcd", 4));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("pbce", 4));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("qs", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)8, bTree.getEntry("qt", 2));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("qu", 2));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("x", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("y", 1));
      CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree.getEntry("z", 1));

      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("zbb", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)10, bTree.getEntry("zbc", 3));
      CPPUNIT_ASSERT_EQUAL((off64_t)0, bTree.getEntry("zbd", 3));

      ToolBox::unlink("test");
      ToolBox::unlink("btree");
    }
  catch (ToolBox::Exception &e)
    {
      std::cerr << e;
      throw e;
    } 
}

void UnitTest::TestStrBTree::testComplex()
{
  FILE *f = fopen("test", "wb");
  CPPUNIT_ASSERT(f != 0x0);

  StringBTree::writeString(f, "Dykedye", 7);
  StringBTree::writeString(f, "Ticidicco", 9);
  StringBTree::writeString(f, "Wuejac", 6);
  StringBTree::writeString(f, "Phetgi", 6);
  StringBTree::writeString(f, "nijBad", 6);
  StringBTree::writeString(f, "ZelIdDo", 7);
  StringBTree::writeString(f, "MuocOrwog4", 10);
  StringBTree::writeString(f, "kiwywacceu", 10);
  StringBTree::writeString(f, "Oytwobyag", 9);
  StringBTree::writeString(f, "nivurwons", 9);
  StringBTree::writeString(f, "]shrau", 6);
  StringBTree::writeString(f, "dyertEwvUs", 10);
  StringBTree::writeString(f, "Iddyulg\"", 8);
  StringBTree::writeString(f, "octOcGiney", 10);
  StringBTree::writeString(f, "hedsIrshIc", 10);
  StringBTree::writeString(f, "Zwuss7", 6);
  StringBTree::writeString(f, "LoifmivFij", 10);
  StringBTree::writeString(f, "krirAcAn", 8);
  StringBTree::writeString(f, "neHawt", 6);
  StringBTree::writeString(f, "odLixdykRy", 10);
  StringBTree::writeString(f, "UchSeHolf;", 10);
  StringBTree::writeString(f, "HydAnis9", 8);
  StringBTree::writeString(f, "Jievtorp", 8);
  StringBTree::writeString(f, "IrEdLia", 7);
  StringBTree::writeString(f, "jiefsoag", 8);
  StringBTree::writeString(f, "larisIrEyk", 10);
  StringBTree::writeString(f, "cubcens", 7);
  fclose(f);


  // Sort file
  StringBTree::SortStringsFile sort("test", false);
  sort.start("/tmp", 2);
  uint64_t nbValues = sort.getNbValues();
  CPPUNIT_ASSERT_EQUAL((uint64_t)27, nbValues);
  StringBTree::StrBTree bTree("test", nbValues);
  
  // Create String B Tree
  bTree.constructBTree("btree");

  CPPUNIT_ASSERT_EQUAL((off64_t)1, bTree.getEntry("Dykedye", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)2, bTree.getEntry("HydAnis9", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)3, bTree.getEntry("Iddyulg\"", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)4, bTree.getEntry("IrEdLia", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)5, bTree.getEntry("Jievtorp", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)6, bTree.getEntry("LoifmivFij", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)7, bTree.getEntry("MuocOrwog4", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)8, bTree.getEntry("Oytwobyag", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree.getEntry("Phetgi", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)10, bTree.getEntry("Ticidicco", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)11, bTree.getEntry("UchSeHolf;", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)12, bTree.getEntry("Wuejac", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)13, bTree.getEntry("ZelIdDo", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)14, bTree.getEntry("Zwuss7", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)15, bTree.getEntry("]shrau", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)16, bTree.getEntry("cubcens", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)17, bTree.getEntry("dyertEwvUs", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)18, bTree.getEntry("hedsIrshIc", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)19, bTree.getEntry("jiefsoag", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)20, bTree.getEntry("kiwywacceu", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)21, bTree.getEntry("krirAcAn", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)22, bTree.getEntry("larisIrEyk", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)23, bTree.getEntry("neHawt", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)24, bTree.getEntry("nijBad", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)25, bTree.getEntry("nivurwons", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)26, bTree.getEntry("octOcGiney", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)27, bTree.getEntry("odLixdykRy", 10));

  ToolBox::unlink("test");
  ToolBox::unlink("btree");

}

void UnitTest::TestStrBTree::testComplex2()
{
  FILE *f = fopen("test", "wb");
  CPPUNIT_ASSERT(f != 0x0);

  StringBTree::writeString(f, "AgPanKaf", 8);
  StringBTree::writeString(f, "dackDy", 6);
  StringBTree::writeString(f, "hefWahob7", 9);
  StringBTree::writeString(f, "Eeshcon}", 8);
  StringBTree::writeString(f, "Wumdanyof+", 10);
  StringBTree::writeString(f, "Mauk5Ov5", 8);
  StringBTree::writeString(f, "VekOccetsh", 10);
  StringBTree::writeString(f, "SexHek", 6);
  StringBTree::writeString(f, "BepOokyi", 8);
  StringBTree::writeString(f, "angyubir", 8);
  StringBTree::writeString(f, "]quekmephs", 10);
  StringBTree::writeString(f, "Vathvaffos", 10);
  StringBTree::writeString(f, "omdeifyag", 9);
  StringBTree::writeString(f, "Myryilal", 8);
  StringBTree::writeString(f, "IcciHiut1", 9);
  StringBTree::writeString(f, "mucHym", 6);
  StringBTree::writeString(f, "eitNoab", 7);
  StringBTree::writeString(f, "yivHilUsh", 9);
  StringBTree::writeString(f, "NelTaHorv", 9);
  StringBTree::writeString(f, "atNen7", 6);
  StringBTree::writeString(f, "OcshacEb2", 9);
  StringBTree::writeString(f, "Miurdid0", 8);
  StringBTree::writeString(f, "Boltyeks", 8);
  StringBTree::writeString(f, "bocKip", 6);
  StringBTree::writeString(f, "acanthIf", 8);
  StringBTree::writeString(f, "Taijdat", 7);
  fclose(f);


  // Sort file
  StringBTree::SortStringsFile sort("test", false);
  sort.start("/tmp", 2);
  uint64_t nbValues = sort.getNbValues();
  CPPUNIT_ASSERT_EQUAL((uint64_t)26, nbValues);
  StringBTree::StrBTree bTree("test", nbValues);
  
  // Create String B Tree
  bTree.constructBTree("btree");

  CPPUNIT_ASSERT_EQUAL((off64_t)1, bTree.getEntry("AgPanKaf", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)2, bTree.getEntry("BepOokyi", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)3, bTree.getEntry("Boltyeks", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)4, bTree.getEntry("Eeshcon}", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)5, bTree.getEntry("IcciHiut1", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)6, bTree.getEntry("Mauk5Ov5", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)7, bTree.getEntry("Miurdid0", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)8, bTree.getEntry("Myryilal", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)9, bTree.getEntry("NelTaHorv", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)10, bTree.getEntry("OcshacEb2", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)11, bTree.getEntry("SexHek", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)12, bTree.getEntry("Taijdat", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)13, bTree.getEntry("Vathvaffos", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)14, bTree.getEntry("VekOccetsh", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)15, bTree.getEntry("Wumdanyof+", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)16, bTree.getEntry("]quekmephs", 10));
  CPPUNIT_ASSERT_EQUAL((off64_t)17, bTree.getEntry("acanthIf", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)18, bTree.getEntry("angyubir", 8));
  CPPUNIT_ASSERT_EQUAL((off64_t)19, bTree.getEntry("atNen7", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)20, bTree.getEntry("bocKip", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)21, bTree.getEntry("dackDy", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)22, bTree.getEntry("eitNoab", 7));
  CPPUNIT_ASSERT_EQUAL((off64_t)23, bTree.getEntry("hefWahob7", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)24, bTree.getEntry("mucHym", 6));
  CPPUNIT_ASSERT_EQUAL((off64_t)25, bTree.getEntry("omdeifyag", 9));
  CPPUNIT_ASSERT_EQUAL((off64_t)26, bTree.getEntry("yivHilUsh", 9));

  ToolBox::unlink("test");
  ToolBox::unlink("btree");
}
