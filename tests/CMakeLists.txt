INCLUDE_DIRECTORIES(
	${WIKICLUST_SOURCE_DIR}
	${CPPUNIT_INCLUDE}
)

ADD_EXECUTABLE(TestSuite
	TestStrBTree.cpp
	TestStrBTree.h
	TestStrTrieInterpreter.cpp
	TestStrTrieInterpreter.h
	TestStringFactory.cpp
	TestStringFactory.h
	TestSuite.cpp
	TestToolBoxHash.cpp
	TestToolBoxHash.h
	TestToolBoxTrie.cpp
	TestToolBoxTrie.h
	TestTrieToStr.cpp
	TestTrieToStr.h
)

TARGET_LINK_LIBRARIES(TestSuite
	strBTree
	tools
	cppunit
)

ADD_CUSTOM_COMMAND(
                TARGET TestSuite
                POST_BUILD
                COMMAND ${WIKICLUST_SOURCE_DIR}/tests/TestSuite
)
