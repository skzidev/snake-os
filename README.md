<img src="SnakeOS.png">

Snake is fun enough to keep away boredom while still being very simple.

I thought I might as well challenge myself this summer and decided to write an OS.

### Progress So far

- [x] Bootloader in 32-bit protected mode
- [x] C in the binary
- [x] C running in the OS
- [x] Graphics driver running
- [ ] Keyboard Driver working (PS/2)
- [ ] Actual Game/Engine code running
- [ ] Game music and sound effects.

### Building

Build to a `.bin` file, with the directions below.

Then, Boot up Rufus or ImgBurn to burn to a boot medium.

Or, you can run it in a VM with QEMU.

###### Required software

- Qemu x86 emulator (If running in a VM)
- Rufus or ImgBurn  (If booting from PC)
- GCC and LD
- NASM

###### Building the code

Make 2 folders, `bin` and `obj`

On systems with BASH, use the build script provided in the repo.

`./build.sh`

It should build to a .bin file and load up QEMU by default

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
3. Keyboard is not attached to the computer at startup. Restart when attached.
