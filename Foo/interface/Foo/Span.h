/*
    Foo/Span.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_SPAN_H__
#define __FOO_SPAN_H__

#include "ApiMacros.h"

#include <cstddef>

namespace foo
{

template <typename T>
class Span
{
private:

    T * first;
    T * afterLast;

    Span<T> & operator= (const Span<T> &) { throw 0; } // disable

public:

    Span ()
        :
        first(nullptr),
        afterLast(nullptr)
    {}

    Span (T * from, T * afterTo)
        :
        first(from),
        afterLast(afterTo)
    {}

    template <class C>
    explicit Span (C & c)
        :
        first(c.data()),
        afterLast(first+c.size())
    {}

    typedef T * iterator;
    typedef const T * const_iterator;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    const T * data () const { return first; }
          T * data ()       { return first; }

    std::ptrdiff_t ssize () const
    {
        return afterLast - first;
    }

    std::size_t size () const
    {
        return static_cast<std::size_t> (ssize ());
    }

    const_iterator cbegin () const { return first; }
    const_iterator  begin () const { return first; }
          iterator  begin ()       { return first; }
    const_iterator cend   () const { return afterLast; }
    const_iterator  end   () const { return afterLast; }
          iterator  end   ()       { return afterLast; }

    const T & operator[] (std::size_t pos) const { return first[pos]; }
          T & operator[] (std::size_t pos)       { return first[pos]; }
};

template <typename T>
class ConstSpan
{
private:

    const T * first;
    const T * afterLast;

    ConstSpan<T> & operator= (const ConstSpan<T> &) { throw 0; } // disable

public:

    ConstSpan ()
        :
        first(nullptr),
        afterLast(nullptr)
    {}

    ConstSpan (const T * from, const T * afterTo)
        :
        first(from),
        afterLast(afterTo)
    {}

    template <class C>
    explicit ConstSpan (const C & c)
        :
        first(c.data()),
        afterLast(first+c.size())
    {}

    typedef const T * iterator;
    typedef const T * const_iterator;
    typedef T value_type;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

    const T * data () const { return first; }

    std::size_t size () const
    {
        return static_cast<std::size_t> (afterLast - first);
    }

    const_iterator cbegin () const { return first; }
    const_iterator  begin () const { return first; }
    const_iterator cend   () const { return afterLast; }
    const_iterator  end   () const { return afterLast; }

    const T & operator[] (std::size_t pos) const { return first[pos]; }
};

} // namespace foo

#endif // __FOO_SPAN_H__

