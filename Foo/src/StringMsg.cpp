/*
    Foo/StringMsg.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include <Foo/StringMsg.h>

#include <string>

namespace foo
{

struct StringMsg::Impl
{
    std::string msg;
};

FOO_IMPLEMENT_PIMPL (StringMsg)

const char * StringMsg::get () const
{
    return pImpl ? pImpl->msg.c_str() : "";
}

void StringMsg::set (const char * msg)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->msg = msg;
}

void StringMsg::append (const char * msg)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->msg += msg;
}

void StringMsg::clear ()
{
    if (pImpl)
        pImpl->msg.clear ();
}

} // namespace foo

