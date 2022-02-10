---
title: Bare Metal C++
author: Me
category: C++
tags: [c++, clang, gcc, bare metal]
index_img: /img/miniQ-2.webp
---

things about using c++ on bare metal machines

<!-- more -->

## Intro

C++ has a lot of abstractions and containers, so normally it requires standard library support, but standard library might cause large, uncontrollable, non-deterministic binary it generates.

External static library isn't feasible on bare metal, since libraries are packed, unless you cherry pick the library source code and recompile, so symbol links to `libc.a`, `libc++.a`, `libstdc++`,... is no go.

Header only library is likely to create symbol linking to static library, but some header will not, so it's possible to use some [library](#Standard-Library).

## Language

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

when 
{%note danger%}
l
{%endnote%}

#### RTTI

#### Static Variable

## Standard Library

[Freestanding implementations](https://en.cppreference.com/w/cpp/freestanding)

* cstddef
* limits
* climits
* cfloat
* version
* cstdint
* cstdlib (partial)
* new
* typeinfo
* source_location
* exception
* initializer_list
* compare
* coroutine
* cstdarg
* concepts
* type_traits
* bit
* atomic
