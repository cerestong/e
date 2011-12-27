// Copyright (c) 2011, Robert Escriva
// All rights reserved.
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
//     * Redistributions of source code must retain the above copyright notice,
//       this list of conditions and the following disclaimer.
//     * Redistributions in binary form must reproduce the above copyright
//       notice, this list of conditions and the following disclaimer in the
//       documentation and/or other materials provided with the distribution.
//     * Neither the name of this project nor the names of its contributors may
//       be used to endorse or promote products derived from this software
//       without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#ifndef e_slice_h_
#define e_slice_h_

// C
#include <cstring>

namespace e
{

// Refer to another piece of memory.  The memory is assumed to be managed
// somewhere else, and must outlive the use of all slices using it.
class slice
{
    public:
        slice();
        slice(const uint8_t* data, size_t sz);
        template <typename T> slice(const T* data, size_t sz);
        slice(const slice& other);
        ~slice() throw ();

    public:
        const uint8_t* data() const;
        size_t size() const;

    public:
        void reset();
        void reset(const uint8_t* data, size_t sz);

    public:
        slice& operator = (const slice& rhs);
        bool operator < (const slice& rhs) const { return compare(rhs) < 0; }
        bool operator <= (const slice& rhs) const { return compare(rhs) <= 0; }
        bool operator == (const slice& rhs) const { return compare(rhs) == 0; }
        bool operator != (const slice& rhs) const { return compare(rhs) != 0; }
        bool operator >= (const slice& rhs) const { return compare(rhs) >= 0; }
        bool operator > (const slice& rhs) const { return compare(rhs) > 0; }

    private:
        int compare(const slice& rhs) const;

    private:
        const uint8_t* m_data;
        size_t m_sz;
};

inline
slice :: slice()
    : m_data(NULL)
    , m_sz(0)
{
}

inline
slice :: slice(const uint8_t* data, size_t sz)
    : m_data(data)
    , m_sz(sz)
{
}

// sz is the number of bytes, not the number of pointed-to elements.
template <typename T>
inline
slice :: slice(const T* data, size_t sz)
    : m_data(reinterpret_cast<const uint8_t*>(data))
    , m_sz(sz)
{
}

inline
slice :: slice(const slice& other)
    : m_data(other.m_data)
    , m_sz(other.m_sz)
{
}

inline
slice :: ~slice() throw ()
{
}

inline const uint8_t*
slice :: data() const
{
    return m_data;
}

inline size_t
slice :: size() const
{
    return m_sz;
}

inline void
slice :: reset()
{
    m_data = NULL;
    m_sz = 0;
}

inline void
slice :: reset(const uint8_t* data, size_t sz)
{
    m_data = data;
    m_sz = sz;
}

inline slice&
slice :: operator = (const slice& rhs)
{
    // We do not need to check for self-assignment.
    m_data = rhs.m_data;
    m_sz = rhs.m_sz;
}

inline int
slice :: compare(const slice& rhs) const
{
    if (m_sz < rhs.m_sz)
    {
        return -1;
    }
    else if (m_sz > rhs.m_sz)
    {
        return 1;
    }
    else
    {
        return memcmp(m_data, rhs.m_data, m_sz);
    }
}

} // namespace e

#endif // e_slice_h_
