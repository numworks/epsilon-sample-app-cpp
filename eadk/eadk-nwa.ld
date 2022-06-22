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
    KEEP (*(.init_array*))
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

ASSERT(SIZEOF(.init_array) == 0, "Some C++ global variables require a static object constructor. They should be removed (using singleton) because the NumWorks app uploader doest not expect an init_array section. Moreover, in practice, static initialized objects are often a terrible idea: since the init order is not specified, most often than not this yields the dreaded static init order fiasco.")
