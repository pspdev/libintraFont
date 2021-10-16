# G-spec
- added rotation support. The angle is specified by a new argument to intraFontSetStyle,  (float value in degrees). The performance hit is up to 40% when angle is not equal to 0,  because there is 6 vertices per char instead of 2. Rotation center specified by x and y.
- - very little cleanup of the code, converted tabulation to 2 spaces, for a better readability

# 0.31
- added option to set alternative font, which is used for characters that are not present in the current    font (e.g. if you want to print chars from two or more fonts in the same string)
- added support for unpacking LZR streams in libccc:
   * libccc is able to unpack and load the firmwares own codepage conversion tables, thus its tables are no      longer needed (saves around 140kB of size/memory, -DLIBCCC_NO_CPxxx is now obsolete)
   * the routines for decoding and (limited) encoding of LZR streams are also seperately released: libLZR is     available for download from http://www.psp-programming.com/benhur
- bug fixed where intraFontMeasureTextUCS2() could return a wrong value (bug introduced in version 0.30)

# 0.30
- added support for Chinese (gb3s1518.bwfon): now all of the PSPs internal fonts are supported! (thanks to        Tong for his help)
- added libccc (my Character Code Conversion library) for string parsing/conversion:
  * it currrently supports decoding of UTF-8 and the following codepages: 
    CP437 (US), CP850 (Multilingual Latin I), CP866 (Russian), CP932 (Japanese Shift-JIS), 
    CP936 (Simplified Chinese GBK), CP949 (Korean), CP950 (Traditional Chinese Big5), 
    CP1251 (Cyrillic) and CP1252 (Latin I)
  * it's required by intraFont 0.30+ (simply add libccc.o to the OBJS list in your makefile)
  * if you don't need any codepages: add -DLIBCCC_NO_CP to the CFLAGS in your makefile, which 
    saves around 140kB of size/memory.
  * finally, it can be used independantly from intraFont for your own character conversion needs

# 0.26
- bug fixed where text could be mis-aligned after newline character (thanks to Slasher)
- bug fixed in multi-byte string parsing (thanks to xart)
- in scrolling text newline characters are replaced by spaces (to prevent graphical glitches)

# 0.25 
- added text scrolling in intraFontPrintColumn() (flags INTRAFONT_SCROLL_LEFT/RIGHT/SEESAW/THROUGH)

# 0.24
- added column printing with automatic linebreaks - no need to worry about overwriting parts of the screen    or printing outside the screen anymore (use intraFontPrintColumn()) 
- added full justification (flush left&right) for column printing (flag INTRAFONT_ALIGN_FULL)
- various optimizations related to UCS2 conversion (thanks to StrmnNrmn)
- added functions to print/measure the first n chars of a string (intraFontPrintEx() and other ...Ex()    functions; thanks to StrmnNrmn)
- bug fixed where intraFontMeasureText() could return a wrong value because multi-byte strings (S-JIS and    UTF-8) and codepages were not yet properly handled

# 0.23
- added support for UTF-8 string parsing: use flag INTRAFONT_STRING_UTF8 in intraFontLoad() (thanks to 
  NexTOS)
- added support for codepages (conversion of extended ascii to unicode depending on source): use flag   INTRAFONT_STRING_CP??? in intraFontLoad(), where ??? is 437, 850 or 1252 (let me know if you need other   codepages; default conversion uses ISO-8859-1)
- encoding type of text string (ASCII, UTF-8, S-JIS or codepages) can also be set with intraFontSetEncoding

# 0.22
- added support for S-JIS string parsing: use flag INTRAFONT_STRING_SJIS in intraFontLoad() (thanks to     psp-kaihatu-yotien - http://psp.nukenin.jp/ http://ameblo.jp/pspdevblog/ )
- added pre-caching for ASCII characters: use flag INTRAFONT_CACHE_ASCII in intraFontLoad()
- added support for extended ASCII in text strings (e.g. "\251" for the (c) copyright symbol)

# 0.21
- no new features, bugfix version only
- bug fixed which could cause graphical glitches (thanks to StrmnNrmn)
- bug fixed where intraFontMeasureText() could return a wrong value (thanks to StrmnNrmn)

# 0.2 
- added support for Korean (kr0.pgf) and symbols (arib.pgf)
- added cache options (cache size and pre-cache all)
- added right and center alignments
- improved fixed width appearance (width can be set by user or left as default)
- fixed various bugs (mostly in glyph cache to prevent graphical glitches)
- reduced memory required (variable-size texture, free unneeded stuff)
- improved speed (optimizations, texture swizzling)

# 0.1 
- initial release