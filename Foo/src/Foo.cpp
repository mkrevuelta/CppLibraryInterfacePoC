/*
    Foo.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include <Foo.h>
#include <iostream>

namespace foo
{

StringMsg FOO_API getHelloMessage ()
{
    StringMsg msg;
    msg.set ("Hello from Foo");
    return msg;
}

void FOO_API consumeMessage (StringMsg msg)
{
    std::cout << "foo::consumeMessage() received: "
              << msg.get () << std::endl;
}

NumbersMsg FOO_API getSomeNumbers ()
{
    NumbersMsg nums;
    nums.append (6);
    nums.append (7);
    nums.append (42);
    return nums;
}

void FOO_API consumeNumbers (NumbersMsg nums)
{
    std::cout << "foo::consumeNumbers() received:";

    for (auto n : nums.get())
        std:: cout << " " << n;

    std::cout << std::endl;
}

MultiMapMsg FOO_API getNamesMultimap ()
{
    MultiMapMsg names;

    names.add ("Disney", "Minnie");
    names.add ("Disney", "Pluto");

    names.add ("Marvel", "Thor");
    names.add ("Marvel", "Hulk");
    names.add ("Marvel", "Conan");

    return names;
}

} // namespace foo

