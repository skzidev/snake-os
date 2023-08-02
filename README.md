# Snake-OS

Inspired by Tetris-OS by JDH, (R.I.P), This is snake; but as an OS!

### Progress So far

- [x] Bootloader in 32-bit protected mode
- [x] C in the binary
- [x] C running in the OS
- [ ] Game code running
- [ ] Graphics lib working

I'm currently running in QEMU. We'll see if I can get this running on the real metal.
(Probably Not).

The Bootloader is no longer flashing, however, the kernel is not booting just yet. I presume I have the wrong entrypoint.
I believed it should be 0x200 because that's what the hex editor was telling me the number was, but maybe I was wrong.


### Error Codes

There are a couple error messages that may show if the code fails to properly boot or play.
(Similar to below)

```
Err {number}
```

	1. Failed to load kernel into memory.
	2. Drive in an unreadable status (see [Disk Status](https://stanislavs.org/helppc/int_13-1.html))
	
