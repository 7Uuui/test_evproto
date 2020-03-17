set(CXX_FLAGS
 -g
 -Wall
 -Wextra
 # -Werror
 -Wconversion
 -Wunused-parameter
 -Wold-style-cast
 -MMD
 -Wpointer-arith
 -Wshadow
 -Wwrite-strings
 -rdynamic
 -L/usr/local/lib
 -levent_core
 -levent_extra
 -levent_pthreads
 -lgflags
 -lglog
 -lprotobuf
 -pthread
 -lpthread
 -Wl,--rpath
 -Wl,/usr/local/lib
)

message("hello")
message(${PROJECT_SOURCE_DIR})
message(${PROJECT_BINARY_DIR})
message(${PROJECT_SOURCE_DIR}../)




string(REPLACE ";" " " CMAKE_CXX_FLAGS "${CXX_FLAGS}")

set(CMAKE_CXX_FLAGS_DEBUG "-O0")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")
set(AAA sudoku_client.cc sudoku.pb.cc testTime/TimeStamp.cc)
set(BBB sudoku_server.cc sudoku.pb.cc testTime/TimeStamp.cc)






include_directories(${PROJECT_SOURCE_DIR}/../)
include_directories(${PROJECT_SOURCE_DIR}/../evproto)
include_directories(${PROJECT_SOURCE_DIR}/testTime)

link_directories(/usr/local/lib)
link_directories(${PROJECT_SOURCE_DIR})
link_directories(${PROJECT_SOURCE_DIR}/../)
link_directories(${PROJECT_SOURCE_DIR}/../evproto)

message(${PROJECT_SOURCE_DIR}/../)


add_definitions(-std=c++11)
 
add_custom_command(OUTPUT sudoku.pb.cc sudoku.pb.h
  COMMAND protoc
  ARGS --cpp_out . ${CMAKE_CURRENT_SOURCE_DIR}/sudoku.proto -I${CMAKE_CURRENT_SOURCE_DIR}
  DEPENDS sudoku.proto
  VERBATIM )

#add_executable(eventloop_test eventloop_test.cc)
#target_link_libraries(eventloop_test  evproto gflags)


add_library(sudoku_proto sudoku.pb.cc)
target_link_libraries(sudoku_proto evproto protobuf)

add_executable(sudoku_server ${BBB})
target_link_libraries(sudoku_server evproto  pthread protobuf  sudoku_proto  gflags)

add_executable(sudoku_client ${AAA})
target_link_libraries(sudoku_client evproto sudoku_proto  protobuf gflags)
