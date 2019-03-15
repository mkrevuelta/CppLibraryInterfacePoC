/*
    Foo/NumbersMsg.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_NUMBERSMSG_H__
#define __FOO_NUMBERSMSG_H__

#include "ApiMacros.h"
#include "PImplMacros.h"
#include "Span.h"

namespace foo
{

class FOO_API NumbersMsg
{
    FOO_DECLARE_PIMPL (NumbersMsg)

public:

    Span<double> get ();
    ConstSpan<double> get () const;
    void set (ConstSpan<double>);
    void append (double number);
    void clear ();
};

FOO_INLINE_SYMMETRIC_SWAP (NumbersMsg)

} // namespace foo

#endif // __FOO_NUMBERSMSG_H__

