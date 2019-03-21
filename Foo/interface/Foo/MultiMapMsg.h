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

    struct KeyValuePair
    {
        const char * key;
        const char * value;
    };

    void insert (const char * key, const char * value);
    std::size_t erase (const char * key, const char * value);
    std::size_t erase (const char * key);
    void clear ();

    std::size_t size () const;
    std::size_t getAllKeyValuePairs (Span<KeyValuePair> kvPairs) const;

    std::size_t numKeys () const;
    std::size_t getKeys (Span<const char*> keys) const;

    std::size_t numValuesOfKey (const char * key) const;
    std::size_t getValuesOfKey (const char * key, Span<const char*> values) const;

    const char * getOneValueOfKey (const char * key) const;
};

FOO_INLINE_SYMMETRIC_SWAP (MultiMapMsg)

} // namespace foo

#endif // __FOO_MULTIMAPMSG_H__

