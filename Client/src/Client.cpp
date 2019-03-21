/*
    Client.cpp

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#include <iostream>
#include <vector>
#include <Foo.h>

int main ()
{
    {
        auto msg = foo::getHelloMessage ();

        std::cout << "foo::getHelloMessage() returned: "
                  << msg.get () << std::endl;
    }

    {
        auto nums = foo::getSomeNumbers ();

        std::cout << "foo::getSomeNumbers() returned:";
        for (auto n : nums.get())
            std::cout << ' ' << n;
        std::cout << std::endl;
    }

    {
        foo::StringMsg otherMsg;
        otherMsg.set ("Hello from the client");

        foo::consumeMessage (std::move(otherMsg));
    }

    {
        foo::NumbersMsg otherNums;
        #if defined(_MSC_VER) && _MSC_VER < 1800
        std::vector<double> numsVector;
        numsVector.push_back (1);
        numsVector.push_back (2);
        numsVector.push_back (3);
        numsVector.push_back (14);
        otherNums.set (foo::ConstSpan<double>(numsVector));
        #else
        otherNums.set (foo::ConstSpan<double>(
                       std::vector<double>{ 1, 2, 3, 14 }));
        #endif

        foo::consumeNumbers (std::move(otherNums));
    }

    {
        auto names = foo::getNamesMultimap ();

        {
            std::cout << "foo::getNamesMultimap() returned:" << std::endl;
            std::vector<foo::MultiMapMsg::KeyValuePair> kvPairs(names.size());
            names.getAllKeyValuePairs (foo::Span<foo::MultiMapMsg::KeyValuePair>(kvPairs));
            for (auto pair : kvPairs)
                std::cout << '\t' << pair.key << " -> " << pair.value << std::endl;
        }
        {
            std::cout << "Again, but iterating keys one by one (less efficient):" << std::endl;
            std::vector<const char*> keys(names.numKeys());
            names.getKeys (foo::Span<const char*>(keys));
            for (const char * key : keys)
            {
                std::cout << '\t' << key << std::endl;

                std::vector<const char*> values(names.numValuesOfKey(key));
                names.getValuesOfKey (key, foo::Span<const char*>(values));
                for (const char * value : values)
                    std::cout << '\t' << '\t' << value << std::endl;
            }
        }
    }
}

