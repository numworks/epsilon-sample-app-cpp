#include "main.h"
#include "stdint.h"
#include "string.h"

extern char _data_section_start_flash;
extern char _data_section_start_ram;
extern char _data_section_end_ram;
extern char _bss_section_start_ram;
extern char _bss_section_end_ram;
extern char _init_array_start;
extern char _init_array_end;

extern "C" void _eadk_start();

typedef void (*cxx_constructor)();

void _eadk_start() {
  /* Copy data section to RAM
   * The data section is R/W but its initialization value matters. It's stored
   * in Flash, but linked as if it were in RAM. Now's our opportunity to copy
   * it. Note that until then the data section (e.g. global variables) contains
   * garbage values and should not be used. */
  size_t dataSectionLength = (&_data_section_end_ram - &_data_section_start_ram);
  memcpy(&_data_section_start_ram, &_data_section_start_flash, dataSectionLength);

  /* Zero-out the bss section in RAM
   * Until we do, any uninitialized global variable will be unusable. */
  size_t bssSectionLength = (&_bss_section_end_ram - &_bss_section_start_ram);
  memset(&_bss_section_start_ram, 0, bssSectionLength);

  /* Call static C++ object constructors
   * The C++ compiler creates an initialization function for each static object.
   * The linker then stores the address of each of those functions consecutively
   * between _init_array_start and _init_array_end. So to initialize all C++
   * static objects we just have to iterate between theses two addresses and
   * call the pointed function. */
#define SUPPORT_CPP_GLOBAL_CONSTRUCTORS 1
#if SUPPORT_CPP_GLOBAL_CONSTRUCTORS
  for (cxx_constructor * c = (cxx_constructor *)&_init_array_start; c < (cxx_constructor *)&_init_array_end; c++) {
    (*c)();
  }
#else
  /* In practice, static initialized objects are a terrible idea. Since the init
   * order is not specified, most often than not this yields the dreaded static
   * init order fiasco. How about bypassing the issue altogether? */
  if (&_init_array_start != &_init_array_end) {
    return;
  }
#endif
  // Jump to main
  eadk_main();
}

