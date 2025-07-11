# ────────────────  可按需修改的参数  ────────────────
TOOLCHAIN ?= arm-none-eabi
CPU       := -mcpu=cortex-m4 -mthumb -mfpu=fpv4-sp-d16 -mfloat-abi=hard
OPT       := -Og
# ---------------------------------------------------

CC      := $(TOOLCHAIN)-gcc
AS      := $(TOOLCHAIN)-gcc
LD      := $(TOOLCHAIN)-gcc
OBJCOPY := $(TOOLCHAIN)-objcopy
SIZE    := $(TOOLCHAIN)-size

PROJECT := game_console
BUILD   := build
ELF     := $(BUILD)/$(PROJECT).elf
HEX     := $(BUILD)/$(PROJECT).hex
BIN     := $(BUILD)/$(PROJECT).bin

# 递归搜所有 .c / .s
SRC_C   := $(shell find Core Drivers -name "*.c")
SRC_S   := $(shell find Startup -name "*.s")

OBJ_C   := $(addprefix $(BUILD)/,$(SRC_C:.c=.o))
OBJ_S   := $(addprefix $(BUILD)/,$(SRC_S:.s=.o))
OBJS    := $(OBJ_C) $(OBJ_S)

# 头文件搜索路径
INCLUDES = \
  -ICore \
  -IDrivers/CMSIS/Include \
  -IDrivers/CMSIS/Device/ST/STM32F4xx/Include \
  -IDrivers/STM32F4xx_HAL_Driver/Inc \
  -IDrivers/SYSTEM \
  -IDrivers/BSP \
  -IHardware

# 编译、汇编、链接选项
CFLAGS  = $(CPU) $(OPT) -Wall -ffunction-sections -fdata-sections $(INCLUDES)
ASFLAGS = $(CPU) -x assembler-with-cpp
LDFLAGS = -TLinker/STM32F407.ld -Wl,--gc-sections -Wl,-Map=$(BUILD)/$(PROJECT).map $(CPU)

# ────────────────   目标  ────────────────
.PHONY: all clean size

all: $(ELF) $(HEX) $(BIN) size

# 生成目录并编译 C
$(BUILD)/%.o: %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# 生成目录并编译汇编
$(BUILD)/%.o: %.s
	@mkdir -p $(dir $@)
	$(AS) $(ASFLAGS) -c $< -o $@

# 链接
$(ELF): $(OBJS) Linker/STM32F407.ld
	@mkdir -p $(dir $@)
	$(LD) $(OBJS) -o $@ $(LDFLAGS)

# 生成 hex / bin
$(HEX): $(ELF)
	$(OBJCOPY) -O ihex $< $@

$(BIN): $(ELF)
	$(OBJCOPY) -O binary $< $@

size:
	$(SIZE) $(ELF)

clean:
	rm -rf $(BUILD)
