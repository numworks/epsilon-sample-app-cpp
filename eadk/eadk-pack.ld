ENTRY(_eadk_start)

SECTIONS {
  .text : {
    KEEP(*(.text._eadk_start))
    *(.text)
    *(.text.*)
  }

  .rodata : {
    KEEP(*(*.eadk_app_api_level));
    KEEP(*(*.eadk_app_name));
    _eadk_app_icon_start = .;
    KEEP(*(*.eadk_app_icon));
    _eadk_app_icon_end = .;
    *(.rodata)
    *(.rodata.*)
  }

  .init_array : {
    _init_array_start = .;
    KEEP (*(.init_array*))
    _init_array_end = .;
  }

  .data : {
    *(.data)
    *(.data.*)
  }

  .bss : {
    *(.bss)
    *(.bss.*)
  }

  /DISCARD/ : {
    *(.ARM.exidx .ARM.exidx.*);
  }
}
