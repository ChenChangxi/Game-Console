/* STM32H743 ───────────────────────── Cortex-M7 480 MHz ───────────────────────── */
ENTRY(Reset_Handler)

/* -------------------------- Flash / RAM 布局 -------------------------- */
MEMORY
{
  FLASH   (rx)  : ORIGIN = 0x08000000, LENGTH = 2048K   /* 主 Flash 2 MB */
  DTCM    (rwx) : ORIGIN = 0x20000000, LENGTH = 128K    /* DTCM */
  RAM_D1  (rwx) : ORIGIN = 0x24000000, LENGTH = 512K    /* D1 域 RAM */
  SDRAM   (rwx) : ORIGIN = 0xC0000000, LENGTH = 32M     /* SDRAM */
}

/* -------------------------- 常量区 -------------------------- */
_estack         = ORIGIN(DTCM) + LENGTH(DTCM);    /* 栈顶地址 */
_Min_Heap_Size  = 0x00002000;    /* 8  KB 堆 */
_Min_Stack_Size = 0x00010000;    /* 64 KB 栈 */

/* -------------------------- 段定义 -------------------------- */
SECTIONS
{
  /* -------------------------- 1. 代码 / 只读数据 -------------------------- */
  .text:
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
    _sdata = .;                                  /* RAM_D1 起始 */
    *(.data*)
    . = ALIGN(4);
    _edata = .;                                  /* RAM_D1 结束 */
  } > RAM_D1

  /* -------------------------- 3. 未初始化的全局变量 (.bss) -------------------------- */
  .bss (NOLOAD):
  {
    _sbss = .;
    *(.bss*) *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM_D1

  /* -------------------------- 4. 用户堆空间 -------------------------- */
  .heap (NOLOAD):
  {
    . = ALIGN(8);
    _sheap = .;               /* 堆起始地址 */
    . += _Min_Heap_Size;
    . = ALIGN(8);
    _eheap = .;               /* 堆结束地址 */
  } > RAM_D1

  PROVIDE(_end = _sheap);     /* 头文件符号 */
  PROVIDE(end  = _sheap);

  /* -------------------------- 5. 用户栈空间 -------------------------- */
  .stack (NOLOAD):
  {
    . = ALIGN(8);
    . += _Min_Stack_Size;
    _estack = .;              /* 栈起始地址 */
  } > DTCM

  /* -------------------------- 6. SDRAM -------------------------- */
  .sdram (NOLOAD):
  {
    *(.sdram)
  } > SDRAM
}
