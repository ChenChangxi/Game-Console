/* STM32F407VG/ZE/ZG ───────────── Cortex-M4 168 MHz ───────────────────────── */
ENTRY(Reset_Handler)

/* -------------------------- Flash / RAM 布局 -------------------------- */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K   /* 主 Flash 1 MB */
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 192K    /* SRAM1+SRAM2 */
}

/* -------------------------- 常量区 -------------------------- */
_estack         = ORIGIN(RAM) + LENGTH(RAM);    /* 栈顶地址 */
_Min_Heap_Size  = 0x00001400;    /* 5  KB 堆 */
_Min_Stack_Size = 0x00005000;    /* 20 KB 栈 */

/* -------------------------- 段定义 -------------------------- */
SECTIONS
{
  /* -------------------------- 1. 代码 / 只读数据 -------------------------- */
  .text :
  {
    KEEP(*(.isr_vector))                          /* 中断向量表 */
    *(.text*) *(.rodata*) *(.glue_7) *(.glue_7t)
    KEEP(*(.init)) KEEP(*(.fini))
    *(.ARM.exidx*)                                /* 异常索引表并入 */
    _etext = .;
  } > FLASH

  /* -------------------------- 2. 已初始化的全局变量 (.data) -------------------------- */
  _sidata = _etext;                      /* Flash 中源地址 */

  .data : AT ( _sidata )
  {
    _sdata = .;                                  /* RAM 起始 */
    *(.data*)
    . = ALIGN(4);
    _edata = .;                                  /* RAM 结束 */
  } > RAM

  /* -------------------------- 3. 未初始化的全局变量 (.bss) -------------------------- */
  .bss (NOLOAD) :
  {
    _sbss = .;
    *(.bss*) *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  /* -------------------------- 4. 用户堆空间 -------------------------- */
  .heap (NOLOAD):
  {
    . = ALIGN(8);
    _sheap = .;               /* 堆起始地址 */
    . += _Min_Heap_Size;
    . = ALIGN(8);
    _eheap = .;               /* 堆结束地址 */
  } > RAM

  /* -------------------------- 5. 用户栈空间 -------------------------- */
  ._user_stack (NOLOAD):
  {
    . = ALIGN(8);
    . += _Min_Stack_Size;
    _estack = .;              /* 栈起始地址 */
  } > RAM
}
