/*
    Foo/MultiMapMsg.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include <Foo/MultiMapMsg.h>

#include <string>
#include <map>
#include <vector>

namespace foo
{

struct MultiMapMsg::Impl
{
    std::multimap<std::string,std::string> multimap;
};

struct MultiMapMsg::Strings::Impl
{
    std::vector<const char*> strings;
};

FOO_IMPLEMENT_PIMPL (MultiMapMsg)

FOO_IMPLEMENT_INNER_PIMPL (MultiMapMsg::Strings, Strings)

void MultiMapMsg::Strings::add (const char * s)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->strings.push_back (s);
}

ConstSpan<const char*> MultiMapMsg::Strings::getAll () const
{
    return pImpl ? ConstSpan<const char*>(pImpl->strings)
                 : ConstSpan<const char*>();
}

void MultiMapMsg::add (const char * key, const char * value)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->multimap.emplace (std::pair<std::string,
                                       std::string>(key, value));
}

MultiMapMsg::Strings MultiMapMsg::getKeys () const
{
    Strings keys;

    if (pImpl && ! pImpl->multimap.empty())
    {
        auto it = pImpl->multimap.begin ();
        const char * prev = it->first.c_str ();
        keys.add (prev);

        for ( ; it!=pImpl->multimap.end(); ++it)
            if (it->first != prev)
            {
                prev = it->first.c_str ();
                keys.add (prev);
            }
    }

    return keys;
}

MultiMapMsg::Strings
    MultiMapMsg::getValuesForKey (const char * key) const
{
    Strings values;

    if (pImpl)
    {
        auto range = pImpl->multimap.equal_range (key);

        for (auto it=range.first; it!=range.second; ++it)
            values.add (it->second.c_str());
    }

    return values;
}

void MultiMapMsg::clear ()
{
    if (pImpl)
        pImpl->multimap.clear ();
}

} // namespace foo

