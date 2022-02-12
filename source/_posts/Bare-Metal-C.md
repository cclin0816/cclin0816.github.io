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


things about using c++ in bare metal situations

<!-- more -->

## Intro

C++ has a lot of abstractions and containers, so normally it requires standard library support, but standard library might cause large, uncontrollable, non-deterministic binary generation.

External static library isn't feasible on bare metal, since libraries are packed, unless you cherry pick the library source code and recompile it, otherwise symbols linked to `libc.a`, `libc++.a`, `libstdc++.a`,... is no go.

Library headers are likely to create symbols linked to static library, but some header won't, so it's possible to use some (part of) [library](#Standard-Library).

## C++

{%note info%}
add `-ffreestanding` when compiling, it means no OS support and sets `__STDC_HOSTED__` to 0
{%endnote%}
{%note info%}
add `-nostdlib` to disable linkage of static library
{%endnote%}

{%note success%}
see code output on [compiler explorer](https://godbolt.org/)
{%endnote%}

### Startup

#### Stack Pointer

stack pointer needs to be set

#### BSS

zeroing bss section is required, typically uses `__bss_start` and `__bss_end` in linker script to know the span of `.bss` section

```ld
.bss : {
  __bss_start = .;
  *(.bss .bss.*)
  *(COMMON)
  . = ALIGN(8);
  __bss_end = .;
}
```

#### Global Variable Constructor

non-trivially constructable global variable requires call to constructor at startup, typically uses `__init_array_start` and `__init_array_end` to know the span of `.init_array`

```cpp
extern void ctor();
class ntctor {
public:
  ntctor() {
    ctor();
  }
};
ntctor ntctor_gv;
```

```x86asm
_GLOBAL__sub_I_example.cpp: 
  b       ctor()
```

.init_array section is an array of pointers to function that needs to be invoke at startup
ex. _GLOBAL__sub_I_example.cpp

```symbol
[Nr]  Name         Type        Address           Offset    Size              EntSize           Flags  Link  Info  Align
[ 6]  .init_array  INIT_ARRAY  0000000000000000  00000048  0000000000000008  0000000000000000  WA     0     0     8
```

```ld
.rodata : {
  *(.rodata .rodata.*)
  __init_array_start = .;
  *(.init_array)
  __init_array_end = .;
}
```

{%note warning%}
initialize order is non-deterministicand bug prone, use only if you need it
{%endnote%}

#### Main Funtion

branch to main fuction

### Runtime

#### Dynamic Memory

[new](https://en.cppreference.com/w/cpp/memory/new/operator_new) and [delete](https://en.cppreference.com/w/cpp/memory/new/operator_delete) by standard, requires to emit exact symbol, and these symbol can be easily produced just by calling your memory allocation or deallocation function

```cpp
char *alloc() {
  return new char[8];
}
```

```x86asm
alloc():
  mov edi, 8
  jmp operator new[](unsigned long)                           
```

```cpp
void* operator new[](size_t size) {
    return my_malloc(size);
}
...
```

{%note warning%}
some embedded or realtime application can't afford using dynamic memory
{%endnote%}

#### Exceptions

{%note warning%}
using exceptions produces a bunch of symbols
exceptions are normally disabled since it either needs OS support or having huge binary, and throwing exception is costly, because of allocation, unwinding, and class inherit tree traverse
{%endnote%}

```cpp
void func_throw() {
  throw std::exception();
}
extern void func_fail();
void func_try() {
  try {
    func_throw();
  } catch (...) {
    func_fail();
  }
}
```

using exceptions

```x86asm
func_throw(): 
  push    rax
  mov     edi, 8
  call    __cxa_allocate_exception
  mov     qword ptr [rax], offset vtable for std::exception+16
  mov     esi, offset typeinfo for std::exception
  mov     edx, offset std::exception::~exception() [complete object dtor]
  mov     rdi, rax
  call    __cxa_throw
...
```

can't throw and catch if exceptions disabled
but still able to use throwable library

```cpp
void func_throw(std::vector<int> &v) {
    v.push_back(1);
}
```

```x86asm
...
.LBB0_12:
  mov     edi, offset .L.str
  call    std::__throw_length_error(char const*)
.L.str:
  .asciz  "vector::_M_realloc_insert"
```

{%note warning%}
resolve symbol with abort, since unrecoverable error (ex. OOM error) should cause abort, beware if the function is easily throwable (recoverable error)
{%endnote%}

```cpp
[[noreturn]] void std::__throw_length_error(char const*) {
  abort();
}
```

{%note info%}
to disable exception use `-fno-exceptions` `-fno-unwind-tables` when compiling
{%endnote%}

#### RTTI

{%note warning%}
runtime type information is used by dynamic_cast, which is easily throwable, unless exceptions are present, there's no reason to use dynamic cast, rtti creates typeinfo, which is used for inherit tree traverse when dynamic_cast, which causes huge code footprint and unbounded run time
{%endnote%}

{%note info%}
to disable rtti use `-fno-rtti` when compiling
{%endnote%}

#### Static Variable

c++ defaults thread safe static variable initialization, which requires `__cxa_guard_acuire/release` symbol

```cpp
extern int init();
void inc() {
  static int count = init();
  count++;
}
```

```x86asm
...
.LBB0_1:
  mov     edi, offset guard variable for inc()::count
  call    __cxa_guard_acquire
...
  mov     edi, offset guard variable for inc()::count
  call    __cxa_guard_release
...
```

{%note info%}
use atomic to implement guard function
{%endnote%}

{%note info%}
to disable thread safe static variable initialization use `-fno-threadsafe-statics` when compiling
{%endnote%}

#### Abstract Class

abstract class might need `__cxa_pure_virtual` symbol
just implement as abort, newer compiler forbids such abuse, and is unlikely to emit this symbol

### Exit

#### Global and Static Variable Destructor

non-trivially destructable global and static variable requires call to destructor at exit, since destruct order requires to be the reverse order of constuct order, it chains exit function dynamically
for global exit function chains at startup, which uses [Global Variable Constructor](#Global-Variable-Constructor)
for static exit function chains at initialize

```cpp
extern void dtor();
class ntdtor {
public:
  ~ntdtor() {
    ntdtor();
  }
};
ntdtor ntdtor_gv;
```

```x86asm
_GLOBAL__sub_I_example.cpp: 
  mov     edi, offset ntdtor::~ntdtor() [base object destructor]
  mov     esi, offset ntdtor_gv
  mov     edx, offset __dso_handle
  jmp     __cxa_atexit                    # TAILCALL
```

{%note info%}
`__cxa_atexit(void *obj, void (*destructor)(void *), void *ptr__dso_handle)`;
which stores `obj`, and `destructo`r to `*ptr__dso_hande`, than modify `ptr__dso_handle` to handle next call to `__cxa_exit`
requires large enough space of `__dso_handle` to store destruct pairs
{%endnote%}

{%note warning%}
use it only if needed, since bare metal rarely returns from main
{%endnote%}

{%note info%}
to suppress symbols just create empty function of `__cxa_atexit`, and a global pointer `__dso_handle` of nullptr
{%endnote%}

## Standard Library

[Freestanding Implementation](https://en.cppreference.com/w/cpp/freestanding)

### Definitions

won't produce extern symbols

* cstddef
* limits ?
* climits ?
* cfloat ?
* version ?
* cstdint
* type_traits
* concepts
* typeinfo ?
* source_location ?

### Freestanding

tools of language, which doesn't need OS support, but still might need some symbol resolved, ex. `memcpy`

* initializer_list ?
* bit
* cstdarg
* compare ?
* atomic (some new feature is system depended, ex. wait)
* new

### System Depended ?

some part of it will work, depends on implementation, others requires some symbols to be resolved ex. `Unwind`

* coroutine
* exception
* cstdlib

### Others

thanks to constexpr and template function, constexpr and template function is defined in header for compile time support (also increase compile time significantly), so using it is like cherry picking the library, and is less likely to produce external symbols. Check the compiled output to determine whether it is usable, for example:

```cpp
void sort_int(int* ptr, int len) {
  std::sort(ptr, ptr + len);
}
```

`sort_int` create symbol of `std::__introsort_loop` and `std::__final_insertion_sort`, but the code is produced by template function, `introsort` also creates symbol of `__make_heap`, and `final` creates symbol to `memmove`, which is the only external symbol we need to provide

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
for resource intensive system, use it carefully
{%endnote%}

```cpp
void v_1(std::vector<int *> &v) {
    v.push_back(nullptr);
}

void v_2(std::vector<unsigned *> &v) {
    v.push_back(nullptr);
}
```

`v_1` and `v_2` produces same exact code, but not squashed

## Reference

[Practical Guide to Bare Metal C++](https://arobenko.github.io/bare_metal_cpp/)
