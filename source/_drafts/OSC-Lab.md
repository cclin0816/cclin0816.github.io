---
title: OSC Lab
author: Me
category: OSC
tags: [osc, c++, bare metal, os kernel, rpi]
index_img: /img/miniQ-2.webp
---

lab of [NYCU operating system capstone](https://oscapstone.github.io/), source code at [osc2022](https://github.com/cclin0816/osc2022)

<!-- more -->

## Tool Chains

### Build System

`GNU Make`, chose it because I'm too lazy too use new build system

{%note info%}
It's hard to resolve dependency well using make, so It will recompile some unnecessary files, 
but it's a small project, won't hurt that much
{%endnote%}

### Language

`C++`, see [Bare Metal C++](/2022/02/11/Bare-Metal-Cpp/)

### Compiler

`clang++`, with `-target aarch64-none-linux-gnu`, using `linux-gnu` instead of `none-elf` due to usage of libc++ headers

### Linker

`ld.lld`, provide by llvm with gnu interface

### QEMU

`qemu-system-aarch64`

### Debugger

`gdb-multiarch` with [gef](https://gef.readthedocs.io/en/master/)

### Serial Terminal

python - [pwntools](https://docs.pwntools.com/en/stable/)
this resolves the need of write back in uart, and easier to modify kernel image, ex. compress, send by section, ...

### Other

llvm based tools

## Bootloader

* Stage 1 & Stage 2 & Stage 3

  > proprietary bootloader from Broadcom, runs on VPU and initializes most of the system, for detail see [boot-flow](https://www.raspberrypi.com/documentation/computers/raspberry-pi.html#raspberry-pi-4-boot-flow) of rpi document  
  > modify the `config.txt` to configure the system initialization, and `cmdline.txt` to configure argument passed to kernel

* Stage 4

  > usually the kernel image is loaded here, but a bootlloader that loads kernel from uart is easier for debugging

### Start

just relocate itself then zero bss, and jump to `main`  

{%note warning%}
if the original load address is unknown and relocate to absolute address, 
requires indirect jump to `main`
{%endnote%}

{%note warning%}
if the relocate address is unknown, and there is use of vtable, requires vtable fix (using PIE is fine mostly, but vtable will always be absolute address, and reloc information is removed when `objcopy`, so fixing vtable is neccecary)
{%endnote%}

<!-- ### Uart

it's possible to initialize uart from `config.txt`, but still unable to use if mmio layout is unknown, so parsing `dtb` is required

###  -->