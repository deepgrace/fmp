//
// Copyright (c) 2024-present DeepGrace (complex dot invoke at gmail dot com)
//
// Distributed under the Boost Software License, Version 1.0.
// (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// Official repository: https://github.com/deepgrace/fmp
//

#ifndef FMP_VERSION_HPP
#define FMP_VERSION_HPP

#define FMP_STRINGIZE(T) #T

/*
 *   FMP_VERSION_NUMBER
 *
 *   Identifies the API version of fmp.
 *   This is a simple integer that is incremented by one every
 *   time a set of code changes is merged to the master branch.
 */

#define FMP_VERSION_NUMBER 4
#define FMP_VERSION_STRING "fmp/" FMP_STRINGIZE(FMP_VERSION_NUMBER)

#endif
