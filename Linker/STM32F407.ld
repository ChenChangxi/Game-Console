/* STM32F407VG/ZE/ZG ───────────── Cortex-M4 168 MHz ───────────────────────── */
ENTRY(Reset_Handler)

/* —————————————————————————— Flash / RAM 布局 —————————————————————————— */
MEMORY
{
  FLASH (rx)  : ORIGIN = 0x08000000, LENGTH = 1024K   /* 主 Flash 1 MB */
  RAM   (rwx) : ORIGIN = 0x20000000, LENGTH = 192K    /* SRAM1+SRAM2 */
}

/* 堆栈顶地址（启动文件用）*/
_estack = ORIGIN(RAM) + LENGTH(RAM);

/* —————————————————————————— 段定义 —————————————————————————— */
SECTIONS
{
  /* —————————————————————————— 1. 代码 / 只读数据 —————————————————————————— */
  .text :
  {
    KEEP(*(.isr_vector))                          /* 中断向量表 */
    *(.text*) *(.rodata*) *(.glue_7) *(.glue_7t)
    KEEP(*(.init)) KEEP(*(.fini))
    *(.ARM.exidx*)                                /* 异常索引表并入 */
  } > FLASH

  /* —————————————————————————— 2. 已初始化的全局变量 (.data) —————————————————————————— */
  _sidata = LOADADDR(.data);                      /* Flash 中源地址 */

  .data : AT ( _sidata )
  {
    _sdata = .;                                  /* RAM 起始 */
    *(.data*)
    . = ALIGN(4);
    _edata = .;                                  /* RAM 结束 */
  } > RAM

  /* —————————————————————————— 3. 未初始化的全局变量 (.bss) —————————————————————————— */
  .bss (NOLOAD) :
  {
    _sbss = .;
    *(.bss*) *(COMMON)
    . = ALIGN(4);
    _ebss = .;
  } > RAM

  /* 提供给启动文件 / HAL 的符号 —— Flash 端 .text 结束地址 */
  _etext = LOADADDR(.data);
}
