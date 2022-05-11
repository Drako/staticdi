cmake_minimum_required(VERSION 3.16)
cmake_policy(VERSION 3.16)

if (NOT DEFINED PROJECT_NAME)
  set(SDI_IS_ROOT ON)
else ()
  set(SDI_IS_ROOT OFF)
endif ()

project(staticdi LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (SDI_IS_ROOT)
  enable_testing()

  include(FetchContent)
  FetchContent_Declare(
      trompeloeil
      GIT_REPOSITORY https://github.com/rollbear/trompeloeil
      GIT_TAG v42
  )
  FetchContent_Declare(
      Catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v2.13.8
  )
  FetchContent_MakeAvailable(trompeloeil Catch2)
endif ()

add_library(staticdi INTERFACE)
target_include_directories(staticdi INTERFACE "${CMAKE_CURRENT_LIST_DIR}/include")
target_sources(staticdi INTERFACE
    include/sdi.hxx
    include/sdi/component.hxx
    include/sdi/container.hxx
    include/sdi/tmp/generic.hxx
    include/sdi/tmp/type_list.hxx
    )

if (SDI_IS_ROOT)
  add_executable(staticdi_tests
      test/container.cxx
      test/tmp/generic.cxx
      test/tmp/type_list.cxx
      )
  target_link_libraries(staticdi_tests PRIVATE staticdi Catch2::Catch2)
  add_test(NAME staticdi_tests COMMAND staticdi_tests)

  add_subdirectory(example)
endif ()
