/*
    Foo/PImplMacros.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_PIMPLMACROS_H__
#define __FOO_PIMPLMACROS_H__

#include "ApiMacros.h"
#include "UniquePtr.h"

#define FOO_DECLARE_PIMPL(CLASS)                          \
                                                          \
private:                                                  \
                                                          \
    struct Impl;                                          \
    UniquePtr<Impl> pImpl;                                \
                                                          \
public:                                                   \
                                                          \
    CLASS () FOO_NOEXCEPT;                                \
    CLASS (CLASS &&) FOO_NOEXCEPT;                        \
    CLASS (const CLASS &);                                \
    ~CLASS () FOO_NOEXCEPT;                               \
    CLASS & operator= (CLASS &&) FOO_NOEXCEPT;            \
    CLASS & operator= (const CLASS &);                    \
    void swap (CLASS &) FOO_NOEXCEPT;

#define FOO_INLINE_SYMMETRIC_SWAP(CLASS)                  \
                                                          \
inline void swap (CLASS & a, CLASS & b) FOO_NOEXCEPT      \
{                                                         \
    a.swap (b);                                           \
}

#define FOO_IMPLEMENT_INNER_PIMPL(FULLNAME,CLASS)         \
                                                          \
FULLNAME::CLASS () FOO_NOEXCEPT                           \
{                                                         \
}                                                         \
                                                          \
FULLNAME::CLASS (FULLNAME && other) FOO_NOEXCEPT          \
    :                                                     \
    pImpl(std::move(other.pImpl))                         \
{                                                         \
}                                                         \
                                                          \
FULLNAME::CLASS (const FULLNAME & other)                  \
    :                                                     \
    pImpl(other.pImpl ? *other.pImpl.get()                \
                      : Impl())                           \
{                                                         \
}                                                         \
                                                          \
FULLNAME::~CLASS () FOO_NOEXCEPT                          \
{                                                         \
}                                                         \
                                                          \
FULLNAME & FULLNAME::operator= (                          \
                FULLNAME && other) FOO_NOEXCEPT           \
{                                                         \
    pImpl = std::move (other.pImpl);                      \
    return *this;                                         \
}                                                         \
                                                          \
FULLNAME & FULLNAME::operator= (                          \
                const FULLNAME & other)                   \
{                                                         \
    FULLNAME tmp(other);                                  \
    swap (tmp);                                           \
    return *this;                                         \
}                                                         \
                                                          \
void FULLNAME::swap (FULLNAME & other) FOO_NOEXCEPT       \
{                                                         \
    pImpl.swap (other.pImpl);                             \
}

#define FOO_IMPLEMENT_PIMPL(CLASS)                        \
        FOO_IMPLEMENT_INNER_PIMPL (CLASS, CLASS)

#endif // __FOO_PIMPLMACROS_H__

