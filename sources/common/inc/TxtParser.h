/// @file TxtParser.h
///
/// The text log parser.
///
/// @par Full Description
/// The text log parser. It expects the basic vcdMaker log syntax.
///
/// @ingroup Parser
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

#include "LogParser.h"
#include "LineCounter.h"

namespace PARSER
{
    /// The text log parser class.
    class TxtParser : public LogParser
    {
        public:

            /// The text log parser constructor.
            ///
            /// This constructor is used by the vcdMaker app.
            /// It opens the input log file, sets the timebase and the verbose mode.
            ///
            /// @param filename The name of the log file to be open.
            /// @param timeBase The time base used in the log.
            /// @param sourceRegistry Signal sources registry.
            /// @param lineCounter The name of the line counting signal
            ///        or empty if not used.
            /// @param verboseMode Value 'true' enables the verbose mode.
            TxtParser(const std::string &filename,
                      const std::string &timeBase,
                      SIGNAL::SourceRegistry &sourceRegistry,
                      const std::string &lineCounter,
                      bool verboseMode);

            /// The destructor.
            ~TxtParser();

        private:

            /// Parses the input file.
            void Parse();

            /// Line counter suffix for name in source registry.
            static const std::string LINE_COUNTER_SUFFIX;

            /// The number of valid lines.
            uint64_t m_ValidLines;

            /// The number of invalid lines.
            uint64_t m_InvalidLines;

            /// The signal source handle.
            SIGNAL::SourceRegistry::HandleT m_SourceHandle;

            /// The line counter.
            LineCounter m_LineCounter;

            /// The line counter mode.
            bool m_LineCounterEnabled;

            /// The line counter signal source handle.
            SIGNAL::SourceRegistry::HandleT m_LineCounterSourceHandle;
    };

}
