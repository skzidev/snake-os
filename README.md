# Snake-OS

Inspired by Tetris-OS by JDH, (R.I.P), This is snake; but as an OS!

### Progress So far

- [x] Bootloader in 32-bit protected mode
- [x] C in the binary
- [x] C running in the OS
- [x] Graphics driver running
- [x] Keyboard Driver working (PS/2)
- [ ] Actual Game/Engine code running
- [ ] Game music and sound effects.

Sorry for not working yesterday. I was on a trip somewhere for the day. There is an update.

2 days ago, when I finished work for the day, I fixed the keyboard driver.
It was reading at the beginning, not every frame. Fixed now, made some changes.
They keyboard driver is done. The font is not entirely required right now, but will be later.

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
