/*
    Foo/UniquePtr.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_UNIQUEPTR_H__
#define __FOO_UNIQUEPTR_H__

#include "ApiMacros.h"

namespace foo
{

template <typename T>
class FOO_API UniquePtr
{
private:

    T * ptr;

    UniquePtr<T> & operator= (const UniquePtr<T> &) { throw 0; } // disable
    UniquePtr (T * p) FOO_NOEXCEPT : ptr(p) {}

public:

    UniquePtr ();
    explicit UniquePtr (const T &);
    ~UniquePtr () FOO_NOEXCEPT;

    UniquePtr<T> & operator= (UniquePtr<T> && other) FOO_NOEXCEPT
    {
        UniquePtr<T> tmp (std::move(other));
        swap (tmp);
        return *this;
    }

    UniquePtr (UniquePtr<T> && other) FOO_NOEXCEPT
        : ptr(other.ptr)
    {
        other.ptr = nullptr;
    }

    void swap (UniquePtr<T> & other) FOO_NOEXCEPT
    {
        T * tmp = ptr;
        ptr = other.ptr;
        other.ptr = tmp;
    }

    bool    empty () const { return ptr == nullptr; }
    operator bool () const { return ptr != nullptr; }

    const T * get        () const { return  ptr; }
          T * get        ()       { return  ptr; }
    const T * operator-> () const { return  ptr; }
          T * operator-> ()       { return  ptr; }
    const T & operator*  () const { return *ptr; }
          T & operator*  ()       { return *ptr; }
};

template <typename T>
void swap (UniquePtr<T> & a, UniquePtr<T> & b)
{
    a.swap (b);
}

#ifdef COMPILING_FOO

template <typename T>
UniquePtr<T>::UniquePtr ()
    :
    ptr (new T)
{
}

template <typename T>
UniquePtr<T>::UniquePtr (const T & t)
    :
    ptr (new T(t))
{
}

template <typename T>
UniquePtr<T>::~UniquePtr () FOO_NOEXCEPT
{
    if (ptr)
        delete ptr;
}

#endif // COMPILING_FOO

} // namespace foo

#endif // __FOO_UNIQUEPTR_H__

