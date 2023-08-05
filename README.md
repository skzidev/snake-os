# Snake-OS

Inspired by Tetris-OS by JDH, (R.I.P), This is snake; but as an OS!

### Progress So far

- [x] Bootloader in 32-bit protected mode
- [x] C in the binary
- [x] C running in the OS
- [x] Graphics driver running
- [ ] Keyboard Driver working (PS/2)
- [ ] Create a working 8x8 pixel font.
- [ ] Actual Game/Engine code running

I need to finish the keyboard driver, but before that I need to get GDB working.

Currently, GDB is giving me memory addresses, and breakpoints won't work, So It's basically useless.

I need to get my compiler information loaded into it.

I'm currently running in QEMU. We'll see if I can get this running on the real metal.
(Probably Not).

### Error Codes

There are a couple error messages that may show if the code fails to properly boot or play.
(Similar to below)

The first 2 take place when the OS is in its bootloader stage.
All other error codes added will be in the kernel stage.

```
Err {number}
```


1. Failed to load kernel into memory. Most likely a compilation (or flashing if on real hardware) issue
2. Drive in an unreadable status (see [Disk Status](https://stanislavs.org/helppc/int_13-1.html))
	
### Building

###### Required software

- Qemu x86 emulator
- GCC and LD
- NASM

###### Building the code

Make 2 folders, `bin` and `obj`

On systems with BASH, use the build script provided in the repo.

`./build.sh`

It should build to a .bin file and load up QEMU.
