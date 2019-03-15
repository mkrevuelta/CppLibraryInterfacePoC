/*
    Foo/ApiMacros.h

    Copyright (c) 2019, Martin Knoblauch Revuelta
    See accompanying LICENSE

    https://github.com/mkrevuelta/CppLibraryInterfacePoC
*/

#ifndef __FOO_API_MACROS_H__
#define __FOO_API_MACROS_H__

#if defined (_WIN32)
  #if defined (COMPILING_FOO)
    #define FOO_API __declspec(dllexport)
    #define EXTERN_TO_ALL_BUT_FOO
  #else
    #define FOO_API __declspec(dllimport)
    #define EXTERN_TO_ALL_BUT_FOO extern
  #endif
#elif defined (__GNUC__)
  #if __GNUC__ >= 4
    #define FOO_API __attribute__ ((visibility ("default")))
  #else
    #define FOO_API
  #endif
  #define EXTERN_TO_ALL_BUT_FOO extern
#else
  #define FOO_API
  #define EXTERN_TO_ALL_BUT_FOO extern
  #pragma error "Missing specification of import/export method"
#endif

#define FOO_NOEXCEPT throw()

#endif // __FOO_API_MACROS_H__

