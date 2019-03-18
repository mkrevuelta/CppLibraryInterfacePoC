/*
    Foo/MultiMapMsg.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_MULTIMAPMSG_H__
#define __FOO_MULTIMAPMSG_H__

#include "ApiMacros.h"
#include "PImplMacros.h"
#include "Span.h"

namespace foo
{

class FOO_API MultiMapMsg
{
    FOO_DECLARE_PIMPL (MultiMapMsg)

public:

    class FOO_API Strings
    {
        FOO_DECLARE_PIMPL (Strings)
    public:
        void add (const char * s);
        ConstSpan<const char*> getAll () const;
    };

    void insert (const char * key, const char * value);
    Strings getKeys () const;
    Strings getValuesForKey (const char * key) const;
    void clear ();
};

FOO_INLINE_SYMMETRIC_SWAP (MultiMapMsg)
FOO_INLINE_SYMMETRIC_SWAP (MultiMapMsg::Strings)

} // namespace foo

#endif // __FOO_MULTIMAPMSG_H__

