#pragma once

#include <iostream>

#if defined(BUILD_STATIC)  // Если собираем статическую библиотеку
#  define LIBRARY_API
#  define LIBRARY_LOCAL
#else
#  if defined(_MSC_VER) || defined(WIN32) || defined(_WIN32) || defined(__NT__)
#    ifdef LIBRARY_EXPORTS
#      define LIBRARY_API __declspec(dllexport)
#    else
#      define LIBRARY_API __declspec(dllimport)
#    endif
#    define LIBRARY_LOCAL
#  else
#    define LIBRARY_API __attribute__((visibility("default")))
#    define LIBRARY_LOCAL __attribute__((visibility("hidden")))
#  endif
#endif

LIBRARY_API void MyTestFunction();