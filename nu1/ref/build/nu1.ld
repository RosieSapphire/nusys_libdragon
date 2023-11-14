OUTPUT_ARCH (mips)
SECTIONS
{
   __romPos = 0;
   _bootSegmentStart = ADDR(.boot); _bootSegmentRomStart = __romPos; .boot 0x04000000 : AT(__romPos)
   {
      build/asm/rom_header.o(.text);
      build/boot.6102.o(.data);
   }
   _bootSegmentEnd = ALIGN(ADDR(.boot) + SIZEOF(.boot),0x10); _bootSegmentRomEnd = _bootSegmentEnd - _bootSegmentStart + _bootSegmentRomStart; __romPos = _bootSegmentRomEnd; . = _bootSegmentEnd;
   _codeSegmentStart = ADDR(.code); _codeSegmentRomStart = __romPos; .code 0x80025c00 : AT(__romPos) SUBALIGN(16)
   {
  build/asm/entry.o(.start);
      /usr/lib/n64/nusys/nusys_isv.o(.text);
      build/src/main*.o(.text);
      */libultra_d.a:*.o(.text);
      */libnusys_d.a:*.o(.text);
      */libgcc.a:*.o(.text);
      /usr/lib/n64/PR/rspboot.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.text);
      /usr/lib/n64/PR/gspL3DEX2.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.Rej.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DEX2.NoN.fifo.o(.text);
      /usr/lib/n64/PR/gspF3DLX2.Rej.fifo.o(.text);
      /usr/lib/n64/PR/gspS2DEX2.fifo.o(.text);
      /usr/lib/n64/nusys/nusys_isv.o(.data*);
      build/src/main*.o(.data*);
      */libultra_d.a:*.o(.data*);
      */libnusys_d.a:*.o(.data*);
      /usr/lib/n64/PR/rspboot.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.fifo.o(.data*);
      /usr/lib/n64/PR/gspL3DEX2.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.Rej.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DEX2.NoN.fifo.o(.data*);
      /usr/lib/n64/PR/gspF3DLX2.Rej.fifo.o(.data*);
      /usr/lib/n64/PR/gspS2DEX2.fifo.o(.data*);
      /usr/lib/n64/nusys/nusys_isv.o(.*rodata*);
      build/src/main*.o(.*rodata*);
      */libultra_d.a:*.o(.*rodata*);
      */libnusys_d.a:*.o(.*rodata*);
      */libgcc.a:*.o(.*rodata*);
   }
   _codeSegmentEnd = ALIGN(ADDR(.code) + SIZEOF(.code),0x10); _codeSegmentRomEnd = _codeSegmentEnd - _codeSegmentStart + _codeSegmentRomStart; __romPos = _codeSegmentRomEnd; . = _codeSegmentEnd;
   _codeSegmentBssStart = ADDR(.code.noload); .code.noload (NOLOAD) :
   {
      /usr/lib/n64/nusys/nusys_isv.o(COMMON);
      /usr/lib/n64/nusys/nusys_isv.o(.scommon);
      /usr/lib/n64/nusys/nusys_isv.o(.*bss*);
      build/src/main*.o(.*bss*);
      */libultra_d.a:*.o(COMMON);
      */libultra_d.a:*.o(.scommon);
      */libultra_d.a:*.o(.*bss*);
      */libnusys_d.a:*.o(COMMON);
      */libnusys_d.a:*.o(.scommon);
      */libnusys_d.a:*.o(.*bss*);
   }
   _codeSegmentBssEnd = ALIGN(ADDR(.code.noload) + SIZEOF(.code.noload),0x10); _codeSegmentBssSize = _codeSegmentBssEnd - _codeSegmentBssStart; . = _codeSegmentBssEnd;
   /DISCARD/ :
   {
      *(*);
   }
}
