#pragma once

#ifndef NDEBUG

#include <iostream>

#define JGASSERT(condition, message) \
    do { if (!(condition)) { \
        std::cerr << "assertion '" #condition "' failed, " \
                  << "in file " << __FILE__ << ", line " << __LINE__ \
                  << ": " << message << std::endl; std::abort(); \
    } } while (false)

#else

#define JGASSERT(condition, message) do {} while (false)

#endif
