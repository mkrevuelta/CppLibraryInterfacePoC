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

FOO_IMPLEMENT_PIMPL (MultiMapMsg)

void MultiMapMsg::insert (const char * key, const char * value)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->multimap.emplace (key, value);
}

std::size_t MultiMapMsg::erase (const char * key, const char * value)
{
    if (!pImpl)
        return 0;

    std::size_t count = 0;
    auto range = pImpl->multimap.equal_range (key);

    for (auto it=range.first; it!=range.second; )
        if (it->second == value)
        {
            ++ count;
            it = pImpl->multimap.erase (it);
        }
        else
            ++ it;

    return count;
}

std::size_t MultiMapMsg::erase (const char * key)
{
    return pImpl ? pImpl->multimap.erase (key) : 0;
}

void MultiMapMsg::clear ()
{
    if (pImpl)
        pImpl->multimap.clear ();
}

std::size_t MultiMapMsg::size () const
{
    return pImpl ? pImpl->multimap.size () : 0;
}

std::size_t MultiMapMsg::getAllKeyValuePairs (Span<KeyValuePair> kvPairs) const
{
    if (!pImpl)
        return 0;

    auto destPos = kvPairs.begin ();

    for (auto & source : pImpl->multimap)
    {
        if (destPos == kvPairs.end())
            break;

        destPos->key = source.first.c_str ();
        destPos->value = source.second.c_str ();
        ++ destPos;
    }

    return static_cast<std::size_t> (destPos - kvPairs.begin());
}

std::size_t MultiMapMsg::numKeys () const
{
    if (!pImpl || pImpl->multimap.empty())
        return 0;

    auto it = pImpl->multimap.begin ();
    auto mapEnd = pImpl->multimap.end ();

    std::size_t count = 1;
    const char * prevKey = it->first.c_str ();

    for (++it; it!=mapEnd; ++it)
        if (it->first != prevKey)
        {
            ++ count;
            prevKey = it->first.c_str ();
        }

    return count;
}

std::size_t MultiMapMsg::getKeys (Span<const char*> keys) const
{
    if (!pImpl || pImpl->multimap.empty() || keys.size()==0)
        return 0;

    auto it = pImpl->multimap.begin ();
    auto mapEnd = pImpl->multimap.end ();

    auto destPos = keys.begin ();
    auto keysEnd = keys.end ();

    std::size_t count = 1;
    const char * prevKey = *destPos = it->first.c_str ();

    for (++it, ++destPos; it!=mapEnd && destPos!=keysEnd; ++it)
        if (it->first != prevKey)
        {
            ++ count;
            *destPos = prevKey = it->first.c_str ();
            ++ destPos;
        }

    return count;
}

std::size_t MultiMapMsg::numValuesOfKey (const char * key) const
{
    if (!pImpl)
        return 0;

    std::size_t count = 0;
    auto range = pImpl->multimap.equal_range (key);

    for (auto it=range.first; it!=range.second; ++it)
        ++ count;

    return count;
}

std::size_t MultiMapMsg::getValuesOfKey (const char * key, Span<const char*> values) const
{
    if (!pImpl)
        return 0;

    auto destPos = values.begin ();
    auto range = pImpl->multimap.equal_range (key);

    for (auto it=range.first; it!=range.second; ++it)
    {
        if (destPos == values.end())
            break;

        *destPos = it->second.c_str ();
        ++ destPos;
    }

    return static_cast<std::size_t> (destPos - values.begin());
}

const char * MultiMapMsg::getOneValueOfKey (const char * key) const
{
    if (!pImpl)
        return nullptr;

    auto it = pImpl->multimap.find (key);

    return it != pImpl->multimap.end () ? it->second.c_str ()
                                        : nullptr;
}

} // namespace foo

