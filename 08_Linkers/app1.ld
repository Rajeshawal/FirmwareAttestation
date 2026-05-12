MEMORY
{
  FLASH (rx) : ORIGIN = 0x08004000, LENGTH = 24K
  RAM (rwx)  : ORIGIN = 0x20000000, LENGTH = 20K
}

/* Application vector table must be placed after metadata if metadata is stored first. */
