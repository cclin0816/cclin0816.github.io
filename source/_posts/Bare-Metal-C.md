---
title: Bare Metal C++
category: C++
tags:
  - c++
  - clang
  - gcc
  - bare metal
author: Me
index_img: /img/miniQ-2.webp
date: 2022-02-11 10:17:05
---


things about using c++ on bare metal machines

<!-- more -->

## Intro

C++ has a lot of abstractions and containers, so normally it requires standard library support, but standard library might cause large, uncontrollable, non-deterministic binary generation.

External static library isn't feasible on bare metal, since libraries are packed. Unless you cherry pick the library source code and recompile, so symbol links to `libc.a`, `libc++.a`, `libstdc++`,... is no go.

Header only library is likely to create symbol linking to static library, but some header will not, so it's possible to use some [library](#Standard-Library).

## C++

{%note info%}
add `-ffreestanding` when compiling
it sets `__STDC_HOST__` to 0
{%endnote%}

### Startup

#### Stack Pointer

stack pointer needs to be set

#### BSS

zeroing bss section is required, typically uses `__bss_start` and `__bss_end` emmit by linker script to know the span of `.bss` section

#### Global Variable Constructor

non-trivially constructable global variable requires call to constructor at startup, typically uses `__init_array_start` and `__init_array_end` to know the span of `.init_array`
{%note warning%}
initialize order is non-deterministic, and non-trivially constructable global variable is weird and should be avoid  
{%endnote%}

#### Main Funtion

branch to main fuction

### Runtime

#### Dynamic Memory

[new](https://en.cppreference.com/w/cpp/memory/new/operator_new) and [delete](https://en.cppreference.com/w/cpp/memory/new/operator_delete) by standard, requires to emit exact symbol, and these symbol can be easily produced just by calling your memory allocation or deallocation function
{%note warning%}
some embedded or realtime application can't afford using dynamic memory
{%endnote%}

#### Exceptions

{%note warning%}
using exceptions produces a bunch of symbols
exceptions are normally disabled since it either needs OS support or having huge binary, and throwing exception is costly
{%endnote%}

{%note info%}
to disable exception use `-fno-exceptions` `-fno-unwind-tables` when compiling
throw will be alias to abort
{%endnote%}

#### RTTI

{%note info%}
to disable rtti use `-fno-rtti` when compiling
careful when casting
{%endnote%}

#### Static Variable

c++ defaults thread safe static variable initialization, which requires `__cxa_guard_acuire/release` symbol

{%note info%}
to disable thread safe static variable initialization use `-fno-threadsafe-statics` when compiling
{%endnote%}

#### Pure Virtual Function

pure virtual functions of class requires `__cxa_pure_virtual` symbol
just implement it as infinite loop or abort

### Exit

#### Global and Static Variable Destructor

non-trivially destructable global and static variable requires call to destructor at exit, requires `__atexit` symbol

{%note warning%}
using this is also weird and should be avoid  
{%endnote%}

## Standard Library

[Freestanding Headers](https://en.cppreference.com/w/cpp/freestanding)

### Safe

won't produce extern symbols, at least as far as I know

* cstddef
* limits
* climits
* cfloat
* version
* cstdint
* type_traits
* concepts
* typeinfo
* source_location
* initializer_list
* bit
* cstdarg

### Mostly Safe

might need some easy resolvable symbols `ex. operator new[]`
some won't work `ex. atomic - wait`

* compare
* atomic
* coroutine
* new
* exception

### Some Safe

only specified function works

* cstdlib

### Others

thanks to constexpr and template function, constexpr and template function is defined in header for compile time support, so using it is like cherry picking the library, is less likely to produce extern symbols. Check the compiled output to determine whether it is usable.
`ex. algorithm - sort for int` - good, only produce memove symbol

{%note warning%}
standard library might cause unexpected behaivior when used in bare metal
ex. it's throwable, exceptions are turned off, and has a abort symbol
use it only if you know what it's doing, otherwise write your own
{%endnote%}

{%note info%}
containers are like functions, most of it actually works fine
{%endnote%}

{%note warning%}
using template functions and containers can cause bloated binary
ex. array\<int \*\> and array\<unsigned \*\> might produce exact same code
for resource intensive system, use it carefully
{%endnote%}


## Reference

[Practical Guide to Bare Metal C++](https://arobenko.github.io/bare_metal_cpp/)