r2-clippy

if you open r2 and type `????` you get a cute character
that looks like the following:

this is directly radare2's code, i would suggest looking at
the [source](https://github.com/radareorg/radare2/blob/6ef5e4460a7a0baf5f6a9abf8f1dc41e1550cee3/libr/core/cmd_help.c#L1226).

this repository is for *fun* purposes, because clippy is cute, and i need a cli friend.

---
 ╭──╮    ╭─────────────────────╮
 │ _│_   │                     │
 │ O O  <  What are you doing? │
 │  │╷   │                     │
 │  ││   ╰─────────────────────╯
 │ ─╯│
 ╰───╯
 ---

 i desperately need this as a cli tool.
 this repository takes the code required from [radare2](https://github.com/radareorg/radare2)
 to give the clippy character as a cli friend.

Usage

 --
 $ ./r2-clippy "message"
 --

Building

deps: automake, clang

-- 
$ make
---