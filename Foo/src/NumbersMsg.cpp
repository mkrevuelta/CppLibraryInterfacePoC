/*
    Foo/NumbersMsg.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include <Foo/NumbersMsg.h>

#include <vector>

namespace foo
{

struct NumbersMsg::Impl
{
    std::vector<double> nums;
};

FOO_IMPLEMENT_PIMPL (NumbersMsg)

Span<double> NumbersMsg::get ()
{
    return pImpl ? Span<double>(pImpl->nums)
                 : Span<double>();
}

ConstSpan<double> NumbersMsg::get () const
{
    return pImpl ? ConstSpan<double>(pImpl->nums)
                 : ConstSpan<double>();
}

void NumbersMsg::set (ConstSpan<double> nums)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->nums = std::vector<double> (nums.begin(), nums.end());
}

void NumbersMsg::append (double number)
{
    if (!pImpl)
        pImpl = UniquePtr<Impl>();

    pImpl->nums.push_back (number);
}

void NumbersMsg::clear ()
{
    if (pImpl)
        pImpl->nums.clear ();
}

} // namespace foo

