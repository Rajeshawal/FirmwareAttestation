MEMORY
{
  FLASH (rx) : ORIGIN = 0x0800A000, LENGTH = 20K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

/* App2 is update staging slot. */
