# CMAKE generated file: DO NOT EDIT!
# Generated by CMake Version 3.16

# SRC_FILES at src/network/CMakeLists.txt:1 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/hjkim/Lets_go_RDMA/client/src/network/*.cpp")
set(OLD_GLOB
  "/home/hjkim/Lets_go_RDMA/client/src/network/RDMA.cpp"
  "/home/hjkim/Lets_go_RDMA/client/src/network/tcp.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/hjkim/Lets_go_RDMA/client/build/CMakeFiles/cmake.verify_globs")
endif()

# SRC_FILES at src/tools/CMakeLists.txt:1 (file)
file(GLOB_RECURSE NEW_GLOB LIST_DIRECTORIES false "/home/hjkim/Lets_go_RDMA/client/src/tools/*.cpp")
set(OLD_GLOB
  "/home/hjkim/Lets_go_RDMA/client/src/tools/Parser.cpp"
  "/home/hjkim/Lets_go_RDMA/client/src/tools/ThreadPool.cpp"
  )
if(NOT "${NEW_GLOB}" STREQUAL "${OLD_GLOB}")
  message("-- GLOB mismatch!")
  file(TOUCH_NOCREATE "/home/hjkim/Lets_go_RDMA/client/build/CMakeFiles/cmake.verify_globs")
endif()
