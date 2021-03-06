/// @file Utils.h
///
/// The utilities.
///
/// @par Full Description
/// The utilities used among vcdMaker applications.
///
/// @ingroup Utils
///
/// @par Copyright (c) 2016 vcdMaker team
///
/// Permission is hereby granted, free of charge, to any person obtaining a
/// copy of this software and associated documentation files (the "Software"),
/// to deal in the Software without restriction, including without limitation
/// the rights to use, copy, modify, merge, publish, distribute, sublicense,
/// and/or sell copies of the Software, and to permit persons to whom the
/// Software is furnished to do so, subject to the following conditions:
///
/// The above copyright notice and this permission notice shall be included
/// in all copies or substantial portions of the Software.
///
/// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
/// OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
/// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
/// THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
/// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
/// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
/// IN THE SOFTWARE.

#pragma once

#include <vector>
#include <string>

/// @defgroup Utils Utils
///
/// @brief Utilities.
///
/// @par Full Description
/// The utilities used among vcdMaker applications.

/// Utilities namespace.
namespace UTILS {

    /// Returns a vector of separated strings.
    ///
    /// @param inString The string to be split.
    /// @param delimiter The delimiter.
    std::vector<std::string> Split(const std::string &inString,
                                   const char delimiter);

    /// Checks if given time unit is supported.
    bool IsTimeUnitValid(const std::string &unit);

    /// Returns given time unit index in supported units list.
    size_t GetTimeUnitIndex(const std::string &unit);

}
