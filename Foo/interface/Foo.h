/*
    Foo.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include "Foo/StringMsg.h"
#include "Foo/NumbersMsg.h"
#include "Foo/MultiMapMsg.h"

namespace foo
{

StringMsg FOO_API getHelloMessage ();

void FOO_API consumeMessage (StringMsg msg);

NumbersMsg FOO_API getSomeNumbers ();

void FOO_API consumeNumbers (NumbersMsg nums);

MultiMapMsg FOO_API getNamesMultimap ();

} // namespace foo


