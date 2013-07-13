include_directories(../../include)
link_directories(../../../lib)

add_executable(StringBTree_benchmark StringBTree_benchmark.cpp)
target_link_libraries(StringBTree_benchmark gflags tools strBTree utils)
