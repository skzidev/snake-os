# Snake-OS

Inspired by Tetris-OS by JDH, (R.I.P), This is snake; but as an OS!

### Progress So far

- [x] Bootloader in 32-bit protected mode
- [x] C in the binary
- [x] C running in the OS
- [x] Graphics driver running
- [ ] Keyboard Driver Running (PS/2)
- [ ] Actual Game/Engine code running

I'm currently running in QEMU. We'll see if I can get this running on the real metal.
(Probably Not).

It works. The kernel is loaded, and the C code is running.

### Error Codes

There are a couple error messages that may show if the code fails to properly boot or play.
(Similar to below)

```
Err {number}
```

	1. Failed to load kernel into memory. Most likely a compilation (or flashing if on real hardware) issue
	2. Drive in an unreadable status (see [Disk Status](https://stanislavs.org/helppc/int_13-1.html))
	
