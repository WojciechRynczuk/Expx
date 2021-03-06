/// @file Signal.h
///
/// The base VCD signal class.
///
/// @par Full Description
/// The base signal class contains the common signal properties and
/// methods.
///
/// @ingroup Signal
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

/// @defgroup Signal Signal
///
/// @brief The group defines different types of signals.
///
/// @par Full Description
/// The group consists of the base class defining the common behaviours as
/// well as of the inheriting signal classes specifying concrete signals.

#include <cstdint>
#include <string>
#include <vector>
#include <set>

#include "SourceRegistry.h"

namespace SIGNAL
{
    /// The base VCD signal class. The integer and real signal classes
    /// inherit from it.

    /// A base signal class.
    class Signal
    {
        public:
            /// A type for splited signal name fields.
            using SignalNameFieldsT = std::vector<std::string>;

            /// Signal name components delimeter.
            static const char SIGNAL_NAME_DELIM = '.';

            /// List of allowed time units.
            /// @note This can't be const because of TCLAP's stupidity -
            ///       TCLAP::ValuesConstraint constructor doesn't take its
            ///       argument using constant reference like it should.
            static std::vector<std::string> TIME_UNITS;

            /// The signal constructor.
            ///
            /// This constructor shall be used by the iheriting classes.
            /// It initializes the basic signal properties: the name, the size
            /// and the type.
            ///
            /// The name shall consist of any alphanumeric string in which the module's
            /// levels are separated with '.'.
            /// E.g. Module1.Level3.Variable6
            ///
            /// The size usually corresponds to any of the integral data type
            /// sizes: 8, 16, 32 or 64.
            ///
            /// The type string is used to produce the VCD header. It describes
            /// the type of the signal and shall equal to "wire" or "real".
            Signal(const std::string &name,
                   size_t size,
                   uint64_t timestamp,
                   const std::string &type,
                   SourceRegistry::HandleT sourceHandle) :
                m_Name(name),
                m_Type(type),
                m_Size(size),
                m_Timestamp(timestamp),
                m_SourceHandle(sourceHandle)
            {
            }

            /// The default constructor.
            ///
            /// It is needed by the multiset container within the VCD tracer module.
            Signal() = default;

            /// The signal cloning method.
            virtual Signal *Clone() const = 0;

            /// The destructor.
            virtual ~Signal() = 0;

            /// Returns the signal's name.
            ///
            /// The method is used while generating the header and the body
            /// of the VCD file.
            const std::string &GetName() const
            {
                return m_Name;
            }

            /// Sets the new signal's name.
            ///
            /// @param name The new signal's name.
            void SetName(const std::string &name)
            {
                m_Name = name;
            }

            /// Returns signal name splited into fields.
            ///
            /// The module, the sub-module and the signal name must
            /// be separated by a single '.'.
            SignalNameFieldsT GetNameFields() const;

            /// Returns the signal's size in bits.
            ///
            /// The method is used while generating the VCD header.
            size_t GetSize() const
            {
                return m_Size;
            }

            /// Returns the signal's timestamp in time units.
            ///
            /// The method is used while generating the body of the VCD file.
            uint64_t GetTimestamp() const
            {
                return m_Timestamp;
            }

            /// Sets the timestamp.
            ///
            /// @param timestamp The new timestamp value.
            void SetTimestamp(uint64_t timestamp)
            {
                m_Timestamp = timestamp;
            }

            /// Returns the signal's type.
            ///
            /// The method is used while generating the VCD header.
            const std::string &GetType() const
            {
                return m_Type;
            }

            /// Returns the source handle of the signal.
            SourceRegistry::HandleT GetSource() const
            {
                return m_SourceHandle;
            }

            /// Returns the signal's value as a string in the VCD format.
            ///
            /// The method is used while generating the body of the VCD file.
            virtual std::string Print() const = 0;

            /// Returns the signal's footprint as a string in the VCD format.
            ///
            /// The method is used while generating the header of the VCD file.
            virtual std::string Footprint() const = 0;

        protected:

            /// The signal comparison method.
            ///
            /// This comparison method is used by the overloaded comparison operator
            /// within the base class. It allows for comparing two signals of the same
            /// type. It is not important if it's greater or lesser. It is crucial to
            /// determine its change.
            virtual bool EqualTo(Signal const &other) const = 0;

            /// The signal's name.
            std::string m_Name {};

            /// The signal's type.
            const std::string m_Type {};

            /// The signal's size.
            const size_t m_Size = 0;

            /// The signal's timestamp.
            uint64_t m_Timestamp = 0;

            /// The signal's source.
            const SourceRegistry::HandleT m_SourceHandle =
                SIGNAL::SourceRegistry::BAD_HANDLE;

        private:

            /// The overloaded == operator.
            ///
            /// Checks if two signal values are equal. Virtual EqualTo is used.
            friend bool operator == (const Signal &lsignal, const Signal &rsignal)
            {
                return lsignal.EqualTo(rsignal);
            }

            /// The overloaded != operator.
            ///
            /// Checks if two signal values are not equal. Virtual EqualTo is used.
            friend bool operator != (const Signal &lsignal, const Signal &rsignal)
            {
                return !lsignal.EqualTo(rsignal);
            }

    };

    /// Comparator for multiset.
    class PtrTimestampLtComparator
    {
        public:
            /// Checks if one signal's timestamp is lower than other signal's timestamp.
            bool operator()(const Signal *lhs, const Signal *rhs)
            {
                return (lhs->GetTimestamp() < rhs->GetTimestamp());
            }
    };

    /// A type defining a container for pointers to Signal objects.
    using SignalCollectionT = std::multiset<const Signal *,
                                            PtrTimestampLtComparator>;

    /// Type used for unique signals map: name => signal pointer.
    using UniqueSignalsCollectionT = std::map<std::string, const Signal *>;

    inline Signal::~Signal() = default;

}
