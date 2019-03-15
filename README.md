# CppLibraryInterfacePoC

A *Proof-of-Concept* library with:
+ Mostly C++ interface (objects, move semantics)
+ Easy to write (real C++, **no** conversion to/from extern "C" functions)
+ Easy to use (objects are given away, managed by unique pointers)
+ Highly compatible across compiler versions from a given vendor (only requirement: C++11 or above)

This repository contains evolved versions of the examples I proposed in this presentation:

+ https://www.mkrevuelta.com/en/2019/03/06/lets-make-easy-to-use-libraries-using-stdcpp-2019/

## Foo library

The Foo library can receive or return the next data structures, or "messages":

+ StringMsg: a text string
+ NumbersMsg: an array of numbers
+ MultiMapMsg: a string-to-string multimap (this one will change a bit, so stay tuned!)

Each type of message is wrapped in a class. With respect to the usage of C++, the main restriction is that the methods provide access to the data through C types (i.e., const char \*). On the other hand, these classes are implemented with the PIMPL idiom and support move semantics. Thus, data can be passed with minimal overhead and, at the same time, the lifetime of objects is very easy to manage.

## Client program

Sample program that calls every Foo function.

Both Foo and Client can be compiled for MSVC 2012 and MSVC 2019. Note that each Client project is configured to copy and use the DLL compiled with **the other** version of the compiler!
