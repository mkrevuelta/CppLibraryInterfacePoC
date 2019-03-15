/*
    Foo/StringMsg.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_STRINGMSG_H__
#define __FOO_STRINGMSG_H__

#include "ApiMacros.h"
#include "PImplMacros.h"

namespace foo
{

class FOO_API StringMsg
{
    FOO_DECLARE_PIMPL (StringMsg)

public:

    const char * get () const;
    void set (const char * msg);
    void append (const char * msg);
    void clear ();
};

FOO_INLINE_SYMMETRIC_SWAP (StringMsg)

} // namespace foo

#endif // __FOO_STRINGMSG_H__

