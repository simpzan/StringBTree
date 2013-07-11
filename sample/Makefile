CXXFLAGS= -I .. -I ../../include/
LDFLAGS= ../olib/libstrBTree.a ../olib/libtools.a ../../lib/libutils.a -lgflags
StringBTree_benchmark: StringBTree_benchmark.cpp
	g++ $^ -o $@ ${CXXFLAGS} ${LDFLAGS}
