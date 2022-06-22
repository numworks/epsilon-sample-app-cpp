ENTRY(_eadk_start)

SECTIONS {
  .text : {
    KEEP(*(.text._eadk_start))
    *(.text)
    *(.text.*)
  }

  .rodata.eadk_app_api_level : {
    KEEP(*(*.eadk_app_api_level));
  }

  .rodata.eadk_app_name : {
    KEEP(*(*.eadk_app_name));
  }

  .rodata.eadk_app_icon : {
    KEEP(*(*.eadk_app_icon));
  }

  .rodata : {
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
