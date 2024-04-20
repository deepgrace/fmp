#
# Copyright (c) 2024-present DeepGrace (complex dot invoke at gmail dot com)
#
# Distributed under the Boost Software License, Version 1.0.
# (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
# Official repository: https://github.com/deepgrace/fmp
#

set(CMAKE_VERBOSE_MAKEFILE ON)
set(CMAKE_BUILD_TYPE Release)
SET(CMAKE_CXX_FLAGS "-m64 -std=c++26 -s -Wall -O3")

include(GNUInstallDirs)

include_directories(${PROJECT_SOURCE_DIR}/include)

set(FUPLE fuple)
set(LIST lists)
set(REFLECT reflect)
set(FMP fmp)
set(VISITOR visitor)
set(MEMBER_INFO member_info)
set(INVOCABLE_NAME invocable_name)

add_executable(${FUPLE} fuple.cpp)
add_executable(${LIST} lists.cpp)
add_executable(${REFLECT} reflect.cpp)
add_executable(${FMP} fmp.cpp)
add_executable(${VISITOR} visitor.cpp)
add_executable(${MEMBER_INFO} member_info.cpp)
add_executable(${INVOCABLE_NAME} invocable_name.cpp)

install(TARGETS ${FUPLE} ${LIST} ${REFLECT} ${FMP} ${VISITOR} ${MEMBER_INFO} ${INVOCABLE_NAME} DESTINATION ${PROJECT_SOURCE_DIR}/bin)
