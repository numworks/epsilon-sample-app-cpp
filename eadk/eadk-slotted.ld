INCLUDE "target/device_information.ld";

MEMORY {
  /* The maximal size of the external app depends on how many apps you already
   * stored. */
  FLASH (rx) : ORIGIN = EXTERNAL_APPS_FLASH_START, LENGTH = EXTERNAL_APPS_FLASH_END - EXTERNAL_APPS_FLASH_START
  RAM (rwx) : ORIGIN = EXTERNAL_APPS_RAM_START, LENGTH = EXTERNAL_APPS_RAM_END - EXTERNAL_APPS_RAM_START
}

SECTIONS {
  .eadk_app_info ORIGIN(FLASH) : {
    LONG(0xDEC0BEBA);
    *(.rodata.eadk_app_api_level)
    LONG(eadk_app_name - ORIGIN(FLASH)); /* This symbol must be defined and point to a NULL-terminated UTF-8 string */
    LONG(SIZEOF(.rodata.eadk_app_icon));
    LONG(ADDR(.rodata.eadk_app_icon) - ORIGIN(FLASH));
    LONG(_eadk_start - ORIGIN(FLASH));
    LONG(_eadk_app_end - ORIGIN(FLASH));
    LONG(0xDEC0BEBA);
  } >FLASH

  .text : {
    *(.text)
  } >FLASH

  .rodata : {
    . = ALIGN(4);
    *(.rodata)
    _eadk_app_end = .;
    ASSERT (SIZEOF(.init_array) == 0, "Error: init_array non-empty");
  } >FLASH

  .data : {
    . = ALIGN(4);
    _data_section_start_flash = LOADADDR(.data);
    _data_section_start_ram = .;
    *(.data)
    _data_section_end_ram = .;
  } >RAM AT >FLASH

  .bss : {
    . = ALIGN(4);
    _bss_section_start_ram = .;
    *(.bss)
    _bss_section_end_ram = .;
  } >RAM

  .heap : {
    _heap_start = .;
    . = (ORIGIN(RAM) + LENGTH(RAM));
    _heap_end = .;
  } >RAM
}
