# 08_Linkers

This folder contains example linker scripts.

## Files

### `bootloader.ld`

Places bootloader at:

```text
0x08000000
```

### `app1.ld`

Places App1 at:

```text
0x08004000
```

### `app2.ld`

Places App2 at:

```text
0x0800A000
```

## Why Linker Scripts Matter

The linker decides where the compiled firmware will run in flash.

If App1 is linked for the wrong address, the bootloader jump may fail.
