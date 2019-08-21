#ifndef DEFINES_H
#define DEFINES_H

#ifdef __EMSCRIPTEN__
 #include <emscripten.h>
#else
 #define EMSCRIPTEN_KEEPALIVE
#endif

#define GETMASK(index, size) (((1U << (size)) - 1) << (index))
#define READFROM(data, index, size) (((data) & GETMASK((index), (size))) >> (index))
#define WRITE(data, index, size, value) ((data) = ((data) & (~GETMASK((index), (size)))) | ((uint32_t)(value) << (index)))

#define write8(data, index, value) WRITE(data, index, 8, value)
#define read8(data, index) READFROM(data, index, 8)

/* MSVC doesn't support __builtin_expect, stub it out */
#ifndef _MSC_VER
 #define unlikely(x) __builtin_expect((x), 0)
#else
 #define unlikely(x) (x)
#endif

#define likely(x) !unlikely(!(x))

#ifndef __has_builtin
 #define __has_builtin(x) 0
#endif

#endif
